#include <stdio.h>
#include <allegro5/allegro.h>
#include "config.h"
#include "snake_logic.h"
#include "snake_pc.h"
#include "snake_graphic_base.h"

 
int main(void){
    
    logic_vars logic;
    full_graphic_content content;
    graphic_vars plot_basic_vars;
    content.plot_game_graphic = &plot_basic_vars;
    
    init_snake_pc(&content);
    
    logic.pSnake = malloc(sizeof(snake_node_t)*MAX_LENGTH);
    
    init_snake_struct(INIT_LENGTH, logic.pSnake); // set snake position coordenates
    
    
    content.key_press = NO_KEY;
    content.direction = KEY_RIGHT;
    content.dir_control = 0;
    content.refresh = 0;

    while(!content.do_exit){ 
        handle_events(&logic , &content );
        
    }
    
    free(logic.pSnake);
    destroy_graphic_base(&content);
    return 0;
}