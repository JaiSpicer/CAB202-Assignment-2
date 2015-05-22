/*
 * lives.c
 *
 *  Created on: 9 May 2015
 *      Author: Jai Spicer
 */



// test

#include "lives.h"

int lives = 3; // Initialise lives for the start of game
char l[15];
void lives_setup() {
	draw_string("L:", 2,3);
	sprintf(l, "%d", lives);
	draw_string(l, 11, 3);
}

void update_lives() {
	lives = lives - 1;
}

void reset_lives() {
	lives = 3;
}
