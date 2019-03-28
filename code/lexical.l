%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "bison.h"
    
    #include "syntax.tab.h"
/*
    #define LT 0
    #define LE 1
    #define EQ 2
    #define NE 3
    #define GT 4
    #define GE 5
    #define IF 6
    #define ELSE 7
    #define ID 8
    #define NUMBER 9
    #define RELOP 10
    #define INT 11
    #define FLOAT 12
    #define SEMI 13
    #define COMMA 14
    #define ASSIGNOP 15
    #define PLUS 16
    #define MINUS 17
    #define STAR 18
    #define DIV 19
    #define AND 20
    #define OR 21
    #define DOT 22
    #define NOT 23
    #define LP 24
    #define RP 25
    #define LB 26
    #define RB 27
    #define LC 28
    #define RC 29
    #define STRUCT 30
    #define RETURN 31
    #define WHILE 32 
    
"<"         {strcpy(yylval.val.name,yytext); yylval.val.lineno=yylineno; return LT;}
"<="        {strcpy(yylval.val.name,yytext); yylval.val.lineno=yylineno; return LE;}
"=="        {strcpy(yylval.val.name,yytext); yylval.val.lineno=yylineno; return EQ;}
"!="        {strcpy(yylval.val.name,yytext); yylval.val.lineno=yylineno; return NE;}
">"         {strcpy(yylval.val.name,yytext); yylval.val.lineno=yylineno; return GT;}
">="        {strcpy(yylval.val.name,yytext); yylval.val.lineno=yylineno; return GE;}
    */
    extern int error;
    int lines=0;
    int intox_2_intd(char*);
%}

/* regular definations */
delim            [ \t\r\n]
ws               {delim}+
letter           [a-zA-Z]
digit1           [0-9]
digit2           [1-9]
digit3           [0-7]
digit4           [0-9a-fA-F]
power            [eE][+-]?({digit1})+
int8             0{digit3}+
intx             0[xX]{digit4}+
int10            ({digit2}({digit1})*{power}?)|0
int              {int10}|{int8}|{intx}
float            {digit1}*\.{digit1}+({power})?
id               {letter}({letter}|{digit1})*
semi             ;
comma            ,
assignop         =
lt               <
le               <=
eq               ==
ne               !=
gt               >
ge               >=
plus             \+
relop            {lt}|{le}|{eq}|{ne}|{gt}|{ge}
minus            -
star             \*
div              \/
and              &&
or               \|\|
dot              \.
not              !
lp               \(
rp               \)
lb               \[
rb               \]
lc               \{
rc               \}
typeint          int
typefloat        float
struct           struct
return           return
if               if
else             else
while            while
comments1        \/\/(.)*
comments2        "/*"([^\*]|(\*)*[^\*/])*(\*)*"*/"
%option yylineno

%%

{comments1} {;}
{comments2} {char a=' '; while(a==' '||a=='\r'||a=='\n') a=input(); char b=input(); if(a!='*'||b!='/'){unput(b); unput(a);}
            else {error=0; fprintf(stderr,"Error type B at line %d: Syntax error.\n",yylineno);}}
{ws}        {;}
{if}        {strcpy(yylval.val.name,yytext); yylval.val.lineno=yylineno; return IF;}
{else}      {strcpy(yylval.val.name,yytext); yylval.val.lineno=yylineno; return ELSE;}
{int8}|{int10}|{intx}       {yylval.val.ival=intox_2_intd(yytext); yylval.val.lineno=yylineno; return INT;}
{float}     {yylval.val.fval=atof(yytext); yylval.val.lineno=yylineno; return FLOAT;}
{relop}     {strcpy(yylval.val.name,yytext); yylval.val.lineno=yylineno; return RELOP;}
{assignop}  {strcpy(yylval.val.name,yytext); yylval.val.lineno=yylineno; return ASSIGNOP;}
{plus}      {strcpy(yylval.val.name,yytext); yylval.val.lineno=yylineno; return PLUS;}
{semi}      {strcpy(yylval.val.name,yytext); yylval.val.lineno=yylineno; return SEMI;}
{comma}     {strcpy(yylval.val.name,yytext); yylval.val.lineno=yylineno; return COMMA;}
{minus}     {strcpy(yylval.val.name,yytext); yylval.val.lineno=yylineno; return MINUS;}
{star}      {strcpy(yylval.val.name,yytext); yylval.val.lineno=yylineno; return STAR;}
{div}       {strcpy(yylval.val.name,yytext); yylval.val.lineno=yylineno; return DIV;}
{and}       {strcpy(yylval.val.name,yytext); yylval.val.lineno=yylineno; return AND;}
{or}        {strcpy(yylval.val.name,yytext); yylval.val.lineno=yylineno; return OR;}
{dot}       {strcpy(yylval.val.name,yytext); yylval.val.lineno=yylineno; return DOT;}
{not}       {strcpy(yylval.val.name,yytext); yylval.val.lineno=yylineno; return NOT;}
{lp}        {strcpy(yylval.val.name,yytext); yylval.val.lineno=yylineno; return LP;}
{rp}        {strcpy(yylval.val.name,yytext); yylval.val.lineno=yylineno; return RP;}
{lb}        {strcpy(yylval.val.name,yytext); yylval.val.lineno=yylineno; return LB;}
{rb}        {strcpy(yylval.val.name,yytext); yylval.val.lineno=yylineno; return RB;}
{lc}        {strcpy(yylval.val.name,yytext); yylval.val.lineno=yylineno; return LC;}
{rc}        {strcpy(yylval.val.name,yytext); yylval.val.lineno=yylineno; return RC;}
{struct}    {strcpy(yylval.val.name,yytext); yylval.val.lineno=yylineno; return STRUCT;}
{return}    {strcpy(yylval.val.name,yytext); yylval.val.lineno=yylineno; return RETURN;}
{while}     {strcpy(yylval.val.name,yytext); yylval.val.lineno=yylineno; return WHILE;}
{typeint}|{typefloat} {strcpy(yylval.val.name,yytext); yylval.val.lineno=yylineno; return TYPE;}
{id}        {strcpy(yylval.val.name,yytext); yylval.val.lineno=yylineno; return ID;}
.           {fprintf(stderr, "Error type A at line %d: Mysterious character ‘%s’\n",yylineno,yytext); error=0;}

%%
/*
int main(int argc,char* argv[])
{
    int i=yylex();
    while(1){
        printf("%d,%s\n",i,yytext);
        i=yylex();
    }
}*/

int intox_2_intd(char* str)
{
    int sum=0;
    if(strlen(str)>2&&(str[1]=='x'||str[1]=='X')){   // 0x
        int ii=1;
        for(int i=strlen(str)-1;i>=2;i--){
            if (str[i]<='9'&&str[i]>='0'){
                sum+=(str[i]-'0')*ii;
            }
            else if (str[i]<='F'&&str[i]>='A'){
                sum+=(str[i]-'A'+10)*ii;
            }
            else if (str[i]<='f'&&str[i]>='a'){
                sum+=(str[i]-'a'+10)*ii;
            }
            ii*=16;
        }
    }
    else if(str[0]=='0'){    // 0...
        int ii=1;
        for (int i=strlen(str)-1;i>=1;i--){
            sum+=(str[i]-'0')*ii;
            ii*=8;
        }
    }
    else sum=atoi(str);
    return sum;
}

int yywrap()
{
    return 1;
}