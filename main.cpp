

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
#include "xo_functions.h"//include prototype declarations for class functions. 
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

class Tree;//prototype declaration

class Computer: public Player //computer is a subclass of player
{
    protected:
        Game_Tree* tree;
        
        //TODO: double randomness;//if randomness is non zero, then the computer will sometimes pick non optimal moves
    public:
        Computer(char player_colour, bool playergoesfirst):  tree(playergoesfirst); //will construct the computer object to play as the opposite colour. Also call the game_tree constructor.
        bool make_move (Game_State* p_game);//changes the object passed to it to reflect the new board state
        
};

class Human: public Player //human is a subclass of player
{
    public:
        Human (void);//default constructor. lets the player choose his colour

        bool make_move (Game_State* p_game);//returns true if a legal move has just been played. else, returns false
    //                                  //its important that this function accepts a pointer as its argument, and not he actual class object,
    //                                  //if it accepted the class itself then a temporay object would be creted of the wrong scope which screws everything up.
};

class Tree_Node
{
    protected:
       int game_turn;
       char board[9];//state of the board at this point in the game tree

       //bool max_or_min; //true if this node is a maximum of the previous nodes.
       double value; //+10 for victory from this node, -10 if this node causes loss.
                            //eventually i plan to a wider variety of numbers here.
      
       int depth; //0 for top level nodes, all the way down to 8 for terminating nodes.

       //At each ply, there are potentially up to 8 different ways the game can develop
       Tree_Node leaves [8]; //array of pointers to the potentially up to 8 different game leafs that are below this game leaf.
                                    //some of the pointers might be NULL if moves cannot be played there

    public:
        Tree_Node(game_state* p_game); //constructor. second argument is an array of pointers to the lower down nodes
        Tree_Node(game_state* p_game, int value); //constructor for a terminating node.

        double get_node_value(void);
        Tree_node* get_lower_node (int i);//returns leaves[i]
        
        //double get_next_node(int depth);//returns a rarandom leaf at 
};
class Tree//will store the best possible move at each node
{
        Tree_Node* head;//pointer to the first leaf in the game tree
        Tree_Node* current_leaf;//iterator
        bool playergoesfirst;//true if player is X, false if computer is X
        //int minimax (bool maximising);//used in constructing the game tree.
   public:
        Game_Tree(Game_State* p_game, bool pgoesfirst); //constructor. 
        
        double get_next_node(int depth, int i);//returns the next node at a given depth.
  
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
