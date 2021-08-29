#include<bits/stdc++.h>
using namespace std;

/*
Grammar:
E -> T | T + E
T -> int | int*T | (E)
*/

string str;
int index = 0;
bool match(string token){
	if(token == "int"){
		int c = str[index++] - '0';
		if(c >=0 && c <= 9) return true;
		return false;
	}
	else{
		char c = token[0];
		return c == str[index++];
	}
}
bool T(bool last=false);
bool E(bool last=false);

bool E1(bool last=false){
	return T(last);
}

bool E2(bool last=false){
	if(T()){
		if(match("+")){
			if(E(last)) return true;
		}
	}
	return false;
}

bool E(bool last){
	int copy = index;
	bool x = E1(last);
	if(x){
		if(last){
			if(index == str.size()) return true;
		}
		else return true;
	}
	index = copy;
	x = E2(last);
	if(x){
		if(last){
			if(index == str.size()) return true;
		}
		else return true;
	}
	index = copy;
	return false;
}

bool T1(bool last=false){
	return match("int");
}

bool T2(bool last=false){
	if(match("int")){
		if(match("*")){
			if(T(last)) return true;
		}
	}
	return false;
}

bool T3(bool last=false){
	if(match("(")){
		if(E()){
			if(match(")")){
				if(last) return index == str.size();
				return true;
			}
		}
	}
	return false;
}

bool T(bool last){
	int copy = index;
	if(T1(last)) {
		if(last){
			if(index == str.size()) return true;
		}
		else return true;
	}
	index = copy;
	if(T2(last)) {
		if(last){
			if(index == str.size()) return true;
		}
		else return true;
	}
	index = copy;
	if(T3(last)) {
		if(last){
			if(index == str.size()) return true;
		}
		else return true;
	}
	index = copy;
	return false;
}

int main(){
	str = "(1+1)+1";
	cout<<"input string = "<<str<<endl;
	index = 0;
	if(E(true)) cout<<"YES";
	else cout<<"NO";
	cout<<endl<<"index = "<<index<<endl;
	cout<<"size of string = "<<str.size()<<endl;
}
