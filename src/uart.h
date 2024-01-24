// SPDX-License-Identifier: GPL-2.0
#ifndef __UART_H
#define __UART_H

#include "stm8s.h"

ITStatus uart_get_it_status(void);
void init_uart(void);
u8 uart_receive_data8(void);
void uart_send_data8(u8 Data);
void uart_sent_cmd(u8 cmd, u8 data);

#endif /* __UART_H */

