
#include "xo_classes.h"
#include <algorithm> // needed for calls to max()
#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;


//----------------------------
//Tree stuff
//-----------------------
Tree::Tree (Game_State* p_game)//constructor
{
    current_leaf= NULL;
    first=p_game->goes_first();


    for (int i=0; i<9; i++)
        array[i]= 0;

    //recursively builds the tree:
    head= new Tree_Node(this,  p_game, true);

}

Tree_Node* Tree::get_node( int i)
{

       return current_leaf->get_lower_node(i);
}

Tree::~Tree()
{
        head->Prune ();//destruct everything below the head node, ie destruct everything
}


//-----------------------------
//Tree_Node stuff
//--------------------
/*
Tree_Node::Tree_Node(Tree* tree, Game_State* p_game, bool maximize)
{//construct the head node and recursively call Make_Node in order to construct the rest of the tree

    //copy the input game state into this class.
    //note that the class Game_State has a custom copy constructor.
    this->state = *p_game;

    //we can work out what colour the curerent player is by considering the fact that X alwatys plays first,
    //and the computer will always be trying to maximize
    char colour;
    if (maximize== p_game->player_first())
        colour= 'O';
    else
        colour= 'X';

    //create some variables that will be used in calcualting the node value:
    double best_value=0, test_value;
    Tree_Node temp_node();// this node is constructed using the constructor for temporary Tree_Node objects


        for (int i=0; i<9; i++)
            {
                tree->array[0]++;

                this->temp_game= state;

                if( temp_game.make_move(colour, i)==true)//try to make a move. if its an allowed move, then create the next branch of the tree, and store the info about this particular node.
                {

                    temp_node= new Make_Node(tree, &temp_game, !maximize);//construct the next level down of leaves

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
}*/
 Tree_Node::Tree_Node(void) //empty constructor for making temporary Tree_Node objects
: state(false), temp_game(false)
 {
     state= Game_State(true);
     //state.get_turn()= 10;//set this to a dissalowed value as a flag for the fact that this is temporary object

     for (int i=0; i<9; i++)
        leaves[i]= NULL;
 }
Tree_Node::Tree_Node(const Tree_Node& input) //copy constructor
{
    value= input.value;
    state= input.state;//note that this calls my custom copy operator for game states

    for (int i=0; i<9; i++)
        leaves[i]= input.leaves[i];

}
Tree_Node::Tree_Node(Tree* tree, Game_State* p_game, bool maximize)//construct Nodes recursively.
 {

    //copy the input game state into this class.
    //note that the class Game_State has a custom copy constructor.
    this->state = *p_game;

    tree->array[state.get_turn()]++;//notate the existence of this node

    //we can work out what colour the curerent player is by considering the fact that X alwatys plays first,
    //and the computer will always be trying to maximize
    char colour;
    if (maximize== p_game->goes_first())
        colour= 'O';
    else
        colour= 'X';

    //create some variables that will be used in calcualting the node value:
    double best_value=0, test_value;
    int win_value=1;//this is the wieght that will be assigned for a win
    Tree_Node temp_node();// this node is constructed using the constructor for temp Tree_Node objects




    if (p_game->victory()!= ' ' || this->state.get_turn()> 8 )//base case. This is a terminating node.
    {
        //set all the sub nodes to NULL
        for (int i=0; i<9;i++)
            leaves[i]=NULL;

        //set the value of this terminating node depending on who has won
        //this is a bit confusingly done. could i maybe use a switch statement here instead?
        int index=1;
        if (maximize==true)
           index++;
        if (p_game->victory()== 'X')
           value= win_value*pow(-1, index);
        if (p_game->victory()== 'O')
           value= win_value*pow(-1, index+1);


    }
    else //general recursive case. construct this node by calling the next node
    {

         for (int i=0; i<9 ; i++)
          {
                temp_game= state;

                if ( temp_game.make_move(colour, i)==true)//try to make a move. if its an allowed move, then create the next branch of the tree, and store the info about this particular node.
                {
                    temp_node= new Make_Node(tree, &temp_game, !maximize);//construct the next level down of leaves

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
           this->value = best_value;
    }
}

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

void Tree_Node::Prune()//recursively calls the delete function on all lower nodes, and then deletes this node.
{
    for (int i=0; i<9; i++)
       leaves[i] -> Prune ();

    delete this;
}


