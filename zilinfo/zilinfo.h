/* zilinf -- print out info about ZIL story file
 * Nicholas Mosier 2019
 */

#ifndef __ZILINFO_H
#define __ZILINFO_H

#define HA_BEGIN 0x0
#define HA_VERSION_NO 0x0
#define HA_FLAGS1 0x1
#define HB_STAT_LINE_TYPE 1
#define HB_STAT_LINE_AVAIL 4
#define HB_STAT_SCRN_SPLIT_AVAIL 5
#define HB_VAR_PITCH_FONT 6
#define HA_FLAGS2 0x10
#define HA_HIGHMEM 0x4
#define HA_INITPC 0x6
#define HA_DICT 0x8
#define HA_OBJTAB 0xa
#define HA_GLOBALVARS 0xc
#define HA_STATICMEM 0xe

#define HA_ABBRTAB 0x18
#define HA_LENGTH 0x1a
#define HA_CHECKSUM 0x1c

#define UBYTE_AT(ptr, off) (*((uint8_t *) (ptr + off)))
#define UWORD_AT(ptr, off) (
#define ADDR_AT(ptr, off) UWORD_AT(ptr, off)

const char *binstr(unsigned int b);
void z_print_header(FILE *outf, char *zimg);

uint8_t ubyte_at(void *ptr, size_t off);
uint16_t uword_at(void *ptr, size_t off);
uint16_t addr_at(void *ptr, size_t off);

#endif

