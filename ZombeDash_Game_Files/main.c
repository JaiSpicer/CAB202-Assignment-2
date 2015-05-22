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

#include "random_seed.h"
#include "start_screen.h"
#include "screen.h"
#include "lives.h"
#include "score.h"
#include "hero.h"
#include "zombies.h"
#include "game_over.h"

#include "pit.h"
#include "items.h"

void setup_device(void);

int main() {
	setup_device();
	while( 1 ) {
		dead_zombies = 0;
		setup_start_screen();
		screen_lines();
		reset_lives();
		lives_setup();
		reset_score();
		score_setup();
		start_pit();

		sword_setup();
		grenades_setup();

		start_hero();
		start_zombies ();

		clear();

		int zombie_update = 0;
		int score_update = 0;
		while ( lives > 0 && dead_zombies < 8) {
			clear();
			screen_lines();
			lives_setup();
			score_setup();

			draw_pit();
    		draw_sword();
    		pickup_sword();
    		draw_granades();
    		pickup_granades();
    		granade_use();
    		bang_setup();

			update_hero();

			if ( zombie_update == 10 ) {
				zombie_updater();
				zombie_update = 0;
			}
			if ( score_update == 50 ) {
				update_score_time();
				score_update = 0;
			}
			zombie_drawer();

			check_zombie();
			pit_collision(); // Hero pit collision
//			zombie_pit();

			refresh();
			zombie_update++;
			score_update++;
			_delay_ms( 100 );
		}
		clear();
		refresh();
		draw_string("GAMEOVER",20,10);
		wait_until(pressed(SW1));
		clear();
		refresh();
	}
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
