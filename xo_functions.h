// --------------- Header guard ---------------------------
#ifndef xo_functions_H
#define xo_functions_H


//---------------- protoype declarations --------------------------
//the detail of what these finctions do is in the .cpp file of the same name.

//this function is implemented in xo_game.cpp
void instructions(void);//prints instruction on how to play to std::out


//---------------------------------------------------------------
//the implementation of these next classes is in xo_game.cpp
//------------------------------------------------------------
class Game_State
{
    char board[9];// board is numbered from 0 to 8.
    int game_turn;
public:
    Game_State (void); //default constructor
    Game_State (const Game_State& input) ;//this is a custom copy constructor, the default copy constructor does not fit my needs.

    void draw_board (void);
    bool make_move (char player_colour, int position);//returns true, and updates the game state if 'position' is a legal move. else, returns false
    char victory (void);//returns X if X has won, O if O has won. else returns ' '.
    int get_turn(void);
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
//the implementation of these next classes is in xo_AI.cpp
//-------------------------------------------------------------
class Tree_Node
{
    protected:
       Game_State state, temp;


       //bool max_or_min; //true if this node is a maximum of the previous nodes.
       double value; //+10 for victory from this node, -10 if this node causes loss.
                            //eventually i plan to a wider variety of numbers here.

       int depth; //0 for top level nodes, all the way down to 8 for terminating nodes.

       //At each ply, there are potentially up to 8 different ways the game can develop
       Tree_Node* leaves [8]; //array of pointers to the potentially up to 8 different game leafs that are below this game leaf.
                                    //some of the pointers might be NULL if moves cannot be played there

    public:
        Tree_Node(Tree* tree, Tree_Node* current_leaf,  Game_State* p_game, bool maximize, bool pgoesfirst); //constructor. second argument is an array of pointers to the lower down nodes
        Tree_Node(); //empty constructor for making temporary tree_node objects
        Tree_Node(const Tree_Node& input) ;//copy constructor

        double get_node_value(void);
        Tree_Node* get_lower_node (int i);//returns leaves[i]

        //double get_next_node(int depth);//returns a rarandom leaf at
};

class Tree//will store the best possible move at each node
{
        Tree_Node* head;//pointer to the first leaf in the game tree

        bool playergoesfirst;//true if player is X, false if computer is X
        //int minimax (bool maximising);//used in constructing the game tree.
        
        int array[9];//this will store how many nodes there are at each depth. 
                    //eg, at depth=0, there should be 9 nodes; and at depth=1, there should be 9*8=72 nodes
       
   public:
       //Tree(void); //empty constructor for testing

        Tree(Game_State* p_game, bool pgoesfirst); //constructor.
    
        ~Tree();//this destructor cals the delete function for all the pointers

        Tree_Node* current_leaf;//iterator
        Tree_Node* get_node(int i);//returns a pointer to the next node after the current_leaf


        //Game_Leaf* picknextmove(double randomness);//returns the next play the computer should make
                                                    //if randomness is non zero, then the computer will sometimes pick non optimal moves
};



class Computer: public Player //computer is a subclass of player
{
    protected:
        Tree tree;
        char colour;
        double randomness;//if randomness is non zero, then the computer will sometimes pick non optimal moves
    public:
        Computer(Game_State* p_game, char player_colour, bool playergoesfirst)  ; //will construct the computer object to play as the opposite colour. Also call the game_tree constructor.
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





/*
//Game_State functions
class Game_State;
Game_State::Game_State (void);//constructor. done
void Game_State::draw_board (void);//prints the current game to the screen. done
bool Game_State::make_move (char player_colour, int position);
char Game_State::victory (void);//check whether X or O has won.

//player functions
char Player::get_colour();

//human functions. Human inherits from player
Human::Human(void);
bool Human::make_move (Game_State* p_game);


//computer fuctions. Computer inherits from player.
void Computer::make_move(Game_State* p_game);
void Computer::make_move (void);
Computer::Computer(char player_colour, char whoplaysfirst);//default constructor

//other functions
void instructions(void);


// This is the end of the header guard

*/
#endif
