/*** 
snake_pc.h: In this file a part user interaction is handled
The criteria was to here write the front-end actualization (menu->game)

There are some mixes with snake_graphic_base.c but, the idea is to write
all things that change frecuently in snake_pc.h and all things that
tend to be more static in snake_graphic_base.c 
***/



#ifndef SNAKE_PC_H
#define SNAKE_PC_H

#include "config.h"
#include "snake_logic.h"
#include "interface.h"
#include "snake_graphic_base.h"

#include <allegro5/allegro.h>

#define BLACK al_map_rgb(0,0,0)



/// Handle all front-end events
void handle_events(logic_vars_t* vars , full_graphic_content * content );

/// Update game calculations in general 
void update_game( logic_vars_t* game_data , full_graphic_content* content );

/// Update game graphics, more precisely, call draw functions
void update_pc_graphic_screen( logic_vars_t* game_data , full_graphic_content* graphic_data);

/// Draw in particular the snake and the food
void draw_game( logic_vars_t* game_vars, full_graphic_content* content);

/// Actions to be taken when the game starts
void handle_start_game( logic_vars_t *game_data,full_graphic_content *content);

/// Handle game key presses
void handle_key_press( logic_vars_t * vars , full_graphic_content *content , ALLEGRO_EVENT *ev);

/// Handle when scoreboard is updated
void update_scoreboard(logic_vars_t * vars , full_graphic_content *content);

/// Convert scoreboard to white color (used in gameover)
static void set_scoreboard_to_white(full_graphic_content *content);

static void set_scoreboard_to_grey(full_graphic_content *content);

#endif /* SNAKE_PC_H */

