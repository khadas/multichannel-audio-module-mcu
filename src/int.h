// SPDX-License-Identifier: GPL-2.0
#ifndef __INT_H
#define __INT_H

#include "stm8s.h"

#define CPU_INT_DISABLED ((u8)0x28)
#define IS_INT_DISABLED (get_soft_int_status() == CPU_INT_DISABLED)

typedef enum {
    itc_irq_tli            = (u8)0,   // Software interrupt
    itc_irq_awu            = (u8)1,   // Auto wake up from halt interrupt
    itc_irq_clk            = (u8)2,   // Clock controller interrupt
    itc_irq_port_a         = (u8)3,   // Port A external interrupts
    itc_irq_port_b         = (u8)4,   // Port B external interrupts
    itc_irq_port_c         = (u8)5,   // Port C external interrupts
    itc_irq_port_d         = (u8)6,   // Port D external interrupts
    itc_irq_port_e         = (u8)7,   // Port E external interrupts
    itc_irq_spi            = (u8)10,  // SPI interrupt
    itc_irq_tim1_ovf       = (u8)11,  // TIM1 update/overflow/underflow/trigger/ break interrupt
    itc_irq_tim1_capcom    = (u8)12,  // TIM1 capture/compare interrupt
    itc_irq_tim2_ovf       = (u8)13,  // TIM2 update /overflow interrupt
    itc_irq_tim2_capcom    = (u8)14,  // TIM2 capture/compare interrupt
    itc_irq_tim3_ovf       = (u8)15,  // TIM3 update /overflow interrupt
    itc_irq_tim3_capcom    = (u8)16,  // TIM3 update /overflow interrupt
    itc_irq_uart_tx        = (u8)17,  // UART TX interrupt
    itc_irq_uart_rx        = (u8)18,  // UART RX interrupt
    itc_irq_i2c            = (u8)19,  // I2C interrupt
    itc_irq_adc            = (u8)22,  // ADC interrupt
    itc_irq_tim4_ovf       = (u8)23,  // TIM4 update /overflow interrupt
    itc_irq_eeprom_eec     = (u8)24   // Flash interrupt
} itc_irq;


typedef enum {
    itc_priority_level_0 = (u8)0x02,
    itc_priority_level_1 = (u8)0x01,
    itc_priority_level_2 = (u8)0x00,
    itc_priority_level_3 = (u8)0x03
} priority_level;

typedef enum {
    exti_sensitivity_fall_low  = (u8)0x00,
    exti_sensitivity_rise_only = (u8)0x01,
    exti_sensitivity_fall_only = (u8)0x02,
    exti_sensitivity_rise_fall = (u8)0x03
} sensitivity_type;

typedef enum {
    exti_port_gpio_a = (u8)0x00,
    exti_port_gpio_b = (u8)0x01,
    exti_port_gpio_c = (u8)0x02,
    exti_port_gpio_d = (u8)0x03,
    exti_port_gpio_e = (u8)0x04
} exti_port;

void set_irq_priority(void);
void set_interrupt_sensitivity(exti_port port, sensitivity_type type);


#endif /* __INT_H */

