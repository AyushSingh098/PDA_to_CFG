#include "PDA_CFG.h"
void FileRead(ifstream &fin)
{
    string line,ch,temp;
    fin.open("input_pda.txt");
    if(!fin)
    {
        cerr<<"ERROR IN OPENING FILE\n";
        exit(1);
    }
    //Get each line of the input file
    getline(fin,line);
    istringstream ss(line);
    //First line in input file contains the states in PDA
    while(ss >> ch)
    {
        states.push_back(ch);
    }
    int i,j;
    //Subsequent lines contain the transitions eg. δ(q,a,a) = (p,ε)
    while(getline(fin,line))
    {
        istringstream ss(line);
        ss>>ch;
        istringstream s2(ch);
        i=0;
        //seperate by comma
        while(getline(s2,temp,','))
        {
           if(i==0)
           {
                //Erase the first three terms i.e. δ(
                temp.erase(temp.begin(),temp.begin()+3);
                init_state.push_back(temp);
           }
           else if(i==1)
           {
                input_symbol.push_back(temp);
           }
           else if(i==2)
           {
                //Erase the last term i.e. )
                temp.erase(temp.end()-1,temp.end());
                stack_top.push_back(temp);
           }
           i++;
        }
        ss>>ch;
        ss>>ch;
        istringstream s3(ch);
        i=0;
        while(getline(s3,temp,','))
        {
            if(i==0)
            {
                //remove the opening paranthesis and save the final state
                temp.erase(temp.begin(),temp.begin()+1);
                final_state.push_back(temp);
            }
            else if(i==1)
            {
                //remove the ending paranthesis and save the element to be pushed
                //onto to the stack
                temp.erase(temp.end()-1,temp.end());
                push_stack.push_back(temp);
            }
            i++;
        }
    }
}

void DisplayPDA()
{
  cout<<"STATES = ";
  int i,j;
  for(i=0 ; i<states.size() ; i++)
  {
      cout<<states[i]<<" ";
  }
  cout<<endl;
  for( i=0 ; i<init_state.size() ; i++)
  {
      cout<<"δ("<<init_state[i]<<","<<input_symbol[i]<<","<<stack_top[i]<<") = ("<<final_state[i]<<","<<push_stack[i]<<")\n";
  }
}

//Permuting all the variables in the Grammar (composite [pXq]) using standard recursive permutation technique
void Permute(vector<string> states, vector<string> &temp,vector<vector<string> > &permutes,int x)
{
    if(x == 0)
    {
        permutes.push_back(temp);
    }
    else
    {
        for(int i=0 ; i<states.size() ; i++)
        {
            temp[x-1] = states[i];
            Permute(states,temp,permutes,x-1);
        }
    }
}

void Print_Permutes(string init_state, string input_symbol, string stack_top, string final_state, string push_stack, vector<string> states)
{
    int i,j;
    vector<string>temp(push_stack.size());
    vector<vector<string > >permutes;
    Permute(states,temp,permutes,push_stack.size());
    for(i=0 ; i<permutes.size() ; i++)
    {
        cout<<"["<<init_state<<stack_top;
        cout<<permutes[i][0]<<"] -> "<<input_symbol<<" ["<<final_state<<push_stack[0];
        for(j=1 ; j<permutes[i].size() ; j++)
        {
            cout<<permutes[i][j]<<"] ["<<permutes[i][j]<<push_stack[j];
        }
        cout<<permutes[i][0]<<"]\n";
    }
}

void PDA_to_CFG(vector<string> &init_state, vector<string> &input_symbol, vector<string> &stack_top, vector<string> &final_state, vector<string> &push_stack, vector<string> states)
{
    int i,j,n = init_state.size();
    cout<<"START STATE = S -> ";
    cout<<"["<<states[0]<<"X"<<states[0]<<"]";
    //PRINTING THE COMPOSITE SYMBOL [pXq] FOR START STATE
    for(i=1 ; i<states.size() ; i++)
    {
        cout<<" | ["<<states[0]<<"X"<<states[i]<<"]";
    }
    cout<<endl;
    //PRINTING ALL THE VARIABLES OF IN THE GRAMMAR USING THE STATE AND STACK SYMBOLS
    for(i=0 ; i<n ; i++)
    {
        cout<<"\nδ("<<init_state[i]<<","<<input_symbol[i]<<","<<stack_top[i]<<") = ("<<final_state[i]<<","<<push_stack[i]<<")\n";
        if(push_stack[i].compare("ε") == 0)
        {
            cout<<"["<<init_state[i]<<stack_top[i]<<final_state[i]<<"] -> "<<input_symbol[i]<<endl;
        }
        else
        {
            //Otherwise print all the permutations from states and stack symbols
            Print_Permutes(init_state[i],input_symbol[i],stack_top[i],final_state[i],push_stack[i],states);
        }
    }
    cout<<endl;
    for(i=0 ; i<states.size() ; i++)
    {
        for(j=0 ; j<states.size() ; j++)
        {
            cout<<"["<<states[i]<<"X"<<states[j]<<"] -> ε\n";
        }
    }
}
