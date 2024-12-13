/*
 * software_timer.c
 *
 *  Created on: Dec 4, 2024
 *      Author: TruongThien
 */
#include "software_timer.h"

int timeout_flag = 0;
int timeout_counter = 0;
int TIMER_CYCLE = 1;

void setTimer(){
	timeout_counter = TIMEOUT_VALUE / TIMER_CYCLE;
	timeout_flag = 0;
}

void timerRun() {
	if (timeout_counter > 0) {
		timeout_counter--;
	}
	if (timeout_counter <= 0){
		timeout_flag = 1;
	}
}
