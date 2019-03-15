#include<iostream>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<stack>
#include<algorithm>
using namespace std;
char sy[8][8]={'>','>','<','<','<','>','<','>',
               '>','>','<','<','<','>','<','>',
			   '>','>','>','>','<','>','<','>',
			   '>','>','>','>','<','>','<','>',
			   '<','<','<','<','<','=','<','$',
			   '>','>','>','>','$','>','$','>',
			   '>','>','>','>','$','>','$','>',
			   '<','<','<','<','<','$','<','$'};
int a[2][8];
char s[100];
int f(char c ,int m,int n)
{
	if(c=='+') return m+n;
	if(c=='-') return m-n;
	if(c=='*') return m*n;
	if(c=='/') return m/n;
}
int map(char c)
{
	switch(c)
	{
	case '+': {return 0;break;}
	case '-': {return 1;break;}
	case '*': {return 2;break;}
	case '/': {return 3;break;}
	case '(': {return 4;break;}
	case ')': {return 5;break;}
	case '#': {return 7;break;}
	default:   cout<<"匹配出错"<<endl;
    }
	return 9; 
}
int eva()
{
	stack <char> optr; optr.push('#');
	stack <int> opnd;
	int p1=0;
	while(s[p1]!='#'||optr.top()!='#')
	{
		if(isdigit(s[p1]))
		{
			int n=s[p1]-'0';
			while(isdigit(s[p1+1]))
			{
				n=n*10+s[p1+1]-'0';
				p1++;
			}
			opnd.push(n);
			p1++;
		
		}
		else 
		{
			int x=map(optr.top());int y=map(s[p1]);
			if(a[0][x]<a[1][y])
			{
				optr.push(s[p1]);
				p1++;
			}
			else if(a[0][x]==a[1][y])
			{
				optr.pop();p1++;
			}
			else
			{
				char c=optr.top();optr.pop();
				int k1=opnd.top();opnd.pop();
				int k2=opnd.top();opnd.pop(); 
				int k3=f(c,k2,k1);
				opnd.push(k3); 
			}
		}
	}
	return opnd.top();
}
void init()
{
	int flag=0;
	while(!flag)
	{
		flag=1;
		for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
		if(sy[i][j]=='>'&&a[0][i]<=a[1][j])
		{
			a[0][i]+=a[1][j]+1;
			flag=0;
		}
		else 
		if(sy[i][j]=='<'&&a[0][i]>=a[1][j])
		{
			a[1][j]=a[0][i]+1;
			flag=0;
		}
		else 
		if(sy[i][j]=='='&&a[0][i]!=a[1][j])
		{
			int k=max(a[0][i],a[1][j]);
			a[0][i]=k;a[1][j]=k;
			flag=0;
		}
		
	}
	cout<<"+   -   *   /   (   )   i   #"<<endl;
	for(int i=0;i<8;i++)  cout<<a[0][i]<<"   ";
	cout<<endl;
	for(int i=0;i<8;i++)  cout<<a[1][i]<<"   ";
	cout<<endl;
	
}
int main()
{
	
	memset(a,0,sizeof(a));
	memset(s,0,sizeof(s));
	init();
	cout<<"请输入表达式,以#结束!"<<endl;
	int i=0; char c;
	cin>>c;
	while(c!='#')
	{
		if(c!=' ') s[i++]=c;
		cin>>c;
	}
	s[i]=c;	
	//cout<<s<<endl;
	int ans=eva();
	cout<<"运算结果为："<<ans<<endl; 
	return 0;	
}
