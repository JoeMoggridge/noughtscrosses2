// --------------- Header guard ---------------------------
#ifndef xo_functions_H
#define xo_functions_H
 
 
//---------------- protoype declarations --------------------------
//the detail of what these finctions do is in the .cpp file of the same name.

//Game_State functions
Game_State::Game_State (void);//constructor. done
void Game_State::draw_board (void);//prints the current game to the screen. done
bool Game_State::make_move (char player_colour, int position);
char Game_State::victory (void);//check whether X or O has won.

//player functions
char Player::get_colour();

//human functions. Human inherits from player
Human::Human(void);
bool Human::make_move (Game_State* p_game);


//computer fuctions. Computer inherits from player.
void Computer::make_move(Game_State* p_game);
void Computer::make_move (void);
Computer::Computer(char player_colour, char whoplaysfirst);//default constructor

//other functions
void instructions(void);

  
// This is the end of the header guard
#endif
