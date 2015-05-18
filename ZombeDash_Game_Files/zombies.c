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

void setup_zombies(
	Sprite zombies[],
	byte *zbitmap[],
	byte width[],
	byte height[]
		);
void draw_zombies ( Sprite * sprites );
void start_zombies ();
void section_selector( int picker );

int randx;
int randy;

#define zombie_count (8)

Sprite zombies[zombie_count];
Sprite * z = &zombies;
byte bitmap1[] = {
		BYTE( 11100000 ),
		BYTE( 01000000 ),
		BYTE( 10100000 )
	};

void start_zombies() {


	byte *zbitmaps[1] = { bitmap1 };
	byte width[] = {4};
	byte height[] = {3};

//	Sprite zombies[zombie_count];


	setup_zombies ( zombies, zbitmaps, width, height );

	draw_zombies ( zombies );

}


void setup_zombies(
	Sprite zombies[],
	byte *zbitmaps[],
	byte width[],
	byte height[]
	) {

	for ( int i = 0; i < 8; i++ ) {
		Sprite * sprite = &zombies[i];

		byte * bitmap = zbitmaps[ i % 1];

		int picker = 1 + rand() % 2; // 1 - 70
		section_selector ( picker );

		init_sprite ( sprite, randx, randy, 4, 3, bitmap );
		sprite->is_visible = 1;
		sprite->dx = 1;
		sprite->dy = 0;


	}
}


void section_selector( int picker ) {
	if ( picker == 1 ) { // Left Section
		randx = (rand()%25)+1; // 1 - 28
		randy = (rand()%30)+14; // 14 - 47
	}
	else if ( picker == 2 ) { // Right Section
		randx = (rand()%30)+51; // 50 - 81
		randy = (rand()%30)+14; // 14 - 47
	}
}

void draw_zombies ( Sprite * sprites ) {
	for ( int i = 0; i < zombie_count; i++ ) {
		draw_sprite ( sprites + i );
	}
}

void zombie_updater() {
	update_zombies( zombies );
	draw_zombies( zombies );
}

void update_zombies ( Sprite * sprites ) {
	// pick a direction to move in
	for ( int i = 0; i < zombie_count; i++ ) {
		update_one_zombie( sprites + 1);

	}
}

void update_one_zombie ( Sprite * zombie ) {
	zombie->x = zombie->dx;
	zombie->y = zombie->dy;

//	if ( zombie->x >= (LCD_X - 1) - zombie->width || zombie->x < 1 ) {
//		zombie->dx = 0;
//	}
//
//	if ( zombie->y >= (LCD_Y - 1) - zombie->height || zombie->y < 14 ) {
//		zombie->dy = 0;
//	}
}
