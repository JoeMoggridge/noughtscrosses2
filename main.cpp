xo_main_mk7
Details
Activity
YESTERDAY

You moved an item to
Tue 21:44
Google Drive Folder
programming
Text
xo_main_mk7

You edited an item
Drive Notepad • Tue 17:09
Text
xo_main_mk7

You renamed an item
Drive Notepad • Tue 15:17
Text
xo_main_mk7
xo_mk7

You edited an item
Drive Notepad • Tue 15:14
Text
xo_mk7
EARLIER THIS WEEK

You edited an item
Drive Notepad • Mon 18:16
Text
xo_mk7

You created an item in
Drive Notepad • Mon 16:19
Google Drive Folder
My Drive
Binary File
xo_mk7
New Team Drive

///////////////////////////////////////////////////////////////////////////////
//C++
//Joseph moggridge april 2016
//allows you to play noughts and crosses against the computer.
//at the moment the computer plays randomly. eventually i want to create AI.
//this version will include inherited classes and error checking
//
//TODO:
//write constructor for game_tree
//write computer.make_move();
// im currentl halfway through the process of changing the array board[] from being of type int, to being of type char[].
////////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <iostream>
#include <string.h>
#include <windows.h>//needed for call to "exit()"
#include <math.h>
#include "xo_functions_mk7.h"//include prototype declarations for class functions. 
                            //the classes themselves are written in the cpp file of the same name.

using namespace std;

class Game_State
{
    char board[9];// board is numbered from 0 to 8.
    int game_turn;
public:
    Game_State (void); //default constructor
    void draw_board (void);
    bool make_move (char player_colour, int position);//returns true, and updates the game state if 'position' is a legal move. else, returns false
    char victory (void);//returns X if X has won, O if O has won. else returns ' '.

};

class Player //abstract class
{
protected:
    char colour;
public:
    char get_colour(void);
    virtual bool make_move(Game_State* p_game) =0;//virtual function because "=0"
};

class Game_Tree;//prototype declaration

class Computer: public Player //computer is a subclass of player
{
    protected:
        Game_Tree* tree;
        
        //TODO: double randomness;//if randomness is non zero, then the computer will sometimes pick non optimal moves
    public:
        Computer(char player_colour, bool playergoesfirst):  tree(playergoesfirst); //will construct the computer object to play as the opposite colour. Also call the game_tree constructor.
        bool make_move (Game_State* p_game);//changes the object passed to it to reflect the new board state
        int minimax (Game_Tree* node, int depth, bool maximising);
};

class Human: public Player //human is a subclass of player
{
    public:
        Human (void);//default constructor. lets the player choose his colour

        bool make_move (Game_State* p_game);//returns true if a legal move has just been played. else, returns false
    //                                  //its important that this function accepts a pointer as its argument, and not he actual class object,
    //                                  //if it accepted the class itself then a temporay object would be creted of the wrong scope which screws everything up.
};

class Game_Leaf
{
    protected:
       int game_turn;
       char board[9];

       //bool max_or_min; //true if this node is a maximum of the previous nodes.
       double node_value; //+1 for victory from this node, -1 if this node causes loss.
                            //eventually i plan to a wider variety of numbers here.

       //At each ply, there are potentially up to 8 different ways the game can develop
       new Game_leaf* leaves [8]; //array of pointers to the potentially up to 8 different game leafs that are below this game leaf.
                                    //some of the pointers might be NULL if moves cannot be played there

    public:
        Game_Leaf(bool max_or_min, char* current_board, int ply); //constructor

        double get_node_value(void);
        double get_next_leaf(int prev_leaf);//returns the next element of the array. ie returns 'leaves[prev_leaf++]''
};
class Game_Tree//will store the best possible move at each node
{
        Game_Leaf* head;//pointer to the first leaf in the game tree
        Game_Leaf* current_leaf;
        bool playergoesfirst;
   public:
        Game_Tree(bool playergoesfirst); //constructor. 

        //Game_Leaf* picknextmove(double randomness);//returns the next play the computer should make
                                                    //if randomness is non zero, then the computer will sometimes pick non optimal moves
};



void instructions(void);//prints instruction on how to play to std::out



/*------------//------------//------------//-----------//-------------*/
int main()
{

    Human player1;//construct the player. user will be asked what colour they want to play.

    
    Game_State game1;//construct the game
    instructions();//show the instructions

    if (player1.get_colour()=='X')//if player is playing x, then he goes first
    {
        player1.make_move(&game1);// we must pass a pointer to the class here, not the actual class
        game1.draw_board();
        
        Computer computer1(player1.get_colour() , true); //construct the computer, based on what colour the player is
                                                    //also constructs the game tree
    }
    else
        Computer computer1(player1.get_colour() , false, ); //construct the computer, based on what colour the player is
                                                    //also constructs the game tree

    do//repeat until someone wins
    {
        cout<< "the computer makes a play:"<<endl;
        computer1.make_move(&game1);
        game1.draw_board();

        if (game1.victory()!=' ')
            break;

        player1.make_move(&game1);
        game1.draw_board();
        
    }
    while (game1.victory()==' ');

    //i would prefer not having to call "Game_State::victory()" all over again here.
    //however i cant think of a way to instantly get out of the do-while loop and avoid it.
    if (game1.victory()=='X')
        cout<< "X has won the game!"<<endl;
    else if (game1.victory()=='O')
        cout<< "O has won the game!"<<endl;
    else
        cout<< "something very weird has happened"<<endl;

    return 0;
}
/*------------//------------//----------//------------//-----------------*/
