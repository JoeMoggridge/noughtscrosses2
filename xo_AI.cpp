//contains
class Tree;//prototype declaration

class Computer: public Player //computer is a subclass of player
{
    protected:
        Game_Tree* tree;
        
        //TODO: double randomness;//if randomness is non zero, then the computer will sometimes pick non optimal moves
    public:
        Computer(char player_colour, bool playergoesfirst):  tree(playergoesfirst); //will construct the computer object to play as the opposite colour. Also call the game_tree constructor.
        bool make_move (Game_State* p_game);//changes the object passed to it to reflect the new board state
        
};


class Tree_Node
{
    protected:
       Game_state* state, temp;
  

       //bool max_or_min; //true if this node is a maximum of the previous nodes.
       double value; //+10 for victory from this node, -10 if this node causes loss.
                            //eventually i plan to a wider variety of numbers here.
      
       int depth; //0 for top level nodes, all the way down to 8 for terminating nodes.

       //At each ply, there are potentially up to 8 different ways the game can develop
       Tree_Node leaves [8]; //array of pointers to the potentially up to 8 different game leafs that are below this game leaf.
                                    //some of the pointers might be NULL if moves cannot be played there

    public:
        Tree_Node(Tree_Node* current_leaf,  game_state* p_game, bool maximize, bool pgoesfirst); //constructor. second argument is an array of pointers to the lower down nodes
        
    //Tree_Node(Tree_Node* current_leaf, game_state* p_game, int value); //constructor for a terminating node.

        double get_node_value(void);
        Tree_node* get_lower_node (int i);//returns leaves[i]
        
        //double get_next_node(int depth);//returns a rarandom leaf at 
};
class Tree//will store the best possible move at each node
{
        Tree_Node* head;//pointer to the first leaf in the game tree
        Tree_Node* current_leaf;//iterator
        bool playergoesfirst;//true if player is X, false if computer is X
        //int minimax (bool maximising);//used in constructing the game tree.
   public:
        Game_Tree(Game_State* p_game, bool pgoesfirst); //constructor. 
        
        double get_next_node(int depth, int i);//returns the next node at a given depth.
  
        //Game_Leaf* picknextmove(double randomness);//returns the next play the computer should make
                                                    //if randomness is non zero, then the computer will sometimes pick non optimal moves
};



Tree::Tree( Game_state* p_game, bool pgoesfirst)//constructor
{
    curent_leaf= NULL;
    playergoesfirst=pgoesfirst;

    //recursively builds the tree:
    head= Tree_Node(current_leaf, p_game, true, pgoesfirst);
}

Tree_Node::Tree_Node(Tree_Node* current_leaf,  game_state* p_game, bool maximize, bool pgoesfirst)
//constructor. 
 {
    
    depth= p_game->depth;
    
    //create some variable that will be used in vcalcualting the node value
    int win_value=1;//this is the wieght that will be assigned for a win
    double scale=0.1;
    
    int index=1;
    
    //we can work out what colour the curerent player is by considering the fact that X alwatys plays first, 
    //and the computer will always be trying to maximize
    char colour;
    if (maximize== pgoesfirst)
        colour= 'O';
    else
        colour= 'X';
    
    
    *state = *p_game; //PROBLEM i need to redefine the copy operator for class Game_State. 
                        //at the moment we're simply equating the pointers, which is not enough.
    *temp= *state;
    
    if (current_leaf= NULL)//this is the initial call. construct the head node.
    {
               
        double best_value =0, test_value;
        if (maximize==true)
        {
            for (int i=0; i<9 i++)
            {
                best_value=0;
                if( temp.make_move(colour, i)==true);//try to make a move. if its an allowed move, then create the next branch of the tree, and store the info about this particular node.
                {
                    leaves[i]= Tree_Node(this, temp, !maximize, pgoesfirst);//construct the next level down of leaves
                    test_value= leaves[i]->value;

                    //seacrh for the best node from the next level down
                    //TODO make the upper node a more complicated combination of the lower nodes
                    if (maximize==true)
                        best_value= max(test_value, best_value);
                    else if (maximize==false)
                        best_value= min(test_value, best_value);
                }
                else //not an allowed move
                    leaves[i]= NULL;
            }
            value = best_value;//assign this nodes value
        }
    }
    else if (p_game->victory()!= ' ' || depth> 8 )//base case. This is a terminating node.
    {
        //set all the sub nodes to NULL
        for (int i=0; i<9 i++)
            leaves[i]=NULL;
        
        //set the value of this terminating node depending on who has won
        if (maximize==true);
           index++; 
        if (p_game->victory()== 'X')
           value= win_value*pow(-1, index);
        if (p_game->victory()== 'O')
           value= win_value*pow(-1, index+1);
        
        
    }
    else //general recursive case. construct this node by calling the next node
    {
         double best_value, test_value, accumulator=0;
         for (int i=0; i<9 ; i++)
          {
                best_value=0, accumulator=0;;
                if( temp.make_move(colour, i)==true);//try to make a move. if its an allowed move, then create the next branch of the tree, and store the info about this particular node.
                {
                    leaves[i]= Tree_Node(this, temp, !maximize, pgoesfirst);//construct the next level down of leaves
                    test_value= leaves[i]->value ;

                    
                    //assign a value to this node based on a sum of the lower nodes
                    //TODO this might be a stupid way of assigning value. 
                    //for example, the minimax algorithm just picks the biggest/smallest at each level.
                    //maybe it would make more sense to assign greater weight to nodes that cause victory at a smaller depth.
                    if (maximize==true)
                        accumulator+= test_value*scale;
                    else if (maximize==false)
                        accumulator-= test_value*scale;
                }
                else //not an allowed move
                    leaves[i]= NULL;
           }
           value=accumulator;
    }
}       

//computer fuctions
void Computer::make_move(Game_State* p_game)
{

    int position=-1;
    double max=0;//play the move that maximizes this value
    game_leaf* trial_leaf= NULL;
    do//loop through searching for moves until a move is found that can be played.
    {
        //1) search the game tree for the best move
        for (int i=0; i<9 ;i++)
        {
            trial_leaf = tree.current_leaf->get_next_node (tree.curent_leaf->depth, i);
            
            if (trial_leaf.get_node_value()> max)
            {
                max= trial_leaf.get_node_value();
                position= i;
            }
        }
        
    } while (p_game->make_move(computer.get_colour(), position) == false);
    

}


Computer::Computer(char player_colour, char whoplaysfirst)//default constructor
{

    if (player_colour=='X')
        colour= 'O';

    else if (player_colour=='O')
        colour= 'X';

    else
        cout<< "an error has occured, computer could not choose colour."<<endl;
        cout<<"press enter to end the program"<<endl;
        string input;
        getline(cin, input);
        exit (1);
}

