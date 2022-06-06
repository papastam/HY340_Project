#include "alphavm.h"
#include "execute_functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

#define IOP_BIN_SIZE 13U

struct __read_bfile {

    uint8_t op;

    uint32_t res;
    uint32_t arg1;
    uint32_t arg2;
};

typedef struct {

    uint size;
    char ** array;

} __string_array_t;

typedef struct {

    uint size;
    double * array;

} __const_array_t;

typedef struct {

    uint size;
    struct userfunc * array;

} __userfunc_array_t;

typedef __string_array_t __libfunc_array_t;


__string_array_t sarr;
__const_array_t  carr;

__userfunc_array_t ufarr;
__libfunc_array_t  lfarr;

struct vminstr * iarr;

unsigned char   execution_finished = 0;
unsigned        pc = 0;
unsigned        currLine = 0;
unsigned        codeSize = 0;
struct vminstr* code = (struct vminstr*) 0;
#define AVM_ENDING_PC codeSize

#define AVM_STACKENV_SIZE 4


int main(int argc, char ** argv)
{
    if ( argc != 2 )
    {
        printf("usage: acomp <binfile>\n");
        exit(EXIT_FAILURE);
    }

    if ( vm_parse_bin_file(argv[1]) < 0 )
    {
        // perror("error");
        exit(EXIT_FAILURE);
    }


    return EXIT_SUCCESS;
}

char * __avm_strdup(const char * str, uint * retsz)
{
    const char * p;
    char * nstr;

    for (p = str; *p; ++p);

    *retsz = p - str + 1U;
    nstr = malloc(*retsz);

    memcpy(nstr, str, *retsz);

    return nstr;
}

int vm_parse_bin_file(const char * filename)
{
    int fd;

    if ( (fd = open(filename, O_RDONLY)) < 0 )
    {
        perror("open()");
        return -(EXIT_FAILURE);
    }

    struct stat sb;

    if ( fstat(fd, &sb) < 0 )
    {
        perror("fstat()");
        close(fd);

        return -(EXIT_FAILURE);
    }

    uint8_t * bfile;

    if ( (bfile = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE | MAP_POPULATE, fd, 0UL)) == MAP_FAILED )
    {
        perror("mmap()");
        close(fd);

        return -(EXIT_FAILURE);
    }

    /** check if the file is in alpha binary format **/

    if ( *((uint32_t *)(bfile)) != ALPHA_MAGICNUM )
    {
        munmap(bfile, sb.st_size);
        close(fd);

        return -(EXIT_FAILURE);
    }

    bfile += 4UL;

    uint s;
    uint l;
    uint i;

    /** strings array **/

    sarr.size = *((uint32_t *)(bfile));
    bfile += 4UL;

    if ( !(sarr.array = malloc(sarr.size * sizeof( *sarr.array ))) )
    {
        perror("malloc()");

        munmap(bfile, sb.st_size);
        close(fd);

        return -(EXIT_FAILURE);
    }

    for (i = 0U, l = sarr.size; i < l; ++i, bfile += s)
        sarr.array[i] = __avm_strdup((char *)(bfile), &s);  // stupid warnings...

    /** const numbers array **/

    carr.size = *((uint32_t *)(bfile));
    bfile += 4UL;

    if ( !(carr.array = malloc(carr.size * sizeof( *carr.array ))) )
    {
        perror("malloc()");

        munmap(bfile, sb.st_size);
        free(sarr.array);  /** TODO: free() strings */
        close(fd);

        return -(EXIT_FAILURE);
    }

    for (i = 0U, l = carr.size; i < l; ++i, bfile += sizeof( *carr.array ))
        carr.array[i] = *((double *)(bfile));

    /** struct userfunc array **/

    ufarr.size = *((uint32_t *)(bfile));
    bfile += 4UL;

    if ( !(carr.array = malloc(carr.size * sizeof( *carr.array ))) )
    {
        perror("malloc()");

        munmap(bfile, sb.st_size);
        free(carr.array);
        free(sarr.array);  /** TODO: free() strings */
        close(fd);

        return -(EXIT_FAILURE);
    }

    for (i = 0U, l = ufarr.size; i < l; ++i)
    {
        ufarr.array[i].address = *((uint32_t *)(bfile));
        bfile += 4UL;

        ufarr.array[i].localSize = *((uint32_t *)(bfile));
        bfile += 4UL;

        ufarr.array[i].id = __avm_strdup((char *)(bfile), &s);
        bfile += s;
    }

    /** libfucns (strings) array **/

    lfarr.size = *((uint32_t *)(bfile));
    bfile += 4UL;

    if ( !(lfarr.array = malloc(lfarr.size * sizeof( *lfarr.array ))) )
    {
        perror("malloc()");

        munmap(bfile, sb.st_size);
        free(ufarr.array);
        free(carr.array);
        free(sarr.array);  /** TODO: free() strings */
        close(fd);

        return -(EXIT_FAILURE);
    }

    for (i = 0U, l = lfarr.size; i < l; ++i, bfile += s)
        lfarr.array[i] = __avm_strdup((char *)(bfile), &s);

    /** code **/

    s = *((uint32_t *)(bfile));  // total opcodes
    bfile += 4UL;

    if ( !(iarr = malloc(s * sizeof( *iarr ))) )
    {
        perror("malloc()");

        munmap(bfile, sb.st_size);
        free(lfarr.array);
        free(ufarr.array);
        free(carr.array);
        free(sarr.array);  /** TODO: free() strings */
        close(fd);

        return -(EXIT_FAILURE);
    }

    uint t;
    struct vmarg ** tarr;

    for (i = 0U; i < s; ++i)
    {
        iarr[i].opcode = *((uint8_t *)(bfile));
        ++bfile;

        for (tarr = &iarr[i].result, t = 0U; t < 3U; ++t)
        {
            l = *((uint32_t *)(bfile));

            if ( l != VM_ARG_NULL )
            {
                tarr[t] = malloc(sizeof( *iarr[i].result ));
                tarr[t]->type = l >> 28;
                tarr[t]->val  = l & 0x0fffffff;
            }
            else
                (*tarr) = NULL;

            bfile += 4UL;
        }
    }


    return EXIT_SUCCESS;
}


void execute_cycle(void){
    if(execution_finished){
        return;
    }else{
        if(pc == AVM_ENDING_PC){
            execution_finished=1;
            return;
        }else{
            assert( pc < AVM_ENDING_PC);
            struct vminstr* instr = code + pc;
            assert(
                instr->opcode >= 0 
                && instr->opcode <= AVM_MAX_INSTRUCTIONS
            );
            if(instr->srcLine){
                currLine = instr->srcLine;
            }
            unsigned oldPC = pc;
            (*executeFuncs[instr->opcode])(instr);
            if(pc == oldPC){
                ++pc;
            }
        }
    }
}