/*
 * pit.h
 *
 *  Created on: 15 May 2015
 *      Author: Reflectin88
 */

#ifndef __PIT__
#define __PIT__

void start_pit( void );

Sprite pit;
extern Sprite * pit_prt;

void pit_collision( void );
void move_out_pit( void );
void draw_pit( void );
//void zombie_pit( void );s

extern int in_pit;

#endif /* PIT */
