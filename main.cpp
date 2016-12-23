

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
#include "xo_classes.h"//include prototype declarations for class functions.
                            //the classes themselves are written in other .cpp files

using namespace std;


/*------------//------------//------------//-----------//-------------*/
int main()
{

    Human player1;//construct the player. user will be asked what colour they want to play.

    Game_State game1(false);//construct the game
    instructions();//show the instructions


    if (player1.get_colour()=='X')//if player is playing x, then he goes first
    {
        Game_State temp(true);
        game1=temp;//custom copy the temp object into the game1 object.
                    //I cant simply construct the object within this if statement, because it will go out of scope.
                    //v annoying.

        player1.make_move(&game1);// we must pass a pointer to the class here, not the actual class
        game1.draw_board();

    }

    Computer computer1 (&game1 /* ,double randomness */ ); //construct the computer, based on what colour the player is
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
