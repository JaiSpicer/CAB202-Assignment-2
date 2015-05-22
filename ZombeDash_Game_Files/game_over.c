/*
 * game_over.c
 *
 *  Created on: 19 May 2015
 *      Author: Reflectin88
 */

#include "game_over.h"
#include "score.h"


void game_over() {
	draw_string( 'GAMEOVER', 15, 1 );
	game_over_score();
}
