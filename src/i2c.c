// SPDX-License-Identifier: GPL-2.0
#include "i2c.h"

void i2c_start()
{
	init_gpio_for_i2c();

	I2C_SDA_H();
	delay_us(5);
	I2C_SCL_H();
	delay_us(5);
	I2C_SDA_L();
	delay_us(5);
}

void i2c_stop()
{
	init_i2c_sda_for_output();

	I2C_SDA_L();
	delay_us(2);
	I2C_SCL_L();
	delay_us(2);
	I2C_SCL_H();
	delay_us(2);
	I2C_SDA_H();
	delay_us(2);
}

u8 i2c_send_byte(u8 data_send)
{
    u8 cnt = 0;

	I2C_SCL_L();
	delay_us(2);
	init_i2c_sda_for_output();

	for (cnt = 0; cnt < 8; cnt++) {
		if ((data_send << cnt) & 0x80) {
			I2C_SDA_H();
		} else {
			I2C_SDA_L();
		}

		delay_us(2);
		I2C_SCL_H();
		delay_us(5);
		I2C_SCL_L();
		delay_us(2);
	}

	delay_us(2);
	I2C_SDA_H();
    init_i2c_sda_for_input();
	delay_us(5);
	I2C_SCL_H();
	delay_us(5);


	// ack/nack
	if (I2C_SDA_INPUT() != RESET) {
		I2C_SCL_L();
		delay_us(5);

	} else {
		I2C_SCL_L();
		delay_us(5);
		return ACK;
	}

	return NACK;
}

bool i2c_detect(u8 i2c_addr)
{
    i2c_start();
	delay_us(20);

    if (i2c_send_byte(i2c_addr) == NACK) {
		i2c_stop();
        return FALSE;
    }

	return TRUE;
}

u8 i2c_receive_byte(u8 ack)
{
	u8 data_receive = 0;
	u8 cnt = 0;

	init_i2c_sda_for_input();
	delay_us(5);
	I2C_SCL_L();
	delay_us(5);
	I2C_SDA_H();

	for (cnt = 0; cnt < 8; cnt++) {
		I2C_SCL_H();
		delay_us(5);

		data_receive = data_receive << 1;
		if (I2C_SDA_INPUT() != RESET) {
			data_receive = data_receive + 1;
		}
		I2C_SCL_L();
		delay_us(5);
	}

	init_i2c_sda_for_output();
	delay_us(2);

	if (ack == 0) {
		I2C_SDA_L();

	} else {
		I2C_SDA_H();
	}

	delay_us(2);
	I2C_SCL_H();
	delay_us(2);
	I2C_SCL_L();
	delay_us(2);
	I2C_SDA_H();
	delay_us(2);

	return(data_receive);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
u8 i2c_write(u8 i2c_addr, u8 sub_reg, u8 data)
{
    i2c_start();
	delay_us(20);

    if (i2c_send_byte(i2c_addr) == NACK) {
		i2c_stop();
        return 0;
    }
    delay_ms(1);

    if (i2c_send_byte(sub_reg) == NACK) {
		i2c_stop();
        return 2;
    }
    delay_ms(1);

    if (i2c_send_byte(data) == NACK) {
		i2c_stop();
        return 3;
    }

    i2c_stop();

    return(1);
}

void delay_us(u16 cnt)
{
    u16 count;
	for (count = cnt; count > 0; count--) {
		;
	}
}

void delay_ms(u16 cnt)
{
	u16 i,j;
	for (i = cnt; i > 0; i--) {
		for (j = 276; j > 0; j--) {
			;
		}
	}
}
