/*function CONVERTTONFA ( enfa )
Initialize an empty object of type NFA with variable name t
Initialize t . numstates = enfa . numstates , t . numalphabets = enfa .
numalphabets and
t . finalstates = enfa . finalstates
Iterate through each of the state i in Q
Initialize l to the closure of state i of e - N F A enfa
Iterate through each of the input symbol j in Z
Initialize an empty list of states f
Iterate through each state k in l
Add all states of enfa . transitiontable [ k ][ j + 1] to f
Remove all the duplicates from f
Compute the e - closure c of f
Set t . transitiontable [ i ][ j ] = c
Return t as the NFA without e - transitions corresponding to the
e - NFA enfa
end function*/
#include "bits/stdc++.h"

using namespace std;

set<int> epsilon_closure(vector<vector<set<int> > > transitions, int start){
        queue<int> answer;
        set<int> res;
        answer.push(start);
        int t;
        while(!answer.empty()){
                t = answer.front();
                cout<<t<<" ";
                if(res.find(t) == res.end())
                    res.insert(t);
                for(auto i = transitions[t][0].begin(); i != transitions[t][0].end(); i++)
                        answer.push(*i);
                answer.pop();
        }
        cout<<endl;
        return res;
}

int main(){

        vector<vector<set<int> > > transitions;
        vector<vector<set<int> > > nfa_transitions;
        int states,symbols;
        vector<string> sym;
        string s;
        cout<<"Enter number of states\n";
        cin>>states;
        cout<<"Enter number of symbols\n";
        cin>>symbols;
        cout<<"Enter symbols"<<endl;
        sym.push_back("ε");
        for(int i = 1; i < symbols; i++){
                cin>>s;
                sym.push_back(s);
        }
        transitions.resize(states);
        nfa_transitions.resize(states);
        for(int i = 0; i < states; i++){
            transitions[i].resize(symbols);
            nfa_transitions[i].resize(symbols);
        }
        int t;
        int val;
        for(int i = 0; i < states; i++){
            for(int j = 0; j < symbols; j++){
                    cout<<"Enter number of transitions for state "<<i<<" and symbol "<<sym[j]<<endl;
                    cin>>t;
                    cout<<"Enter transition states\n";
                    while(t--){
                        cin>>val;
                        transitions[i][j].insert(val);
                    }
            }
        }
        vector<set<int> > eClos;
        eClos.resize(states);
        for(int i = 0; i < states; i++){
            cout<<i<<" : ";
            eClos[i] = epsilon_closure(transitions,i);
        }
        for(int i = 0; i < states; i++){
                for(int j = 1; j < symbols; j++){
                    for(auto itr = eClos[i].begin(); itr != eClos[i].end(); itr++){
                        for(auto jtr = transitions[*itr][j].begin(); jtr != transitions[*itr][j].end(); jtr++){
                            if(nfa_transitions[i][j].find(*jtr) == nfa_transitions[i][j].end())
                                nfa_transitions[i][j].insert(*jtr);
                        }
                    }
                }            
        }
        cout<<endl;
        for(int i = 0; i < states; i++){
            for(int j = 1; j < symbols; j++){
                for(auto itr = nfa_transitions[i][j].begin(); itr != nfa_transitions[i][j].end(); itr++){
                    for(auto jtr = eClos[*itr].begin(); jtr != eClos[*itr].end(); jtr++){
                        if(nfa_transitions[i][j].find(*jtr) == nfa_transitions[i][j].end())
                            nfa_transitions[i][j].insert(*jtr);
                    }
                }
            }
        }
        for(int i = 0; i < states; i++){
            for(int j = 1; j < symbols; j++){
                cout<<i<<" -> "<<sym[j]<<" : ";
                for(auto itr = nfa_transitions[i][j].begin(); itr != nfa_transitions[i][j].end(); itr++)
                    cout<<*itr<<" ";
                cout<<endl;
            }
            cout<<endl;
        }
        return 0;
}
