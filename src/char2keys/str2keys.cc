#include <cstdio>
#include <ctype>
#include <cstdlib>
#include <cassert>

using Key = std::string;
using Keys = std::list<Key>;

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
      keys.push_back("alpha");
      keys.push_back(alpha2key(c));
   } else if (c == ' ') {
      keys.push_back("alpha");
      keys.push_back("0");
   } else {
      fprintf("don't know how to translate '%c' into keypresses\n", c);
      exit(1);
   }
}

int main(int argc, char *argv[]) {
   if (argc != 2) {
      fprintf(stderr, "usage: %s <string>", argv[0]);
      return 1;
   }

   std::string s = argv[1];
   Keys keys;
   for (char c : s) {
      keys.splice(keys.end(), ascii2key(c));
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
