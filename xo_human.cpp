#include "xo_functions.h"
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <windows.h>
using namespace std;

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
bool Human::make_move (Game_State* p_game)
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


