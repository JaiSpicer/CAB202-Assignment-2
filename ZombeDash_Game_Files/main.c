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
#include "pit.h"
#include "items.h"

void setup_device(void);

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
