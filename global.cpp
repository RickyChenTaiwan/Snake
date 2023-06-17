#include <iostream>
#include "global.h"

int getFoodType() {
	//set random seed, usually use time as seed.
	srand(time(NULL)); //if pass NULL, it just ignore it and merely return a new time_t object that represents a current time
	int val = (rand() % 3) + 1;
	return val;
}