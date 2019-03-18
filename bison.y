%{
    #include <stdio.h>
    #include <stdlib.h>

    #include "bison.h"

	char** symbol_table_start=NULL;

    void bison_error(const char*);
    node* node_con(char*);
    //node* add_node(const char*);
    extern int yylex(void);
    void yyerror(char *);  
%}

%union{
    union value val;
    node* _node;
    char name[32];
}

%token <name> INT FLOAT
%token <name> ID
%token <name> SEMI COMMA ASSIGNOP
%token <name> LT LE EQ NE GT GE
%token <name> PLUS MINUS
%token <name> STAR
%token <name> DIV AND OR DOT NOT
%token <name> LP RP LB RB LC RC
%token <name> STRUCT RETURN
%token <name> IF ELSE WHILE
%token TYPE
%token RELOP

%type <_node> Program ExtDefList ExtDef ExtDecList 
%type <_node> Specifier StructSpecifier OptTag Tag
%type <_node> VarDec FunDec VarList ParamDec
%type <_node> CompSt StmtList Stmt
%type <_node> DefList Def DecList Dec
%type <_node> Exp Args

%%

Program: ExtDefList {;}
        ;
ExtDefList: ExtDef ExtDefList {;}
            | {;}
            ;
ExtDef: Specifier ExtDecList SEMI {;}
        | Specifier SEMI {;}
        | Specifier FunDec CompSt {;}
        ;
ExtDecList: VarDec {;}
            | VarDec COMMA ExtDecList {;}
            ;

Specifier: TYPE StructSpecifier {;}
        ;
StructSpecifier: STRUCT OptTag LC DefList RC {;}
                | STRUCT Tag {;}
                ;
OptTag: ID {;}
        | {;}
        ;
Tag: ID {;}
    ;

VarDec: ID {;}
        | VarDec LB INT RB {;}
        ;
FunDec: ID LP VarList RP {;}
        | ID LP RP {;}
        ;
VarList: ParamDec COMMA VarList {;}
        | ParamDec {;}
        ;
ParamDec: Specifier VarDec {;}
        ;

CompSt: LC DefList StmtList RC {;}
        ;
StmtList: Stmt StmtList {;}
        | {;}
        ;
Stmt: Exp SEMI {;}
        | CompSt {;}
        | RETURN Exp SEMI {;}
        | IF LP Exp RP Stmt {;}
        | IF LP Exp RP Stmt ELSE Stmt {;}
        | WHILE LP Exp RP Stmt {;}
        ;

DefList: Def DefList {;}
        | {;}
        ;
Def: Specifier DecList SEMI {;}
    ;
DecList: Dec {;}
        | Dec COMMA DecList {;}
        ;
Dec: VarDec {;}
    | VarDec ASSIGNOP Exp {;}
    ;

Exp: Exp ASSIGNOP Exp {;}
    | Exp AND Exp {;}
    | Exp OR Exp {;}
    | Exp RELOP {;}
    | Exp PLUS Exp {;}
    | Exp MINUS Exp {;}
    | Exp STAR Exp {;}
    | Exp DIV Exp {;}
    | LP Exp RP {;}
    | MINUS Exp {;}
    | NOT Exp {;}
    | ID LP Args RP {;}
    | ID LP RP {;}
    | Exp LB Exp RB {;}
    | Exp DOT ID {;}
    | ID {;}
    | INT {$$=node_con($1);}
    | FLOAT {$$=node_con($1);}
    ;
Args: Exp COMMA Args {;}
    | Exp {;}
    ;

%%

node* node_con(char* str)
{
    return NULL;
}

node* add_node(char* str)
{
    return NULL;
}

void yyerror (char *s) {
   fprintf (stderr, "%s\n", s);
 }