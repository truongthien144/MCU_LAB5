/*
 * uart.c
 *
 *  Created on: Dec 4, 2024
 *      Author: TruongThien
 */
#include "uart.h"
#include "software_timer.h"

uint8_t mode = 0;
uint8_t mode1_code[] = "!RST#";
uint8_t mode2_code[] = "!OK#";


uint8_t temp = 0;
uint8_t buffer [MAX_BUFFER_SIZE];
uint8_t index_buffer = 0;
uint8_t buffer_flag = 0;


char str[30];
uint32_t ADC_value = 0;


void clear_buffer(){
	for (int i = 0; i < MAX_BUFFER_SIZE; i++){
		buffer[i] = 0;
	}
	index_buffer = 0;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == USART2){
		if (temp == '!'){
			clear_buffer();
		}
		buffer[index_buffer++] = temp ;
		if( index_buffer == 30){
			index_buffer = 0;
		}
		buffer_flag = 1;
		timeout_counter = TIMEOUT_VALUE; //Do not print out value while receiving data
		HAL_UART_Receive_IT (& huart2 , & temp , 1) ;
	}
}


void command_parser_fsm(){
	for (int i = 0; i < sizeof(mode1_code); i++){
		if (buffer[i] != mode1_code[i]){ //escape if not in this case
			break;
		}
		if (mode1_code[i] == '#'){ //Change stage if enter true command
			mode = 1;
			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 0); //Turn on
			return;
		}
	}
	for (int i = 0; i < sizeof(mode2_code); i++){
		if (buffer[i] != mode2_code[i]){//escape if not in this case
			break;
		}
		if (mode2_code[i] == '#'){	//Change stage if enter true command
			mode = 2;
			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 1); //Turn off
			return;
		}
	}
}

void uart_communication_fsm(){
	if (mode != 1){ //Escape if not in this case
		return;
	}
	if (timeout_flag == 1){
		ADC_value = HAL_ADC_GetValue(&hadc1);
		int len = sprintf(str, "\r!ADC=%ld#\r\n", ADC_value);
		HAL_UART_Transmit(&huart2, (uint8_t *)str, len, 50);
		setTimer(TIMEOUT_VALUE);
	}

}
