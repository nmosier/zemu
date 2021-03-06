/* zmap.c -- create a binary file that can be converted to a TI-OS appvar
 * that represents a map of the zpages of a story file
 * Nicholas Mosier 2019
 */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdint.h>

#define ZHDR_MAXSIZE 56
#define ZPAGE_SIZE_ENV "ZPAGE_SIZE"
#define VARNAMELEN 8

#define ZMAP_ENT_FLAGS_COPY 0

#define ZHDR_STATIC 0xe
#define ZHDR_STORYSIZE 0x1a // packed address

#define ZMAP_STORYSIZE_LEN 3

#define MASK(bit) (1 << bit)

struct zmap_storysize {
   
};

struct zmap_header {
   uint8_t zmh_pagemask; // high byte page mask
   uint8_t zmh_pagebits;
   uint32_t zmh_storysize; // actually treated as uint24_t
   uint8_t zmh_npages;
   uint16_t zmh_staticaddr; // start address of static Z-memory
};

struct zfile {
   char varname[VARNAMELEN];
   uint16_t size;
   uint8_t zfd;
   uint32_t ptr;
};

struct zmap_tabent {
   struct zfile file;
   uint8_t flags;
};

uint8_t read_be8(void *ptr);
uint16_t read_be16(void *ptr);

void zmap_header_write(FILE *outf, const struct zmap_header *hdr);
void zmap_table_write(FILE *outf, const struct zmap_tabent *tab, int cnt);

int main(int argc, char *argv[]) {
   const char *usage = "usage: %s [-n page_size] [-o outfile] storyfile [zpagefile...]\n";
   const char *optstring = "n:hvo:";
   int exitno = 1;
   int verbose = 0;
   
   /* parameters */
   unsigned long zpage_size = 0;
   FILE *outf; /* output binary */
   const char *storyname = NULL; /* story name */
   int storyfd = -1; /* story file descriptor */
   struct stat storystat; /* story file */
   uint8_t *storym = NULL; /* story memory map */
   struct zmap_tabent *tab = NULL;
   
   /* set defaults */
   outf = stdout;
   char *zpage_size_str;
   if ((zpage_size_str = getenv(ZPAGE_SIZE_ENV)) != NULL &&
       *zpage_size_str != '\0') {
      char *endptr;
      zpage_size = strtoul(zpage_size_str, &endptr, 0);
      if (*endptr != '\0') {
         /* invalid number */
         fprintf(stderr, "%s: environment variable %s must be integer (is set to `"\
                 "%s'\n", argv[0], ZPAGE_SIZE_ENV, zpage_size_str);
         goto cleanup;
      }
   }

   /* parse options */
   int optchar;
   int optgood = 1;
   while ((optchar = getopt(argc, argv, optstring)) >= 0) {
      switch (optchar) {
      case 'n': {
         char *endptr;
         zpage_size = strtoul(optarg, &endptr, 0);
         if (*endptr != '\0') {
            /* invalid number */
            fprintf(stderr, "%s: invalid page size %s\n", argv[0], optarg);
            optgood = 0;
         }
         break;
      }

      case 'o': {
         if ((outf = fopen(optarg, "w")) == NULL) {
            perror("fopen");
            optgood = 0;
         }
         break;
      }

      case 'v':
         verbose = 1;
         break;

      case 'h':
      case '?':
      default:
         fprintf(stderr, usage, argv[0]);
         optgood = 0;
         break;
      }
   }

   /* check for valid number of args */
   if (argc - optind < 1) {
      fprintf(stderr, usage, argv[0]);
      optgood = 0;
   }
   
   /* if parsing failed or necessary parameters not set, exit */
   if (!optgood) {
      goto cleanup;
   }

   /* validate page size */
   if (zpage_size == 0) {
      fprintf(stderr, "%s: invalid zpage size (must be set with `-n' option or "\
              "through environment variable %s)\n", argv[0], ZPAGE_SIZE_ENV);
      goto cleanup;
   } else {
      /* verify that zpage_size is power of 2 */
      if ((zpage_size & (zpage_size - 1)) != 0) {
         fprintf(stderr, "%s: zpage size must be a power of 2\n", argv[0]);
         goto cleanup;
      }

      /* verify that zpage_size is greater than or equal to 256 */
      if ((zpage_size & 0xff) != 0) {
         fprintf(stderr, "%s: zpage size must be greater than or equal to 256\n", argv[0]);
         goto cleanup;
      }
   }

   /* parse arguments */
   int argi = optind;
   storyname = argv[argi++];
   
   /* open story file & get info */
   if ((storyfd = open(storyname, O_RDONLY)) < 0) {
      perror("open");
      goto cleanup;
   }
   if (fstat(storyfd, &storystat) < 0) {
      perror("fstat");
      goto cleanup;
   }
   if ((storym = mmap(NULL, ZHDR_MAXSIZE, PROT_READ, MAP_PRIVATE, storyfd, 0)) == MAP_FAILED) {
      perror("mmap");
      goto cleanup;
   }
   
   /* construct header */
   struct zmap_header hdr;
   hdr.zmh_pagemask = (zpage_size >> 8) - 1;
   hdr.zmh_pagebits = 0;
   for (uint32_t mask = 1; (mask & (zpage_size - 1)); mask <<= 1, ++hdr.zmh_pagebits) {}
   hdr.zmh_pagebits -= 8;
   /* Older v3 story files don't include file size information, according to the standard.
    * First check for story size in the header, and if missing (i.e. is zero), default
    * to file size given by stat(2).
    */
   if ((hdr.zmh_storysize = read_be16(storym + ZHDR_STORYSIZE) * 2) == 0) {
     hdr.zmh_storysize = storystat.st_size;
   }
   hdr.zmh_npages = (storystat.st_size + zpage_size - 1) / zpage_size;
   hdr.zmh_staticaddr = read_be16(storym + ZHDR_STATIC);
   
   /* construct table */

   /* check proper number of pages are given */
   int pages_given = argc - argi;
   if (pages_given > hdr.zmh_npages) {
      fprintf(stderr, "%s: too many zpage files (need %lu, given %lu)\n", argv[0],
              (unsigned long) hdr.zmh_npages, (unsigned long) pages_given);
      goto cleanup;
   }
   if (pages_given < hdr.zmh_npages) {
      fprintf(stderr, "%s: not enough zpage files (need %lu, given %lu)\n", argv[0],
              (unsigned long) hdr.zmh_npages, (unsigned long) pages_given);
      goto cleanup;
   }

   /* allocate table */
   if ((tab = calloc(hdr.zmh_npages, sizeof(*tab))) == NULL) {
      perror("calloc");
      goto cleanup;
   }

   /* populate table */
   for (int i = 0; i < hdr.zmh_npages; ++i) {
      /* get filename stem of path */
      char *stem;
      int stem_len;
      if ((stem = strrchr(argv[argi], '/')) == NULL) {
         stem = argv[argi];
      } else {
         ++stem;
      }
      stem_len = strcspn(stem, ".");

      /* uppercase stem */
      char *stem_end = stem + stem_len;
      for (char *stem_it = stem; stem_it != stem_end; ++stem_it) {
         *stem_it = toupper(*stem_it);
      }

      /* copy strings into table entry */
      strncpy(tab[i].file.varname, stem, stem_len);
      memset(tab[i].file.varname + stem_len, 0, VARNAMELEN - stem_len);
      tab[i].file.size = 0; /* determined at runtime */
      tab[i].file.zfd = 0;
      tab[i].file.ptr = 0;

      /* initialize flags */
      tab[i].flags = (i * zpage_size < hdr.zmh_staticaddr) ? MASK(ZMAP_ENT_FLAGS_COPY) : 0;
      
      ++argi;
   }

   /* print verbose configuration information */
   if (verbose) {
      fprintf(stderr, "zpage size (B): %lu\n", (unsigned long) zpage_size);
      fprintf(stderr, "zpage mask: %2lx\n", (unsigned long) hdr.zmh_pagemask);
      fprintf(stderr, "zpage bits: %lu\n", (unsigned long) hdr.zmh_pagebits);
      fprintf(stderr, "story size (B): %lu\n", (unsigned long) storystat.st_size);
      fprintf(stderr, "number of zpages: %lu\n", (unsigned long) hdr.zmh_npages);
      fprintf(stderr, "static memory: 0x%x\n", hdr.zmh_staticaddr);
      fprintf(stderr, "zpage appvars:\n");
      for (int i = 0; i < hdr.zmh_npages; ++i) {
         fprintf(stderr, "\t%.*s\n", VARNAMELEN, tab[i].file.varname);
      }
   }

   /* write headers & table */
   zmap_header_write(outf, &hdr);
   zmap_table_write(outf, tab, hdr.zmh_npages);

   /* success */
   exitno = 0;
   
 cleanup:
   if (tab != NULL) {
      free(tab);
   }
   if (fclose(outf) < 0) {
      perror("fclose");
      exitno = 1;
   }
   
   return exitno;
}

#define BYTE(val,n) ((uint8_t) (((val) >> ((n) * 8)) & 0xff))

void zmap_header_write(FILE *outf, const struct zmap_header *hdr) {
   fputc(hdr->zmh_pagemask, outf); // zmh_pagemask
   fputc(hdr->zmh_pagebits, outf); // zmh_pagebits
   for (int i = 0; i < ZMAP_STORYSIZE_LEN; ++i) {   // zmh_storysize
      fputc(BYTE(hdr->zmh_storysize, i), outf); 
   }
   fputc(hdr->zmh_npages, outf);   // zmh_npages
   for (int i = 0; i < 2; ++i) {   // zmh_staticaddr
      fputc(BYTE(hdr->zmh_staticaddr, i), outf);
   }
}

void zfile_write(FILE *outf, const struct zfile *zf) {
   fwrite(zf->varname, 1, VARNAMELEN, outf);
   for (int byte = 0; byte < 2; ++byte) {
      fputc(BYTE(zf->size, byte), outf);
   }
   fputc(zf->zfd, outf);
   for (int byte = 0; byte < 3; ++byte) {
      fputc(BYTE(zf->ptr, byte), outf);
   }
}

void zmap_table_write(FILE *outf, const struct zmap_tabent *tab, int cnt) {
   for (int i = 0; i < cnt; ++i) {
      zfile_write(outf, &tab[i].file);
      fputc(tab[i].flags, outf);
   }
}

uint8_t read_be8(void *ptr) {
   return ((uint8_t *) ptr)[0];
}

uint16_t read_be16(void *ptr) {
   uint8_t *ptr8 = (uint8_t *) ptr;
   return (ptr8[0] << 8) + ptr8[1];
}
