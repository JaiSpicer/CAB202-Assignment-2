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
#include "pit.h"

int hero_d;

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
void update_checker() {
	if ( in_pit == 1 ) {
		pit_hero( hero_prt );
	}
	else {
		move_hero( hero_prt );
	}
}

void pit_hero ( Sprite * hero ) {
	hero->x += hero->dx;
	hero->y += hero->dy;

	if ( ( pressed( SW0 ) ) && ( pressed( SW1 ) )) {
		hero->x -=1;
		hero->x = hero->x - 6;
		in_pit = 0;

	}

	if ( hero->x > pit.x + 5 - hero->width) {
		hero->x -=1;
	}

	if (hero->x < pit.x + hero->width - 2) {
		hero ->x +=1;
	}

	if ( hero->y >= pit.y + 5 - hero->height ) {
		hero->y -=1;
	}

	if ( hero->y < pit.y ) {
		hero->y +=1;
	}
}

void move_hero( Sprite * hero ) {

	if ( ( hero->dx == 1) && ( pressed ( SW1 ) ) ) { // Right Button, turn right, down
		_delay_ms(100);
		hero->dx = 0;
		hero->dy = 1;
		hero_d = 3;
	}
	if ( (hero->dx == -1) && ( pressed ( SW1 ) )) { // Right Button, turn right, up
		_delay_ms(100);
		hero->dx = 0;
		hero->dy = -1;
		hero_d = 1;
	}
	if ( ( hero->dy == 1 ) && ( pressed ( SW1 ) )) { // Right Button, turn right, left
		_delay_ms(100);
		hero->dx = -1;
		hero->dy = 0;
		hero_d = 4;
	}
	if ( ( hero->dy == -1 ) && ( pressed ( SW1 ) )) { // Right Button, turn right , right
		_delay_ms(100);
		hero->dx = 1;
		hero->dy = 0;
		hero_d = 2;
	}
	if ( ( hero->dx == 1 ) && ( pressed ( SW0 ) )) { // Left Button, turn left, up
		_delay_ms(100);
		hero->dx = 0;
		hero->dy = -1;
		hero_d = 1;
	}
	if ( ( hero->dx == -1 ) && ( pressed ( SW0 ) )) { // Left Button, turn left, down
		_delay_ms(100);
		hero->dx = 0;
		hero->dy = 1;
		hero_d = 3;
	}
	if ( ( hero->dy == 1 ) && ( pressed ( SW0 ) )) { // Left Button, turn left, right
		_delay_ms(100);
		hero->dx = 1;
		hero->dy = 0;
		hero_d = 2;
	}
	if ( ( hero->dy == -1 ) && ( pressed ( SW0 ) )) { // Left Button, turn left, left
		_delay_ms(100);
		hero->dx = -1;
		hero->dy = 0;
		hero_d = 4;
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
//	move_hero ( hero_prt );
	update_checker();
	draw_sprite ( hero_prt );
}

