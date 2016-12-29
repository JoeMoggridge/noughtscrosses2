
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <windows.h>//needed for call to "exit()"
#include <math.h>
#include "xo_game.h"//include prototype declarations for game functions.
                            //the classes themselves are written in other .cpp files
#include "xo_computer.h"//include prototype declarations for AI classes

using namespace std;

//----------------------------
//Tree stuff
//-----------------------
Tree::Tree (Game_State* p_game)//constructor
{
    current_leaf= NULL;
    first=p_game->goes_first();


    for (int i=0; i<10; i++)
        nodesatdepth[i]= 0;

    //recursively builds the tree:
    head= new Tree_Node(this,  p_game, true);

    current_leaf= head;

    Tree_Checker test1(this);
    test1.check_tree();

}


Tree_Node* Tree::get_node( int i)
{
       return current_leaf->get_lower_node(i);
}

Tree::~Tree()
{
        head->Prune ();//destruct everything below the head node, ie destruct everything
}

bool Tree::increment_bin( int i)
{
    if (i<0 || i>9)
    {
        cout<< "OOB error"<<endl;
        return false;
    }
    /*else*/
    nodesatdepth[i]++;
    return true;
}


//-----------------------------
//Tree_Node stuff
//--------------------
 Tree_Node::Tree_Node(void) //empty constructor for making temporary Tree_Node objects
 {
     state= Game_State(true);
     //state.get_turn()= 10;//set this to a dissalowed value as a flag for the fact that this is temporary object

     for (int i=0; i<9; i++)
        leaves[i]= NULL;
 }
Tree_Node::Tree_Node(const Tree_Node& input) //copy constructor
{
    value= input.value;
    state= input.state;//note that this calls my custom copy operator for Game_State objects

    for (int i=0; i<9; i++)
        leaves[i]= input.leaves[i];

}
Tree_Node::Tree_Node(Tree* tree, Game_State* p_game, bool maximize)//construct Nodes recursively.
 {

    //copy the input game state into this class.
    //note that the class Game_State has a custom copy constructor.
    this->state = *p_game;

    if (tree->increment_bin(state.get_turn())==false)//notate the existence of this node
    {
        cout<< "error in notating number of nodes" <<endl;
        exit(-1);
    }

    //we can work out what colour the curerent player is by considering the fact that X alwatys plays first,
    //and the computer will always be trying to maximize
    char colour;
    if ( p_game->goes_first()==true)
        colour= 'O';//player is X, therfore computer is O.
    else
        colour= 'X';

    //create some variables that will be used in calcualting the node value:
    double best_value=0, test_value;
    int win_value=1;//this is the wieght that will be assigned for a win

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
                    leaves[i]= new Tree_Node(tree, &temp_game, !maximize);//construct the next level down of leaves

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
int Tree_Node::depth(void)
{
    return state.get_turn();
}


