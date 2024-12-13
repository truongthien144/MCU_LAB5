/*
 * software_timer.h
 *
 *  Created on: Dec 4, 2024
 *      Author: TruongThien
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "main.h"
#define TIMEOUT_VALUE 300

extern int timeout_flag;
extern int timeout_counter;
void setTimer();
void timerRun();


#endif /* INC_SOFTWARE_TIMER_H_ */
