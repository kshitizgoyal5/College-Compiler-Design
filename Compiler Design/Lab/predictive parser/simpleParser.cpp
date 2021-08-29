#include<bits/stdc++.h>
using namespace std;

/*
Grammar :-

A -> TE
E -> +TE | epsi
T -> FS
S -> *FS | epsi
F -> (E) | int
*/

map<pair<string, string>, vector<string>> table;
set<string> non_terminals;
string start = "A";			// start of Grammar

stack<string> stk;
string cur;
int index = 0;

void ShowStack(){
	stack<string> temp;
	int size = 0;
	while(!stk.empty()){
		temp.push(stk.top());
		stk.pop();
	}
	while(!temp.empty()){
		cout<<temp.top()<<" ";
		size+=temp.top().size()+1;
		stk.push(temp.top());
		temp.pop();
	}
	cout<<std::setw(30-size)<<cur.substr(index, cur.size()-index);
	cout<<endl;
}

bool check(){
	string s = stk.top();
	stk.pop();
	if(s == "epsi"){
		return true;
	}
	if(s == "$"){
		return (s[0] == cur[index++]); 
	}
	if(s == "int"){
		int c = cur[index++] - '0';
		if(c >=0 && c <= 9) return true;
		return false;
	}
	if(non_terminals.find(s) == non_terminals.end()){
		if(s.size() > 1) return false;
		return (s[0] == cur[index++]);
	}
	// lexical analysis of character in input string
	string terminal;
	char c = cur[index];
	// rules
	if(c-'0' >=0 && c-'0'<=9) terminal = "int";
	//else ifs...
	else terminal += c;
	if(table.find({s, terminal}) == table.end()) return false;
	auto tokens = table[{s, terminal}];
	for(int i=tokens.size()-1; i>=0; i--){
		stk.push(tokens[i]);
	}
	return true;
}

bool PredictiveParser(){
	index = 0;
	stk.push("$");
	stk.push(start);
	ShowStack();
	while(!stk.empty()){
		if(!check()) return false; 
		ShowStack();
	}
	return true;
}


int main(){
	// filling table manually
	table[{"A", "int"}] = {"T", "E"};
	table[{"A", "("}] = {"T", "E"};
	
	table[{"E", "+"}] = {"+", "T", "E"};
	table[{"E", ")"}] = {"epsi"};
	table[{"E", "$"}] = {"epsi"};
	
	table[{"T", "int"}] = {"F", "S"};
	table[{"T", "("}] = {"F", "S"};
	
	table[{"S", "+"}] = {"epsi"};
	table[{"S", "*"}] = {"*", "F", "S"};
	table[{"S", ")"}] = {"epsi"};
	table[{"S", "$"}] = {"epsi"};
	
	table[{"F", "int"}] = {"int"};
	table[{"F", "("}] = {"(", "E", ")"};
	
	non_terminals.insert("A");
	non_terminals.insert("E");
	non_terminals.insert("T");
	non_terminals.insert("S");
	non_terminals.insert("F");
	cur = "0+1*2a$";
	cout<<"STACK\t\t\tString"<<endl<<endl;
	if(PredictiveParser()) cout<<"YES";
	else cout<<"NO";
	return 0;
}













