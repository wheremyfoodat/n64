#include <frontend/tas_movie.h>
#include "pif.h"
#include "n64bus.h"

void pif_rom_execute_hle(n64_system_t* system) {
    system->cpu.gpr[0] = 0;
    system->cpu.gpr[1] = 0;
    system->cpu.gpr[2] = 0;
    system->cpu.gpr[3] = 0;
    system->cpu.gpr[4] = 0;
    system->cpu.gpr[5] = 0;
    system->cpu.gpr[6] = 0;
    system->cpu.gpr[7] = 0;
    system->cpu.gpr[8] = 0;
    system->cpu.gpr[9] = 0;
    system->cpu.gpr[10] = 0;
    system->cpu.gpr[11] = 0;
    system->cpu.gpr[12] = 0;
    system->cpu.gpr[13] = 0;
    system->cpu.gpr[14] = 0;
    system->cpu.gpr[15] = 0;
    system->cpu.gpr[16] = 0;
    system->cpu.gpr[17] = 0;
    system->cpu.gpr[18] = 0;
    system->cpu.gpr[19] = 0;
    system->cpu.gpr[20] = 0x1;
    system->cpu.gpr[21] = 0;
    system->cpu.gpr[22] = 0x3F;
    system->cpu.gpr[23] = 0;
    system->cpu.gpr[24] = 0;
    system->cpu.gpr[25] = 0;
    system->cpu.gpr[26] = 0;
    system->cpu.gpr[27] = 0;
    system->cpu.gpr[28] = 0;
    system->cpu.gpr[29] = 0xFFFFFFFFA4001FF0;
    system->cpu.gpr[30] = 0;
    system->cpu.gpr[31] = 0;

    system->cpu.cp0.index         = 0;
    system->cpu.cp0.random        = 0x0000001F;
    system->cpu.cp0.entry_lo0.raw = 0;
    system->cpu.cp0.entry_lo1.raw = 0;
    system->cpu.cp0.context       = 0;
    system->cpu.cp0.page_mask.raw = 0;
    system->cpu.cp0.wired         = 0;
    system->cpu.cp0.r7            = 0;
    system->cpu.cp0.bad_vaddr     = 0;
    system->cpu.cp0.count         = 0;
    system->cpu.cp0.entry_hi.raw  = 0;
    system->cpu.cp0.compare       = 0;
    system->cpu.cp0.status.raw    = 0x34000000;
    system->cpu.cp0.cause.raw     = 0;
    system->cpu.cp0.EPC           = 0;
    system->cpu.cp0.PRId          = 0x00000B00;
    system->cpu.cp0.config        = 0x0006E463;
    system->cpu.cp0.lladdr        = 0;
    system->cpu.cp0.watch_lo.raw  = 0;
    system->cpu.cp0.watch_hi      = 0;
    system->cpu.cp0.x_context     = 0;
    system->cpu.cp0.r21           = 0;
    system->cpu.cp0.r22           = 0;
    system->cpu.cp0.r23           = 0;
    system->cpu.cp0.r24           = 0;
    system->cpu.cp0.r25           = 0;
    system->cpu.cp0.parity_error  = 0;
    system->cpu.cp0.cache_error   = 0;
    system->cpu.cp0.tag_lo        = 0;
    system->cpu.cp0.tag_hi        = 0;
    system->cpu.cp0.error_epc     = 0;
    system->cpu.cp0.r31           = 0;

    loginfo("CP0 status: ie:  %d", system->cpu.cp0.status.ie);
    loginfo("CP0 status: exl: %d", system->cpu.cp0.status.exl);
    loginfo("CP0 status: erl: %d", system->cpu.cp0.status.erl);
    loginfo("CP0 status: ksu: %d", system->cpu.cp0.status.ksu);
    loginfo("CP0 status: ux:  %d", system->cpu.cp0.status.ux);
    loginfo("CP0 status: sx:  %d", system->cpu.cp0.status.sx);
    loginfo("CP0 status: kx:  %d", system->cpu.cp0.status.kx);
    loginfo("CP0 status: im:  %d", system->cpu.cp0.status.im);
    loginfo("CP0 status: ds:  %d", system->cpu.cp0.status.ds);
    loginfo("CP0 status: re:  %d", system->cpu.cp0.status.re);
    loginfo("CP0 status: fr:  %d", system->cpu.cp0.status.fr);
    loginfo("CP0 status: rp:  %d", system->cpu.cp0.status.rp);
    loginfo("CP0 status: cu0: %d", system->cpu.cp0.status.cu0);
    loginfo("CP0 status: cu1: %d", system->cpu.cp0.status.cu1);
    loginfo("CP0 status: cu2: %d", system->cpu.cp0.status.cu2);
    loginfo("CP0 status: cu3: %d", system->cpu.cp0.status.cu3);

    //n64_write_word(system, 0x04300004, 0x01010101);

    // Copy the first 0x1000 bytes of the cartridge to 0xA4000000

    word src_ptr  = 0xB0000000;
    word dest_ptr = 0xA4000000;

    for (int i = 0; i < (0x1000 >> 3); i++) {
        word src_address = src_ptr + (i << 3);
        word dest_address = dest_ptr + (i << 3);
        dword src = n64_read_dword(system, resolve_virtual_address(src_address, &system->cpu.cp0));
        n64_write_dword(system, resolve_virtual_address(dest_address, &system->cpu.cp0), src);

        logtrace("PIF: Copied 0x%016lX from 0x%08X ==> 0x%08X", src, src_address, dest_address);
    }

    system->cpu.pc = 0xA4000040;
    system->cpu.next_pc = system->cpu.pc + 4;
}

void pif_rom_execute_lle(n64_system_t* system) {
    system->cpu.pc = 0x1FC00000 + SVREGION_KSEG1;
    system->cpu.next_pc = system->cpu.pc + 4;
}

void pif_rom_execute(n64_system_t* system) {
    switch (system->mem.rom.cic_type) {
        case CIC_NUS_6101_7102:
            n64_write_word(system, SREGION_PIF_RAM + 0x24, 0x00043F3F);
            break;
        case CIC_NUS_6102_7101:
            n64_write_word(system, SREGION_PIF_RAM + 0x24, 0x00003F3F);
            break;
        case CIC_NUS_6103_7103:
            n64_write_word(system, SREGION_PIF_RAM + 0x24, 0x0000783F);
            break;
        case CIC_NUS_6105_7105:
            n64_write_word(system, SREGION_PIF_RAM + 0x24, 0x0000913F);
            break;
        case CIC_NUS_6106_7106:
            n64_write_word(system, SREGION_PIF_RAM + 0x24, 0x0000853F);
            break;
        case UNKNOWN_CIC_TYPE:
            logwarn("Unknown CIC type, not writing seed to PIF RAM! The game may not boot!");
    }

    if (system->mem.rom.pif_rom == NULL) {
        logalways("No PIF rom loaded, HLEing...");
        pif_rom_execute_hle(system);
    } else {
        logalways("PIF rom loaded, executing it...");
        pif_rom_execute_lle(system);
    }
}

#define PIF_COMMAND_CONTROLLER_ID 0x00
#define PIF_COMMAND_READ_BUTTONS  0x01
#define PIF_COMMAND_MEMPACK_READ  0x02
#define PIF_COMMAND_MEMPACK_WRITE 0x03
#define PIF_COMMAND_EEPROM_READ   0x04
#define PIF_COMMAND_EEPROM_WRITE  0x05
#define PIF_COMMAND_RESET         0xFF

void pif_command(n64_system_t* system, sbyte cmdlen, byte reslen, int r_index, int* index, int* channel) {
    byte command = system->mem.pif_ram[(*index)];
    (*index)++;
    switch (command) {
        case PIF_COMMAND_RESET:
        case PIF_COMMAND_CONTROLLER_ID: {
            bool plugged_in = (*channel) < 4 && system->si.controllers[*channel].plugged_in;
            if (plugged_in) {
                system->mem.pif_ram[(*index)++] = 0x05;
                system->mem.pif_ram[(*index)++] = 0x00;
                system->mem.pif_ram[(*index)++] = 0x01; // Controller pak plugged in.
            } else {
                system->mem.pif_ram[(*index)++] = 0x05;
                system->mem.pif_ram[(*index)++] = 0x00;
                system->mem.pif_ram[(*index)++] = 0x01;
            }
            (*channel)++;
            break;
        }
        case PIF_COMMAND_READ_BUTTONS: {
            byte bytes[4];
            if (*channel < 4 && system->si.controllers[*channel].plugged_in) {
                if (tas_movie_loaded()) {
                    // Load inputs from TAS movie
                    n64_controller_t controller = tas_next_inputs();
                    bytes[0] = controller.byte1;
                    bytes[1] = controller.byte2;
                    bytes[2] = controller.joy_x;
                    bytes[3] = controller.joy_y;
                } else {
                    // Load inputs normally
                    bytes[0] = system->si.controllers[*channel].byte1;
                    bytes[1] = system->si.controllers[*channel].byte2;
                    bytes[2] = system->si.controllers[*channel].joy_x;
                    bytes[3] = system->si.controllers[*channel].joy_y;
                }
                system->mem.pif_ram[r_index]   |= 0x00; // Success!
                system->mem.pif_ram[(*index)++] = bytes[0];
                system->mem.pif_ram[(*index)++] = bytes[1];
                system->mem.pif_ram[(*index)++] = bytes[2];
                system->mem.pif_ram[(*index)++] = bytes[3];
            } else {
                system->mem.pif_ram[r_index]   |= 0x80; // Device not present
                system->mem.pif_ram[(*index)++] = 0x00;
                system->mem.pif_ram[(*index)++] = 0x00;
                system->mem.pif_ram[(*index)++] = 0x00;
                system->mem.pif_ram[(*index)++] = 0x00;
            }
            (*channel)++;
            break;
        }
        case PIF_COMMAND_MEMPACK_READ:
            unimplemented(cmdlen != 3, "Mempack read with cmdlen != 3");
            unimplemented(reslen != 33, "Mempack read with reslen != 33");
            //logfatal("PIF_COMMAND_MEMPACK_READ");
            (*index) += 35; // NOOP
            break;
        case PIF_COMMAND_MEMPACK_WRITE:
            unimplemented(cmdlen != 35, "Mempack write with cmdlen != 35");
            unimplemented(reslen != 1, "Mempack write with reslen != 1");
            system->mem.pif_ram[r_index]   |= 0x80; // Device not present
            system->mem.pif_ram[(*index) + 34] = 0x00;
            (*index) += 35; // NOOP
            break;
        case PIF_COMMAND_EEPROM_READ:
            logfatal("PIF_COMMAND_EEPROM_READ");
        case PIF_COMMAND_EEPROM_WRITE:
            logfatal("PIF_COMMAND_EEPROM_WRITE");
        default:
            logfatal("Unknown PIF command: %d", command);
    }
}

void process_pif_command(n64_system_t* system) {
    byte control = system->mem.pif_ram[63];
    if (control == 1) {
        int i = 0;
        int channel = 0;
        while (i < 63) {
            byte t = system->mem.pif_ram[i++] & 0x3F;
            if (t == 0) {
                channel++;
            } else if (t == 0x3F) {
                continue;
            } else if (t == 0x3E) {
                break;
            } else {
                int r_index = i;
                byte r = system->mem.pif_ram[i++] & 0x3F; // TODO: out of bounds access possible on invalid data
                pif_command(system, t, r, r_index, &i, &channel);
            }
        }
    }
}


void update_button(n64_system_t* system, int controller, n64_button_t button, bool held) {
    switch(button) {
        case N64_BUTTON_A:
            system->si.controllers[controller].a = held;
            break;

        case N64_BUTTON_B:
            system->si.controllers[controller].b = held;
            break;

        case N64_BUTTON_Z:
            system->si.controllers[controller].z = held;
            break;

        case N64_BUTTON_DPAD_UP:
            system->si.controllers[controller].dp_up = held;
            break;

        case N64_BUTTON_DPAD_DOWN:
            system->si.controllers[controller].dp_down = held;
            break;

        case N64_BUTTON_DPAD_LEFT:
            system->si.controllers[controller].dp_left = held;
            break;

        case N64_BUTTON_DPAD_RIGHT:
            system->si.controllers[controller].dp_right = held;
            break;

        case N64_BUTTON_START:
            system->si.controllers[controller].start = held;
            break;

        case N64_BUTTON_L:
            system->si.controllers[controller].l = held;
            break;

        case N64_BUTTON_R:
            system->si.controllers[controller].r = held;
            break;

        case N64_BUTTON_C_UP:
            system->si.controllers[controller].c_up = held;
            break;

        case N64_BUTTON_C_DOWN:
            system->si.controllers[controller].c_down = held;
            break;

        case N64_BUTTON_C_LEFT:
            system->si.controllers[controller].c_left = held;
            break;

        case N64_BUTTON_C_RIGHT:
            system->si.controllers[controller].c_right = held;
            break;
    }
}

void update_joyaxis(n64_system_t* system, int controller, sbyte x, sbyte y) {
    system->si.controllers[controller].joy_x = x;
    system->si.controllers[controller].joy_y = y;
}

void update_joyaxis_x(n64_system_t* system, int controller, sbyte x) {
    system->si.controllers[controller].joy_x = x;
}

void update_joyaxis_y(n64_system_t* system, int controller, sbyte y) {
    system->si.controllers[controller].joy_y = y;
}

void load_pif_rom(n64_system_t* system, const char* pif_rom_path) {
    FILE *fp = fopen(pif_rom_path, "rb");

    if (fp == NULL) {
        logfatal("Error opening the PIF ROM file! Are you sure this is a correct path?");
    }

    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);

    fseek(fp, 0, SEEK_SET);
    byte *buf = malloc(size);
    fread(buf, size, 1, fp);

    system->mem.rom.pif_rom = buf;
    system->mem.rom.pif_rom_size = size;
}
