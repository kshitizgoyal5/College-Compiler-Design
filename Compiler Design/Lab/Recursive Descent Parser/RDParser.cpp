#include<bits/stdc++.h>
using namespace std;

/*

Grammar:
E -> T | T+E
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
bool T();
bool E();

bool E1(){
	return T();
}

bool E2(){
	if(T()){
		if(match("+")){
			if(E()) return true;
		}
	}
	return false;
}

bool E(){
	int copy = index;
	bool x = E2();
	if(x) return true;
	index = copy;
	x = E1();
	if(x) return true;
	index = copy;
	return false;
}

bool T1(){
	return match("int");
}

bool T2(){
	if(match("int")){
		if(match("*")){
			if(T()) return true;
		}
	}
	return false;
}

bool T3(){
	if(match("(")){
		if(E()){
			if(match(")")) return true;
		}
	}
	return false;
}

bool T(){
	int copy = index;
	if(T1()) return true;
	index = copy;
	if(T2()) return true;
	index = copy;
	if(T3()) return true;
	index = copy;
	return false;
}

int main(){
	str = "1+1ab";
	index = 0;
	if(E()) cout<<"YES";
	else cout<<"NO";
	cout<<endl<<"index = "<<index<<endl;
	cout<<"size of string = "<<str.size()<<endl;
}
