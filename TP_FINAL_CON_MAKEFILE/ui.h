
// Ui: user interface.
// Here all basic graphical structures, like button, reg_box (a counter with two buttons), shown_text, are written
// There are lots of functions to work easily with this kind of graphcs, and to avoid repetition.


#ifndef UI_H
#define UI_H


#include <allegro5/allegro_font.h>

#define COUNT_BOX_NUMBERS 2

enum {HOLD , RELEASE};

/// Handler structure to manage mouse cursors
typedef struct{
    ALLEGRO_SYSTEM_MOUSE_CURSOR next_cursor;
    ALLEGRO_SYSTEM_MOUSE_CURSOR default_cursor;
    ALLEGRO_DISPLAY *display_ref;
}cursor_handler_t;

/// Handler to deal with buttons (given two surfaces)
typedef struct{
    double x , y , w , h;
    ALLEGRO_BITMAP * surface_a;
    ALLEGRO_BITMAP * surface_b;
    cursor_handler_t *cursor;
    int status;
    int wait_to_release;
}button_t;

/// Handler to deal with two buttons counters (that we call 'reg_box')
typedef struct{
    button_t *up , *down;
    int value;
    ALLEGRO_FONT *font;
    int x,y;
    int flag_up , flag_down;
    int min_value , max_value;
}reg_box_t;

/// Handler to work with texts
typedef struct{
    int x,y;
    char* text;
    ALLEGRO_FONT * font;
    ALLEGRO_COLOR color;
}show_text_t;

// Button functions
button_t *init_button( ALLEGRO_BITMAP* surface_a , ALLEGRO_BITMAP* surface_b ,cursor_handler_t* cursor , int x ,int y );

void draw_button(button_t* button);
void update_button_position(button_t* button, int x,int y);
int update_button(button_t* button);
void destroy_button(button_t* button);

//// Increment/decrement box ('reg_box') functions
reg_box_t *init_reg_box(ALLEGRO_BITMAP* surfaces[],cursor_handler_t* cursor,ALLEGRO_FONT* font,int x,int y,int default_value,int min_value,int max_value);
void update_reg_box(reg_box_t *reg_box);
void update_reg_box_position(reg_box_t* reg_box,int x,int y);
void draw_reg_box(reg_box_t *reg_box);
void destroy_reg_box(reg_box_t *reg_box);

/// Cursor functions

cursor_handler_t* init_cursor_handler(ALLEGRO_DISPLAY *display); // Create a dynamic cursor handler
void destroy_handler(cursor_handler_t* cursor); // Set cursor for next iteration
void set_current_cursor(cursor_handler_t* handler, ALLEGRO_SYSTEM_MOUSE_CURSOR cursor); // Update cursor for the current iteration, set then default cursor again, because we don't want the same cursor to stay forever
void update_display_cursor(cursor_handler_t* handler);


/// Show text functions
show_text_t * init_show_text(char *text,ALLEGRO_COLOR color,ALLEGRO_FONT* font,int x,int y);
void draw_show_text(show_text_t* show_text);
void destroy_text(show_text_t* text);
void update_show_text_position(show_text_t* show_text,int x,int y);
void update_show_text_content(show_text_t* show_text,char *content);
void set_show_text_color(show_text_t* show_text,ALLEGRO_COLOR color);

#endif /* UI_H */

