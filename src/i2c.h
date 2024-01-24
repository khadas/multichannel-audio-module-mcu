// SPDX-License-Identifier: GPL-2.0
#include "stm8s.h"

#include "gpio.h"


#define ACK         0
#define NACK        1

#define I2C_SDA_H()         gpio_write_high(GPIOB, gpio_pin_5)
#define I2C_SDA_L()         gpio_write_low(GPIOB, gpio_pin_5)
#define I2C_SCL_H()         gpio_write_high(GPIOB, gpio_pin_4)
#define I2C_SCL_L()         gpio_write_low(GPIOB, gpio_pin_4)
#define I2C_SDA_INPUT()     gpio_read_input_pin(GPIOB,gpio_pin_5)

void i2c_start();
void i2c_stop();
bool i2c_detect(u8 i2c_addr);
u8 i2c_send_byte(u8 data_send);
u8 i2c_receive_byte(u8 ack);
u8 i2c_write(u8 i2c_addr, u8 sub_reg, u8 data);
void delay_us(u16 cnt);
void delay_ms(u16 cnt);
