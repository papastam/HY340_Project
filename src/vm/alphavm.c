#include "alphavm.h"
#include "exec.h"
#include "mman.h"
#include "debug_functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>

#define IOP_BIN_SIZE 13U

__string_array_t sarr;
__const_array_t  carr;

__userfunc_array_t ufarr;
__libfunc_array_t  lfarr;

uint execution_finished;
uint pc=1;
uint currLine;
uint codeSize;

struct vminstr * code;
#define AVM_ENDING_PC codeSize

struct avm_memcell ax, bx, cx;
struct avm_memcell retval;

uint top;
uint topsp;


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

    print_readable_instructions();

    int ret;
    while( (ret = avm_execute_cycle()) );

    return ret;
}

static char * __avm_strdup(const char * str, uint * retsz)
{
    const char * p;
    char * nstr;

    for (p = str; *p; ++p);

    *retsz = p - str + 1U;
    nstr = malloc(*retsz);

    memcpy(nstr, str, *retsz);

    return nstr;
}

/****************************************************************/

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

    if ( sarr.size )
    {
        if ( (sarr.array = mmap(NULL, sarr.size * sizeof( *sarr.array ), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0UL)) == MAP_FAILED )
        {
            perror("mmap()");

            munmap(bfile, sb.st_size);
            close(fd);

            return -(EXIT_FAILURE);
        }

        for (i = 0U, l = sarr.size; i < l; ++i, bfile += s)
            sarr.array[i] = __avm_strdup((char *)(bfile), &s);  // stupid warnings...

        mprotect(sarr.array, sarr.size * sizeof( *sarr.array ), PROT_READ);
    }

    /** const numbers array **/

    carr.size = *((uint32_t *)(bfile));
    bfile += 4UL;

    if ( carr.size )
    {
        if ( (carr.array = mmap(NULL, carr.size * sizeof( *carr.array ), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0UL)) == MAP_FAILED )
        {
            perror("mmap()");

            munmap(bfile, sb.st_size);
            munmap(sarr.array, sarr.size);  /** TODO: free() strings */
            close(fd);

            return -(EXIT_FAILURE);
        }

        for (i = 0U, l = carr.size; i < l; ++i, bfile += sizeof( *carr.array ))
            carr.array[i] = *((double *)(bfile));

        mprotect(carr.array, carr.size * sizeof( *carr.array ), PROT_READ);
    }


    /** struct userfunc array **/

    ufarr.size = *((uint32_t *)(bfile));
    bfile += 4UL;

    if ( ufarr.size )
    {
        if ( (ufarr.array = mmap(NULL, ufarr.size * sizeof( *ufarr.array ), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0UL)) == MAP_FAILED )
        {
            perror("mmap()");

            munmap(bfile, sb.st_size);
            munmap(sarr.array, sarr.size);  /** TODO: free() strings */
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

        mprotect(ufarr.array, ufarr.size * sizeof( *ufarr.array ), PROT_READ);
    }

    /** libfucns (strings) array **/

    lfarr.size = *((uint32_t *)(bfile));
    bfile += 4UL;

    if ( lfarr.size ){
        if ( (lfarr.array = mmap(NULL, lfarr.size * sizeof( *lfarr.array ), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0UL)) == MAP_FAILED )
        {
            perror("mmap()");

            munmap(bfile, sb.st_size);
            munmap(carr.array, carr.size);
            munmap(sarr.array, sarr.size);  /** TODO: free() strings */
            close(fd);

            return -(EXIT_FAILURE);
        }

        for (i = 0U, l = lfarr.size; i < l; ++i, bfile += s)
            lfarr.array[i] = __avm_strdup((char *)(bfile), &s);

        mprotect(lfarr.array, lfarr.size * sizeof( *lfarr.array ), PROT_READ);
    }
    /** code **/

    s = *((uint32_t *)(bfile));  // total opcodes
    bfile += 4UL;

    if ( !s )
    {
        munmap(bfile, sb.st_size);
        munmap(lfarr.array, lfarr.size);  /** TODO: free() strings */
        munmap(ufarr.array, ufarr.size);
        munmap(carr.array, carr.size);
        munmap(sarr.array, sarr.size);    /** TODO: free() strings */

        fprintf(stderr, "binfile is empty!\n");

        return -(EXIT_FAILURE);
    }

    if ( (code = mmap(NULL, s * sizeof( *code ), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0UL)) == MAP_FAILED )
    {
        perror("mmap()");

        munmap(bfile, sb.st_size);
        munmap(lfarr.array, lfarr.size);  /** TODO: free() strings */
        munmap(ufarr.array, ufarr.size);
        munmap(carr.array, carr.size);
        munmap(sarr.array, sarr.size);    /** TODO: free() strings */
        close(fd);

        return -(EXIT_FAILURE);
    }

    uint t;
    struct vmarg ** tarr;

    for (i = 1U; i < s+1; ++i)
    {
        code[i].opcode = *((uint8_t *)(bfile));
        ++bfile;

        for (tarr = &code[i].result, t = 0U; t < 3U; ++t)
        {
            l = *((uint32_t *)(bfile));

            if ( l != VM_ARG_NULL )
            {
                tarr[t] = malloc(sizeof( *code[i].result ));
                tarr[t]->type = l >> 28;
                tarr[t]->val  = l & 0x0fffffff;
            }
            else
                tarr[t] = NULL;

            bfile += 4UL;
        }
    }
    
    codeSize = s;

    mprotect(code, s * sizeof( *code ), PROT_READ);


    return EXIT_SUCCESS;
}


int avm_execute_cycle(void){
    if(execution_finished)
        return EXIT_FAILURE;

    if(pc == AVM_ENDING_PC){
        execution_finished=1;
        return EXIT_FAILURE;
    }

    assert( pc < AVM_ENDING_PC);
    struct vminstr* instr = code + pc;
    assert(
        instr->opcode >= 0\
        && instr->opcode <= AVM_MAX_INSTRUCTIONS\
    );
    if(instr->srcLine){
        currLine = instr->srcLine;
    }
    unsigned oldPC = pc;
    (*executeFuncs[instr->opcode])(instr);
    if(pc == oldPC){
        ++pc;
    }
    return EXIT_SUCCESS;
}