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

class Human: public Player //human is a subclass of player
{
    public:
        Human (void);//default constructor. lets the player choose his colour

        bool make_move (Game_State* p_game);//returns true if a legal move has just been played. else, returns false
    //                                  //its important that this function accepts a pointer as its argument, and not he actual class object,
    //                                  //if it accepted the class itself then a temporay object would be creted of the wrong scope which screws everything up.
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
        Tree_Node(Tree_Node* current_leaf,  game_state* p_game); //constructor. second argument is an array of pointers to the lower down nodes
        Tree_Node(Tree_Node* current_leaf, game_state* p_game, int value); //constructor for a terminating node.

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
    head= Tree_Node(current_leaf, p_game);
}

Tree_Node::Tree_Node(Tree_Node* current_leaf,  game_state* p_game, bool maximize)
//constructor. 
 {
    bool maximize; 
    
    if (current_leaf= NULL)
    {
        //initial call. construct the head node.
        *state = *p_game; //PROBLEM i need to redefine the copy operator for class Game_State. 
                        //at the moment we're simply equating the pointers, which is not enough.
        *temp= *state;
        
        double best_value =0, test_value;
        if (maximize==true)
        {
            for (int i=0; i<9 i++)
            {
                if( temp.make_move(i)==true);
                {
                    leaves[i]= Tree_Node(leaves[i], temp, !maximize);//construct the next level down of leaves
                    test_value= leaves[i]->value ;
                    if (maximize==true)
                           best_value= max(test_value, best_value);
                    else if (maximize==false)
                        best_value= min(test_value, best_value);
                }
                else //not an allowed move
                    leaves[i]= NULL;
            }
            node_value = best_value;
        }
         
                
            
        node_value= max(all sub nodes)
    }
    
    
    
    
    
    
    
    
    
    double best_value=0;
    double V;
    Game_Leaf* trial_leaf, next_leaf;
    const double INF= std::numeric_limits<float>::infinity();
    bool maximizing= !pgoesfirst;
    int win_value= 10 ;//defines the weight associated with a win
    int index, depth=0; //used to cut down the number of if satements
    double weighting; //defines how the weight of a previous node is determined based on the lower node    
           //base case
    if (depth > 8 || p_game->victory()!= ' ')//'if (this is a terminating node)'
    {
        

            //these next two if statements are used to make sure maximum and minimums are correctly assigned.
            if (playergoesfirst==true)
                index =1;
            else /*playergoesfirst=false*/
                index=0;

            if (trial_leaf->p_game->victory()=='X') //x win
            {
                trial_leaf= Tree_Node(trial_leaf->p_game, win_value*pow(-1, index));
            }
            else if (trial_leaf->p_game->victory()=='O' )   //o win
                trial_leaf= Tree_Node(trial_leaf->p_game, win_value*pow(-1, index+1));
            else    //draw
                trial_leaf=Tree_Node(trial_leaf->p_game, 0);
            
       
        
        
    }
    //else recursive
    else
    {
        for (int i=0; i<(9-depth) ; i++)
        {
                 current_leaf = Tree_Node(p_game, Current )
                

         }
    }
    
    //asisgn the head leaf
    /*
    for (int depth=0; depth<8; depth++)
    {//loop throught the entire tree, generate the tree.
        
        if (maximizing==true)
            best_value = −INF;
        else /* minimizing player*/
         /*   best_value = INF;
        
        
        }
        
        maximizing= !maximizing;
        
    }
    
    /*
    if (depth > 8 || p_game->victory()!= ' ')//'if (this is a terminating node)'
    {
        int index=0;//this is used to change the sign of the terminating nodes, depending on whehter a victory for X is good or bad
        if (player goesfirst==true)
            index=1;
        
        if (p_game->victory()=='X' && playergoesfirst== true)
                this.current_leaf->node_value= 10*pow(-1, index);
        else if (p_game->victory()=='O')
                this.current_leaf->node_value= 10*pow(-1, index+1);
        }
    }
         return node.get_node_value();
         
    
    */
        
 }
        
Tree_Node(Tree_Node* current_leaf, game_state* p_game, int value);
 {
            
}

//computer fuctions
void Computer::make_move(Game_State* p_game)
{
    

    minimax(tree.head, 0, TRUE )
    
    /*
    int position=-1;
    double max=0;
    game_leaf* trial_leaf= NULL;
    do//loop through searching for moves until a move is found that can be played.
    {
        //1) search the game tree for the best move
        for (int i=0; i<9 ;i++)
        {
            trial_leaf = tree.current_leaf->get_next_leaf (i);
            
            if (trial_leaf.get_node_value()> max)
            {
                max= trial_leaf.get_node_value();
                position= i;
            }
        }
        
    } while (p_game->make_move(computer.get_colour(), position) == false);
    */

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

