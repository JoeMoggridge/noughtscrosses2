
//Game_State functions
Game_State::Game_State (void)//constructor. done
{
    game_turn=0;

    for (int i=0; i<9; i++)
        board [i]=' ';
}
void Game_State::draw_board (void)//prints the current game to the screen. done
{
    cout << endl;

    for (int i=0; i<3; i++)
    {
        cout << " ";

        for (int j=0; j<3; j++)
        {
            if (board [3*i+j]== 'X')//For each row, we want the label to inrease by 3, hence the multiple of 3.
                cout << "X";
            else if (board [3*i+j]=='O')
                cout << "O";
            else if (board [3*i+j]==' ')
                cout << " ";

            if (j!=2)
                cout <<" | ";
        }

        cout <<endl;

        if (i!=2)
            cout << "---+---+---\n";

    }
}
bool Game_State::make_move (char player_colour, int position)//done
{
    if (board[position]==' ')
    {
        board[position]=player_colour;
        game_turn++;
        return true;
    }
    else
        return false;//not a valid play. say so.

}
char Game_State::victory (void)//check whether X or O has won.
{
    char list [3] = "XO";

    for (int i=0; i<2; i++)// check for X victory and then check for O victory
    {
        if (board [0]== list[i] && board [3*(1)+1]==list[i] && board [3*(2)+2]==list[i])//check leading diagonal
            return list[i];
        if (board [2]== list[i] && board [3*(1)+1]==list[i] && board [3*(2)]==list[i])//check other diagonal
            return list[i];

        for (int i=0; i<3; i++)
        {
            if (board [3*i]== list[i] && board [3*i+1]==list[i] && board [3*i+2]==list[i])//check for horizontal line
                return list[i];

            for (int j=0; j<3; j++)
            {
                if (board [3*i+j]== list[i] && board [3*(i+1)+j]== list[i] && board [3*(i+2)+j]==list[i])//check for vertical line
                    return list[i];
            }
        }
    }
    //else, if no victory position is found, return false
    return (' ');
}

//player functions
char Player::get_colour()
{
    return colour;
}

//human functions
Human::Human(void)//done
{
    string input;
    int i=0;

    do//repeatably ask for input until the user enters the correct thing
    {
        if (i>0)
            cout<< "please enter either X or O, nothing else" <<endl;

        cout << "If you would like to play as X, and therfore play first, type X." <<endl;
        cout << "Otherwise, if you would like to play as O, type O" <<endl;

        getline (cin,input);

        if (input=="h" ||  input=="help")
        {
            instructions ();
            i=0;
        }

        else
            i++;

    }
    while (i <100 && input!="X" && input!="x"&& input!="O"&& input!="o" && input!="0");

    if (input=="X" || input=="x")
        colour= 'X';
    else if (input=="O"|| input=="o" || input=="0")
        colour= 'O';
    else
    {
        cout<< "an error has occured. could not interpret which colour you want to play."<<endl;
        cout<<"press enter to end the program"<<endl;
        getline(cin, input);
        exit (1);
    }

}
bool Human::make_move (Game_State* p_game)//TODO
{
    string input="blank";
    int processed_input=9;//set to a dissalowed value to start with. we hope that this will be changed.
    int i=0;

    do//repeatedly check whether the given position is a valid move
    {
        do//repeatedly ask the user for input
        {
            if (i>0)
                cout<< "please enter a number between 0 and 8, nothing else" <<endl;

            cout<<"where would you like to play?"<<endl;
            getline (cin,input);

            if (input=="h" || input=="help")
            {
                instructions ();
                i=0;
                input="blank";
            }
            else
                i++;

            //these next lines could be massively simplified if i could use "std::stoi".
            //However, my compiler doesnt support it.
            if (isdigit(input[0])==true)
                processed_input = atoi (input.c_str());
            else
                processed_input=9;//wrong input, therfore ask the user to try again.

        }
        while (processed_input>9 || processed_input<0);//stop asking when the user enters a valid integer


        //ask the game whether the chosen position is a legal move
        //note the use of the "->" operator. this selects a member function from the class pointed to be the thingy on the LHS
        if (p_game->make_move(colour, atoi(input.c_str()))==true)
            return true;//valid play has been made

        else
        {
            cout<< "you cannot play there!"<<endl;
            //then loop round until the player enters a valid play
            i=0;

        }

    }
    while (i<100);//random 100 here because why not

    return false;
}

double Game_Tree::Game_Tree(Game_state* p_game, bool playergoesfirst)
{
    //runs the minimax algorithm in order to contrauct the game tree and assign weights to each node.
    
    double best_value=0;
    double V;
    Game_Leaf* trial_leaf, next_leaf;
    const double INF= std::numeric_limits<float>::infinity();
    bool maximizing= !playergoesfirst;
    int win_value= 10 ;//defines the weight associated with a win
    int index; //used to cut down the number of if satements
    double weighting; //defines how the wieght of a previos node is determined based on the lower nodes
    
    
    //recursively call each layer. build tree from bottom up.
     depth=9; 
    
    //base case
    if (depth > 8 || p_game->victory()!= ' ')//'if (this is a terminating node)'
    {
        
        for (int i=0; i<9 ; i++)
        {
            //these next two if statements are used to make sure maximum and minimums are correctly assigned.
            if (playergoesfirst==true)
                index =1;
            else /*playergoesfirst=false*/
                index=0;

            if (p_game->victory()=='X') //x win
                trial_leaf= Tree_Node(p_game, win_value*pow(-1, index));
            else if (p_game->victory()=='O' )   //o win
                trial_leaf= Tree_Node(p_game, win_value*pow(-1, index+1));
            else    //draw
               trial_leaf=Tree_Node(p_game, 0);
            
            next_leaf.leaves[i]= trial_leaf;
        }
        
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

//other functions
void instructions(void)//done
{
    cout<< "when asked to make a play, enter a number between zero and 8."<<endl<<endl;

    cout <<" 0 | 1 | 2 \n";
    cout <<"---+---+---\n";
    cout <<" 3 | 4 | 5 \n";
    cout <<"---+---+---\n";
    cout <<" 6 | 7 | 8 \n";

    cout<<endl<< "type 'help' or 'h' at any point in order to bring up these instructions again."<<endl<<endl;
}
