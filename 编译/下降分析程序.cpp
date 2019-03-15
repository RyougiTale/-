#include <iostream>
#include <cstring>
using namespace std;

void trim(string &s)
{
	int index=0;
	if(!s.empty()){
		while((index=s.find(' ',index))!=string::npos){
		s.erase(index,1);
		}
	}
}

bool isN(string s){
	for(int i=0;i<s.length();i++){
		if(s[i]>='1'&&s[i]<='9'||s[i]=='0') continue;
		else return false;
	}
	return true;
}

bool isletter(string s){
	for(int i=0;i<s.length();i++){
		if(s[i]>='a'&&s[i]<='z'||s[i]>='A'&&s[i]<='Z'){
			continue;
		}
		else{
			cout<<s[i]<<"变量存在问题"<<endl;
			return false;
		}
	}
	return true;
}

bool isW(string s){
	if(s[0]>='a'&&s[0]<='z'||s[0]>='A'&&s[0]<='Z'||s[0]>='1'&&s[0]<='9'||s[0]=='0'||s[0]=='_'){
		string s1=s.substr(1);
		if(isW(s1)) return true;
		else return false;
	}
	if(s.length()==0) return true;
	else{
		cout<<"W产生式出错"<<endl;
		return false;
	}
}

bool isV(string s){
	string s1;
	if(s[0]=='_') {
		s1=s.substr(1);
	}
	else{
		if(s[0]>='a'&&s[0]<='z'||s[0]>='A'&&s[0]<='Z'||s[0]>='1'&&s[0]<='9') s1=s.substr(1);
		else{
			cout<<"V产生式出错"<<endl;
			return false;
		}
	}
	if(isW(s1)) return true;
	else return false;
}

bool isO(string s){
	for(int i=0;i<s.length();i++){
		if(s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/'){
			string s1=s.substr(0,i);
			string s2=s.substr(i+1);
			cout<<s1<<" "<<s2<<endl;
			if(isW(s1)&&isO(s2)) return true;
			else{
				cout<<"O产生式错误"<<endl;
				return false;
			}
			break;
		}
		
	}
	if(isV(s) || isN(s)) return true;
	else{
		cout<<"O产生式错误"<<endl;
		return false;
	}
}

int main(){
	string temp;
	cin>>temp;
	int n=0;
	while(temp[n]!='='){
	n++;
		if(n==temp.length()){
			cout<<"wrong:no any '='"<<endl;;
			return 0;
		}
	}
	n++;
	string v = temp.substr(0,n-1);
	cout<<v<<endl;
	string o=temp.substr(n);
	cout<<o<<endl;
	if(isV(v) && isO(o)) cout<<"赋值成功"<<endl;
	else cout<<"wrong"<<endl;
	return 0;
}
