#include <bits/stdc++.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

//Vectors to store the tuples of PDA
//eg δ(q,a,a) = (p,ε)
//states --> q p
//input_symbol --> a
//init_state --> q
//final_state --> p
//stack_top --> a
//push_stack --> a

//States in the PDA
vector<string> states;

//Input symbol
vector<string> input_symbol;

//Stores the initial state and final state after transition
vector<string> init_state;
vector<string> final_state;

//Stores the top of the stack
vector<string> stack_top;

//Element to be pushed onto the stack
vector<string> push_stack;

void FileRead(ifstream &);
void DisplayPDA();
void Permute(vector<string>, vector<string> &,vector<vector<string> > &,int );
void Print_Permutes(string, string, string, string, string, vector<string>);
void PDA_to_CFG(vector<string> &, vector<string> &, vector<string> &, vector<string> &, vector<string> &, vector<string>);
