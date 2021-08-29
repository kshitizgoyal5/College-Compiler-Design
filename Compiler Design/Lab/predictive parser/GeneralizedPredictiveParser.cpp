#include<bits/stdc++.h>
using namespace std;

class Grammar{
public:
	Grammar(vector<string>& g){
		start = "";
		for(auto rule: g){  			// for every production rule in Grammar
			auto t = split(rule);		// store the Symbol of the non terminal
			string non_terminal = t[0];
			if(start.size() == 0) start = non_terminal; 	// if it is first non terminal then save it as Start
			non_terminals.insert(non_terminal);
			t.erase(t.begin());		// split the tokens from the rule
			grammar[non_terminal].push_back(t);		// and store int map -> grammar
		}
		ShowGrammar();
		CreateFirst();
		CreateFollow();
		CreateTable();
	}
	
	vector<string> split(string &s){			// to split string at '/b'{sapce}
		vector<string> ans;
		string temp="";
		for(auto c: s){
			if(c == ' '){
				if(temp.size()>0){
					ans.push_back(temp);
					temp = "";
				}
			}
			else temp += c;
		}
		if(temp.size() > 0) ans.push_back(temp);
		return ans;
	}
	
	void ShowGrammar(){
		cout<<"\tGrammar:"<<endl;
		for(auto non_terminal: grammar){
			cout<<non_terminal.first;
			cout<<"-> ";
			int s = non_terminal.second.size();
			for(auto pro_rule: non_terminal.second){
				s--;
				for(auto token: pro_rule) cout<<token;
				if(s) cout<<" | ";
			}
			cout<<endl;
		}
		cout<<endl;
	}

	void DFS(string child){
		if(First.find(child) != First.end()) return;
		else{
			for(auto p: grammar[child]){
				bool check = false;
				int ii = 0;
				while(ii < p.size()){
					check = false;
					string t = p[ii];
					if(grammar.find(t) == grammar.end()){
						First[child].insert(t);
					}
					else{
						DFS(t);
						for(auto c: First[t]){
							if(c == "epsi") check = true;
							else First[child].insert(c);
						}
					}
					if(!check) break;
					ii++;
				}
				if(check && ii == p.size()) First[child].insert("epsi");
			}
		}
	}
	
	void CreateFirst(){
		for(auto i: grammar){
			if(First.find(i.first) == First.end()){
				DFS(i.first);	
			}
		}
		ShowFirst();
	}
	
	void ShowFirst(){
		cout<<"\tFIRST : "<<endl;
		for(auto i: First){
			cout<<i.first<<" : ";
			for(auto j: i.second) cout<<j<<" ";
			cout<<endl;
		}
		cout<<endl;
	}
	
	// Creating Follow set for Grammar
	
	void DFS2(string curr, map<string, stack<string>>& temp){
		if(temp[curr].empty()) return;
		else{
			while(!temp[curr].empty()){
				string t = temp[curr].top();
				temp[curr].pop();
				if(curr == t) continue;
				if(!temp[t].empty()) DFS2(t, temp);
				for(auto tt: Follow[t]){
					Follow[curr].insert(tt);
				}
			}
		}
	}
	
	void CreateFollow(){
		map<string, stack<string>> temp;
		Follow[start].insert("$");
		for(auto rules: grammar){
			string non_terminal = rules.first;
			auto r = rules.second;
			for(auto t: r){
				for(int i=0; i<t.size(); i++){
					if(grammar.find(t[i]) != grammar.end()){
						if(i+1 == t.size()){
							temp[t[i]].push(non_terminal);
						}
						else if(grammar.find(t[i+1]) == grammar.end())
							Follow[t[i]].insert(t[i+1]);
						else{
							int j = i+1;
							bool check;
							while(j < t.size()){
								check = false;
								if(grammar.find(t[j]) == grammar.end())
									Follow[t[i]].insert(t[j]);
								for(auto tt: First[t[j]]){
									if(tt == "epsi"){
										check = true;
									}
									else Follow[t[i]].insert(tt);
								}
								if(!check) break;
								j++;
							}
							if(check) temp[t[i]].push(non_terminal);
						}
					}
				}
			}
		}	
		for(auto i: temp){
			if(!i.second.empty()){
				DFS2(i.first, temp);
			}
		}
		ShowFollow();	
	}
	
	void ShowFollow(){
		cout<<"\tFollow : "<<endl;
		for(auto i: Follow){
			cout<<i.first<<" : ";
			for(auto j: i.second) cout<<j<<" ";
			cout<<endl;
		}
		cout<<endl;
	}
	
	// Create Parsing Table
	void CreateTable(){
		for(auto rules: grammar){
			string non_terminal = rules.first;
			auto r = rules.second;
			for(auto rule: r){
				bool check = false;
				for(auto token: rule){
					if(token == "epsi"){
						for(auto b: Follow[non_terminal]){
							table[{non_terminal, b}] = rule;
						}
						break;
					}
					else if(grammar.find(token) == grammar.end()){
						table[{non_terminal, token}] = rule;
						break;
					}
					else{
						check = false;
						for(auto a: First[token]){
							if(a == "epsi"){
								check = true;
							}
							else table[{non_terminal, a}] = rule;
						}
						if(!check) break;
					}
				}
				if(check) {
					for(auto b: Follow[non_terminal]){
						table[{non_terminal, b}] = rule;
					}
				}
			}
		}
		ShowTable();
	}
	
	void ShowTable(){
		cout<<"\tTable : "<<endl;
		for(auto i: table){
			cout<<i.first.first<<" - "<<i.first.second<<"\t\t";
			for(auto j: i.second){
				cout<<j;
			}
			cout<<endl;
		}
		cout<<endl;
	}
	
	//Predictive Parser
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
		cout<<"STACK\t\t\tINPUT"<<endl;
		ShowStack();
		while(!stk.empty()){
			if(!check()) return false; 
			ShowStack();
		}
		return true;
	}
	
	void Verify(string s){
		cur = s;
		bool result = PredictiveParser();
		if(result) cout<<"YES";
		else cout<<"NO";
	}
	
private:
	map<string, vector<vector<string>>> grammar;
	map<string, set<string>> First;
	map<string, set<string>> Follow;
	map<pair<string, string>, vector<string>> table;
	set<string> non_terminals;
	string start;
	stack<string> stk;
	string cur;
	int index = 0;
};


int main(){
	string s = "input2.txt";
	ifstream file(s);
	vector<string> grammar;
	string temp;
	if(file.is_open()){
		while(getline(file, temp)){
			grammar.push_back(temp);
		}
	}
	else{
		cout<<"CANNOT OPEN FILE"<<endl;
	}
	Grammar g(grammar);
	g.Verify("1+0*2$");
}
