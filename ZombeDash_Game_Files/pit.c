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
#include "hero.h"
#include "lives.h"

Sprite pit;
Sprite * pit_prt = &pit;

byte bitmap_pit[] = {
			BYTE( 11111100 ),
			BYTE( 10000100 ),
			BYTE( 10000100 ),
			BYTE( 10000100 ),
			BYTE( 10000100 ),
			BYTE( 11111100 ),
	};

int in_pit = 0;

void start_pit() {


	const int pit_width = 6;
	const int pit_height = 6;

	int rand_x = (rand()%70)+5;;
	int rand_y = (rand()%30)+14;

	init_sprite( &pit, rand_x,rand_y,pit_width,pit_height, bitmap_pit );
	draw_sprite( &pit );
	pit_prt->is_visible = 1;
}

void draw_pit() {
	draw_sprite ( &pit );
}
void pit_collision() {
	if (
			( hero.x > pit_prt->x && hero.y + 1 > pit_prt->y && hero.x < pit_prt->x+5 && hero.y < pit_prt->y+5 ) || // right side
			( hero.x + 1 > pit_prt->x && hero.y + 1 > pit_prt->y && hero.x < pit_prt->x+5 && hero.y < pit_prt->y+5 )
	) {
		in_pit = 1;

	}

}


