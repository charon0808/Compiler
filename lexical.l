%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "bison.h"
    
    #include "bison.tab.h"

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

    int lines=0;
%}

/* regular definations */
delim            [ \t\n]
ws               {delim}+
letter           [a-zA-Z]
digit            [0-9]
power            E[+-]?{digit}+
int              [+-]?{digit}+{power}?
float            {digit}+(\.{digit}+)?({power})?
id               {letter}({letter}|{digit})*
semi             ;
comma            ,
assignop         =
relop            > | < | >= | <= | == | !=
plus             \+
minus            -
star             \*
div              \/
and              &&
or               \|\|
dot              \.
not              !
type             {int} | {float}
lp               \(
rp               \)
lb               \[
rb               \]
lc               \{
rc               \}
struct           struct
return           return
if               if
else             else
while            while

%option yylineno

%%

"\n"        {lines++;}
{if}        {strcpy(yylval.name,yytext); return IF;}
{else}      {strcpy(yylval.name,yytext); return ELSE;}
{int}       {strcpy(yylval.name,yytext); return INT;}
{float}     {strcpy(yylval.name,yytext); return FLOAT;}
"<"         {strcpy(yylval.name,yytext); return LT;}
"<="        {strcpy(yylval.name,yytext); return LE;}
"="         {strcpy(yylval.name,yytext); return EQ;}
"!="        {strcpy(yylval.name,yytext); return NE;}
">"         {strcpy(yylval.name,yytext); return GT;}
">="        {strcpy(yylval.name,yytext); return GE;}
{semi}      {strcpy(yylval.name,yytext); return SEMI;}
{comma}     {strcpy(yylval.name,yytext); return COMMA;}
{plus}      {strcpy(yylval.name,yytext); return PLUS;}
{minus}     {strcpy(yylval.name,yytext); return MINUS;}
{star}      {strcpy(yylval.name,yytext); return STAR;}
{div}       {strcpy(yylval.name,yytext); return DIV;}
{and}       {strcpy(yylval.name,yytext); return AND;}
{or}        {strcpy(yylval.name,yytext); return OR;}
'.'         {strcpy(yylval.name,yytext); return DOT;}
{not}       {strcpy(yylval.name,yytext); return NOT;}
{lp}        {strcpy(yylval.name,yytext); return LP;}
{rp}        {strcpy(yylval.name,yytext); return RP;}
{lb}        {strcpy(yylval.name,yytext); return LB;}
{rb}        {strcpy(yylval.name,yytext); return RB;}
{lc}        {strcpy(yylval.name,yytext); return LC;}
{rc}        {strcpy(yylval.name,yytext); return RC;}
{struct}    {strcpy(yylval.name,yytext); return STRUCT;}
{return}    {strcpy(yylval.name,yytext); return RETURN;}
{while}     {strcpy(yylval.name,yytext); return WHILE;}
{id}        {strcpy(yylval.name,yytext); return ID;}
.           {strcpy(yylval.name,yytext); printf("error\n"); return -1;}

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

int yywrap()
{
    return 1;
}