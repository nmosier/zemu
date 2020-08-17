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

constexpr char ESCAPE = '\\';

enum class Mode {ALOCK, ALPHA, SECOND, NORMAL};
Mode mode = Mode::NORMAL;

Keys set_mode_normal() {
   switch (mode) {
   case Mode::NORMAL: return Keys();
   case Mode::SECOND: return {"2nd"};
   case Mode::ALPHA:
   case Mode::ALOCK:
      return {"alpha"};
   default: abort();
   }
}

void decay_mode() {
   switch (mode) {
   case Mode::SECOND:
   case Mode::ALPHA:
      mode = Mode::NORMAL;
      break;
   case Mode::NORMAL:
   case Mode::ALOCK:
      break;
   default: abort();
   }
}

Keys set_mode(Mode new_mode) {
   if (mode == new_mode) { return Keys(); }

   Keys keys = set_mode_normal();

   switch (new_mode) {
   case Mode::SECOND:
      keys.push_back("2nd");
      break;
   case Mode::NORMAL:
      break;
   case Mode::ALOCK:
      keys.push_back("2nd");
   case Mode::ALPHA:
      keys.push_back("alpha");
      break;
   default: abort();
   }

   mode = new_mode;

   return keys;
}


Mode ascii2mode(char c) {
   if (isalpha(c)) {
      return Mode::ALOCK;
   }
   
   if (isdigit(c)) {
      return Mode::NORMAL;
   }

   switch (c) {
   case '"': 
   case '?':
   case ':':
   case ' ':
      return Mode::ALOCK;
   }
   
   return Mode::NORMAL;
}


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
   if (isalpha(c)) {
      return {alpha2key(c)};
   }

   if (isdigit(c)) {
      return {std::string(&c, &c + 1)};
   }

   switch (c) {
   case ' ': return {"0"};
   case ':': return {"."};
   case '.': return {"."};
   case '"': return {"+"};
   case '+': return {"+"};
   case '-': return {"-"};
   case '*': return {"*"};
   case '/': return {"/"};
   case '^': return {"^"};
   case '(': return {"("};
   case ')': return {")"};
   case ',': return {","};
   case '?': return {"(-)"};
   }

   fprintf(stderr, "don't know how to translate '%c' into keypresses\n", c);
   exit(1);
}

Mode escape2mode(char c) {
   switch (c) {
   case 'n':
      return Mode::ALOCK;
   case 'd': 
   case 'u': 
   case 'l': 
   case 'r': 
   case 'b': 
      return Mode::NORMAL;
   default:
      return ascii2mode(c);
   }
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
            "usage: %s [-h] <string>\n"         \
            "";
         fprintf(f, usage, argv[0]);
      };

   const char *optstring = "h";
   int optchar;
   while ((optchar = getopt(argc, argv, optstring)) >= 0) {
      switch (optchar) {
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
         ++s;
         keys.splice(keys.end(), set_mode(escape2mode(*s)));
         keys.splice(keys.end(), escape2key(*s));
         break;
      default:
         keys.splice(keys.end(), set_mode(ascii2mode(*s)));
         keys.splice(keys.end(), ascii2key(*s));
         break;
      }

      decay_mode();
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
