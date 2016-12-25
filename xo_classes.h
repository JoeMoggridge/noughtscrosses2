// --------------- Header guard ---------------------------
#ifndef xo_functions_H
#define xo_functions_H

using namespace std;
//---------------- protoype declarations --------------------------
//These are the declarations for the classes etc that are called in main.cpp
//the classe's implementations are in other files.

//this function is implemented in xo_game.cpp
void instructions(void);//prints instruction on how to play to std::out


//---------------------------------------------------------------
//the implementation of these next classes is in xo_game.cpp
//------------------------------------------------------------
class Game_State
{
    char board[9];// board is numbered from 0 to 8.
    int game_turn;
    bool first;//true if the player goes first, false if the computer goes first
public:
    Game_State (bool playerfirst); //constructor
    Game_State (void);//default constructor used for making temporary tree objects
    Game_State (const Game_State& input) ;//this is a custom copy constructor, the default copy constructor does not fit my needs.

    void draw_board (void);
    bool make_move (char player_colour, int position);//returns true, and updates the game state if 'position' is a legal move. else, returns false
    char victory (void);//returns X if X has won, O if O has won. else returns ' '.
    int get_turn(void);
    bool goes_first();
};

class Player //abstract class
{
protected:
    char colour;
public:
    char get_colour(void);
    virtual bool make_move(Game_State* p_game) =0;//virtual function because "=0"
};


//-----------------------------------------------------------------
//the implementation of these next classes is in xo_tree.cpp
//-------------------------------------------------------------
class Tree; //forward declaration

class Tree_Node
{
    protected:
        Game_State state, temp_game;

        double value; //+1 for victory from this node, -1 if this node causes loss.
                            //eventually i plan to a wider variety of numbers here.


        //At each ply, there are potentially up to 8 different ways the game can develop
        Tree_Node* leaves [8]; //array of pointers to the potentially up to 8 different game leafs that are below this game leaf.
                                    //some of the pointers might be NULL if moves cannot be played there



        //Make_Node(Tree* tree,  Game_State* p_game, bool maximize);//recursively build nodes
    public:
        //constructors:
        Tree_Node(Tree* tree,  Game_State* p_game, bool maximize);//recursively construct nodes
        Tree_Node(); //empty constructor for making temporary tree_node objects
        Tree_Node(const Tree_Node& input) ;//copy constructor

        //functions:
        double get_node_value(void);
        Tree_Node* get_lower_node (int i);//returns leaves[i]

        void Prune ();//recursively delete all the pointers below this one

};

class Tree//will store the best possible move at each node
{
        Tree_Node* head;//pointer to the first leaf in the game tree

        bool first;//true if player is X, false if computer is X
        //int minimax (bool maximising);//used in constructing the game tree.

        int nodesatdepth[10];//this will store how many nodes there are at each depth.
                    //eg, at depth=0, there should be 9 nodes; and at depth=1, there should be 9*8=72 nodes

   public:
       //Tree(void); //empty constructor for testing

        Tree(Game_State* p_game); //constructor.

        ~Tree();//this destructor calls head->Delete_Node(this)

        Tree_Node* current_leaf;//iterator
        Tree_Node* get_node(int i);//returns a pointer to the next node after the current_leaf
        bool increment_bin(int i);//increments the relevant bin of nodesatdepth


        //Game_Leaf* picknextmove(double randomness);//returns the next play the computer should make
                                                    //if randomness is non zero, then the computer will sometimes pick non optimal moves
};


//-----------------------------------------------------------------
//the implementation of these next classes is in xo_computer.cpp
//-------------------------------------------------------------
class Computer: public Player //computer is a subclass of player
{
    protected:
        Tree tree;
        char colour;
        double randomness;//if randomness is non zero, then the computer will sometimes pick non optimal moves
    public:
        Computer(Game_State* p_game)  ; //will construct the computer object to play as the opposite colour. Also call the game_tree constructor.
        Computer ()= default; //default constructor
        bool make_move (Game_State* p_game);//changes the object passed to it to reflect the new board state

};

//------------------------------------------------------
// this class is implemented in human.cpp
//---------------------------------------------------
class Human: public Player //human is a subclass of player
{
    public:
        Human (void);//default constructor. lets the player choose his colour

        bool make_move (Game_State* p_game);//returns true if a legal move has just been played. else, returns false
    //                                  //its important that this function accepts a pointer as its argument, and not he actual class object,
    //                                  //if it accepted the class itself then a temporay object would be creted of the wrong scope which screws everything up.
};



#endif

