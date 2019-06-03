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

#define ZPAGE_SIZE_ENV "ZPAGE_SIZE"
#define VARNAMELEN 8
#define EZ80_WORDSIZE 3

struct zmap_header {
   uint16_t zmh_pagesize;
   unsigned int zmh_storysize: 24;
   uint8_t zmh_npages;
};

struct zmap_tabent {
   char zme_varname[VARNAMELEN];
   uint8_t zme_flags;
   unsigned int zme_ptr: 24;
};

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
   struct stat storystat; /* story file */
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
   if (zpage_size == 0) {
      fprintf(stderr, "%s: invalid zpage size (must be set with `-n' option or "\
              "through environment variable %s)\n", argv[0], ZPAGE_SIZE_ENV);
      goto cleanup;
   }

   /* parse arguments */
   int argi = optind;

   /* get story file info (1st arg.) */
   if (stat(argv[argi++], &storystat) < 0) {
      perror("stat");
      goto cleanup;
   }   

   /* construct header */
   struct zmap_header hdr;
   hdr.zmh_pagesize = zpage_size;
   hdr.zmh_storysize = storystat.st_size;
   hdr.zmh_npages = (storystat.st_size + hdr.zmh_pagesize - 1) / zpage_size;

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
      strncpy(tab[i].zme_varname, stem, stem_len);
      memset(tab[i].zme_varname + stem_len, 0, VARNAMELEN - stem_len);

      /* NOTE: we can leave the zme_flags and zme_ptr fields as containing 
       * garbage. */
      ++argi;
   }

   /* print verbose configuration information */
   if (verbose) {
      printf("zpage size (B): %lu\n", (unsigned long) hdr.zmh_pagesize);
      printf("story size (B): %lu\n", (unsigned long) storystat.st_size);
      printf("number of zpages: %lu\n", (unsigned long) hdr.zmh_npages);
      printf("zpage appvars:\n");
      for (int i = 0; i < hdr.zmh_npages; ++i) {
         printf("\t%.*s\n", VARNAMELEN, tab[i].zme_varname);
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
   /* write page sizes */
   for (int i = 0; i < 2; ++i) {
      fputc(BYTE(hdr->zmh_pagesize, i), outf);
   }

   /* write story size */
   for (int i = 0; i < 3; ++i) {
      fputc(BYTE(hdr->zmh_storysize, i), outf);
   }

   /* write npages */
   fputc(hdr->zmh_npages, outf);
}

void zmap_table_write(FILE *outf, const struct zmap_tabent *tab, int cnt) {
   for (int i = 0; i < cnt; ++i) {
      fwrite(tab[i].zme_varname, 1, VARNAMELEN, outf);
      fputc(tab[i].zme_flags, outf);
      for (int j = 0; j < 3; ++j) {
         fputc(BYTE(tab[i].zme_ptr, j), outf);
      }
   }
}
