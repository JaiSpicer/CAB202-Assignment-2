/*
 * items.h
 *
 *  Created on: 15 May 2015
 *      Author: Reflectin88
 */

#ifndef __ITEMS__
#define __ITEMS

void sword_setup( void );
void sword_pickup( void );
void sword_use( void );
void draw_sword( void );
Sprite sword;
extern Sprite *sword_prt;

void grenades_setup( void );
void pickup_granades( void );
void granade_use( void );
void draw_granades( void );
void bang_setup( void );
Sprite grenades;
extern Sprite *grenades_prt;
Sprite bomb;
extern Sprite *bomb_prt;

#endif /* ITEMS */
