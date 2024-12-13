/*
 * uart.h
 *
 *  Created on: Dec 4, 2024
 *      Author: TruongThien
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "main.h"
#include "stdio.h"

#define MAX_BUFFER_SIZE 30

extern uint8_t temp;
extern uint8_t buffer_flag;

extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim2;
extern UART_HandleTypeDef huart2;

void clear_buffer();
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void command_parser_fsm ();
void uart_communication_fsm ();

#endif /* INC_UART_H_ */
