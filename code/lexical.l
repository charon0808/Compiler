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
    
"<"         {strcpy(yylval.name,yytext); return LT;}
"<="        {strcpy(yylval.name,yytext); return LE;}
"=="        {strcpy(yylval.name,yytext); return EQ;}
"!="        {strcpy(yylval.name,yytext); return NE;}
">"         {strcpy(yylval.name,yytext); return GT;}
">="        {strcpy(yylval.name,yytext); return GE;}
    */
    extern int error;
    int lines=0;
%}

/* regular definations */
delim            [ \t\r\n]
ws               {delim}+
letter           [a-zA-Z]
digit1           [0-9]
digit2           [1-9]
digit3           [0-7]
digit4           [0-9a-fA-F]
power            E[+-]?({digit1})+
int8             0{digit3}+
intx             0[xX]{digit4}+
int10            ({digit2}({digit1})*{power}?)|0
int              {int10}|{int8}|{intx}
float            {digit1}+\.{digit1}+({power})?
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
comments2        \/\*(.|\n|\r\n)*?\*\/
%option yylineno

%%

{comments1} {printf("comments1: [%s] at line %d\n",yytext,yylineno);}
{comments2} {printf("comments2: [%s] at line %d\n",yytext,yylineno);}
{ws}        {;}
{if}        {strcpy(yylval.name,yytext); return IF;}
{else}      {strcpy(yylval.name,yytext); return ELSE;}
{int8}|{int10}|{intx}       {printf("INT:%s\n",yytext);strcpy(yylval.name,yytext); return INT;}
{float}     {strcpy(yylval.name,yytext); return FLOAT;}
{relop}     {strcpy(yylval.name,yytext); return RELOP;}
{assignop}  {strcpy(yylval.name,yytext); return ASSIGNOP;}
{plus}      {strcpy(yylval.name,yytext); return PLUS;}
{semi}      {strcpy(yylval.name,yytext); return SEMI;}
{comma}     {strcpy(yylval.name,yytext); return COMMA;}
{minus}     {strcpy(yylval.name,yytext); return MINUS;}
{star}      {strcpy(yylval.name,yytext); return STAR;}
{div}       {strcpy(yylval.name,yytext); return DIV;}
{and}       {strcpy(yylval.name,yytext); return AND;}
{or}        {strcpy(yylval.name,yytext); return OR;}
{dot}       {strcpy(yylval.name,yytext); return DOT;}
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
{typeint}|{typefloat} {strcpy(yylval.name,yytext); return TYPE;}
{id}        {printf("ID:%s\n",yytext);strcpy(yylval.name,yytext); return ID;}
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



int yywrap()
{
    return 1;
}