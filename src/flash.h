// SPDX-License-Identifier: GPL-2.0
#ifndef __FLASH_H
#define __FLASH_H

#include "stm8s.h"

#define FLASH_DATA_START_PHYSICAL_ADDRESS ((u32)0x004000)
#define FLASH_RASS_KEY1 ((u8)0x56)
#define FLASH_RASS_KEY2 ((u8)0xAE)

void flash_unlock();
void flash_lock();
void flash_program_byte(u32 addr, u8 data);
u8 flash_read_byte(u32 addr);
FlagStatus flash_get_flag_status();

#endif /*__FLASH_H */

