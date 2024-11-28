#include "uart.h"

void start_uart_resive()
{
	TX_EN_GPIO_Port->BSRR = TX_EN_Pin << 16;

	// Включение прерывания по приходу данных
	// Включение прерывания по окончанию приема
	// Включение приема

	USART3->CR1 |= USART_CR1_RXNEIE | USART_CR1_IDLEIE | USART_CR1_RE;
}

void uart_transmit(uint8_t* data, size_t len)
{
	USART3->CR1 &= ~USART_CR1_RE; 						// Выключение приема
	GPIOA->BSRR = TX_EN_Pin;							// Перевод трансивера в режим передачи
	USART3->CR1 |= USART_CR1_TE;						// Включение передачи

	for(int i = 0; i < len; i++)
	{
	    while(!(USART3->ISR & USART_ISR_TXE));
		USART3->RDR = data[i];
	}

	while(!(USART3->ISR & USART_ISR_TC));				// Ожидание окончания передачи

	USART3->CR1 &= ~USART_CR1_TE; 						// Выключение передачи
	USART3->ISR &= ~USART_ISR_TC;						// Сброс флага окончания передачи

	TX_EN_GPIO_Port->BSRR = TX_EN_Pin << 16;			// Перевод трансивера в режим приема
	USART3->CR1 |= USART_CR1_RE; 						// Включение приема
}
