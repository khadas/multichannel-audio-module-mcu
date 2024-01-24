// SPDX-License-Identifier: GPL-2.0
#ifndef __GPIO_H
#define __GPIO_H

#include "stm8s.h"
#include "int.h"


typedef enum
{
    gpio_mode_in_fl_no_it      = (u8)0x00,  // Input floating, no external interrupt
    gpio_mode_in_pu_no_it      = (u8)0x40,  // Input pull-up, no external interrupt
    gpio_mode_in_fl_it         = (u8)0x20,  // Input floating, external interrupt
    gpio_mode_in_pu_it         = (u8)0x60,  // Input pull-up, external interrupt
    gpio_mode_out_od_low_fast  = (u8)0xA0,  // Output open-drain, low level, 10MHz
    gpio_mode_out_pp_low_fast  = (u8)0xE0,  // Output push-pull, low level, 10MHz
    gpio_mode_out_od_low_slow  = (u8)0x80,  // Output open-drain, low level, 2MHz
    gpio_mode_out_pp_low_slow  = (u8)0xC0,  // Output push-pull, low level, 2MHz
    gpio_mode_out_od_hiz_fast  = (u8)0xB0,  // Output open-drain, high-impedance level,10MHz
    gpio_mode_out_pp_high_fast = (u8)0xF0,  // Output push-pull, high level, 10MHz
    gpio_mode_out_od_hiz_slow  = (u8)0x90,  // Output open-drain, high-impedance level, 2MHz
    gpio_mode_out_pp_high_slow = (u8)0xD0   // Output push-pull, high level, 2MHz
} gpio_mode;

typedef enum
{
    gpio_pin_0    = ((u8)0x01),
    gpio_pin_1    = ((u8)0x02),
    gpio_pin_2    = ((u8)0x04),
    gpio_pin_3    = ((u8)0x08),
    gpio_pin_4    = ((u8)0x10),
    gpio_pin_5    = ((u8)0x20),
    gpio_pin_6    = ((u8)0x40),
    gpio_pin_7    = ((u8)0x80),
    gpio_pin_lnib = ((u8)0x0F),
    gpio_pin_hnib = ((u8)0xF0),
    gpio_pin_all  = ((u8)0xFF)
} gpio_pin;


void gpio_deinit(gpio_reg* GPIOx);
void gpio_init(gpio_reg* GPIOx, gpio_pin pin, gpio_mode mode);
void gpio_write_high(gpio_reg* GPIOx, gpio_pin pin);
void gpio_write_low(gpio_reg* GPIOx, gpio_pin pin);
BitStatus gpio_read_input_pin(gpio_reg* GPIOx, gpio_pin pin);

void init_gpio(void);
void init_gpio_for_i2c(void);
void init_i2c_sda_for_output(void);
void init_i2c_sda_for_input(void);

#endif /* __GPIO_H */

