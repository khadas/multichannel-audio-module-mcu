// SPDX-License-Identifier: GPL-2.0
#include "main.h"

int main(void)
{
	mcu_init();

	audio_init();

	while (1) {
		if (sys_status == SYS_STATUS_OFF) {
			standby_thread();	// reserve function, not use now.

		} else {
			work_thread();
		}
	}
}


void mcu_init(void)
{
	// Internal 16M clock
	hsi_prescaler_set();
	set_irq_priority();
	init_gpio();
	init_tim4_for_timer();
	init_uart();
	enableInterrupts();

}

void init_vol_gently()
{
	if (sys_vol_data > 0) {
		sys_vol_data_temp = sys_vol_data;
		sys_vol_data = 0;
		sys_vol_init_flag = VOL_INIT_ING;

	} else {
		knob_change = TRUE;
		sys_op_mode = OP_MODE_VOL;
	}
}

void audio_init(void)
{
	SYS_POWER_ON();
	tim4_delay_ms = 700;
	while (tim4_delay_ms) {};

	dac_init();

	// load sys config
	sys_dac_filter = eeprom_read_byte(E2P_ADD_FILTER);
	i2c_write(I2C_DAC1_ADDR, DAC_REG_FILTER, dac_filter[sys_dac_filter-1]);
	i2c_write(I2C_DAC2_ADDR, DAC_REG_FILTER, dac_filter[sys_dac_filter-1]);

	sys_vol_data = eeprom_read_byte(E2P_ADD_VOL);

	init_vol_gently();
}

bool dac_init(void)
{
	u8 i  = 0;
	u8 status = FALSE;

	// Init DAC: input source, vol, THD+N parameter...
	for (i = 0; i < 18; i++) {
		if (i > 12 && i < 17) {
			DAC_REG[i][1] = eeprom_read_byte((E2P_ADD_DAC116 + i - 13));
		}

		status = i2c_write(I2C_DAC1_ADDR, DAC_REG[i][0], DAC_REG[i][1]);
		if (0x01 != status) {
			return FALSE;
		}
	}

	for (i = 0; i < 18; i++) {
		if(i > 12 && i < 17){
			DAC_REG[i][1] = eeprom_read_byte((E2P_ADD_DAC216+i-13));
		}
		status = i2c_write(I2C_DAC2_ADDR, DAC_REG[i][0], DAC_REG[i][1]);
		if(0x01 != status){
			return FALSE;
		}
	}

	dac_filter_init();

	return TRUE;

}

void dac_filter_init(void)
{
	u8 i = 0;
	u8 j = 0;
	u8 temp = 0;

	for (i = 0; i < 144; i++) {
		for (j = 40; j < 45; j++) {
			switch (j) {
			case 40:
				temp = i;
				break;

			case 41:
			case 42:
			case 43:
				if (i < 25) {
					temp = 0;
				}
				if (i > 24 && i < 32) {
					temp = foeffs_stage[i - 25][j - 41];
				}
				if (i > 31 && i < 140) {
					temp = 0;
				}
				if (i > 139 && i < 142) {
					temp=foeffs_stage[i - 133][j - 41];
				}
				if (i > 141) {
					temp = 0;
				}
				break;

			case 44:
				temp = 2;
				break;

			default:
				break;
			}

			i2c_write(I2C_DAC1_ADDR, j, temp);
			i2c_write(I2C_DAC2_ADDR, j, temp);
		}
	}

}

void mqa_rendering_en(void)
{
	i2c_write(I2C_DAC1_ADDR, DAC_REG_FILTER,  0x00);	// LINEAR FAST
	i2c_write(I2C_DAC1_ADDR, DAC_REG_FIR_CFG, 0x05);	// enable custom filter with stage 2 even

	i2c_write(I2C_DAC2_ADDR, DAC_REG_FILTER,  0x00);	// LINEAR FAST
	i2c_write(I2C_DAC2_ADDR, DAC_REG_FIR_CFG, 0x05);	// enable custom filter with stage 2 even
}

void mqa_rendering_disable(void)
{
	i2c_write(I2C_DAC1_ADDR, DAC_REG_FIR_CFG, 0x00);	// enable custom filter with stage 2 even
	i2c_write(I2C_DAC1_ADDR, DAC_REG_FILTER, dac_filter[(sys_dac_filter-1)]);	// Reload DAC Filter

	i2c_write(I2C_DAC2_ADDR, DAC_REG_FIR_CFG, 0x00);	// enable custom filter with stage 2 even
	i2c_write(I2C_DAC2_ADDR, DAC_REG_FILTER, dac_filter[(sys_dac_filter-1)]);	// Reload DAC Filter
}


void sys_volume_ctrl()
{
	i2c_write( I2C_DAC1_ADDR, DAC_REG_VOL_L, VOL_REG[sys_vol_data]);
	i2c_write( I2C_DAC1_ADDR, DAC_REG_VOL_R, VOL_REG[sys_vol_data]);
	i2c_write( I2C_DAC2_ADDR, DAC_REG_VOL_L, VOL_REG[sys_vol_data]);
	i2c_write( I2C_DAC2_ADDR, DAC_REG_VOL_R, VOL_REG[sys_vol_data]);
}


void work_thread(void)
{
	u8 hist_sys_status = sys_status;
	u8 hist_filter_mode = sys_dac_filter;

	while (hist_sys_status == sys_status) {

		switch (sys_op_mode) {
		// volume control get from Tone2 uart cmd
		case OP_MODE_VOL:
			if (knob_change == TRUE) {
				knob_change = FALSE;

				// cancel volume init gradient while Tone2 knob operation.
				sys_vol_init_flag = VOL_INIT_REL_KEY;

				if(sys_vol_data < VOL_STEP_COUNT) {
					sys_volume_ctrl();
					eeprom_write_byte(E2P_ADD_VOL, sys_vol_data);
				}
			}
			break;

		// filter control get from Tone2 uart cmd
		case OP_MODE_FILTER:
			if (hist_filter_mode != sys_dac_filter) {
				hist_filter_mode = sys_dac_filter;
				eeprom_write_byte(E2P_ADD_FILTER, sys_dac_filter);
				i2c_write(I2C_DAC1_ADDR, 0x07, dac_filter[sys_dac_filter-1]);
				i2c_write(I2C_DAC2_ADDR, 0x07, dac_filter[sys_dac_filter-1]);
			}
			break;

		default:
			break;
		}

		// volume init gradient, it can cancel by Tone2 knob operation.
		if ((sys_vol_init_flag > VOL_INIT_REL_KEY) && (sys_vol_change != FALSE)) {
			sys_vol_change = FALSE;
			if (sys_vol_data < VOL_STEP_COUNT) {
				sys_volume_ctrl();
			}
		}
		if (sys_vol_init_flag == VOL_INIT_REL_KEY) {
			sys_vol_init_flag = VOL_INIT_FINISHED;
		}

		// audio fomat change, get from Tone2
		if (uart_send_delay == 1) {
			uart_send_delay = 0;

			if (uart_cmd_temp == UC_DATA) {
				mqa_rendering_disable();

			} else if (uart_cmd_temp == UC_DATA_MQA) {
				mqa_rendering_en();

			}
		}

		// uart cmd respone, get from Tone2
		if(uart_msg_ready == TRUE){
			uart_cmd_respone(uart_data_buff);
			uart_msg_ready = FALSE;
		}
	}//////////////////////////////////////////////////////

}

void standby_thread(void)
{
	SYS_POWER_OFF();

	tim4_delay_ms = 500;
	while (tim4_delay_ms) {};

	sys_key_en = TRUE;

	// ####### Wait For Status Change #####################//
	while (sys_status != SYS_STATUS_PLAY) {

	}

	// Reinit Audio
	audio_init();

}



void eeprom_write_byte(u16 dLocal_Addr,u8 dLocal_Data)
{
	flash_unlock();
	while (flash_get_flag_status() == RESET);

	flash_program_byte(FLASH_DATA_START_PHYSICAL_ADDRESS + dLocal_Addr,dLocal_Data);
	flash_lock();

	return;
}

u8 eeprom_read_byte(u16 dLocal_Addr)
{
	u8 dLocal_1;
	dLocal_1 = flash_read_byte(FLASH_DATA_START_PHYSICAL_ADDRESS + dLocal_Addr);

	return dLocal_1;
}


void uart_cmd_respone(u8 cmd[4])
{
	u8 i = 0;

	// write SN
	if (uart_cmd_sn_flag > 6) {
		for (i = 0; i < 4; i++) {
			eeprom_write_byte((E2P_ADD_SN12 + i), cmd[i]);	// E2P_ADD_SN12(0x10)
			uart_sent_cmd((UC_SN12 + i), cmd[i]);
		}
		uart_cmd_sn_flag = 0;
		return;

	// read SN
	} else if (uart_cmd_sn_flag == 3) {
		for (i = 0; i < 4; i++) {
			cmd[i] = eeprom_read_byte((E2P_ADD_SN12 + i));	// E2P_ADD_SN12(0x10)
			uart_sent_cmd((UC_SN12 + i), cmd[i]);
		}
		uart_cmd_sn_flag = 0;
		return;
	}

	switch (cmd[1]) {
	case UC_VOL:
		if (UD_AVOL_QUERY == cmd[2]) {
			uart_sent_cmd(UC_VOL, (sys_vol_data+1));

		} else if (UD_AVOL_QUERY < cmd[2] && cmd[2] <= UD_AVOL_MAX) {
			sys_vol_data = (cmd[2] - 1);
			sys_op_mode = OP_MODE_VOL;
			knob_change = TRUE;

		} else if (UD_DVOL_UP == cmd[2]) {
			uart_sent_cmd(UC_VOL, UD_DVOL_UP);
		}
		break;

	case UC_FILTER:
		switch (cmd[2]) {
		case UD_FILTER_QUERY:
			uart_sent_cmd(UC_FILTER, sys_dac_filter);
			break;

		case UD_FILTER_A:
		case UD_FILTER_B:
		case UD_FILTER_C:
		case UD_FILTER_D:
		case UD_FILTER_E:
		case UD_FILTER_G:
		case UD_FILTER_H:
			sys_dac_filter = cmd[2];
			sys_op_mode = OP_MODE_FILTER;
			break;

		default:
			break;
		}

		break;

	case UC_DATA:
	case UC_DATA_MQA:
		// delay 1.5s to receive audio format msg, cause xmos will send it serval times, and the last one is right.
		uart_send_delay = UART_SEND_DELAY;
		uart_cmd_temp = cmd[1];
		uart_data_temp = cmd[2];
		break;

	case UC_DAC116:
	case UC_DAC117:
	case UC_DAC118:
	case UC_DAC119:
		eeprom_write_byte((cmd[1] - 0x31), cmd[2]);			// 0x31 = UC_DAC119(0x55) - E2P_ADD_DAC119(0x24)
		i2c_write(I2C_DAC1_ADDR, (cmd[1] - 0x3C), cmd[2]);	// 0x3C = UC_DAC119(0x55) - DAC_REG_THD_C32(0x19)
		break;

	case UC_DAC216:
	case UC_DAC217:
	case UC_DAC218:
	case UC_DAC219:
		eeprom_write_byte((cmd[1] - 0x31), cmd[2]);			// 0x31 = UC_DAC19(0x59) - E2P_ADD_DAC19(0x28)
		i2c_write(I2C_DAC2_ADDR, (cmd[1] - 0x41), cmd[2]);	// 0x41 = UC_DAC19(0x59) - DAC_REG_THD_C32(0x19)
		break;

	case UC_MODULE:
		if (UD_MODULE_QUERY == cmd[2]) {
			uart_sent_cmd(UC_MODULE, UD_MODULE_MUL);
		}
		break;

	case UC_VER_LOCAL:
		uart_sent_cmd(UC_VER_LOCAL, UD_VER_LOCAL);
		break;


	case UC_SN12:
	case UC_SN34:
	case UC_SN56:
	case UC_SN78:
		uart_sent_cmd(cmd[1], eeprom_read_byte((cmd[1] - 0x61)));	// 0x61 = UC_SN78(0x74) - E2P_ADD_SN78(0x13)
		break;

	default:
		break;
	}

}


///////////////////////////////////////////////////////////////////////////////////////////
// interrupt respone
#pragma vector=0x2
__interrupt void TLI_IRQHandler(void)
{

}

#pragma vector=0x3
__interrupt void AWU_IRQHandler(void)
{

}
#pragma vector=0x4
__interrupt void CLK_IRQHandler(void)
{

}

#pragma vector=0x5
__interrupt void EXTI_PORTA_IRQHandler(void)
{

}

#pragma vector=0x6
__interrupt void EXTI_PORTB_IRQHandler(void)
{

}

#pragma vector=0x7
__interrupt void EXTI_PORTC_IRQHandler(void)
{

}

#pragma vector=0x8
__interrupt void EXTI_PORTD_IRQHandler(void)
{

}

#pragma vector=0x9
__interrupt void EXTI_PORTE_IRQHandler(void)
{

}

#pragma vector=0xC
__interrupt void SPI_IRQHandler(void)
{

}

#pragma vector=0xD
__interrupt void TIM1_UPD_OVF_TRG_BRK_IRQHandler(void)
{

}

#pragma vector=0xE
__interrupt void TIM1_CAP_COM_IRQHandler(void)
{

}

#pragma vector=0xF
__interrupt void TIM2_UPD_OVF_BRK_IRQHandler(void)
{

}

#pragma vector=0x10
__interrupt void TIM2_CAP_COM_IRQHandler(void)
{

}

#pragma vector=0x13
__interrupt void UART_TX_IRQHandler(void)
{

}

#pragma vector=0x14
__interrupt void UART_RX_IRQHandler(void)
{
    u8 receive;
	if (uart_get_it_status() != RESET) {
		receive = uart_receive_data8();

		if (uart_msg_ready == FALSE) {

			// General Protocol Match
			if ((receive == UD_START) && (uart_cmd_sn_flag < 3)) {
				uart_cmd_flag = 1;
			}

			if (uart_cmd_flag > 0) {
				uart_data_buff[(uart_cmd_flag - 1)] = receive;
				uart_cmd_flag++;

				if (uart_cmd_flag == 5) {
					if(uart_data_buff[3] == UD_END){
						uart_msg_ready = TRUE;
					}
					uart_cmd_flag = 0;
				}
			}

			// Special SN Protocol Match
			if (uart_cmd_sn_flag > 2) {
				uart_data_buff[uart_cmd_sn_flag - 3] = receive;
				uart_cmd_sn_flag++;
				if (uart_cmd_sn_flag > 6) {
					uart_msg_ready = TRUE;
				}
			} else if (uart_cmd_sn_flag > 1) {
				if (receive == 0xFF) {
					uart_cmd_sn_flag = 3;
				} else if (receive == 0x3D) {
					uart_cmd_sn_flag = 3;
					uart_msg_ready = TRUE;
				}
			} else if (uart_cmd_sn_flag > 0) {
				if(receive == 0x4E){
					uart_cmd_sn_flag = 2;
				}
			} else if (uart_cmd_sn_flag == 0) {
				if (receive == 0x53) {
					uart_cmd_sn_flag = 1;
				}
			}
		}
	}
}

#pragma vector=0x15
__interrupt void I2C_IRQHandler(void)
{

}

#pragma vector=0x18
__interrupt void ADC_IRQHandler(void)
{

}

#pragma vector=0x19
__interrupt void TIM4_UPD_OVF_IRQHandler(void)
{
	tim4_ms_cnt++;

	if (tim4_ms_cnt > 16) {
		tim4_ms_cnt = 0;

		// TIMEER
		if (tim4_delay_ms > 0) {
			tim4_delay_ms--;
		}

		if (uart_send_delay > 1) {
			uart_send_delay--;
		}

		if (sys_vol_init_flag > VOL_INIT_REL_KEY) {
			sys_vol_init_flag++;
			if (sys_vol_init_flag > 250) {
				sys_vol_init_flag = VOL_INIT_ING;
				if (sys_vol_data < sys_vol_data_temp) {
					sys_vol_data++;
					sys_vol_change = TRUE;
				} else {
					sys_vol_init_flag = VOL_INIT_REL_KEY;
					sys_vol_data_temp = 0;
				}
			}
		}

	}

	clear_tim4_pending_bit();
}

#pragma vector=0x1A
__interrupt void EEPROM_EEC_IRQHandler(void)
{

}
///////////////////////////////////////////////////////////////////////////////////////////


