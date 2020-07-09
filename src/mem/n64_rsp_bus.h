#ifndef N64_N64_RSP_BUS_H
#define N64_N64_RSP_BUS_H

#include "../common/util.h"
#include "../system/n64system.h"

word n64_rsp_read_word(n64_system_t* system, word address);
void n64_rsp_write_word(n64_system_t* system, word address, word value);

half n64_rsp_read_half(n64_system_t* system, word address);
void n64_rsp_write_half(n64_system_t* system, word address, half value);

#endif //N64_N64_RSP_BUS_H