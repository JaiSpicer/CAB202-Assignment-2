/*
 * zombies.h
 *
 *  Created on: 9 May 2015
 *      Author: Jai Spicer
 */

#ifndef __ZOMBIES__
#define __ZOMVIES__

void setup_zombies(
	Sprite zombies[],
	byte *zbitmap[],
	byte width[],
	byte height[]
		);
void draw_zombies ( Sprite * sprites );
void start_zombies ( void );
void update_zombies ( Sprite * zombies );
void new_zombies_pos( void );

#endif /* ZOMBIES */
