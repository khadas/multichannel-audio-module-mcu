// SPDX-License-Identifier: GPL-2.0
#ifndef __TIM4_H
#define __TIM4_H

#include "stm8s.h"

#define TIM4_AUTO_RELOAD    64
#define TIM4_IT_UPDATE      0x01
typedef enum
{
    tim4_prescaler_1    = ((u8)0x00),
    tim4_prescaler_2    = ((u8)0x01),
    tim4_prescaler_4    = ((u8)0x02),
    tim4_prescaler_8    = ((u8)0x03),
    tim4_prescaler_16   = ((u8)0x04),
    tim4_prescaler_32   = ((u8)0x05),
    tim4_prescaler_64   = ((u8)0x06),
    tim4_prescaler_128  = ((u8)0x07)
} tim4_prescaler;


typedef enum
{
    tim4_psc_reload_mode_update     = ((u8)0x00),
    tim4_psc_reload_mode_immediate  = ((u8)0x01)
} tim4_psc_reload_mode;


void clear_tim4_pending_bit(void);
void init_tim4_for_timer(void);


#endif /* __TIM4_H */

