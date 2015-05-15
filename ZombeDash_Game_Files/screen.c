/*
 * screen.c
 *
 *  Created on: 9 May 2015
 *      Author: Jai Spicer
 */

#include "screen.h"

void screen_lines() {
	draw_line(0,0,0,47); // Left Line
	draw_line(83,0,83,47); // Right Line
	draw_line(0,0,84,0); // Top Line
	draw_line(0,47,83,47); // Bottom Line
	draw_line(0,12,83,12); // Score area

	//zombie spawn debug
	draw_line(28,18,51,18);
	draw_line(28,41,51,41);
	draw_line(28,18,28,41);
	draw_line(51,18,51,41);
}


