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

#include "start_screen.h"
#include "screen.h"
#include "lives.h"
#include "score.h"
#include "hero.h"
#include "zombies.h"
#include "pit.h"
#include "items.h"

int px = 1;
int py = 0;

void start_hero() {
	byte bitmap_hero[] = {
			BYTE( 11100000 ),
			BYTE( 01000000 ),
			BYTE( 11100000 )
	};

	const int hero_width = 3; // Maybe 4
	const int hero_height = 3;

	Sprite hero;

	init_sprite( &hero, 38,28,hero_width,hero_height, bitmap_hero );
	hero.dx = 1;
	hero.dy = 0;

	draw_sprite( &hero );
	int zombie_update = 0;
	int score_update = 0;
	while (1) {
		clear();
		screen_lines();
    	lives_setup();
    	score_setup();

//    	start_pit();
//    	sword_setup();
//    	grenades_setup();

		move_hero( &hero );
		draw_sprite (&hero );
		if ( zombie_update == 10 ) {
			new_zombies_pos();
//			start_zombies();
			zombie_update = 0;
		}
		if ( score_update == 50 ) {
			update_score_time();
			score_update = 0;
		}
		refresh();
		zombie_update++;
		score_update++;
		_delay_ms( 100 );
	}

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

	if ( hero->x >= (LCD_X - 1) - hero->width || hero->x < 2 ) {
		hero->dx = 0; // each ege
	}

	if ( hero->y >= (LCD_Y - 1) - hero->height || hero->y < 14 ) {
		hero->dy = 0;
	}

}

//void turn_hero() {
//
//}
