/*
Project Name 	: Chat++
Description 	: Chat client prototype, uses a shared folder over LAN/WiFi/Internet to trasmit files.
The Team 		: Abhishek Sarin, Priyanshu Mukhopadhyay, Puranjay Rajvanshi, Raghav Bhasin
Special Thanks 	: Shiv Capoor, Ms. Monica Dewan (HOD CS, DPSN)
GitHub 			: https://github.com/raghavb95/chatpp
Build Version 	: v2.2
*/
#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<time.h>
#include<string.h>

#define gt gotoxy
#define TRUE 1
#define FALSE 0
#define EXIT -255
#define OK 255

void chatmain();
int transmit(char*,char*,int);
int srch(char*,char*);
int receive(char*,int);
void getChatName(char*,char*);
void chatHistory(char*,char*);
void insertTimestamp(char*,char*);

char username[10],frndname[10],chatname[8];

void main()
{
	clrscr();
	cout<<"Username   : ";
	gets(username);
	cout<<"Connect To : ";
	gets(frndname);

	getChatName(username,frndname);
	
	cout<<"\nChat Name:"<<chatname;
	cout<<"\nYou can access your conversation history here.";
	getch();

	clrscr();
	chatmain();	
	clrscr();
	cout<<"Thank you for using Chat++\n";
	cout<<"See You Soon...";
	getch();
}

void chatmain()
{
	char msg[100],key;
	int stat=OK,kcount=0,ntrans=0,len=0;
	
	insertTimestamp(username,"Connected");
	
	gt(1,20);
	for(int i=1;i<=80;i++)
		cout<<"Ä";
	gt(1,21);
	do
	{
		ntrans=receive(frndname,ntrans);
		gt(1+kcount,21);
		if(kbhit())
		{
			key=getch();
			if(key==(char)13)
			{
				if(len==0)
				continue;
				ntrans++;
				stat=transmit(msg,username,ntrans);
				kcount=0;
				strcpy(msg,NULL);
				len=0;
				continue;
			}
			if(key==(char)8)
			{
				if(len>0)
				{
					cout<<"\b \b";
					len--;
					kcount--;
					msg[len]=NULL;
				}
				continue;
			}
			kcount++;
			cout<<key;
			msg[len++]=key;
			msg[len]=NULL;
		}
		if(ntrans>18)
		{
			clrscr();
			gt(1,20);
			for(int i=1;i<=80;i++)
				cout<<"Ä";
			gt(1,21);
			ntrans=0;
		}
	}
	while(stat!=EXIT);
	insertTimestamp(username,"Disconnected");
}

int transmit(char msg[],char username[],int ntrans)
{
	if(strlen(msg)==0)
	return OK;
	else if(srch(msg,"exit"))
	return EXIT;
	else
	{
		ofstream fileOut(username,ios::app);
		for(int i=0;i<strlen(msg);i++)
			fileOut.put(msg[i]);
		fileOut<<'\n';
		gt(1,ntrans);
		cout<<username<<": ";
		puts(msg);
		gt(1,21);
		clreol();
		chatHistory(username,msg);
		return OK;
	}
}

int srch(char input[], char sub_str[])
{
	int m,s;
	m=strlen(input);
	s=strlen(sub_str);
	if(!s || !m)
	return FALSE;
	int i=0, j=0,k=0;
	while(i<m && j<s)
	{
		if(sub_str[j]==input[i])
		{
			j++;
			i++;
			k=1;
		}
		else if(!k)
		{
			i++;
			j=0;
		}
		else
		{
			j=0;
			k=0;
		}
	}
	if(j==s)
		return TRUE;
	else
		return FALSE;
}

int receive(char frndname[],int ntrans)
{
	ifstream fileIn(frndname);
	char str[50];
	if(!fileIn)
	{
		fileIn.close();
		return ntrans;
	}
	ntrans++;
	int i=0;
	time_t t1,t2;
	time(&t1);
	do
	{
		time(&t2);
	}
	while(difftime(t2,t1)<=1);
	while(!fileIn.eof())
		fileIn.get(str[i++]);
	str[i-1]='\0';
	gt(1,ntrans);
	cout<<frndname<<": ";
	puts(str);
	fileIn.close();
	unlink(frndname);
	return ntrans;
}

void getChatName(char username[],char frndname[])
{
	char first=NULL;
	if(username[0]<frndname[0])
	{
		for(int i=0;i<3;i++)
			chatname[i]=username[i];
		first='u';
	}
	else
	{
		for(int i=0;i<3;i++)
			chatname[i]=frndname[i];
		first='o';
	}
	chatname[3]='&';
	if(first=='u')
	{
		for(int i=0;i<3;i++)
			chatname[i+4]=frndname[i];
	}
	else
	{
		for(int i=0;i<3;i++)
			chatname[i+4]=username[i];
	}
	chatname[7]='\0';
}

void chatHistory(char userid[],char msg[])
{
	ofstream fileOut(chatname,ios::app);
	int i=0;
	int len=strlen(msg);
	fileOut<<userid<<": ";
	while(i<len)
		fileOut.put(msg[i++]);
	fileOut<<"\n";
	fileOut.close();
}

void insertTimestamp(char username[], char status[])
{
	ofstream fileOut(chatname,ios::app);
	time_t t;
	time(&t);
	char dtime[30];
	strcpy(dtime,ctime(&t));
	int len=strlen(dtime),i=0;
	fileOut<<"\n"<<username<<" "<<status<<" at: ";
	while(i<len)
		fileOut.put(dtime[i++]);
	fileOut<<"\n";
	fileOut.close();
}
