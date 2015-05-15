/*
 * score.c
 *
 *  Created on: 9 May 2015
 *      Author: Reflectin88
 */

#include "score.h"

int score = 0;
char s[15];
void score_setup() {
//	score = scoretotal;


	draw_string("S:", 18,3);
	sprintf(s, "%d", score);
	draw_string(s, 27, 3);
}

void update_score_time() {
	score = score + 1;
}
