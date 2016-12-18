
//Game_State functions
Game_State::Game_State (void)//constructor. done
{
    game_turn=0;

    for (int i=0; i<9; i++)
        board [i]=' ';
}
 Game_state (const Game_state &input) //copy constructor
{
    game_turn= input.game_turn;

    for (int i=0; i<9; i++)
        board [i]=input.board[i];

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
