#include "alphavm.h"
#include "exec.h"
#include "mman.h"
#include "debug_functions.h"
#include "vmutils.h"

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

/*   [ TESTFILES PHASE 5 (/tests/original_testfiles/phase5) ]:
 *   01_err_1.asc                                                   > WORKING
 *   02_err_2.asc                                                   > WORKING
 *   03_err_3.asc                                                   > WORKING
 *   04_err_4.asc                                                   > WORKING
 *   05_err_5.asc                                                   > WORKING
 *   06_err_6.asc                                                   > NOT WORKING (malloc does the memory dirty)
 *   07_relop_logic.asc                                             > WORKING
 *   08_arith.asc                                                   > WORKING
 *   09_if_else.asc                                                 > WORKING
 *   10_loop_simple.asc                                             > WORKING
 *   11_loop_advanced.asc                                           > WORKING
 *   12_loop_bubblesort_tables_calls.asc                            > NOT WORKING
 *   13_func_calls.asc                                              > NOT WORKING (assertion fail)
 *   14_tables1.asc                                                 > SEG
 *   15_tables2.asc                                                 > CORE DUMP (bison:978)
 *   16_libfuncs_bonus1.asc                                         > NOT WORKING (assertion fail) (recursive table_toString call error)
 *   17_libfuncs_bonus2_part2_tables_catch_self_reference_error.asc > SEG
 *   18_tables_bonus.asc                                            > SEG
 *   19_Circle.asc                                                  > WORKING
 *   20_delegation.asc                                              > NOT WORKING
 *   21_queens.asc                                                  > SEEMS TO BE WORKING
 *   22_hercules.asc                                                > SEG
 *   23_visitor.asc                                                 > NOT WORKING
 *   24_Tree1.asc                                                   > HALF WORKING -> SEG
 *   25_Tree2.asc                                                   > HALF WORKING -> SEG
 *   26_basic_complex.asc                                           > ALMOST WORKING -> CORE DUMPED
 *   27_basic_simple.asc                                            > WORKING
 *   28_calc.asc                                                    > WORKING
 *   29_funcs.asc                                                   > NOT WORKING (assertion fail)
 *   30_if_else.asc                                                 > WORKING
 *   31_line_point.asc                                              > WORKING
 *   32_Random.asc                                                  > WORKING (based on our rules)
 *   33_relational.asc                                              > WORKING
 *   34_ShadowedFunctions.asc                                       > NOT WORKING (assertion failed)
 *   35_tables1.asc                                                 > NOT WORKING (runtime error)
 *   36_tables1.asc                                                 > SEG
 * 
 */ 

#define IOP_BIN_SIZE 13U

__string_array_t sarr;
__const_array_t  carr;

__userfunc_array_t ufarr;
__libfunc_array_t  lfarr;

uint execution_finished;
uint total_globals;
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
        printf("usage: avm <binfile>\n");
        exit(EXIT_FAILURE);
    }

    if ( vm_parse_bin_file(argv[1]) < 0 )
    {
        // perror("error");
        exit(EXIT_FAILURE);
    }

    print_readable_instructions();

    if(compare_code_files()){return EXIT_FAILURE;}

    init_stack();

    if(AVMDEBUG){printf("AVM Debug is active. To turn this off redefine AVMDEBUG to 0 in src/vm/alphavm.h:17\n\n");}
    int ret=0;
    while(ret != -1){
        ret = avm_execute_cycle();
    }

    return EXIT_SUCCESS;
}

void init_stack(void){
    /* for(uint i=0U;i<AVM_STACKSIZE;++i){
        AVM_WIPEOUT(stack[i]);
        stack[i].type=undef_m;
    } */

    bzero(stack, AVM_STACKSIZE * sizeof(stack[0]));

    topsp = AVM_STACKSIZE - 1U;
    top   = AVM_STACKSIZE - 1U -total_globals;
}

int compare_code_files(void){
    FILE *file1 = fopen("output_comparison/parser_generated.txt", "r");
    FILE *file2 = fopen("output_comparison/vm_parsed.txt", "r");
    if (file1 == NULL || file2 == NULL){
        printf("Error : Check files not open");
        exit(0);
    }
    
    char ch1 = getc(file1);
    char ch2 = getc(file2);
    while (ch1 != EOF && ch2 != EOF){
        if (ch1 != ch2){
            avm_error(0,"Parser generated file and vm parsed file does not match!\nExiting...\n");
            return EXIT_FAILURE;
        }
        ch1 = getc(file1);
        ch2 = getc(file2);
    }

    // printf("Parser generated file and vm parsed file match!\n");

    fclose(file1);
    fclose(file2);
    return EXIT_SUCCESS;
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

    total_globals = *((uint32_t *)(bfile));

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

            ufarr.array[i].totalFormals = *((uint32_t *)(bfile));
            bfile += 4UL;

            ufarr.array[i].id = __avm_strdup((char *)(bfile), &s);
            bfile += s;
        }

        mprotect(ufarr.array, ufarr.size * sizeof( *ufarr.array ), PROT_READ);
    }

    /** libfucns (strings) array **/

    lfarr.size = *((uint32_t *)(bfile));
    bfile += 4UL;

    if ( lfarr.size )
    {
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

    codeSize = *((uint32_t *)(bfile)) ;  // total instructions
    bfile += 4UL;

    if ( !codeSize )
    {
        munmap(bfile, sb.st_size);
        munmap(lfarr.array, lfarr.size);  /** TODO: free() strings */
        munmap(ufarr.array, ufarr.size);
        munmap(carr.array, carr.size);
        munmap(sarr.array, sarr.size);    /** TODO: free() strings */

        fprintf(stderr, "binfile is empty!\n");

        return -(EXIT_FAILURE);
    }

    if ( (code = mmap(NULL, codeSize * sizeof( *code ), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0UL)) == MAP_FAILED )
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

    for (i = 1U; i < codeSize; ++i)
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

        code[i].srcLine = *((uint32_t *)(bfile));
        bfile += 4UL;
    }

    mprotect(code, codeSize * sizeof( *code ), PROT_READ);


    return EXIT_SUCCESS;
}


int avm_execute_cycle(void){
    if(execution_finished)
        return -(EXIT_FAILURE);

    if(pc == AVM_ENDING_PC){
        execution_finished=1;
        return -(EXIT_FAILURE);
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
    avm_debug("Executing operation [%14s] pc=%d",op_toString[instr->opcode],pc);
    unsigned oldPC = pc;
    (*executeFuncs[instr->opcode])(instr);
    if(pc == oldPC){
        ++pc;
    }
    return EXIT_SUCCESS;
}