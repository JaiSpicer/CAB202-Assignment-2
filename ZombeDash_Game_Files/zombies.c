/*
 * zombies.c
 *
 *  Created on: 9 May 2015
 *      Author: Jai Spicer
 */

#include "sprite.h"
#include "graphics.h"
#include "friendly_ports.h"

#include "zombies.h"

void setup_zombies( Sprite zombies[], byte width, byte height, byte *bitmaps[] );
void draw_zombies( Sprite * zombies );

void zombies_start() {
	byte bitmap_zombies[] = {
			BYTE( 11100000 ),
			BYTE( 01000000 ),
			BYTE( 10100000 )
	};

	const int zombies_width = 8;
	const int zombies_height = 3;

#define zombie_count (8)

	Sprite zombies[zombie_count];

	setup_zombies ( zombies, zombies_width, zombies_height, bitmap_zombies );
	draw_zombies ( zombies );

	refresh();
}

void setup_zombies( Sprite zombies[], byte width, byte height, byte *bitmaps[]) {
	for (int i = 0; i < zombie_count; i++ ) {
		Sprite * sprite = &zombies[i];

		init_sprite( sprite, 20,20, 8, 3, zombies);


		sprite->dx = 1;
		sprite->dy = 0;
	}
}

void draw_zombies( Sprite * zombies ) {
	for ( int i = 0; i < zombie_count; i++ ) {
		draw_sprite( zombies + i );
	}
}
