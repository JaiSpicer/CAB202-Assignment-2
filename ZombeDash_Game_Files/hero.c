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

void start_hero() {
	byte bitmap_hero[] = {
			BYTE( 1110000 ),
			BYTE( 0100000 ),
			BYTE( 1110000 )
	};

	const int hero_width = 4;
	const int hero_height = 3;

	Sprite hero;

	init_sprite( &hero, 38,28,hero_width,hero_height, bitmap_hero );
	hero.dx = 1;
	hero.dy = 0;

	draw_sprite( &hero );

	while (1) {
		clear();
		screen_lines();
    	lives_setup();
		score_setup();
		zombies_start();
		move_hero( &hero );
		draw_sprite (&hero );
		refresh();
		_delay_ms( 100 );
	}

}

void move_hero( Sprite * hero ) {
	int px = 1;
	int py = 0;

	hero->x += hero->dx;
	hero->y += hero->dy;

	if ( pressed ( SW1 ) ) {
		if ( ( px = 1) ) {
			hero->dx = 0;
			hero->dy = 1;
			px = 0;
			py = 1;
		}
		else if ( (px = -1) ) {
			hero->dx = 0;
			hero->dy = -1;
			px = 0;
			py = -1;
		}
		else if ( ( py = 1 ) ) {
			hero->dx = -1;
			hero->dy = 0;
			px = -1;
			py = 0;
		}
		else if ( ( py = -1 ) ) {
			hero->dx = 1;
			hero->dy = 0;
			px = 1;
			py = 0;
		}
	}

	if ( pressed ( SW0 ) ) {
		if ( ( px = 1 ) ) {
			hero->dx = 0;
			hero->dy = -1;
			px = 0;
			py = -1;
		}
		else if ( ( px = -1 ) ) {
			hero->dx = 0;
			hero->dy = 1;
			px = 0;
			py = 1;
		}
		else if ( ( py = 1 ) ) {
			hero->dx = 1;
			hero->dy = 0;
			px = 1;
			py = 0;
		}
		else if ( ( py = -1 ) ) {
			hero->dx = -1;
			hero->dy = 0;
			px = -1;
			py = 0;
		}
	}

	if ( hero->x >= (LCD_X - 1) - hero->width || hero->x < 1 ) {
		hero->dx = 0;
	}

	if ( hero->y >= (LCD_Y - 1) - hero->height || hero->y < 14 ) {
		hero->dy = 0;
	}

}

//void turn_hero() {
//
//}
