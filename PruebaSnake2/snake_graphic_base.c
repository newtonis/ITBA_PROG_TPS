#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include "snake_graphic_base.h"

#include "snake_pc.h"
#include "ui.h"

void init_snake_pc(full_graphic_content *content){

    int i = 0;
    
    for (i = 0;i < 4;i++){
        content->key_pressed[i] = 0;
    }
    
    content->redraw = false;
    content->do_exit = false; 
 
    snake_node_t snake_H[MAX_LENGTH]; // initial snake
    snake_node_t *pHead = snake_H; // pointer to snake
        
    food_t gameFood; // food in game
    food_t *pGameFood = &gameFood; // pointer to food struct
        
    if(!al_init()) {
	fprintf(stderr, "failed to initialize allegro!\n");
	exit(1);
    }
 
    if(!al_install_keyboard()) {
	fprintf(stderr, "failed to initialize the keyboard!\n");
	exit(1);
    }
 
    content->timer_a = al_create_timer(1.0 / FPS_A);
    if(!content->timer_a) {
	fprintf(stderr, "failed to create timer!\n");
	exit(1);
    }
    
    content->timer_b = al_create_timer(1.0 / FPS_B);
    if(!content->timer_b) {
	fprintf(stderr, "failed to create timer!\n");
	exit(1);
    }
        
    for(i = 0; i < MAX_LENGTH; i++){ // snake create
        content->images->snake[i] = al_create_bitmap(CUADRADITO_SIZE, CUADRADITO_SIZE);
        if(!content->images->snake[i]) {
            fprintf(stderr, "failed to create snake bitmap!\n");
            al_destroy_timer(content->timer_a);
            al_destroy_timer(content->timer_b);

            while(i >= 0){
                al_destroy_bitmap(content->images->snake[i]);
                i--;
            }
            exit(1);
        }
    }
        
    content->images->food = al_create_bitmap(CUADRADITO_SIZE, CUADRADITO_SIZE); // food create
    if(!content->images->food){
        fprintf(stderr, "failed to create food bitmap!\n");
        al_destroy_timer(content->timer_a);
	al_destroy_timer(content->timer_b);

        al_destroy_bitmap(content->images->snake[i]);
        exit(1);
    }
    
    content->event_queue = al_create_event_queue();
    if(!content->event_queue) {
	fprintf(stderr, "failed to create event_queue!\n");
        for(i = 0; i < MAX_LENGTH; i++){ // snake destroy
            al_destroy_bitmap(content->images->snake[i]);
        }
        al_destroy_bitmap(content->images->food);
	al_destroy_timer(content->timer_a);
	al_destroy_timer(content->timer_a);
	exit(1);
    }
 
    content->display = al_create_display(SCREEN_W, SCREEN_H);
    if(!content->display) {
	fprintf(stderr, "failed to create display!\n");
	al_destroy_timer(content->timer_a);
	al_destroy_timer(content->timer_b);
	for(i = 0; i < MAX_LENGTH; i++){ // snake destroy
            al_destroy_bitmap(content->images->snake[i]);
        }
        al_destroy_bitmap(content->images->food);
	al_destroy_event_queue(content->event_queue);
        exit(1);
    }
	
    for(i = 0; i < MAX_LENGTH; i++){ // pink snake
        al_set_target_bitmap(content->images->snake[i]);
        al_clear_to_color(al_map_rgb(255, 0, 255));
    }
	
    al_set_target_bitmap(content->images->food); // Pink Food
    al_clear_to_color(al_map_rgb(255, 0, 255));
    
    al_set_target_bitmap(al_get_backbuffer(content->display));
  
    al_register_event_source(content->event_queue, al_get_display_event_source(content->display));
    al_register_event_source(content->event_queue, al_get_timer_event_source(content->timer_a));
    al_register_event_source(content->event_queue, al_get_timer_event_source(content->timer_b));
    al_register_event_source(content->event_queue, al_get_keyboard_event_source()); 
 
    al_clear_to_color(al_map_rgb(0,0,0));
        
    al_start_timer(content->timer_a);
    al_start_timer(content->timer_b);
    
    content->front_end_status = INITIAL_MENU;
    
    /// start mouse cursor handler
    content->cursor_handler = init_cursor_handler(content->display);
    
    /// init fonts
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    load_fonts(content->fonts);
    
    //// load all game images
    al_init_image_addon();
    load_images(content->images);

    /// init mouse driver
    al_install_mouse();
    
    /// init menu
    init_menu(content);
    
}

//**** Main allegro event handler ****/ 
void handle_events(logic_vars* vars , full_graphic_content * content){

    ALLEGRO_EVENT ev;
    if( al_get_next_event(content->event_queue, &ev) ){ 
	if(ev.type == ALLEGRO_EVENT_TIMER){
            if (ev.timer.source == content->timer_a){  /// Logical timer
                update_game( vars , content);
            }else if(ev.timer.source == content->timer_b){ /// graphic timer
                update_pc_graphic_screen( vars , content );
            }
        }else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            content->do_exit = true;
        }else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
       
            switch(ev.keyboard.keycode){
                case ALLEGRO_KEY_UP:
                    content->key_pressed[KEY_UP] = true;
                break;
                case ALLEGRO_KEY_DOWN:
                    content->key_pressed[KEY_DOWN] = true;
                break;
                case ALLEGRO_KEY_LEFT: 
                    content->key_pressed[KEY_LEFT] = true;
                break;

                case ALLEGRO_KEY_RIGHT:
                    content->key_pressed[KEY_RIGHT] = true;
                break;
            }
        }else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
            switch(ev.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                    content->key_pressed[KEY_UP] = false;
                break;
                case ALLEGRO_KEY_DOWN:
                    content->key_pressed[KEY_DOWN] = false;
                break;
                case ALLEGRO_KEY_LEFT: 
                    content->key_pressed[KEY_LEFT] = false;
                break;
                case ALLEGRO_KEY_RIGHT:
                    content->key_pressed[KEY_RIGHT] = false;
                break;
                case ALLEGRO_KEY_ESCAPE:
                    content->do_exit = true;
                break;
            }
        }
    }
}

void destroy_graphic_base(full_graphic_content * content){
    int i;
    for(i = 0; i < MAX_LENGTH; i++){ // snake destroy
        al_destroy_bitmap(content->images->snake[i]);
    }
    al_destroy_timer(content->timer_a);
    al_destroy_timer(content->timer_b);
    al_destroy_bitmap(content->images->food);
    al_destroy_display(content->display);
    
    destroy_handler(content->cursor_handler);
    destroy_menu(content);
    destroy_images(content->images);
    destroy_fonts(content->fonts);
    
}

//// Load all game bitmaps
void load_images(images_t* images){
   
    images->arr_down  = load_or_crash("flecha_abajo.png");
    images->arr_down_2= load_or_crash("flecha_abajo_2.png");
    images->arr_up    = load_or_crash("flecha_arriba.png");
    images->arr_up_2  = load_or_crash("flecha_arriba_2.png");
    
    
    images->game_over = load_or_crash("game_over.png");
    images->easy      = load_or_crash("lento.png");
    images->medium    = load_or_crash("medio.png");
    images->hard      = load_or_crash("rapido.png");
    images->start_button_image = load_or_crash("start.png");
    images->start_button_image_b = load_or_crash("start_b.png");
    
}

/*** Create all user interface elements ***/
void init_menu(full_graphic_content *content){
    //content->intial_menu->play_button = init_button( NULL , NULL );
    content->intial_menu->play_button = init_button(content->images->start_button_image , content->images->start_button_image_b, content->cursor_handler, SCREEN_W / 2 , SCREEN_H - START_BUTTON_CORR);
    
    ALLEGRO_BITMAP *arr_box_images[] = {
        content->images->arr_up,
        content->images->arr_up_2,
        content->images->arr_down,
        content->images->arr_down_2
    };
    
    content->intial_menu->width_config_ui = init_reg_box(arr_box_images, content->cursor_handler,content->fonts->iso_text,SCREEN_W/8*1,SCREEN_H/2,10,MIN_TABLE_WIDTH,MAX_TABLE_WIDTH);
    content->intial_menu->height_config_ui = init_reg_box(arr_box_images, content->cursor_handler, content->fonts->iso_text,SCREEN_W/4,SCREEN_H/2,10,MIN_TABLE_HEIGHT,MAX_TABLE_HEIGHT);
    content->intial_menu->diff_ui = init_reg_box(arr_box_images, content->cursor_handler, content->fonts->iso_text,SCREEN_W/4*3,SCREEN_H/2,1,MIN_DIFF,MAX_DIFF);
    
    
    content->intial_menu->text_config_size = init_show_text(MAP_SIZE_TEXT,BOX_COLOR,content->fonts->iso_text,SCREEN_W/16*3,SCREEN_H/2-TEXT_CONF_DISTANCE);
    content->intial_menu->extra_text_config = init_show_text("X",BOX_COLOR,content->fonts->iso_text,SCREEN_W/16*3,SCREEN_H/2-DEF_SZ/2);
    content->intial_menu->title_text = init_show_text(GAME_TITLE_TEXT,BOX_COLOR,content->fonts->iso_title,SCREEN_W/2,TITLE_DISTANCE_Y);
    content->intial_menu->diff_text = init_show_text(DIFF_TEXT,BOX_COLOR,content->fonts->iso_text,SCREEN_W/4*3,SCREEN_H/2-TEXT_CONF_DISTANCE);
}

void destroy_menu(full_graphic_content *content){
    destroy_button(content->intial_menu->play_button);
    destroy_reg_box(content->intial_menu->width_config_ui);
    destroy_reg_box(content->intial_menu->height_config_ui);
}
void destroy_images(images_t* images){
    al_destroy_bitmap(images->arr_down);
    al_destroy_bitmap(images->arr_up);
    al_destroy_bitmap(images->game_over);
    al_destroy_bitmap(images->easy);
    al_destroy_bitmap(images->medium);
    al_destroy_bitmap(images->hard);
    al_destroy_bitmap(images->start_button_image);
}

void load_fonts(fonts_t* fonts){
    fonts->iso_text = NULL;
    fonts->iso_title = NULL;
    fonts->iso_text = al_load_font("fonts/isocpeur.ttf",FONT_SIZE_A,0);
    fonts->iso_title = al_load_font("fonts/isocpeur.ttf",FONT_SIZE_B,0);
    
    if (!fonts->iso_text || !fonts->iso_title){
        fprintf(stderr,"Could not load fonts");
        exit(1);
    }
}
void destroy_fonts(fonts_t* fonts){
    al_destroy_font(fonts->iso_text);
    al_destroy_font(fonts->iso_title);
}

/// load a image. If loading fails then throws an errors
ALLEGRO_BITMAP* load_or_crash(const char *filename){
    ALLEGRO_BITMAP * image = NULL;
    image = al_load_bitmap(filename);
    if (!image){
        fprintf(stderr,"Error loading %s\n",filename);
        exit(1);
    }
    return image;
}