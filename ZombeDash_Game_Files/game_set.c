/*
 * game_set.c
 *
 *  Created on: 19 May 2015
 *      Author: Reflectin88
 */

#include "sprite.h"
#include "graphics.h"
#include "friendly_ports.h"

#include "screen.h"
#include "hero.h"
#include "zombies.h"
#include "game_over.h"

void hero_die() {
	clear();
	screen_lines();
	start_hero();
	start_zombies ();
}
