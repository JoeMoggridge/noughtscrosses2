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
{

    int position=-1;//initially set the move-to-make to a dissallowed value.

    double best=0;//play the move that maximizes this value
    Tree_Node* trial_leaf= NULL;

    std::vector<int> goodpositions;//create an empty listof integers. this list will contain all the postions which are equally good.
    bool oneofthebest;
    bool clear_list;

    //loop through searching for moves until the best move is found
    do
    {
        //search the game tree for the best move
        for (int i=0; i<9 ; i++)
        {
            goodpositions.clear();
            oneofthebest=true;
            clear_list=true;

            trial_leaf = tree.current_leaf->get_lower_node ( i);
            //note that if a move in position i is a dissallowed move, then get_lower_node(i) will return NULL

            if (trial_leaf!= NULL) //check that its an allowed move
             {
                 if (trial_leaf->get_node_value()> best)//is this move better than all the other moves found so far?
                 {
                    best= trial_leaf->get_node_value();//it is the best move found so far
                    tree.current_leaf= trial_leaf;
                    position= i;
                    goodpositions.clear();
                    goodpositions.push_back(position);
                 }
                 if (trial_leaf->get_node_value()= best)//is this move better than all the other moves found so far?
                 {
                    best= trial_leaf->get_node_value();//it is one of the best move found so far
                    tree.current_leaf= trial_leaf;
                    position= i;
                    goodpositions.push_back(position);
                 }
             }
             for (int n:goodpositions)//iterate through the list, checking that this latest leaf is at tleast as good as any already in the list
            {

                if (best<n)
                {
                    //if best is smaller than any elemetn in the list, then it is not the best possible, and we should discard it
                    oneofthebest=false;

                }
                if (best<=n)
                {
                    //if best is less than or equal to any elements currently in the list, then dont clear the list
                    clear_list=false;
                }
                //else
                    //best is higher than every element in the list. the list should be cleared and replaced twith the value of best

            }
            if (oneofthebest==true && clear_list==true)
            {
                //the found value is higher than any found so far.
                goodpositions.clear();
                goodpositions.push_back(position);
            }
            else if (oneofthebest==true && clear_list==false)
            {
                //the found value is equal to previously found vlaues. add it to the list
                goodpositions.push_back (position);
            }
        }
        if (goodpositions.empty()==false)
        {
            //if there are multiple postions which all have equal value, then pick one randomly.
            int rand_index = floor(goodpositions.size() * rand()/RAND_MAX);
            position= goodpositions.at(rand_index);
        }

    }while (p_game->make_move(this->get_colour(), position) == false);
    //the while condition ensures that the computer will keep trying moves until it plays one that is allowed by the game_State object

    return true;
}


