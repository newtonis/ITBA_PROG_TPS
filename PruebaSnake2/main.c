#include <stdio.h>
#include <time.h>
#include <allegro5/allegro.h>
#include "config.h"
#include "snake_logic.h"
#include "snake_pc.h"
#include "snake_graphic_base.h"
#include "interface.h"
 
int main(void){
    full_graphic_content content;
    images_t plot_basic_vars;
    fonts_t fonts;
    
    content.images = &plot_basic_vars;
    content.fonts = &fonts;

    init_snake_pc(&content);
    
    logic_vars_t *logic = init_snake_struct(INIT_LENGTH); // set snake position coordenates
    set_logic_call_time(logic, 1.0f/FPS_A);
    

    while(!content.do_exit){ 
        //clock_t t1;
        //t1 = clock();
        
        //printf("%f ",(double)t1 / CLOCKS_PER_SEC * 1000.0);
        
        handle_events(logic , &content );
        
    }
    
    destroy_game(logic);
    destroy_graphic_base(&content);
    return 0;
}
