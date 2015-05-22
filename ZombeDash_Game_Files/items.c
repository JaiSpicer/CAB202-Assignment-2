/*
 * items.c
 *
 *  Created on: 15 May 2015
 *      Author: Jai Spicer
 */
#include "graphics.h"
#include "sprite.h"
#include "friendly_ports.h"
#include "hero.h"

#include "score.h"
#include "pit.h"

int sword_pickup = 0;
int grenades_pickup = 0;
int grenade_drop = 0;

Sprite sword;
Sprite *sword_prt = &sword;

byte bitmap_sword_right[] = {
		BYTE( 00010000 ),
		BYTE( 10100000 ),
		BYTE( 01000000 ),
		BYTE( 10100000 ),
};
byte bitmap_sword_left[] = {
		BYTE( 10000000 ),
		BYTE( 01010000 ),
		BYTE( 00100000 ),
		BYTE( 01010000 ),
};
byte bitmap_sword_bottom[] = {
		BYTE( 01000000 ),
		BYTE( 11100000 ),
		BYTE( 01000000 ),
		BYTE( 01000000 ),
};
byte bitmap_sword_top[] = {
		BYTE( 01000000 ),
		BYTE( 01000000 ),
		BYTE( 11100000 ),
		BYTE( 01000000 ),
};
byte bitmap_sword[] = {
		BYTE( 00010000 ),
		BYTE( 10100000 ),
		BYTE( 01000000 ),
		BYTE( 10100000 ),
};

Sprite grenades;
Sprite *grenades_prt = &grenades;

Sprite bomb;
Sprite *bomb_prt = &bomb;

byte bitmap_grenades[] = {
			BYTE( 01100000 ),
			BYTE( 11110000 ),
			BYTE( 10010000 ),
			BYTE( 11110000 ),
	};
//void sword_dir() {
//	if ( hero_d == 1 ) {
//		bitmap_sword = bitmap_sword_top;
//	}
//	if ( hero_d == 2 ) {
//		bitmap_sword = bitmap_sword_right;
//	}
//	if ( hero_d == 3 ) {
//		bitmap_sword = bitmap_sword_bottom;
//	}
//	if ( hero_d == 4 ) {
//		bitmap_sword = bitmap_sword_left;
//	}
//}

void sword_setup() {
	sword_pickup = 0;

	const int sword_width = 4;
	const int sword_height = 4;

	int rand_x = (rand()%70)+5;;
	int rand_y = (rand()%30)+14;

	init_sprite( &sword, rand_x,rand_y,sword_width,sword_height, bitmap_sword );
	sword.is_visible = 1;
	sword_prt->is_visible = 1;
	draw_sprite( &sword );
}

void sword_pickup_title() {
	// Draw the sword into the infromation bar
	byte bitmap_sword_tool[] = {
			BYTE( 00000011 ),
			BYTE( 00000011 ),
			BYTE( 11001100 ),
			BYTE( 11001100 ),
			BYTE( 00110000 ),
			BYTE( 00110000 ),
			BYTE( 11001100 ),
			BYTE( 11001100 ),
	};

	const int sword_tool_width = 8;
	const int sword_tool_height = 8;

	Sprite sword_tool;

	init_sprite( &sword_tool, 49, 2, sword_tool_width, sword_tool_height, bitmap_sword_tool);

	draw_sprite( &sword_tool );

}

void draw_sword() {
	if ( sword_pickup == 1 ) {
		sword_prt->x = hero_prt->x + 2;
		sword_prt->y = hero_prt->y;
	}
	draw_sprite( sword_prt );
	if (sword_pickup == 1) {
		sword_pickup_title();
		kill_zombies();
	}
}

void pickup_sword() {
	if (
			(hero.x > sword_prt->x && hero.y > sword_prt->y && hero.x < sword_prt->x + 4 && hero.y < sword_prt->y + 4 )||
			( hero.x + 2 > sword_prt->x && hero.y + 2 > sword_prt->y  && hero.x + 2 < sword_prt->x + 4 && hero.y + 2 < sword_prt->y + 4)
			) {
		sword_pickup =1;
		score = score + 3;
	}
}

int grenade_count = 3;
char g[1];

void grenades_setup() {
	const int grenades_width = 4;
	const int grenades_height = 4;

	init_sprite( &grenades, 70,38,grenades_width,grenades_height, bitmap_grenades );
	grenades.is_visible = 1;
	grenades_prt->is_visible = 1;
	draw_sprite( &grenades );

}

void grenades_pickup_title() {
	// Draw the grenades into the infromation bar
	byte bitmap_grenades_tool[] = {
			BYTE( 00111100 ),
			BYTE( 00111100 ),
			BYTE( 11111111 ),
			BYTE( 11111111 ),
			BYTE( 11000011 ),
			BYTE( 11000011 ),
			BYTE( 11111111 ),
			BYTE( 11111111 ),
	};

	const int grenades_tool_width = 8;
	const int grenades_tool_height = 8;

	Sprite grenades_tool;

	init_sprite( &grenades_tool, 59, 2, grenades_tool_width, grenades_tool_height, bitmap_grenades_tool);
	draw_sprite( &grenades_tool );

	sprintf(g, "%d", grenade_count);
	draw_string(g, 68, 3);

}

void pickup_granades() {
	if (
			( hero.x > grenades_prt->x && hero.y > grenades_prt->y && hero.x < grenades_prt->x + 4 && hero.y < grenades_prt->y + 4 )||
			( hero.x + 2 > grenades_prt->x && hero.y + 2 > grenades_prt->y  && hero.x + 2 < grenades_prt->x + 4 && hero.y + 2 < grenades_prt->y + 4)
				) {
		grenades_pickup = 1;
		grenades_prt->x = 90;
		grenades_prt->y = 50;
	}
}

void bang_setup() {
	init_sprite( &bomb, -10,-10,4,4, bitmap_grenades );
	bomb.is_visible = 1;
	grenades_prt->is_visible = 1;
	draw_sprite( &bomb );
}

void draw_granades() {
	if ( grenades_pickup == 1 && grenade_count > 0) {
		grenades_pickup_title();
		draw_sprite(grenades_prt);
	}
	if ( grenade_drop ) {
		draw_sprite (bomb_prt );
	}
	else {
		draw_sprite(grenades_prt);
	}
}

void granade_use() {
	if ( in_pit == 0 && grenades_pickup == 1 &&  grenade_count > 0) {
		if ( pressed( SW0 ) && pressed( SW1 ) ) {
			grenade_count = grenade_count - 1;
			bomb_prt->x = hero_prt->x;
			bomb_prt->y = hero_prt->y;
			grenade_drop = 1;

		}

	}
}

