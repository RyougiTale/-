#include<iostream>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<cctype>
#include<stack>
#include<map> 
using namespace std;
const int signtable_count=1200;//0-999为普通变量，1000-1050为T 
const int number=100;
int T_i=0;int quad_i=0;int NXQ=0;
int h_num=0;
char s[100];
string hb[50][5];
int lrtable[19][12]={
		{-1,-1,-1,-1,-1,-1,-1,-1,2,-1,1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-1,-1},
		{3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,5,-1,-1,-1,-1,6,-1,7,-1,-1,4},
		{-1,-1,8,9,10,11,-1,-1,-1,101,-1,-1},
		{-1,5,-1,-1,-1,-1,6,-1,7,-1,-1,12},
		{-1,5,-1,-1,-1,-1,6,-1,7,-1,-1,13},
		{-1,-1,108,108,108,108,-1,108,-1,108,-1,-1},
		{-1,5,-1,-1,-1,-1,6,-1,7,-1,-1,14},
		{-1,5,-1,-1,-1,-1,6,-1,7,-1,-1,15},
		{-1,5,-1,-1,-1,-1,6,-1,7,-1,-1,16},
		{-1,5,-1,-1,-1,-1,6,-1,7,-1,-1,17},
		{-1,-1,102,102,102,102,-1,102,-1,102,-1,-1},
		{-1,-1,8,9,10,11,-1,18,-1,-1,-1,-1},
		{-1,-1,103,103,10,11,-1,103,-1,103,-1,-1},
		{-1,-1,104,104,10,11,-1,104,-1,104,-1,-1},
		{-1,-1,105,105,105,105,-1,105,-1,105,-1,-1},
		{-1,-1,106,106,106,106,-1,106,-1,106,-1,-1},
		{-1,-1,107,107,107,107,-1,107,-1,107,-1,-1}
	};


map <char,int> m;
void init()
{
	m['=']=0;m['@']=1;
	m['+']=2;m['-']=3;m['*']=4;m['/']=5;
	m['(']=6;m[')']=7;m['i']=8;
	m['#']=9;m['A']=10;m['E']=11;
}


void gen(string op,string arg1,string arg2,string result)
{
	cout<<"("<<op<<","<<arg1<<","<<arg2<<","<<result<<")"<<endl;
}
void huibian(string op,string arg1,string arg2,string result)
{
	if(op=="=") 
	{
		cout<<"MOV R0,"<<arg1<<endl;cout<<"MOV "<<result<<",R0"<<endl;
	}
	if(op=="+") 
	{
		cout<<"MOV R0,"<<arg1<<endl;cout<<"MOV R1,"<<arg2<<endl;
		cout<<"ADD R0,R1"<<endl;
	    cout<<"MOV "<<result<<",R0"<<endl;
	}
	if(op=="-") 
	{
		cout<<"MOV R0,"<<arg1<<endl;cout<<"move R1,"<<arg2<<endl;
		cout<<"SUB R0,R1"<<endl;
	    cout<<"MOV "<<result<<",R0"<<endl;
	}
	if(op=="*") 
	{
		cout<<"MOV AL,"<<arg1<<endl;
		cout<<"MUL "<<arg2<<endl;
	    cout<<"MOV "<<result<<",AX"<<endl;
	}
	if(op=="/") 
	{
		cout<<"MOV AX,"<<arg1<<endl;
		cout<<"DIV "<<arg2<<endl;
	    cout<<"MOV "<<result<<",AL"<<endl;
	}
	if(op=="@") 
	{
		cout<<"MOV AL,"<<arg1<<endl;
		cout<<"NOT Al"<<endl;
		cout<<"MOV "<<result<<",AL"<<endl;
	}
}
string f(int n)
{
	string s="T";
	char c[5];
	c[0]=n+'0';
	c[1]='\0';
	s+=c;
	return s;
	
}
void Zhidao_tran()
{
	stack <int> sta;//状态栈
	stack <char> symbol;//符号栈 
	stack <string> place;//语义栈(Value栈)
	sta.push(0);symbol.push('#');place.push("_");
    
	int i=0;
	char sym;
	bool acc=false;
	while(!acc)
	{
	    char *p=new char[10]; int p_n=0;
		if(isdigit(s[i])||isalpha(s[i]))
		{
			p[p_n++]=s[i];
			
			while(isdigit(s[i+1])||isalpha(s[i+1]))
			{
				i++;
				p[p_n++]=s[i];
			}
			
			sym='i'; p[p_n]='\0';
		}
		
		else
		{
			sym=s[i];
			p[0]=s[i];p[1]='\0';
		
		}
		int x=sta.top();int y;
		if(m.count(sym))  y=m[sym];
		else 
			{
				cout<<"分析错误,存在未识别符号"<<endl;
				return ;
			}
		int l=lrtable[x][y];
		if(l==-1) 
			{
				cout<<"分析错误"<<endl;
				return ; 
			}
		if(l==-2) acc=true;
		if(l>=0&&l<100)
			{
				i++;
				sta.push(l);symbol.push(sym);place.push(p);
				
				
			}
		if(l>=101&&l<200)
			{
				switch(l)
				{
				 
				case 101: //A->i=E
				{
				sta.pop();sta.pop();sta.pop();
				symbol.pop();symbol.pop();symbol.pop();
				string k1=place.top();
				place.pop();place.pop();string k2=place.top();
				
				gen("=",k1,"-",k2);	
				hb[h_num][0]="=";	hb[h_num][1]=k1;	
				hb[h_num][2]="-";	hb[h_num][3]=k2; h_num++;
				int x=sta.top();int y=m['A'];
				sta.push(lrtable[x][y]);symbol.push('A');
				
				break;
		     	}
				case 102: //E->-E
				{
					sta.pop();sta.pop();symbol.pop();symbol.pop();
					string k1=place.top();  place.pop();place.pop();
					int x=sta.top();int y=m['E'];
				    sta.push(lrtable[x][y]);
					symbol.push('E');
					string t=f(T_i);
					T_i++;
					place.push(t);
					gen("@",k1,"-",t);
					hb[h_num][0]="@";	hb[h_num][1]=k1;	
				    hb[h_num][2]="-";	hb[h_num][3]=t; h_num++;
				}
				case 103: //E->E+E
				{
					sta.pop();sta.pop();sta.pop();
					symbol.pop();symbol.pop();symbol.pop();
					string k2=place.top();
				place.pop();place.pop(); string k1=place.top();place.pop();
				
				int x=sta.top();int y=m['E'];
				sta.push(lrtable[x][y]);
				symbol.push('E');
				string t=f(T_i);
					T_i++;
					place.push(t);
				gen("+",k1,k2,t);
    	       	hb[h_num][0]="+";	hb[h_num][1]=k1;	
				hb[h_num][2]=k2;	hb[h_num][3]=t; h_num++;			
                break;
				}
				case 104: //E->E-E
				{
					sta.pop();sta.pop();sta.pop();
					symbol.pop();symbol.pop();symbol.pop();
					string k2=place.top();
				place.pop();place.pop(); string k1=place.top();place.pop();
				
				int x=sta.top();int y=m['E'];
				sta.push(lrtable[x][y]);
				symbol.push('E');
				string t=f(T_i);
					T_i++;
					place.push(t);
				gen("-",k1,k2,t);
            	hb[h_num][0]="-";	hb[h_num][1]=k1;	
				hb[h_num][2]=k2;	hb[h_num][3]=t; h_num++;
                break;
				}
				case 105://E->E*E
				{
						sta.pop();sta.pop();sta.pop();
					symbol.pop();symbol.pop();symbol.pop();
					string k2=place.top();
				place.pop();place.pop(); string k1=place.top();place.pop();
				
				int x=sta.top();int y=m['E'];
				sta.push(lrtable[x][y]);
				symbol.push('E');
				string t=f(T_i);
					T_i++;
					place.push(t);
				gen("*",k1,k2,t);
            	hb[h_num][0]="*";	hb[h_num][1]=k1;	
				hb[h_num][2]=k2;	hb[h_num][3]=t; h_num++;
                break;
				
				}
				case 106://E->E/E
				{
						sta.pop();sta.pop();sta.pop();
					symbol.pop();symbol.pop();symbol.pop();
					string k2=place.top();
				place.pop();place.pop(); string k1=place.top();place.pop();
				
				int x=sta.top();int y=m['E'];
				sta.push(lrtable[x][y]);
				symbol.push('E');
				string t=f(T_i);
					T_i++;
					place.push(t);
				gen("/",k1,k2,t);
				hb[h_num][0]="/";	hb[h_num][1]=k1;	
				hb[h_num][2]=k2;	hb[h_num][3]=t; h_num++;
				break;
				}
				case 107://E->(E) 
				{
					sta.pop();sta.pop();sta.pop();
					symbol.pop();symbol.pop();symbol.pop();
					place.pop();
				    string k1=place.top();place.pop();place.pop();
				
				int x=sta.top();int y=m['E'];
				sta.push(lrtable[x][y]);
				symbol.push('E');
				
				place.push(k1);
				break;
			
				}
				case 108://E->i
				{
					sta.pop();symbol.pop();
				int x=sta.top();int y=m['E'];
				sta.push(lrtable[x][y]);
				symbol.push('E');
				break;
				}
				
			   }
			}
		}
		cout<<"分析成功"<<endl;return ; 
}
								
int main()
{
	memset(s,0,sizeof(s));
	init();
	cout<<"请输入表达式,以#结束!"<<endl;
	int i=0; char c;
	cin>>c;
	s[i++]=c;
	while(c!='=') cin>>c;
	s[i++]=c;
	cin>>c;
	while(c!='#')
	{
		if(c!=' ') s[i++]=c;
		cin>>c;
	}
	s[i]=c;	
	for(i=0;s[i]!='#';i++)
	{
		if(s[1]=='-'&&isdigit(s[2])) s[1]='@';
		if(isdigit(s[i+1])&&s[i]=='-'&&s[i-1]=='(') s[i]='@';
	}
		cout<<"转换成四元式如下："<<endl;
	Zhidao_tran();
	cout<<endl<<endl;
	cout<<"转换成汇编语言如下："<<endl;
	for(i=0;i<h_num;i++)
	huibian(hb[i][0],hb[i][1],hb[i][2],hb[i][3]);
	return 0;
}
