#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cassert>
#include <string>
#include <iostream>
#include <list>
#include <unistd.h>

using Key = std::string;
using Keys = std::list<Key>;

bool alpha_lock = false;
constexpr char ESCAPE = '\\';

Key alpha2key(char c) {
   assert(isalpha(c));
   c = toupper(c);
   switch (c) {
   case 'A': return "math";
   case 'B': return "apps";
   case 'C': return "prgm";
   case 'D': return "-1";
   case 'E': return "sin";
   case 'F': return "cos";
   case 'G': return "tan";
   case 'H': return "^";
   case 'I': return "^2";
   case 'J': return ",";
   case 'K': return "(";
   case 'L': return ")";
   case 'M': return "/";
   case 'N': return "log";
   case 'O': return "7";
   case 'P': return "8";
   case 'Q': return "9";
   case 'R': return "*";
   case 'S': return "ln";
   case 'T': return "4";
   case 'U': return "5";
   case 'V': return "6";
   case 'W': return "-";
   case 'X': return "sto";
   case 'Y': return "1";
   case 'Z': return "2";
   default: abort();
   }
}

Keys ascii2key(char c) {
   Keys keys;
   if (isalpha(c)) {
      if (!alpha_lock) {
         keys.push_back("2nd");
         keys.push_back("alpha");
         alpha_lock = true;
      }
      keys.push_back(alpha2key(c));
   } else if (c == ' ') {
      if (!alpha_lock) {
         keys.push_back("2nd");
         keys.push_back("alpha");
         alpha_lock = true;
      }
      keys.push_back("0");
   } else if (c == '\n') {
      keys.push_back("enter");
   } else {
      fprintf(stderr, "don't know how to translate '%c' into keypresses\n", c);
      exit(1);
   }
   
   return keys;
}

Keys escape2key(char c) {
   switch (c) {
   case 'n': return {"enter"};
   case 'd': return {"down"};
   case 'u': return {"up"};
   case 'l': return {"left"};
   case 'r': return {"right"};
   case 'b': return {"del"};
   default:
      return ascii2key(c);
   }
}

int main(int argc, char *argv[]) {
   const auto usage =
      [&] (FILE *f) {
         const char *usage =
            "usage: %s [-ah] <string>\n"        \
            "";
         fprintf(f, usage, argv[0]);
      };

   const char *optstring = "ah";
   int optchar;
   while ((optchar = getopt(argc, argv, optstring)) >= 0) {
      switch (optchar) {
      case 'a':
         alpha_lock = true;
         break;
      case 'h':
         usage(stdout);
         return 0;
      default:
         usage(stderr);
         return 1;
      }
   }

   if (optind != argc - 1) {
      usage(stderr);
      return 1;
   }

   const char *s = argv[optind++];
   Keys keys;
   for (; *s; ++s) {
      switch (*s) {
      case ESCAPE:
         keys.splice(keys.end(), escape2key(*++s));
         break;
      default:
         keys.splice(keys.end(), ascii2key(*s));
         break;
      }
   }

   for (auto it = keys.begin(); it != keys.end(); ++it) {
      if (it != keys.begin()) {
         std::cout << " ";
      }
      std::cout << *it;
   }
   std::cout << std::endl;

   return 0;
}
