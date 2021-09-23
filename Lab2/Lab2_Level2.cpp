#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;
string keyword[32]={
	"auto","break","case","char","const","continue","default","double",
	"do","else","enum","extern","float","for","goto","if","int","long",
	"register","return","short","signed","sizeof","static","struct",
	"switch","typedef","union","unsigned","void","volatile","while"
	};
int keyword_num=0;
int switch_num=0;
int flag=0;
int switch_case[100]={0};
int ifelse_num=0;
int if_elseif_else_num=0;
int stack[500]={0};
int top=0;
int main ()
{
	int level;
	char file_name[100];
	cout<<"Enter the address of the file:"<<endl;				
	cin>>file_name;						
	cout<<"Enter the level:"<<endl;
	cin>>level;
	ifstream myfile(file_name);			//open-file 
	string temp;
	int Judge1(string str,string str1);	//find str1 in str 
	int Judge_letter(char str);				//Determines whether a character is a letter
	void Level_1(string word_1);			//Statistics the number of keywords
	void Level_2(string word_2);			//Statistic the number of "switch case" 
	while(getline(myfile,temp))			//Read line by line
	{
		istringstream is(temp);	
		string text;
		while(is>>text)					//remove the "space" 
		{
		if(level>=1)
			Level_1(text);
		if(level>=2)
			Level_2(text);
		}
	}
	if(level>=1){
		cout<<"total num: "<<keyword_num<<endl;
	}
	if(level>=2)
	{
		cout<<"switch num: "<<switch_num<<endl;
		cout<<"case num: ";
		for(int a=1;a<=switch_num;a++)
			cout<<switch_case[a]<<" ";
		cout<<endl;
	}

}

//to a void keywords that are part of other words. e.g "double" is regarded as "do" 
int Judge1(string str,string str1)	
{
	int Judge_letter(char str);
	int location=str.find(str1,0);
	int len=str1.length();
	if(location!=string::npos)
	{
		if(location==0)
		{
			if(Judge_letter(str[location+len])==0)
				return 1;
			else 
				return 0;
		}
		else
		{
			if(Judge_letter(str[location-1])==0&&Judge_letter(str[location+len])==0)
				return 1;
			else
				return 0;
		}
	}
	return 0;
}

//Determines whether a character is a letter
int Judge_letter(char str)			
{
	if(str>='a'&&str<='z'){
		return 1;
	}
		
	if(str>='A'&&str<='Z'){
		return 1;
	}
	if(str=='_'){
		return 0; 
	}
	if(str>='0'&&str<='9'){
		
		return 0;
	}
	return 0;
}

void Level_1(string word_1)		
{
	for(int a=0;a<32;a++)			
	{
		if(Judge1(word_1,keyword[a])==1)
		{
			keyword_num++;
			break;
		}
	}
}
	
void Level_2(string word_2)		
{
	if(flag)
	{
		if(Judge1(word_2,"case")==1)
		{
			switch_case[switch_num]++;
		}
	}	
	if(Judge1(word_2,"switch")==1)		
	{
		switch_num++;
		flag=1;
	}
}

