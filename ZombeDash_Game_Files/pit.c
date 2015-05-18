/*
 * pit.c
 *
 *  Created on: 15 May 2015
 *      Author: Jai Spicer
 */

#include "sprite.h"
#include "graphics.h"
#include "friendly_ports.h"

#include "pit.h"

Sprite pit;
Sprite * pit_prt = &pit;

void start_pit() {
	byte bitmap_pit[] = {
			BYTE( 11111100 ),
			BYTE( 10000100 ),
			BYTE( 10000100 ),
			BYTE( 10000100 ),
			BYTE( 10000100 ),
			BYTE( 11111100 ),
	};

	const int pit_width = 6; // Maybe 4
	const int pit_height = 6;


	init_sprite( &pit, 20,28,pit_width,pit_height, bitmap_pit );

	draw_sprite( &pit );
}


