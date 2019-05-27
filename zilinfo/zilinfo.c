/* zilinfo.c -- print out info about ZIL story file.
 * Nicholas Mosier 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "zilinfo.h"

int main(int argc, char *argv[]) {
   const char *usage = "%s [path]\n";
   int error = 1;
   int zfd = -1;
   struct stat zstat;
   char *zimg = MAP_FAILED;

   if (argc != 2) {
      fprintf(stderr, usage, argv[0]);
      goto cleanup;
   }

   /* open & mmap file */
   if ((zfd = open(argv[1], O_RDONLY)) < 0) {
      perror("open");
      goto cleanup;
   }

   if (fstat(zfd, &zstat) < 0) {
      perror("fstat");
      goto cleanup;
   }
   
   if ((zimg = mmap(NULL, zstat.st_size, PROT_READ, MAP_PRIVATE, zfd, 0)) == MAP_FAILED) {
      perror("mmap");
      goto cleanup;
   }

   /* print out info */
   z_print_header(stdout, zimg);
   
   /* success */
   error = 0;
   
 cleanup:
   if (zimg != MAP_FAILED) {
      if (munmap(zimg, zstat.st_size) < 0) {
         error = 1;
      }
   }
   if (zfd >= 0) {
      if (close(zfd) < 0) {
         error = 1;
      }
   }

   return error ? 1 : 0;
}

static char binstr_buf[11];
const char *binstr(unsigned int b) {
   char *binstr_it = binstr_buf;
   *binstr_it++ = '0';
   *binstr_it++ = 'b';
   for (int i = 0; i < 8; ++i) {
      *binstr_it++ = (b & 1) ? '1' : '0';
   }
   *binstr_it = '\0';
   return binstr_buf;
}

void z_print_header(FILE *outf, char *zimg) {
   fprintf(outf, "version number = %d\n", ubyte_at(zimg, HA_VERSION_NO));
   fprintf(outf, "flags 1 = %s\n", binstr(ubyte_at(zimg, HA_FLAGS1)));
   fprintf(outf, "flags 2 = %s\n", binstr(ubyte_at(zimg, HA_FLAGS2)));
   fprintf(outf, "base of high memory = 0x%x\n", addr_at(zimg, HA_HIGHMEM));
   fprintf(outf, "initial value of program counter = 0x%x\n", addr_at(zimg, HA_INITPC));
   fprintf(outf, "location of dictionary = 0x%x\n", addr_at(zimg, HA_DICT));
   fprintf(outf, "location of object table = 0x%x\n", addr_at(zimg, HA_OBJTAB));
   fprintf(outf, "location of global variables table = 0x%x\n", addr_at(zimg, HA_GLOBALVARS));
   fprintf(outf, "base of static memory = 0x%x\n", addr_at(zimg, HA_STATICMEM));
}

uint8_t ubyte_at(void *ptr, size_t off) {
   return *((uint8_t *) ptr + off);
}

uint16_t uword_at(void *ptr, size_t off) {
   uint8_t *byte_ptr = ((uint8_t *) ptr) + off;
   return (((uint16_t) byte_ptr[0]) << 8) + (uint16_t) byte_ptr[1];
}

uint16_t addr_at(void *ptr, size_t off) {
   return uword_at(ptr, off);
}
