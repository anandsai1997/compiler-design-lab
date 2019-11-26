/*Lex program contains three sections : definitions , rules , and user
subroutines . Each section must be separated from the others by a
line containing only the delimiter , %%. The format is as
follows :
definitions
%%
rules
%%
user - subroutines
In definition section , the variables make up the left column , and
their definitions make up the right column . Any C statements
should be enclosed in %{..}%. Identifier is defined such that
the first letter of an identifier is alphabet and remaining
letters are alphanumeric .
In rules section , the left column contains the pattern to be
recognized in an input file to yylex () . The right column
contains the C program fragment executed when that pattern is
recognized . The various patterns are keywords , operators , new
line character , number , string , identifier , beginning and end of
block , comment statements , preprocessor directive statements
etc .
Each pattern may have a corresponding action , that is , a fragment
of C source code to execute
when the pattern is matched .
When yylex () matches a string in the input stream , it copies the
matched text to an external character array , yytext , before it
executes any actions in the rules section .
In user subroutine section , main routine calls yylex () . yywrap () is
used to get more input .
The lex command uses the rules and actions contained in file to
generate a program , lex . yy .c , which can be compiled with the cc
command . That program can then receive input , break the input
into the logical pieces defined by the rules in file , and run
program fragments contained in the actions in file .*/
#include<stdio.h>
#include<ctype.h>
#include<string.h>
void keyw(char *p);
int i=0,id=0,kw=0,num=0,op=0;
char keys[32][10]={"auto","break","case","char","const","continue","default",
"do","double","else","enum","extern","float","for","goto",
"if","int","long","register","return","short","signed",
"sizeof","static","struct","switch","typedef","union",
"unsigned","void","volatile","while"};
main()
{
char ch,str[25],seps[15]=" \t\n,;(){}[]#\"<>",oper[]="!%^&*-+=~|.<>/?";
int j;
char fname[50];
FILE *f1;
//clrscr();
printf("enter file path (drive:\\fold\\filename)\n");
scanf("%s",fname);
f1 = fopen(fname,"r");
//f1 = fopen("Input","r");
if(f1==NULL)
{
printf("file not found");
exit(0);
}
while((ch=fgetc(f1))!=EOF)
{
for(j=0;j<=14;j++)
{
if(ch==oper[j])
{
printf("%c is an operator\n",ch);
op++;
str[i]='\0';
keyw(str);
}
}
for(j=0;j<=14;j++)
{
if(i==-1)
break;
if(ch==seps[j])
{
if(ch=='#')
{
while(ch!='>')
{
printf("%c",ch);
ch=fgetc(f1);
}
printf("%c is a header file\n",ch);
i=-1;
break;
}
if(ch=='"')
{
do
{
ch=fgetc(f1);
printf("%c",ch);
}while(ch!='"');
printf("\b is an argument\n");
i=-1;
break;
}
str[i]='\0';
keyw(str);
}
}
if(i!=-1)
{
str[i]=ch;
i++;
}
else
i=0;
}
printf("Keywords: %d\nIdentifiers: %d\nOperators: %d\nNumbers: %d\n",kw,id,op,num);
//getch();
}
void keyw(char *p)
{
int k,flag=0;
for(k=0;k<=31;k++)
{
if(strcmp(keys[k],p)==0)
{
printf("%s is a keyword\n",p);
kw++;
flag=1;
break;
}
}
if(flag==0)
{
if(isdigit(p[0]))
{
printf("%s is a number\n",p);
num++;
}
else
{
//if(p[0]!=13&&p[0]!=10)
if(p[0]!='\0')
{
printf("%s is an identifier\n",p);
id++;
}
}
}
i=-1;
}


