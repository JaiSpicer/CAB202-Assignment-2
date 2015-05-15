/*
 * zombies.c
 *
 *  Created on: 9 May 2015
 *      Author: Jai Spicer
 */

#include "graphics.h"
#include "friendly_ports.h"
#include "cpu_speed.h"
#include "byte.h"
#include "sprite.h"

#include "sprite.h"
#include "graphics.h"
#include "friendly_ports.h"

void setup_zombies(
	Sprite zombies[],
	byte *zbitmap[],
	byte width[],
	byte height[]
		);
void draw_zombies ( Sprite * sprites );
void section_selector( int picker );
void setup_device( void );

int randx;
int randy;

void main( void ) {
	setup_device();

	byte bitmap1[] = {
		BYTE( 11100000 ),
		BYTE( 01000000 ),
		BYTE( 10100000 )
	};

	byte *zbitmaps[1] = { bitmap1 };
	byte width[] = {4};
	byte height[] = {3};


#define zombie_count (8)

	Sprite zombies[zombie_count];


	setup_zombies ( zombies, zbitmaps, width, height );

	while (1) {
		clear();
		update_zombies( zombies );
		draw_zombies( zombies );
		refresh();
	}

	refresh();
	return 0;

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

void update_zombies ( Sprite * zombies ) {
	// pick a direction to move in
	for ( int i = 0; i < zombie_count; i++ ) {
		update_one_zombie( zombies + 1);

	}
}

void update_one_zombie ( Sprite * zombie ) {
	zombie->x = zombie->dx;
	zombie->y = zombie->dy;



	if ( zombie->x >= (LCD_X - 1) - zombie->width || zombie->x < 1 ) {
		zombie->dx = 0;
	}

	if ( zombie->y >= (LCD_Y - 1) - zombie->height || zombie->y < 14 ) {
		zombie->dy = 0;
	}
}

void setup_device() {
	CPU_PRESCALE(CPU_8MHz);

	DDRB = ( LED0 | LED1 ) & ~( SW0 | SW1 ); // Output to LEDs, input from switches.
	DDRD = LED2; // Turn on the little yellow LED.

	// Turn everything off to start with
	PORTB = 0x00;
	PORTD = 0x00;

	LCDInitialise(LCD_DEFAULT_CONTRAST);
	clear();


}
