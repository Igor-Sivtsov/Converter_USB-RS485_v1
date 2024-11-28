#ifndef INC_UART_H_
#define INC_UART_H_

#include "main.h"

void uart_transmit(uint8_t* data, size_t len);
void start_uart_resive();

#endif /* INC_UART_H_ */
