#ifndef N64_BACKUP_H
#define N64_BACKUP_H
#include <system/n64system.h>
#include "mem_util.h"

void sram_write_word(n64_system_t* system, word index, word value);
word sram_read_word(n64_system_t* system, word index);

void sram_write_byte(n64_system_t* system, word index, byte value);
byte sram_read_byte(n64_system_t* system, word index);

#endif //N64_BACKUP_H