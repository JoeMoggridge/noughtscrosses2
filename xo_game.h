// --------------- Header guard ---------------------------
#ifndef xo_functions_H
#define xo_functions_H

using namespace std;
//---------------- protoype declarations --------------------------
//These are the declarations for the classes etc that are called in main.cpp
//the classe's implementations are in other files.

//this function is implemented in xo_game.cpp
void instructions(void);//prints instruction on how to play to std::out


//---------------------------------------------------------------
//the implementation of these next classes is in xo_game.cpp
//------------------------------------------------------------
class Game_State
{
    char board[9];// board is numbered from 0 to 8.
    int game_turn;
    bool first;//true if the player goes first, false if the computer goes first
public:
    Game_State (bool playerfirst); //constructor
    Game_State (void);//default constructor used for making temporary tree objects
    Game_State (const Game_State& input) ;//this is a custom copy constructor, the default copy constructor does not fit my needs.

    void draw_board (void);
    bool make_move (char player_colour, int position);//returns true, and updates the game state if 'position' is a legal move. else, returns false
    char victory (void);//returns X if X has won, O if O has won. else returns ' '.
    int get_turn(void);
    bool goes_first();
};

class Player //abstract class
{
protected:
    char colour;
public:
    char get_colour(void);
    virtual bool make_move(Game_State* p_game) =0;//virtual function because "=0"
};



//------------------------------------------------------
// this class is implemented in human.cpp
//---------------------------------------------------
class Human: public Player //human is a subclass of player
{
    public:
        Human (void);//default constructor. lets the player choose his colour

        bool make_move (Game_State* p_game);//returns true if a legal move has just been played. else, returns false
    //                                  //its important that this function accepts a pointer as its argument, and not he actual class object,
    //                                  //if it accepted the class itself then a temporay object would be creted of the wrong scope which screws everything up.
};



#endif

