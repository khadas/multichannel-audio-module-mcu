// SPDX-License-Identifier: GPL-2.0
#include "uart.h"

void init_uart(void)
{
    (void)UART->SR;
    (void)UART->DR;

    UART->BRR2 = UART_BRR2_RESET_VALUE;
    UART->BRR1 = UART_BRR1_RESET_VALUE;
    UART->CR1 = UART_CR1_RESET_VALUE;
    UART->CR2 = UART_CR2_RESET_VALUE;
    UART->CR3 = UART_CR3_RESET_VALUE;
    UART->CR4 = UART_CR4_RESET_VALUE;
    UART->CR5 = UART_CR5_RESET_VALUE;
    UART->GTR = UART_GTR_RESET_VALUE;
    UART->PSCR = UART_PSCR_RESET_VALUE;

    // baud rate
    UART->BRR2 = 0x0A;
    UART->BRR1 = 0x08;

    UART->CR3 |= (u8)((u8)0x80 & (u8)(UART_CR3_CPOL | UART_CR3_CPHA | UART_CR3_LBCL));  //uart_sync_mode_clock_disable
#if 0
    UART->CR2 |= 0x0E;
#else
    UART->CR2 |= (u8)(UART_CR2_TEN | UART_CR2_REN); // tx&rx enable
    UART->CR2 |= 0x0A;  // uart int

    UART->CR2 |= (1 <<0x05 );   // can not remove, run too fast will not effect

#endif
    UART->CR1 &= (u8)(~UART_CR1_UARTD);
}


u8 uart_receive_data8(void)
{
    return ((u8)UART->DR);
}

void uart_send_data8(u8 Data)
{
    UART->DR = Data;
    while ((UART->SR & 0x80) == 0x00);
}


ITStatus uart_get_it_status()
{
#if 0
    if(((UART->SR & 0x0A) != 0x00) && (UART->CR2 & 0x0A)) {
        return SET;
    }else{
        return RESET;
    }
#else
    u8 itpos = 0;
    itpos = (1 << 0x05);

    if(((UART->SR & itpos) != (u8)0x00) && 0x0A) {
        return SET;
    }else{
        return RESET;
    }

#endif
}

/*
khadas uart protocol:
* 4 byte [protocol start | cmd | data |protocol end]
*

*/
#define UD_START    0x4B    // 'K'
#define UD_END		0x73    // 'S'
void uart_sent_cmd(u8 cmd, u8 data)
{
	uart_send_data8(UD_START);
	uart_send_data8(cmd);
	uart_send_data8(data);
	uart_send_data8(UD_END);
}


