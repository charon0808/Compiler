%{
    #include <stdio.h>
    #include <stdlib.h>

    void bison_error(const char*);
%}

%token INT FLOAT
%token ID
%token SEMI COMMA ASSIGNOP
%token LT LE EQ NE GT GE
%token PLUS MINUS
%token STAR DIV
%token DIV AND OR DOT NOT
%token LP RP LB RB LC RC
%token STRUCT RETURN
%token IF ELSE WHILE
%token TYPE
%token RELOP

%%

Program: ExtDefList {;}
        ;
ExtDefList: ExtDef ExtDefList {;}
            | {;}
            ;
ExtDef: Specifier ExtDefList SEMI {;}
        | Specifier SEMI {;}
        | Specifier FunDec CompSt {;}
        ;
ExtDefList: VarDec {;}
            | VarDec COMMA ExtDefList {;}
            ;

ifier: TYPE StructSpecifier {;}
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
    | INT {;}
    | FLOAT {;}
    ;
Args: Exp COMMA Args {;}
    | Exp {;}
    ;

%%