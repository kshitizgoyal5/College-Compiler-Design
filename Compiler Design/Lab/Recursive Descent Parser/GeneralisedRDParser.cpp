#include<bits/stdc++.h>
using namespace std;

class Grammar{
public:
	Grammar(vector<string> g){
		start = "";
		for(auto rule: g){  			// for every production rule in Grammar
			auto t = split(rule);		// store the Symbol of the non terminal
			string non_terminal = t[0];
			if(start.size() == 0) start = non_terminal; 	// if it is first non terminal then save it as Start
			t.erase(t.begin());		// split the tokens from the rule
			grammar[non_terminal].push_back(t);		// and store int map -> grammar
		}
	}
	bool check(string token, int &i){			// To check if token is valid
		if(token == "epsi") return true;			// if token is epsilon 
		if(token == "[0-9]" || token == "int"){					// if token is digit
			int x = cur[i++] - '0';
			if(x >=0 && x <=9) return true;
			return false;
		}
		if(token.size() > 1) return false;		// unknown token (possible error)
		return token[0] == cur[(i)++];			// if current character of the input string(cur) 
												// is same as token in production rule, return true;
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
	
	bool recursiveDescentParser(string non_terminal, int &pos, bool last){  // last == true when the non_terminal will end the input string
		int copy = pos;													// store index of current character till which the search is successful
		for(auto production_rule: grammar[non_terminal]){				// for every rule of the non-terminal, loop till
			bool temp = true;											// the rule satisfies the input string
			int size = production_rule.size();							
			for(string token: production_rule){
				size--;
				if(grammar.find(token) != grammar.end()){					// if token is non terminal	
					if(last && size == 0)								    // if last == true and token is the ending of the rule,
					temp &= recursiveDescentParser(token, pos, true);	    // then it will end the input string 
					else temp &= recursiveDescentParser(token, pos, false);
				}
				else{	// token can be character or Keyword
					temp &= check(token, pos);
				}
				if(temp == false){ // input string dont follow the current production rule
					break;
				}
			}
			if(temp == true ){		// input string follow the current production rule
				if(last){			
					if(pos == cur.size()) return true;	// input string ends, else current rule only satisfies a part of input string
				}
				else return true;
			}
			pos = copy;
		}
		return false;
	}
	
	bool verify(string s){
		cur = s;
		int pos = 0;
		return recursiveDescentParser(start, pos, true);
	}
	
	void ShowGrammar(){
		for(auto non_terminal: grammar){
			cout<<non_terminal.first<<" -> ";
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
	
private:
	map<string, vector<vector<string>>> grammar;
	string cur;
	string start;
};

int main(){
	string s = "input3.txt";
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
	cout<<"Grammar : "<<endl;
	g.ShowGrammar();
	string ss = "aaaaaaaaab";
	cout<<"Input String = "<<ss<<endl;
	if(g.verify(ss)) cout<<"YES";
	else cout<<"NO";
	return 0;
}
