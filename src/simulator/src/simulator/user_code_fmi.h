/*
 * user_code_fmi.h
 *
 *  Created on: May 9, 2017
 *      Author: jmgauthier
 */

#ifndef SIMULATOR_USER_CODE_FMI_H_
#define SIMULATOR_USER_CODE_FMI_H_

#include "um_threads.h"

void user_thread_fmi();
void initClock();
abs_time shift(int second, long nanosecond);

#endif /* SIMULATOR_USER_CODE_FMI_H_ */
