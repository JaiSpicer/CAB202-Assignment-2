/*
 * items.c
 *
 *  Created on: 15 May 2015
 *      Author: Jai Spicer
 */
#include "graphics.h"
#include "sprite.h"
#include "friendly_ports.h"

#include "score.h"

void sword_setup() {
	byte bitmap_sword[] = {
			BYTE( 00010000 ),
			BYTE( 10100000 ),
			BYTE( 01000000 ),
			BYTE( 10100000 ),
	};

	const int sword_width = 4;
	const int sword_height = 4;

	Sprite sword;

	init_sprite( &sword, 70,28,sword_width,sword_height, bitmap_sword );

	draw_sprite( &sword );
}

void swor_pickup_bonus() {
	// Update the score each update_score_time is + 1 to score
	update_score_time();
	update_score_time();
	update_score_time();
}

void sword_pickup() {
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

void sword_use() {
	update_score_time();
}


int grenades = 3;
char g[15];

void grenades_setup() {
	byte bitmap_grenades[] = {
			BYTE( 01100000 ),
			BYTE( 11110000 ),
			BYTE( 10010000 ),
			BYTE( 11110000 ),
	};

	const int grenades_width = 4;
	const int grenades_height = 4;

	Sprite grenades;

	init_sprite( &grenades, 70,38,grenades_width,grenades_height, bitmap_grenades );

	draw_sprite( &grenades );
}

void grenades_pickup() {
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

	sprintf(g, "%d", grenades);
	draw_string(g, 68, 3);

}

void grenades_use() {
	grenades = grenades - 1;

}
