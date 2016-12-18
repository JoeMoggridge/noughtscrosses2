


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
    *state = *p_game;
    *temp= *state;

    if (current_leaf= NULL)//if this conditoin is met, then this is the head node. construct the head node.
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
         for (int i=0; i<9 ; i++)
          {

                if( temp.make_move(colour, i)==true);//try to make a move. if its an allowed move, then create the next branch of the tree, and store the info about this particular node.
                {
                    leaves[i]= Tree_Node(this, temp, !maximize, pgoesfirst);//construct the next level down of leaves
                    test_value= leaves[i]->value ;


                    //assign a value to this node using minmax  algorithm
                    if (maximize==true)
                        best_value= max( test_value, best_value);
                    else /*(maximize==false)*/
                        best_value= min( test_value, best_value);
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

    int position=-1;//initially set the move-to-make to a dissallowed value.

    double max=0;//play the move that maximizes this value
    game_leaf* trial_leaf= NULL;


    //loop through searching for moves until a move is found that can be played.
    do
    {
        //search the game tree for the best move
        for (int i=0; i<9 ; i++)
        {
            trial_leaf = tree.current_leaf->get_node (tree.curent_leaf->depth+1, i);
            //if a move in position i is a disslowed move, then trial_leaf will be assigned a value of NULL.

            if (trial_leaf!= NULL) //check that its an allowed move
             {
                 if (trial_leaf.get_node_value()> max)//is this move better than all the other moves found so far?
                 {
                    max= trial_leaf.get_node_value();//it is the best move found so far
                    position= i;
                 }
             }
        }

    }while (p_game->make_move(computer.get_colour(), position) == false)

}


Computer::Computer(Game_state* p_game, char player_colour, bool playergoesfirst)//default constructor
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

    //note that the Tree constructor is allso called (check the prototype declaration to see this call)

}

