#include <stdio.h>
#include <iostream>
#include <string.h>
#include <windows.h>//needed for call to "exit()"
#include <math.h>
#include "xo_game.h"//include prototype declarations for game functions.
                            //the classes themselves are written in other .cpp files
#include "xo_computer.h"//include prototype declarations for AI classes
#include <vector>

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

    //note that the Tree constructor is also called (check the prototype declaration to see this call)

}



//computer fuctions
bool Computer::make_move(Game_State* p_game)
  :tree(p_game)//reconstruct the tree based on the fact that the game state has changed.
{

    int position=-1;//initially set the move-to-make to a dissallowed value.

    double best=0;//play the move that maximizes this value
    Tree_Node* trial_leaf= NULL;
    Game_State game_copy= *p_game;//create a copy of the game

    std::vector<int> goodpositions;//create an empty listof integers. this list will contain all the postions which are equally good.
    int counter;

    //loop through searching for moves until the best move is found
    do
    {
        counter=0;
        goodpositions.clear();

        //search the game tree for the best move
        for (int i=0; i<9 ; i++)
        {
            if (game_copy.make_move(this->get_colour(), i) == true)
            {
                //this is an allowed place to play.
                //next, figure out whether it is a good place


                trial_leaf = tree.current_leaf->get_lower_node ( i);
                //note that if a move in position i is a dissallowed move, then get_lower_node(i) will return NULL

                if (trial_leaf!= NULL) //check that its an allowed move
                 {
                     if (trial_leaf->get_node_value()> best)//is this move better than all the other moves found so far?
                     {
                        best= trial_leaf->get_node_value();//it is the best move found so far
                        position= i;
                        goodpositions.clear();
                        goodpositions.push_back(position);
                     }
                     if (trial_leaf->get_node_value()== best)//is this move better than all the other moves found so far?
                     {
                        best= trial_leaf->get_node_value();//it is one of the best move found so far
                        position= i;
                        goodpositions.push_back(position);
                     }
                 }
                 if (trial_leaf==NULL)
                    counter++;

            }
            if (goodpositions.empty()==false)
            {
                //if there are multiple postions which all have equal value, then pick one randomly.
                int rand_index = floor(goodpositions.size() * rand()/RAND_MAX);
                position= goodpositions.at(rand_index);

            }
            if (counter>8)
            {
                cout<< "PROBLEM: all leaves are NULL."<<endl;
                exit (-1);
            }
        }

    }while (p_game->make_move(this->get_colour(), position) == false);
    //the while condition ensures that the computer will keep trying moves until it plays one that is allowed by the game_State object

    //notate our new position in the tree.
    tree.current_leaf= tree.current_leaf->get_lower_node(position);

    return true;
}


