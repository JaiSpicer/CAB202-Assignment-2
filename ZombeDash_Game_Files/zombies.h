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
void zombie_updater( void );
void zombie_drawer( void );
void check_zombie( void );
void kill_zombies( Sprite * zombie );

#define zombie_count (8)
extern int dead_zombies;
Sprite zombies[zombie_count];
Sprite * z;

#endif /* ZOMBIES */
