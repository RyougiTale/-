#include <stdio.h>
#include <string.h>
#include <iostream>
#define num 20
using namespace std;

char code[80],token[6];
char ch;
int sys,p,m,n,sum;
int f=0;
string temp="";
string key[num] = {"main", "if", "then", "while", "do", "int", "return", "for", "include", "print", "iostream", "namespace", "std", "cout", "using"};


bool iskey(string a){
	for(int i=0; i<num; i++){
		if(key[i]==a) return true;
	}	
	return false;
}


void scaner(int &f){
	if((code[f]>='a' && code[f]<='z') || (code[f]>='A' && code[f] <='Z')){
		temp+=code[f];
		f++;
		while((code[f]>='a' && code[f]<='z') || (code[f]>='A' && code[f] <='Z') || (code[f]>='0' && code[f] <='9')){
			temp+=code[f];
			f++;
		}
		f--;
		if(iskey(temp)){
			if(temp=="void") cout<<temp<<" "<<"28"<<" ";
			else if(temp=="int") cout<<temp<<" "<<"29"<<" ";
			else if(temp=="float") cout<<temp<<" "<<"30"<<" ";
			else if(temp=="char") cout<<temp<<" "<<"31"<<" ";
			else if(temp=="if") cout<<temp<<" "<<"32"<<" ";
			else if(temp=="else") cout<<temp<<" "<<"33"<<" ";
			else if(temp=="while") cout<<temp<<" "<<"34"<<" ";
			else if(temp=="do") cout<<temp<<" "<<"35"<<" ";
			else if(temp=="for") cout<<temp<<" "<<"36"<<" ";
			else cout<<temp<<" "<<"49"<<" ";
		}
		else cout<<temp<<" "<<"1"<<" ";
		return;
	}
	if(code[f]>='0' && code[f] <='9'){
		temp+=code[f];
		f++;
		while(code[f]>='0' && code[f] <='9'){
			temp+=code[f];
			f++;
		}
		f--;
		cout<<temp<<"2"<<" ";
		return;
	}
	if((code[f]=='+' || code[f]=='-' || code[f]=='e') && code[f+1]>='0' && code[f+1]<='9'){
		temp+=code[f];
		f++;
		while(code[f]>='0' && code[f] <='9'){
			temp+=code[f];
			f++;
		}
		f--;
		cout<<temp<<" "<<"有符号整数"<<" ";
		return;
	}
	if(code[f]=='+' || code[f]=='-' || code[f]=='*' || code[f]=='/' || code[f]=='>' || code[f]=='=' || code[f]=='<' || code[f]==',' || code[f]==';' || code[f]==':' || code[f]=='.' || code[f]=='{' || code[f]=='}'){
		temp+=code[f];
		if((code[f]=='>' || code[f]=='=' || code[f]=='<') && code[f+1]=='='){
			f++;
			temp+=code[f];
			if(temp=="<=") cout<<temp<<" "<<"10"<<" ";
			else if(temp=="==") cout<<temp<<" "<<"11"<<" ";
			else if(temp=="!=") cout<<temp<<" "<<"12"<<" ";
			else if(temp==">=") cout<<temp<<" "<<"14"<<" ";
			else cout<<temp<<" "<<"双界符"<<" ";
		}
		else if((code[f]=='<' && code[f+1]=='>') || (code[f]=='<' && code[f+1]=='<') || (code[f]=='>' && code[f+1]=='>')){
			f++;
			temp+=code[f];
			cout<<temp<<"双界符"<<" ";
		}
		else{
			if(temp=="<") cout<<temp<<" "<<"9"<<" ";
			else if(temp==">") cout<<temp<<" "<<"13"<<" ";
			else if(temp=="=") cout<<temp<<" "<<"18"<<" ";
			else if(temp=="+") cout<<temp<<" "<<"5"<<" ";
			else if(temp=="-") cout<<temp<<" "<<"6"<<" ";
			else if(temp=="*") cout<<temp<<" "<<"7"<<" ";
			else if(temp=="/") cout<<temp<<" "<<"8"<<" ";
			else if(temp==",") cout<<temp<<" "<<"27"<<" ";
			else if(temp==";") cout<<temp<<" "<<"26"<<" ";
			else if(temp==":") cout<<temp<<" "<<"25"<<" ";
			else if(temp=="{") cout<<temp<<" "<<"23"<<" ";
			else if(temp=="}") cout<<temp<<" "<<"24"<<" ";
			else if(temp=="[") cout<<temp<<" "<<"21"<<" ";
			else if(temp=="]") cout<<temp<<" "<<"22"<<" ";
			else cout<<temp<<" "<<"界符"<<" ";
		}
		if(code[f]=='#'){
			temp+=code[f];
		cout<<temp<<" ";
		return;
	}
		return;
	}
}

int main(){
	cout<<"input code"<<endl;
	while(scanf("%c",&code[f++])==1){
		if(code[f-1]=='?') break;
	}
	for(int l=0; l<f-1; l++){
		temp="";
		scaner(l);
	}
    return 0;
}
