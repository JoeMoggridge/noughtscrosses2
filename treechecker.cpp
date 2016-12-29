#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <errno.h>
#include "xo_game.h"//include prototype declarations for game functions.
                            //the classes themselves are written in other .cpp files
#include "xo_computer.h"//include prototype declarations for AI classes

using namespace std;


Tree_Checker::Tree_Checker(Tree* tree)
{
    linked_tree = tree;
    tree_is_good= false;

    for (int i=0; i<9; i++)
        tree_is_zero[i]=false;


    logfile.open("logfile.txt");

}

bool Tree_Checker::output_at_depth (int aimed_depth, Tree_Node* this_leaf)
{//recursive function that outputs all the nodes at aimed_depth which are children of this_leaf
    //returns true unless something weird happens

    int current_depth= this_leaf->depth();
    bool function_result=true;
    int output;

    if (aimed_depth<1 || aimed_depth>9|| current_depth> aimed_depth)
        return false;
    else
    {
        if (current_depth==aimed_depth)//base case
        {
            output= this_leaf->get_node_value();
            logfile<< output<< " " ;
            if (output!=0)
            {
                tree_is_zero[aimed_depth]=false;
            }
            return true;
        }
        else//recursive case
        {
            Tree_Node* test_leaf;

            for (int i=0; i<=9;i++)
            {
                test_leaf= this_leaf->get_lower_node(i);//note that get lower node might return NULL!

                //PROBLEM
                //this part of the program breaks because
                //for some reason these if statements cant identify when this_leaf is a NULL pointer
                //GRRRRRR.
                if (this_leaf==NULL)
                {
                    cout<<"im confused"<<endl;
                }
                if (this_leaf!= (Tree_Node*)NULL)
                {
                    //if a previous leaf has already returned false, then make sure not to overwrite this fact
                    if (function_result== false||output_at_depth(aimed_depth, test_leaf)==false)
                    function_result= false;

                }
                else//this node is NULL, notate it so.
                    logfile<< "- ";


            }
        }
        return function_result;//any errors will be passed up the recursive stack.
    }

}

bool Tree_Checker::check_tree()
{
    //investigate the tree
    check_tree(1, 4);

    //were all the nodes zero?
    for (int i=1; i<10; i++)
        if (tree_is_zero[i]==true)
            tree_is_good=false;//notate that all the nodes at this depth were zero, and therefore there is a problem.

    if (tree_is_good==true)
    {
        logfile<< endl<<endl<<"~~~~~~  TREE IS GOOD ~~~~~~"<<endl;
        cout<<"(DEBUGGING NOTE: tree is good)"<<endl;
    }
    else
    {
        logfile<<endl<<endl;
        logfile<< "--------------------------------------------------" <<endl;
        logfile<< "~~~~~~  TREE IS NOT GOOD!!!!!!!! PROBLEM!!!!~~~~~~" <<endl;
        logfile<< "--------------------------------------------------" <<endl;
        cout<<"(DEBUGGING NOTE: tree is NOT good !!!!!!!!!!!!!!!!!)"<<endl;
    }
}


bool Tree_Checker::check_tree(int min_depth, int max_depth)
//checks that the tree is complete, and ouptuts some info to a log file
{
    if (max_depth<min_depth)
    {
        errno=1;
        return false;
    }

    tree_is_good=true;//set it to true unless we discover otherwise. we're about to find out.

    Tree_Node* this_leaf =linked_tree->head;//this means that this function can exit without having changed anything in the tree object


    for (int i= min_depth; i<=max_depth; i++)
    {
        logfile<<"At depth= "<< i <<" nodes have the following values:"<<endl;
        if (tree_is_good==false || output_at_depth(i, this_leaf)==false)
            tree_is_good=false;
        logfile<<endl;
    }

    return tree_is_good;

}
