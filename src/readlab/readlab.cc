#include <iostream>
#include <cstdio>
#include <unordered_map>
#include <getopt.h>
#include <fstream>
#include <list>
#include <string>

using Map = std::unordered_map<std::string, std::string>;
constexpr int SYM_MAXLEN = 128;

Map parse_file(FILE *f) {
   Map map;
   char sym[128];
   char val[128];
   while (fscanf(f, "%128s = %128s\n", sym, val) == 2) {
      std::string sym_(sym);
      for (char& c : sym_) {
         c = toupper(c);
      }
      map.insert({sym_, val});
   }

   return map;
}

unsigned long evaluate(const std::string& s) {
   switch (s[0]) {
   case '$':
      // hex
      return stoul(s.substr(1), nullptr, 16);
   case '%':
      fprintf(stderr, "binary not supported yet\n");
      exit(1);
   default:
      return stoul(s);
   } 
}

int main(int argc, char *argv[]) {
   const auto usage =
      [&] (FILE *f) {
         const char *usage =
            "usage: %s [-he] path sym...\n"      \
            "";
         fprintf(stderr, usage, argv[0]);
      };

   const char *optstring = "he";
   int optchar;
   bool eval = false;
   while ((optchar = getopt(argc, argv, optstring)) >= 0) {
      switch (optchar) {
      case 'h':
         usage(stdout);
         return 0;
      case 'e':
         eval = true;
         break;
      default:
         usage(stderr);
         return 1;
      }
   }

   if (optind == argc) {
      usage(stderr);
      return 1;
   }
   
   FILE *f;
   if ((f = fopen(argv[optind++], "r")) == nullptr) {
      perror("fopen");
      return 1;
   }

   Map map = parse_file(f);

   bool good = true;
   unsigned found = 0;
   for (; optind != argc; ++optind) {
      std::string sym(argv[optind]);
      for (char& c : sym) {
         c = toupper(c);
      }
      auto it = map.find(sym);
      if (it != map.end()) {
         if (eval) {
            std::cout << evaluate(it->second);
         } else {
            std::cout << it->second;
         }
         if (optind != argc - 1) {
            std::cout << " ";
         }
         ++found;
      } else {
         fprintf(stderr, "%s: symbol '%s' not found\n", argv[0], argv[optind]);
         good = false;
      }
   }

   if (found) {
      std::cout << std::endl;
   }

   return good ? 0 : 1;
}
