// SPDX-License-Identifier: GPL-2.0
#include "clk.h"

void hsi_prescaler_set()
{
    CLK->CKDIVR &= (u8)(~CLK_CKDIVR_HSIDIV);
    CLK->CKDIVR |= (u8)0x00;
}

