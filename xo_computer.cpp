
#include "xo_classes.h"
#include <algorithm> // needed for calls to max()
#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;

//--------
//
Computer::Computer (Game_State* p_game)// constructor
: tree (p_game)
{

    if (p_game->goes_first()==true)
        colour= 'O';

    else /*if (p_game.goes_first()==false)*/
        colour= 'X';
/*
    else
    {

        cout<< "an error has occured, computer could not choose colour."<<endl;
        cout<<"press enter to end the program"<<endl;
        string input;
        getline(cin, input);
        exit (1);
    }*/
    //note that the Tree constructor is also called (check the prototype declaration to see this call)

}



//computer fuctions
bool Computer::make_move(Game_State* p_game)
{

    int position=-1;//initially set the move-to-make to a dissallowed value.

    double max=0;//play the move that maximizes this value
    Tree_Node* trial_leaf= NULL;


    //loop through searching for moves until the best move is found
    do
    {
        //search the game tree for the best move
        for (int i=0; i<9 ; i++)
        {
            trial_leaf = tree.current_leaf->get_lower_node ( i);
            //note that if a move in position i is a disslowed move, then get_lower_node(i) will return NULL

            if (trial_leaf!= NULL) //check that its an allowed move
             {
                 if (trial_leaf->get_node_value()> max)//is this move better than all the other moves found so far?
                 {
                    max= trial_leaf->get_node_value();//it is the best move found so far
                    tree.current_leaf= trial_leaf;
                    position= i;
                 }
             }
        }

    }while (p_game->make_move(this->get_colour(), position) == false);
    //the while condition ensures that the computer will keep trying moves until it plays one that is allowed by the game_State object

    return true;
}


