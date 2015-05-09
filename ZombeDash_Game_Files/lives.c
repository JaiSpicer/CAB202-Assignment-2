/*
 * lives.c
 *
 *  Created on: 9 May 2015
 *      Author: Jai Spicer
 */

#include "lives.h"

void lives_setup() {
	int lives = 3;
	draw_string("Lives:", 2,2);
	draw_string("3", 31,2);
}
