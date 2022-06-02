#include "alphavm.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

#define IOP_BIN_SIZE 13U
#define ALPHA_MAGICNUM 0x14470c35U

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
    off_t off;

    if ( (bfile = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0UL)) == MAP_FAILED )
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

    // [1] strings [2] numbers [3] userfuncs [4] libfuncs

    /** strings array **/

    sarr.size = *((uint32_t *)(bfile));


    return EXIT_SUCCESS;
}