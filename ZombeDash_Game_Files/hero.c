/*
 * hero.c
 *
 *  Created on: 8 May 2015
 *      Author: Jai Spicer
 */
#include <util/delay.h>

#include "sprite.h"
#include "graphics.h"
#include "friendly_ports.h"

#include "hero.h"
#include "zombies.h"
#include "lives.h"

int px = 1;
int py = 0;

Sprite hero;
Sprite * hero_prt = &hero;

byte bitmap_hero[] = {
			BYTE( 11100000 ),
			BYTE( 01000000 ),
			BYTE( 11100000 )
	};

void start_hero() {


	const int hero_width = 3; // Maybe 4
	const int hero_height = 3;

//	Sprite hero;

	init_sprite( &hero, 38,28,hero_width,hero_height, bitmap_hero );
	hero.is_visible = 1;
	hero_prt->is_visible = 1;

	hero.dx = 1;
	hero.dy = 0;

	draw_sprite( &hero );


}

void move_hero( Sprite * hero ) {

	if ( ( hero->dx == 1) && ( pressed ( SW1 ) ) ) { // Right Button, turn right, down
		_delay_ms(100);
		hero->dx = 0;
		hero->dy = 1;
		px = 0;
		py = 1;
	}
	if ( (hero->dx == -1) && ( pressed ( SW1 ) )) { // Right Button, turn right, up
		_delay_ms(100);
		hero->dx = 0;
		hero->dy = -1;
		px = 0;
		py = -1;
	}
	if ( ( hero->dy == 1 ) && ( pressed ( SW1 ) )) { // Right Button, turn right, left
		_delay_ms(100);
		hero->dx = -1;
		hero->dy = 0;
		px = -1;
		py = 0;
	}
	if ( ( hero->dy == -1 ) && ( pressed ( SW1 ) )) { // Right Button, turn right , right
		_delay_ms(100);
		hero->dx = 1;
		hero->dy = 0;
		px = 1;
		py = 0;
	}
	if ( ( hero->dx == 1 ) && ( pressed ( SW0 ) )) { // Left Button, turn left, up
		_delay_ms(100);
		hero->dx = 0;
		hero->dy = -1;
		px = 0;
		py = -1;
	}
	if ( ( hero->dx == -1 ) && ( pressed ( SW0 ) )) { // Left Button, turn left, down
		_delay_ms(100);
		hero->dx = 0;
		hero->dy = 1;
		px = 0;
		py = 1;
	}
	if ( ( hero->dy == 1 ) && ( pressed ( SW0 ) )) { // Left Button, turn left, right
		_delay_ms(100);
		hero->dx = 1;
		hero->dy = 0;
		px = 1;
		py = 0;
	}
	if ( ( hero->dy == -1 ) && ( pressed ( SW0 ) )) { // Left Button, turn left, left
		_delay_ms(100);
		hero->dx = -1;
		hero->dy = 0;
		px = -1;
		py = 0;
	}

	hero->x += hero->dx;
	hero->y += hero->dy;

	if ( hero->x >= LCD_X - hero->width) {
		hero->x -=1;
	}

	if (hero->x < 0 + hero->width - 2) {
		hero ->x +=1;
	}

	if ( hero->y >= LCD_Y - hero->height ) {
		hero->y -=1;
	}

	if ( hero->y < 0 + 13) {
		hero->y +=1;
	}
}



void update_hero() {
	move_hero ( hero_prt );
	draw_sprite ( hero_prt );
}

