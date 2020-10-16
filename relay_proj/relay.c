/* Jason Paik, last edit 7/22/20
 * Program to control relay based information recieved from a socket */

#include "relay.h"

#include <assert.h>
#include <pigpio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * Function that delays a program by a specified time in seconds
 */

void delay (int num_secs) {
	int mili_secs = (1000000 * num_secs);
	clock_t start_time = clock();
	while (clock() < start_time + mili_secs);
}

/*
 * Function that turns on a specifide relay module
 */

int relay_on (int mod_num) {
	if (gpioInitialise() == PI_INIT_FAILED) {
		printf("Failed to initialise, ensure you are in root mode\n");
		return FAIL;
	}
	switch (mod_num) {
		case 1:
			gpioSetMode(4, PI_OUTPUT);
			gpioWrite(4, 0);
			break;
		case 2:
			gpioSetMode(17, PI_OUTPUT);
			gpioWrite(17, 0);
			break;
		default:
			printf("Invalid relay\n");
			return FAIL;
	}
	gpioTerminate();
	return SUCCESS;
}

/*
 * Function that turns off a specified relay module
 */

int relay_off (int mod_num) {
	if (gpioInitialise() == PI_INIT_FAILED) {
		printf("Failed to initialise, ensure you are in root mode\n");
		return FAIL;
	}
	switch (mod_num) {
		case 1:
			gpioSetMode(4, PI_OUTPUT);
			gpioWrite(4, 1);
			break;
		case 2:
			gpioSetMode(17, PI_OUTPUT);
			gpioWrite(17, 1);
			break;
		default:
			printf("Invalid relay\n");
			return FAIL;
	}
	gpioTerminate();
	return SUCCESS;
}

int relay_state (int mod_num) {
	int to_return = FAIL;
	if (gpioInitialise() == PI_INIT_FAILED) {
		printf("Failed to initialise, ensure you are in root mode\n");
		return FAIL;
	}
	switch (mod_num) {
		case 1:
			to_return = gpioRead(4);
			break;
		case 2: to_return = gpioRead(17);
			break;
		default:
			printf("Invalid relay\n");
			return FAIL;
	}
	gpioTerminate();
	return to_return;
}
