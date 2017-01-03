// --------------- Header guard ---------------------------
#ifndef xo_computer_H
#define xo_computer_H

#include <fstream>
using namespace std;

// ----------------prototype declarations --------------


//-----------------------------------------------------------------
//the implementation of these next classes is in xo_tree.cpp
//-------------------------------------------------------------
class Tree; //forward declaration

class Tree_Node
{
    friend class Tree;

    protected:
        Game_State state, temp_game;

        double value; //+1 for victory from this node, -1 if this node causes loss.
                            //eventually i plan to a wider variety of numbers here.


        //At each ply, there are potentially up to 8 different ways the game can develop
        Tree_Node* leaves [8]; //array of pointers to the potentially up to 8 different game leafs that are below this game leaf.
                                    //some of the pointers might be NULL if moves cannot be played there

        void Prune ();//recursively delete all the pointers below this one
    public:
        //constructors:
        Tree_Node(Tree* tree,  Game_State* p_game, bool maximize);//recursively construct nodes
        Tree_Node(); //empty constructor for making temporary tree_node objects
        Tree_Node(const Tree_Node& input) ;//copy constructor

        //functions:
        double get_node_value(void);
        Tree_Node* get_lower_node (int i);//returns leaves[i]
        int depth(void);



};


class Tree//will store the best possible move at each node
{
        friend class Tree_Checker;//tree_checker is basically an empty class that contains some functions
                            // useful for investigating the constructed tree

        Tree_Node* head;//pointer to the first leaf in the game tree

        bool first;//true if player is X, false if computer is X

        int nodesatdepth[10];//this will store how many nodes there are at each depth.
                    //eg, at depth=0, there should be 9 nodes; and at depth=1, there should be 9*8=72 nodes

   public:
        Tree(Game_State* p_game); //constructor.

        ~Tree();//this destructor calls the prune function from the head down
        Tree_Node* current_leaf;//iterator
        Tree_Node* get_node(int i);//returns a pointer to the next node down in position i branching from the current_leaf
        bool increment_bin(int i);//increments the relevant bin of nodesatdepth
};

class Tree_Checker
{//this is mostly just a useful way of grouping some otherwise confusing functions.
    //note that this class is a friend of class Tree.

        bool output_at_depth(int aimed_depth, Tree_Node* this_leaf);//outputs the values of all the nodes at aimed depth, that branch from this leaf.
                                                        //therefore, if you want to out put ALL the nodes at a given depth then you need to pass head_node as the second argument
                                                        //only works if 'this_leaf->state.game_turn' is lower than aimed_depth
                                                        //if this is not the case, then the function returns false.

        Tree* linked_tree;
        bool tree_is_zero [9];//this array will store true for each layer of the tree that is all zero.
                            //initialised to all be false.
        bool tree_is_good; //initialised to false.
                            //this variable will subsequently store the return value of the latest call to check_tree

        ofstream logfile;//this will be where information is outputted to.

        bool check_tree(int min_depth, int max_depth);//checks that all the nodes between min_depth and max_depth are non zero.

   public:
        Tree_Checker(Tree* tree); //constructor.

        bool check_tree();//calls check_tree(int, int), and then outputs some things to console

        //bool check_leaf(Tree_Node* this_leaf);

};


//-----------------------------------------------------------------
//the implementation of these next classes is in xo_computer.cpp
//-------------------------------------------------------------
class Computer: public Player //computer is a subclass of player
{
    protected:
        Tree tree;

        double randomness;//if randomness is non zero, then the computer will sometimes pick non optimal moves
    public:
        Computer(Game_State* p_game)  ; //will construct the computer object to play as the opposite colour. Also call the game_tree constructor.
        Computer ()= default; //default constructor
        bool make_move (Game_State* p_game);//changes the object passed to it to reflect the new board state

};

#endif
