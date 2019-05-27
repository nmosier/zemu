#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
   uint16_t val = 0x0102;
   uint8_t *ptr = (uint8_t *) &val;
   printf("reference: %04x\n", val);
   printf("bytes: %02x %02x\n", ptr[0], ptr[1]);

   return 0;
}
