#include "PDA_CFG.cpp"
int main()
{
    vector<string> temp;
    ifstream fin;
    FileRead(fin);
    cout<<"___________________________________"<<endl;
    cout<<"THE INPUT PDA IS :\n";
    DisplayPDA();
    cout<<"___________________________________"<<endl;
    cout<<"Corresponding CFG :\n";
    PDA_to_CFG(init_state, input_symbol, stack_top, final_state, push_stack,states);

}
