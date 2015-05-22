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
#include "score.h"
#include "hero.h"
#include "lives.h"
#include "game_set.h"
#include "pit.h"
#include "items.h"

int dead_zombies = 0;

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

		int picker = 1 + rand() % 2;
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
	update_zombies( z );
	draw_zombies( z );
}

void zombie_drawer() {
	draw_zombies( z );
}

void update_zombies ( Sprite * sprites ) {
	// pick a direction to move in
	for ( int i = 0; i < zombie_count; i++ ) {
		int change = rand()%100;
		if ( change > 95 ) {
			if ( sprites[i].dy > 0 ) {
				sprites[i].dx = -1;
				sprites[i].dy = 0;
			}
			else if( sprites[i].dy < 0 ) {
				sprites[i].dx = 1;
				sprites[i].dy = 0;
			}
			else if ( sprites[i].dx > 0 ) {
				sprites[i].dx = 0;
				sprites[i].dy = 1;
			}
			else if( sprites[i].dx < 0) {
				sprites[i].dx = 0;
				sprites[i].dy = -1;
			}
		}
		if( change < 5 ) {
			if( sprites[i].dy > 0) {
					sprites[i].dx = 1;
					sprites[i].dy = 0;
			}
			else if( sprites[i].dy < 0 ) {
					sprites[i].dx = -1;
					sprites[i].dy = 0;
			}
			else if( sprites[i].dx > 0){
					sprites[i].dx = 0;
					sprites[i].dy = -1;
			}
			else if ( sprites[i].dx < 0){
				sprites[i].dx = 0;
				sprites[i].dy = 1;
			}
		}
		if ( (sprites[i].x >= pit_prt->x) && (sprites[i].x <= pit_prt->x + 5 ) && (sprites[i].y >= pit_prt->y) && (sprites[i].y <= pit_prt->y +5)) {
			sprites[i].dx = 0;
			sprites[i].dy = 0;
			sprites[i].x = pit_prt->x + 1;
			sprites[i].y = pit_prt->y + 1;
		}
		if ( (sprites[i].x >= sword_prt->x) && (sprites[i].x <= sword_prt->x + 4 ) && (sprites[i].y >= sword_prt->y) && (sprites[i].y <= sword_prt->y +4)) {
			sprites[i].dx = 0;
			sprites[i].dy = 0;
			sprites[i].x = -5;
			sprites[i].y = -5;
			sprites[i].is_visible = 0;
			score = score + 2;
			dead_zombies = dead_zombies + 1;


				}
		if ( sprites[i].is_visible == 1) {
			sprites[i].x += sprites[i].dx;
			sprites[i].y += sprites[i].dy;
		}


		if ( sprites[i].x >= LCD_X - sprites[i].width) {
			sprites[i].x -=1;
		}

		if (sprites[i].x < 0 + sprites[i].width - 2) {
			sprites[i].x +=1;
		}

		if ( sprites[i].y >= LCD_Y - sprites[i].height ) {
			sprites[i].y -=1;
		}

		if ( sprites[i].y < 0 + 13) {
			sprites[i].y +=1;
		}

	}
}

void check_zombie() {
	zombies_collission ( z );
	kill_zombies( z );
}

void zombies_collission ( Sprite * zs ) {
	for ( int i = 0; i < zombie_count; i++ ) {
		zombie_collision( zs + i );
	}
}

void zombie_collision( Sprite * z) {
	if (
			( hero.x > z->x && hero.y > z->y && hero.x < z->x + 3 && hero.y < z->y + 3 ) ||
			( hero.x + 1 > z->x && hero.y + 1 > z->y && hero.x + 1 < z->x + 3 && hero.y + 1 < z->y + 3 )  ||
			( hero.x + 2 > z->x && hero.y + 2 > z->y && hero.x + 2 < z->x + 3 && hero.y + 2 < z->y + 3 )
			) {
		lives = lives - 1;
		if ( lives > 0 ){
			hero_die();
		}
		else {
			clear();
		}

	}
}

void kill_zombies( Sprite * zombies ) {
	for ( int i = 0; i < zombie_count; i++ ) {
		kill_zombie( zombies + i );
	}
}

void kill_zombie( Sprite * zombie ) {
	if ( zombie->x < sword_prt->x && zombie->y < sword_prt->y && zombie->y > sword_prt->y + 3) {
		init_sprite ( zombie, -10, -10, 4, 3, bitmap1 );
	}
}

void update_one_zombie_pit ( Sprite * zombie ) {
	zombie->x += zombie->dx;
	zombie->y += zombie->dy;

	if ( zombie->x > pit.x + 5 - zombie->width) {
		zombie->x -=1;
	}

	if (zombie->x < pit.x + zombie->width - 2) {
		zombie ->x +=1;
	}

	if ( zombie->y >= pit.y + 5 - zombie->height ) {
		zombie->y -=1;
	}

	if ( zombie->y < pit.y ) {
		zombie->y +=1;
	}
}

