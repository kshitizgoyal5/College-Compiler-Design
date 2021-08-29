#include<bits/stdc++.h>
using namespace std;

vector<pair<string, vector<string>>> production_rules;
map<string, map<string, pair<string, string>>> table; // state -> map{ token -> {move, state}}

stack<string> stk;
string cur;
string Action;
int idx;

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
	cout<<std::setw(30-size)<<cur.substr(idx, cur.size()-idx);
	cout<<"\t\t\t"<<Action;
	cout<<endl;
}

bool check(){
	string state = stk.top();
	string token;
	if(cur[idx]-'0' >=0 && cur[idx]-'0'<=9) token = "int";
	else token += cur[idx];
	
	if(table[state].find(token) == table[state].end()) return false;
	
	string move = table[state][token].first;
	string next_state = table[state][token].second;
	if(move == "A"){
		while(!stk.empty()) stk.pop();
	}
	else if(move == "S"){
		stk.push(token);
		idx++;
		Action = "SHIFT";
		stk.push(next_state);
	}
	else if(move == "R"){
		int size = 2 * production_rules[stoi(next_state)-1].second.size();
		int check_index = production_rules[stoi(next_state)-1].second.size()-1;
		
		Action = production_rules[stoi(next_state)-1].first + "-> ";
		for(auto i: production_rules[stoi(next_state)-1].second) Action+=i;
		
		while(size > 0){
			if(stk.empty()) return false;
			stk.pop();
			if(stk.empty() || stk.top() != production_rules[stoi(next_state)-1].second[check_index--]) return false;
			stk.pop();
			size-=2;
		}
		if(stk.empty()) return false;
		string new_state = stk.top();
		string look_up_token = production_rules[stoi(next_state)-1].first; 
		stk.push(look_up_token); 
		if(table[new_state].find(look_up_token) == table[new_state].end()) return false;
		stk.push(table[new_state][look_up_token].second);
	}
	return true;
}

void LR_0(){
	idx = 0;
	stk.push("0");
	ShowStack();
	while(!stk.empty()){
		if(!check()){
			cout<<"STRING NOT ACCEPTED"<<endl;
			return;
		}
		ShowStack();
	}
	cout<<"ACCEPTED"<<endl;
}

vector<string> Split(string& temp){
	vector<string> T;
	string t;
	for(auto &c: temp){
		if(c == ' '){
			if(t.size()) T.push_back(t);
			t = "";
		}
		else t += c;
	}
	if(t.size()) T.push_back(t);
	return T;	
}

void ReadRules(){
	string s = "rules.txt";
	ifstream file(s);
	string temp;
	
	if(file.is_open()){
		cout<<"GRAMMAR: "<<endl;
		while(getline(file, temp)){
			vector<string> rule;
			string off;
			rule = Split(temp);
			off = *rule.begin();
			rule.erase(rule.begin());
			cout<<off<<"-> ";
			for(auto i: rule) cout<<i;
			cout<<endl;
			production_rules.push_back({off, rule});
		}
		cout<<endl;
	}
	else{
		cout<<"CANNOT OPEN FILE"<<endl;
	}
}

void ReadTable(){
	string s = "table.txt";
	ifstream file(s);
	string temp;
	
	if(file.is_open()){
		vector<string> tokens;
		int index = -1;
		cout<<"PARSE TABLE: "<<endl<<endl;
		while(getline(file, temp)){
			vector<string> t = Split(temp);
			if(index == -1){
				tokens = t;
				cout<<"STATE\t";
				for(auto i: t) cout<<i<<"\t";
			}
			else{
				cout<<index<<"\t";
				for(int i=0; i<tokens.size(); i++){
					cout<<t[i]<<"\t";
					if(t[i][0] != '_'){
						// map<int, map<string, pair<string, int>>> table;
						table[to_string(index)][tokens[i]] = make_pair(t[i][0], t[i].substr(1, t[i].size()-1));
					}
				}
			}
			cout<<endl;
			index++;		
		}
		cout<<endl;
	}
	else{
		cout<<"CANNOT OPEN FILE"<<endl;
	}
}

int main(){
	ReadRules();
	ReadTable();
	cout<<"Input String : ";
	cin>>cur;
	cout<<endl;
	cur += '$';
	LR_0();
}













