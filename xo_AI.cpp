

#include "xo_functions.h"
#include <algorithm> // needed for calls to max()
#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;
/*
Tree::Tree()
{//empty constructor for testing
    playergoesfirst=true;
}*/


//global variables for testing
int victories=0;
int nodesatdepth=0;
//int nodes=0;

//----------------------------
//Tree stuff
//-----------------------
Tree::Tree (Game_State* p_game, bool pgoesfirst)//constructor
{
    current_leaf= NULL;
    playergoesfirst=pgoesfirst;
    Tree_Node temp_node;

    //recursively builds the tree:
    temp_node= Tree_Node(current_leaf, p_game, true, pgoesfirst);
    head= &temp_node;
}
Tree_Node* Tree::get_node( int i)
{

       return current_leaf->get_lower_node(i);
}

//-----------------------------
//Tree_Node stuff
//--------------------
double Tree_Node::get_node_value( )
{
       return value;
}
 Tree_Node* Tree_Node::get_lower_node (int i)//returns leaves[i]
 {
     if (i<0 || i>8)
     {
         return NULL;
     }
     else
        return this->leaves[i];
 }

 Tree_Node::Tree_Node(void) //empty constructor for making temporary tree_node objects
 {
     depth=10;

     for (int i=0; i<9; i++)
        leaves[i]= NULL;
 }

Tree_Node::Tree_Node(const Tree_Node& input) //copy constructor
{
    depth= input.depth;
    value= input.value;
    state= input.state;//note that this calls my custom copy operator for game states

    for (int i=0; i<9; i++)
        leaves[i]= input.leaves[i];

}

Tree_Node::Tree_Node(Tree_Node* current_leaf,  Game_State* p_game, bool maximize, bool pgoesfirst)
//constructor.
 {
     Tree_Node temp_node;

    depth= p_game->get_turn();

    //create some variables that will be used in calcualting the node value
    int win_value=1;//this is the wieght that will be assigned for a win
    double best_value=0, test_value;

    int index=1;

    //we can work out what colour the curerent player is by considering the fact that X alwatys plays first,
    //and the computer will always be trying to maximize
    char colour;
    if (maximize== pgoesfirst)
        colour= 'O';
    else
        colour= 'X';

    //copy the input game state into this class.
    //note that i have written a cutom copy operator in xo_functions.cpp
    state = *p_game;


    if (current_leaf == (Tree_Node*) NULL)//if this conditoin is met, then this is the head node. construct the head node.
    {
        int i=0;
        nodesatdepth=0;
            //for (int i=0; i<9; i++)
            {

                temp= state;
                best_value=0;
                if( temp.make_move(colour, i)==true)//try to make a move. if its an allowed move, then create the next branch of the tree, and store the info about this particular node.
                {


                    temp_node= Tree_Node(this, &temp, !maximize, pgoesfirst);//construct the next level down of leaves
                                                                            //PROBLEM the object that leaves[i] is now poining at will be destructed as soon as we exit this loop

                    leaves[i]= &temp_node;

                    test_value= leaves[i]->value;

                    //seacrh for the best node from the next level down
                    //TODO make the upper node a more complicated combination of the lower nodes
                    if (maximize==true)
                        best_value= std::max(test_value, best_value);
                    else if (maximize==false)
                        best_value= std::min(test_value, best_value);
                }
                else //not an allowed move
                    leaves[i]= NULL;
            }
            value = best_value;//assign this nodes value

    }
    else if (p_game->victory()!= ' ' || depth> 8 )//base case. This is a terminating node.
    {
        victories++;
        //set all the sub nodes to NULL
        for (int i=0; i<9;i++)
            leaves[i]=NULL;

        state= *p_game;

        //set the value of this terminating node depending on who has won
        if (maximize==true)
           index++;
        if (p_game->victory()== 'X')
           value= win_value*pow(-1, index);
        if (p_game->victory()== 'O')
           value= win_value*pow(-1, index+1);


    }
    else //general recursive case. construct this node by calling the next node
    {
        nodesatdepth++;
        //nodes=0;
        //int i=0;
         for (int i=0; i<9 ; i++)
          {
                temp= state;
                //nodes++;
                if ( temp.make_move(colour, i)==true)//try to make a move. if its an allowed move, then create the next branch of the tree, and store the info about this particular node.
                {



                    temp_node= Tree_Node(this, &temp, !maximize, pgoesfirst);//construct the next level down of leaves
                    //Problem: RHS is temporary. so,when i return up the chain, the objects get destructed, and thus i get sigsev.

                     leaves[i]= &temp_node;

                    test_value= leaves[i]->value ;


                    //assign a value to this node using minmax  algorithm
                    if (maximize==true)
                        best_value= std::max( test_value, best_value);
                    else /*(maximize==false)*/
                        best_value= std::min( test_value, best_value);
                }
                else //not an allowed move
                    leaves[i]= NULL;
           }
           value=best_value;
    }
}


Computer::Computer (Game_State* p_game, char player_colour, bool playergoesfirst)// constructor
: tree (p_game, playergoesfirst)
{


    if (player_colour=='X')
        colour= 'O';

    else if (player_colour=='O')
        colour= 'X';

    else
    {


        cout<< "an error has occured, computer could not choose colour."<<endl;
        cout<<"press enter to end the program"<<endl;
        string input;
        getline(cin, input);
        exit (1);
    }
    //note that the Tree constructor is allso called (check the prototype declaration to see this call)

}



//computer fuctions
bool Computer::make_move(Game_State* p_game)
{

    int position=-1;//initially set the move-to-make to a dissallowed value.

    double max=0;//play the move that maximizes this value
    Tree_Node* trial_leaf= NULL;


    //loop through searching for moves until a move is found that can be played.
    do
    {
        //search the game tree for the best move
        for (int i=0; i<9 ; i++)
        {
            trial_leaf = tree.current_leaf->get_lower_node ( i);
            //if a move in position i is a disslowed move, then trial_leaf will be assigned a value of NULL.

            if (trial_leaf!= NULL) //check that its an allowed move
             {
                 if (trial_leaf->get_node_value()> max)//is this move better than all the other moves found so far?
                 {
                    max= trial_leaf->get_node_value();//it is the best move found so far
                    position= i;
                 }
             }
        }

    }while (p_game->make_move(this->get_colour(), position) == false);

    return true;
}


