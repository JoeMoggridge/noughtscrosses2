#include <stdio.h>
#include <iostream>
#include <string.h>
#include <windows.h>//needed for call to "exit()"
#include <math.h>
#include "xo_game.h"//include prototype declarations for game functions.
                            //the classes themselves are written in other .cpp files
#include "xo_computer.h"//include prototype declarations for AI classes

using namespace std;



/*bool Tree_Checker::check_leaf(Tree_Node* this_leaf)
{//returns true if all the nodes below this leaf are zero.
    bool allnodeszero=true;
    Tree_Node* test_leaf;

    for (int i=0; i<9;i++)
    {
        test_leaf= this_leaf->get_lower_node(i)

        if (test_leaf->get_value()!=0)
        {
            allnodeszero=false;
            break;
        }
    }

    if (allnodeszero==true)
    {
        cout<<"at depth=" << current_leaf->state.get_turn()<<", all the nodes have zero value." <<endl;
    }
    else
    {
       cout << cout<<"at depth=" << test_leaf->state.get_turn()+1 <<",  there exist non zero nodes."<<endl;
       cout<< "these are the nodes values:" <<endl;

        output_at_depth(test_leaf->state.get_turn()+1, 0);//output all the nodes at a given depth

    }

}*/

bool Tree_Checker::output_at_depth (int aimed_depth, Tree_Node* this_leaf)
{
    int current_depth= this_leaf->state.game_turn;
    bool function_result=true;

    if (aimed_depth<1 || aimed_depth>9|| current_depth> aimed_depth)
        return false;
    else
    {
        if (current_depth==aimed_depth)//base case
        {
            cout<< this_leaf->value<< endl;
            return true;
        }
        else//recursive case
        {
            Tree_Node* test_leaf;

            for (int i=0; i<=9;i++)
            {
                test_leaf= this_leaf->get_lower_node(i);

                if (function_result== false||output_at_depth(aimed_depth, test_leaf)==false)
                    function_result= false;
                    //if a previous leaf has already returned false, then make sure not to overwrite this information
            }
        }
        return function_result;//any errors will be passed up the recursive stack.
    }

}


bool Tree_Checker::check_tree(void)//checks that the tree is complete, and ouptuts some info to a log file
{
    /*
    Tree_Node* saved_leaf =current_leaf;//this means that this function can exit without having changed anything in the tree object
    bool allnodeszero;
    Tree_Node* upper_leaf=current_leaf;




    }



    current_leaf= saved_leaf;*/
}
