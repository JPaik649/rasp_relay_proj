#ifndef __PINS__
#define __PINS__

#define FAIL (-1)
#define SUCCESS (0)

void delay(int); // Function that creates a delay of n seconds
int relay_on(int); // Function that turns the nth module on
int relay_off(int); // Function that turns the nth module off
int relay_state(int);

#endif
