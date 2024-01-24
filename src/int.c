// SPDX-License-Identifier: GPL-2.0
#include "int.h"

u8 get_soft_int_status(void)
{
    // get cpu condition code register
#ifdef _COSMIC_
    _asm("push cc");
    _asm("pop a");
#elif defined _RAISONANCE_
    return (u8)(_getCC_() & CPU_CC_I1I0);
#elif defined _SDCC_
    __asm__("push cc");
    __asm__("pop a");
#else   // _IAR_
    asm("push cc");
    asm("pop a");
#endif

    return (u8)(CPU_CC_I1I0);
}

void set_interrupt_priority(itc_irq irq_num, priority_level level)
{
    u8 mask = 0;
    u8 new_level = 0;

    assert_param(IS_INT_DISABLED);

    mask = (u8)(~(u8)(0x03U << (((u8)irq_num % 4U) * 2U)));
    new_level = (u8)((u8)(level) << (((u8)irq_num % 4U) * 2U));

    switch (irq_num) {
    case itc_irq_tli:
    case itc_irq_awu:
    case itc_irq_clk:
    case itc_irq_port_a:
        ITC->ISPR1 &= mask;
        ITC->ISPR1 |= new_level;
        break;

    case itc_irq_port_b:
    case itc_irq_port_c:
    case itc_irq_port_d:
    case itc_irq_port_e:
        ITC->ISPR2 &= mask;
        ITC->ISPR2 |= new_level;
        break;

    case itc_irq_spi:
    case itc_irq_tim1_ovf:
        ITC->ISPR3 &= mask;
        ITC->ISPR3 |= new_level;
        break;

    case itc_irq_tim1_capcom:
    case itc_irq_tim2_ovf:
    case itc_irq_tim2_capcom:
    case itc_irq_tim3_ovf:
        ITC->ISPR4 &= mask;
        ITC->ISPR4 |= new_level;
        break;

    case itc_irq_tim3_capcom:
    case itc_irq_uart_tx:
    case itc_irq_uart_rx:
    case itc_irq_i2c:
        ITC->ISPR5 &= mask;
        ITC->ISPR5 |= new_level;
        break;

    case itc_irq_adc:
    case itc_irq_tim4_ovf:
        ITC->ISPR6 &= mask;
        ITC->ISPR6 |= new_level;
        break;

    case itc_irq_eeprom_eec:
        ITC->ISPR7 &= mask;
        ITC->ISPR7 |= new_level;
        break;

    default:
        break;
    }
}

void set_irq_priority(void)
{
    set_interrupt_priority(itc_irq_uart_rx, itc_priority_level_3);
    set_interrupt_priority(itc_irq_uart_tx, itc_priority_level_3);
    set_interrupt_priority(itc_irq_port_d, itc_priority_level_2);
    set_interrupt_priority(itc_irq_port_c, itc_priority_level_1);
    set_interrupt_priority(itc_irq_tim4_ovf, itc_priority_level_2);
}

void set_interrupt_sensitivity(exti_port port, sensitivity_type type)
{
    switch (port) {
    case exti_port_gpio_a:
        EXTI->CR1 &= (u8)(~EXTI_CR1_PAIS);
        EXTI->CR1 |= (u8)(type);
        break;
    case exti_port_gpio_b:
        EXTI->CR1 &= (u8)(~EXTI_CR1_PBIS);
        EXTI->CR1 |= (u8)((u8)(type) << 2);
        break;
    case exti_port_gpio_c:
        EXTI->CR1 &= (u8)(~EXTI_CR1_PCIS);
        EXTI->CR1 |= (u8)((u8)(type) << 4);
        break;
    case exti_port_gpio_d:
        EXTI->CR1 &= (u8)(~EXTI_CR1_PDIS);
        EXTI->CR1 |= (u8)((u8)(type) << 6);
        break;
    }
}



