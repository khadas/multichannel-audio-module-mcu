// SPDX-License-Identifier: GPL-2.0
#include "tim4.h"

void clear_tim4_pending_bit(void)
{
    TIM4->SR1 = 0xFE;
}

void init_tim4_for_timer(void)
{
    TIM4->CR1  = TIM4_CR1_RESET_VALUE;
    TIM4->IER  = TIM4_IER_RESET_VALUE;
    TIM4->CNTR = TIM4_CNTR_RESET_VALUE;
    TIM4->PSCR = TIM4_PSCR_RESET_VALUE;
    TIM4->ARR  = TIM4_ARR_RESET_VALUE;
    TIM4->SR1  = TIM4_SR1_RESET_VALUE;

    TIM4->PSCR = (u8)(tim4_prescaler_16);
    TIM4->ARR = (u8)(TIM4_AUTO_RELOAD);
    TIM4->EGR = (u8)tim4_psc_reload_mode_immediate;
    TIM4->CR1 |= TIM4_CR1_ARPE;             // Auto-Reload Preload Enable
    TIM4->IER |= TIM4_IT_UPDATE;            // Enable the Interrupt sources
    TIM4->CR1 |= TIM4_CR1_CEN;              // counter enable
}

