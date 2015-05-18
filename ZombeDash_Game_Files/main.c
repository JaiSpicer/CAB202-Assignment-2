/*
 * main.c
 *
 *  Created on: 8 May 2015
 *      Author: Jai Spicer
 */

#define F_CPU 8000000UL
#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define CPU_8MHz 0x01

#include <util/delay.h>

#include "graphics.h"
#include "friendly_ports.h"
#include "cpu_speed.h"
#include "byte.h"
#include "sprite.h"

#include "start_screen.h"
#include "screen.h"
#include "lives.h"
#include "score.h"
#include "hero.h"
#include "zombies.h"

//#include "pit.h"
//#include "items.h"

void zombie_collision( void );
void setup_device(void);
void pit_collision( void );

int main() {
	setup_device();
	setup_start_screen();

	screen_lines();
	lives_setup();
	score_setup();

//	start_pit();
//	sword_setup();
//	grenades_setup();

	start_hero();
	start_zombies ();

	clear();

	int zombie_update = 0;
	int score_update = 0;
	while ( lives > 0 ) {
		clear();
		screen_lines();
    	lives_setup();
    	score_setup();

//    	start_pit();
//    	sword_setup();
//    	grenades_setup();

//    	move_hero ( hero_prt );
//    	draw_sprite ( hero_prt );

    	update_hero();

		if ( zombie_update == 10 ) {
			update_zombies ( z );
//			zombie_updater();
			zombie_update = 0;
		}
		if ( score_update == 50 ) {
			update_score_time();
			score_update = 0;
		}
//		zombie_collision();
		zombie_updater();
//		draw_zombies ( z );
		refresh();
		zombie_update++;
		score_update++;
		_delay_ms( 100 );
	}

	clear();
	draw_string("GAME OVER", 2,3);


	refresh();
	return 0;

}

void setup_device() {
	CPU_PRESCALE(CPU_8MHz);

	DDRB = ( LED0 | LED1 ) & ~( SW0 | SW1 ); // Output to LEDs, input from switches.
	DDRD = LED2; // Turn on the little yellow LED.

	// Turn everything off to start with
	PORTB = 0x00;
	PORTD = 0x00;

	LCDInitialise(LCD_DEFAULT_CONTRAST);
	clear();
}

//void zombie_collision() {
//	if (
//			(hero.x == z->x && hero.y == z->y) || // Top left
//			( hero.x == z->x && hero.y == z->y + 1 ) || // Middle Left
//			( hero.x == z->x && hero.y == z->y + 2 ) || // Bottom Left
//			( hero.x == z->x + 1 && hero.y == z->y ) || // Top Middle
//			( hero.x == z->x + 1 && hero.y == z->y + 1 ) || // Middle Middle
//			( hero.x == z->x + 1 && hero.y == z->y + 2 ) || // Middle Bottom
//			( hero.x == z->x + 2 && hero.y == z->y ) || // Right Top
//			( hero.x == z->x + 2 && hero.y == z->y + 1 ) ||// Right Middle
//			( hero.x == z->x + 2 && hero.y == z->y + 2 ) // Right Bottom
//			) {
//		lives = lives - 1;
//	}
//}

//void pit_collision() {
//	if (
//			( hero.x == pit_prt->x && hero.y == pit_prt->y )
//			) {
//	}
//}
