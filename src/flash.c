// SPDX-License-Identifier: GPL-2.0
#include "flash.h"

void flash_unlock()
{
    FLASH->DUKR = FLASH_RASS_KEY2; // Warning: keys are reversed on data memory !!!
    FLASH->DUKR = FLASH_RASS_KEY1;
}

void flash_lock()
{
    FLASH->IAPSR &= (u8)0xF7;
}

void flash_program_byte(u32 addr, u8 data)
{
    *(PointerAttr u8*) (MemoryAddressCast)addr = data;

    while ((*(PointerAttr u8 *) (MemoryAddressCast)addr) != data) {
		*(PointerAttr u8*) (MemoryAddressCast)addr = data;
	}
}

u8 flash_read_byte(u32 addr)
{
    return(*(PointerAttr u8 *) (MemoryAddressCast)addr);
}

FlagStatus flash_get_flag_status()
{
    if ((FLASH->IAPSR & (u8)0x08) != (u8)RESET) {
        return SET;

    } else {
        return RESET;
    }
}
