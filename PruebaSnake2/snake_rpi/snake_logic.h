#ifndef SNAKE_LOGIC_H
#define SNAKE_LOGIC_H

#include <time.h>
#include "config.h"    

/*
 * Snake game back-end is in this file
 * Usage:
 * 
 * 1- First initialize Snake struct with init_snake_struct that will give a logic_vars pointer that will contain 
 * all the logic game data
 * 
 * 2- Call to set_snake_game_size(logic_vars_t* game_vars,int width,int height)
 * to set game dimensions
 * 
 * 3- Call to void set_game_difficulty(logic_vars_t* game_vars,int dif_level)
 * and set dif_level between 1 and 3
 * 
 * 4- Call to set_logic_call_time(logic_vars_t* game_vars,double time)
 * And set the period of the game update function (  update_snake_logic(logic_vars_t* vars) ) calls
 * 
 * 
 * 5- When the game starts call to
 *     start_snake_logic(logic_vars_t* vars)
 *     and the game will be allowed to advance
 *    
 * 6- And per game tick call to (in the period configured with set_logic_call_time)
 * int update_snake_logic(logic_vars_t* vars)
 * 
 * The function can return
 *  DEAD: The game has finished
 *  FOOD_EAT: The snake has won points (this informs that the scoreboard needs to be updated) 
 *  ALIVE: nothing new
 * 
 * 7- To plot snake you need to access vars->pSnake that contains an array with all snake points 
 * pSnake[i].polar_pos has the current position of a snake tile
 * You need to call int get_length(logic_vars_t* vars) to get the total snake length (the array length)
 * 
 * 8- To update the game key pressed, you need to call void handle_game_key_press(logic_vars_t* logic , int key)
 * with the key pressed by the user that can be LOGIC_KEY_UP , LOGIC_KEY_RIGHT , LOGIC_KEY_DOWN , LOGIC_KEY_LEFT
 * 
 * 9- You may call the function get_highscore(logic_vars_t* vars) to get the highscore for the difficulty configured
 * And read vars->points to get current match variables (Don't cheat this variable)
 * 
 * 10- When game ends call to stop_snake_logic(logic_vars_t* vars) and the game will be inmediatly stoped (Calls 
 * of update_snake_logic(logic_vars_t* vars) will be void
 * 
 * 11- When the game is closed you need to call void destroy_game(logic_vars_t* logic) to delete the game variables
 * dynamic variables
 * 
 * */



#define HEAD 0
#define X_COORD 0
#define Y_COORD 1

#define HIGHSCORES_FILE "game_points.txt"

#define INIT_LIVES 3
#define POINT_RATE 1
#define DEAD 0
#define ALIVE 1

#define INIT_LENGTH 4
#define MAX_LENGTH 1000

#define MAX_LOGIC_WIDTH 100
#define MAX_LOGIC_HEIGHT 100

#define POLAR 2
#define NUM_OK -1
#define NUM_ERR -2

#define FOOD_EAT 7
#define NO_EAT 0

#define GROW_UP -3

#define COLISION -4
#define NO_COL -5


#define CNT_DIFF 3

extern double diff_array[CNT_DIFF][2];

enum {LOGIC_STOP , LOGIC_PLAY , LOGIC_WIN_GAME};

enum {LOGIC_KEY_UP , LOGIC_KEY_RIGHT , LOGIC_KEY_DOWN , LOGIC_KEY_LEFT};

typedef struct snake_nodeT{ // snake single node
    int polar_pos[POLAR];
    
} snake_node_t;

typedef struct foodT{ // food struct
    int pos[POLAR];
    
} food_t;

typedef struct { /// game logic variables
    
    /// Basic game objects
    snake_node_t *pSnake;
    food_t *pFood;
    int used_tiles[MAX_LOGIC_HEIGHT][MAX_LOGIC_WIDTH]; /// we store what game tiles are currently occupied
    
    /// Variables that don't change while game goes on
    int world_height;
    int world_width;
    double speed; /// snake speed in seconds
    int snake_grow; // how much the snake sizes increases per point earned
    int diff_level; // level current difficulty (used for accurate scoreboard)
    int start_length;
    
    /// variables that change while game plays
    int snake_dir;
    int effective_dir;
    int game_status;
    double time_ref; 
    double call_time;
    
    int length; // snake length
    int points; // actual game points
    int highscore[CNT_DIFF]; //highscores
    
    int lives; // snake lives
}logic_vars_t;


// Game logic functions //

// calculate_newPos: calculates the next position of the head, and the others are shifted
// considering that prev_dir and key_in are not oposite, it also needs the actual length
static void calculate_newPos(logic_vars_t* vars);

// calculate_foodPos: sets a random position for the next food to apear
static void calculate_foodPos(logic_vars_t* vars);

// check_if_food_eaten: checks if snake eats food, returns NO_EAT if no eat, else GROW_UP
static int check_if_food_eaten(logic_vars_t* vars);

// check_if_colission: checks if snake colisions with tail, if so, lives -1
static int check_if_colision(logic_vars_t *vars);

// add_snake_node: adds a new node to the snake 
static void add_snake_node(logic_vars_t* vars);
// -------------------- //

// Snake length management //
// ----------------------- //
// init_length: sets initial length value
static void init_length(logic_vars_t* vars,int data);


// inc_length: increments actual length value
static int inc_length(logic_vars_t* vars);
// ----------------------- //

// Lives management functions // 
// -------------------------- // 
// init_lives: sets lives to start value, it must be called before starting game
static void init_lives(logic_vars_t* vars);

// read_lives: returns actual number of lives, 0 is game over
static int read_lives(logic_vars_t* vars);

// lose_lives: -1 live
static void lose_live(logic_vars_t* vars);
// -------------------------- //

// Points management //
// ----------------- //
// read_points: return points from previus game
static void read_points(logic_vars_t* vars);
// inc_points: adds 10 points to actual game
static void inc_points(logic_vars_t* vars);
//// Configure game speed and how much snake grow
static void set_game_level(logic_vars_t * game_vars , double speed,int snake_grow);
// reset_points
static void reset_points(logic_vars_t* vars);

// write_points_file: in game finish, writes final points into file
static void write_points_file(logic_vars_t* vars);



// Functions made to be used outside //

// -------------------- //
// init_snake_struct: inits standard snake with initial length with center coordenates
logic_vars_t* init_snake_struct();

 /// al game logic managment. Must be called in periods of the configured period time.
int update_snake_logic(logic_vars_t* vars);

/// Configure snake size
void set_snake_game_size(logic_vars_t* game_vars,int width,int height);

/// destroy all logic game dynamic memory
void destroy_game(logic_vars_t* logic);

// get_length: returns actual length
int get_length(logic_vars_t* vars);

// game_status_refresh: refresh snake status, if lose returns DEAD, if lives ALIVE,
// and for food eaten FOOD_EAT
int game_status_refresh(logic_vars_t * game_vars);

/// Make game to handle new key pressed.
void handle_game_key_press(logic_vars_t* logic , int key);

// get current highscore
int get_highscore(logic_vars_t* vars);
// ----------------- //

/// Configure game hardness, but selecting directly the difficulty
void set_game_difficulty(logic_vars_t* game_vars,int dif_level);

/// Configure how fast will the logic update function be called
void set_logic_call_time(logic_vars_t* game_vars,double time);

/// Make game play!
void start_snake_logic(logic_vars_t* vars);

/// Stop game!
void stop_snake_logic(logic_vars_t* vars);

#endif /* SNAKE_LOGIC_H */

