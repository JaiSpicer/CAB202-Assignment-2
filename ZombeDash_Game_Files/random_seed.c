/*
 * random_seed.c
 *
 *  Created on: 20 May 2015
 *      Author: Reflectin88
 */

#include "friendly_ports.h"

void random_seed( void );

void random_seed() {
	unsigned int seed = 0;
	while (!(PINB & 3 )) {
	seed++;
	}
	// Seed the random number generator
	srand(seed);
}
