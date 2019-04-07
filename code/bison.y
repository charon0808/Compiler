%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #include "bison.h"
    #include "syntax.tab.h"

    #define YYERROR_VERBOSE 1 

    symbol_list* _var_symbol_table_start=NULL;
    symbol_list* _fun_symbol_table_start=NULL;

    void bison_error(const char*);
    
    node* node_con(char*);
    void add_child(node*,node*);
    void print_tree(node*, int);
    void free_all(node*);

    int add_in2_symbol_table(struct value);
    int is_in_symbol_table(struct value);

    char* empty="\"empty\"";
    char* cat;
    node* program_node;
    FILE* f;
    extern int yylineno;
    extern char* yytext;
    int yylex(void);
    void yyerror(const char *);  
    int error=1;
%}

%union{
    struct value val;
    node* _node;
}

%token WS
%token <val> INT FLOAT
%token <val> ID
%token <val> SEMI COMMA 
%right <val> ASSIGNOP
%left  <val> LT LE EQ NE GT GE
%left  <val> PLUS MINUS
%token <val> STAR
%left  <val> DIV AND OR 
%right <val> NOT
%left  <val> DOT
%left  <val> LP RP LB RB 
%token <val> LC RC
%token <val> STRUCT RETURN
%token <val> IF ELSE WHILE
%token <val> TYPE
%token <val> RELOP

%type <_node> Program ExtDefList ExtDef ExtDecList 
%type <_node> Specifier StructSpecifier OptTag Tag
%type <_node> VarDec FunDec VarList ParamDec
%type <_node> CompSt StmtList Stmt
%type <_node> DefList Def DecList Dec
%type <_node> Exp Args

%start Program

%%
Program: ExtDefList {
        $$=node_con("Program", 0);
        add_child($$,$1);
        program_node=$$;
        if (error){
            print_tree($$,0);
            free_all($$);
        }
    }
    | error {;}
        ;
ExtDefList: ExtDef ExtDefList {
        $$=node_con("ExtDefList", 1);
        add_child($$,$1);
        add_child($$,$2);
    }
        | {
            $$=node_con("ExtDefList", 1);
            add_child($$,node_con(empty));
        }
    | error {;}
        ;
ExtDef: Specifier ExtDecList SEMI {
        $$=node_con("ExtDef", 2);
        add_child($$,$1);
        add_child($$,$2);
        add_child($$,node_con("SEMI"));
        child_node* start=$$->children;
    }
        | Specifier SEMI {
        $$=node_con("ExtDef", 2);
        add_child($$,$1);
        add_child($$,node_con("SEMI"));
    }
        | Specifier FunDec CompSt {
        $$=node_con("ExtDef", 2);
        add_child($$,$1);
        add_child($$,$2);
        add_child($$,$3);
    }
    | error {;}
        ;
ExtDecList: VarDec {
            $$=node_con("ExtDecList", 3);
            add_child($$,$1);
        }
        | VarDec COMMA ExtDecList {
            $$=node_con("ExtDecList", 3);
            add_child($$,$1);
            add_child($$,node_con("COMMA"));
            add_child($$,$3);
        }
    | error {;}
            ;

Specifier: TYPE {
        $$=node_con("Specifier", 4);
        strcpy(cat,"TYPE: ");
        add_child($$,node_con(strcat(cat,$1.name)));
        }
        | StructSpecifier {
        $$=node_con("Specifier", 4);
        add_child($$,$1);
    }
    | error {;}
        ;
StructSpecifier: STRUCT OptTag LC DefList RC {
                    $$=node_con("StructSpecifier", 5);
                    sprintf(cat,"%d^STRUCT",$1.lineno);
                    add_child($$,node_con(cat));
                    add_child($$,$2);
                    add_child($$,node_con("LC"));
                    add_child($$,$4);
                    add_child($$,node_con("RC"));
                }
                | STRUCT Tag {
                    $$=node_con("StructSpecifier", 5);
                    sprintf(cat,"%d^STRUCT",$1.lineno);
                    add_child($$,node_con(cat));
                    add_child($$,$2);
                }
                ;
OptTag: ID {
            if (!add_in2_symbol_table($1)){
                // TODO: if symbol already exists}
            }
            $$=node_con("OptTag");
            strcpy(cat,"ID: ");
            add_child($$,node_con(strcat(cat,$1.name)));
        }              
        | {
            $$=node_con("OptTag");
            add_child($$,node_con(empty));
        }
    | error {;}
        ;
Tag: ID {
            if (!add_in2_symbol_table($1)){
                // TODO: if symbol already exists}
            }
            $$=node_con("Tag");
            strcpy(cat,"ID: ");
            add_child($$,node_con(strcat(cat,$1.name)));
        }
    | error {;}
    ;

VarDec: ID {
        if (!add_in2_symbol_table($1)){
            // TODO: if symbol already exists}
        }
            $$=node_con("VarDec", 6);
            strcpy(cat,"ID: ");
            add_child($$,node_con(strcat(cat,$1.name)));
        }
        | VarDec LB INT RB {
            $$=node_con("VarDec", 6);
            add_child($$,($1));
            add_child($$,node_con("LB"));
            strcpy(cat,"INT: ");
            add_child($$,node_con(strcat(cat,$3.name)));
            add_child($$,node_con("RB"));
        }
    | error {;}
        ;
FunDec: ID LP VarList RP {
            if (!add_in2_symbol_table($1)){
                // TODO: if symbol already exists}
            }
            $$=node_con("FunDec", 7);
            strcpy(cat,"ID: ");
            add_child($$,node_con(strcat(cat,$1.name)));
            add_child($$,node_con("LP"));
            add_child($$,$3);
            add_child($$,node_con("RP"));
        }
        | ID LP RP {
            if (!add_in2_symbol_table($1)){
                // TODO: if symbol already exists}
            }
            $$=node_con("FunDec", 7);
            strcpy(cat,"ID: ");
            add_child($$,node_con(strcat(cat,$1.name)));
            add_child($$,node_con("LP"));
            add_child($$,node_con("RP"));
        }
    | error {;}
        ;
VarList: ParamDec COMMA VarList {
            $$=node_con("VarList", 8);
            add_child($$,$1);
            add_child($$,node_con("COMMA"));
            add_child($$,$3);
        }
        | ParamDec {
            $$=node_con(NULL);
            add_child($$,$1);
        }
    | error {;}
        ;
ParamDec: Specifier VarDec {
            $$=node_con("ParamDec", 9);
            add_child($$,$1);
            add_child($$,$2);
        }
    | error {;}
        ;

CompSt: LC DefList StmtList RC {
            $$=node_con("CompSt", 10);
            sprintf(cat,"%d^LC",$1.lineno);
            add_child($$,node_con(cat));
            add_child($$,$2);
            add_child($$,$3);
            add_child($$,node_con("RC"));
        }
    | error {;}
        ;
StmtList: Stmt StmtList {
            $$=node_con("StmtList", 12);
            add_child($$,$1);
            add_child($$,$2);
            }
        | {
            $$=node_con("StmtList", 12);
            add_child($$,node_con(empty));
        }
        ;
Stmt: Exp SEMI {
            $$=node_con("Stmt", 13);
            add_child($$,$1);
            add_child($$,node_con("SEMI"));
        }
        | CompSt {
            $$=node_con("Stmt", 13);
            add_child($$,$1);
        }
        | RETURN Exp SEMI {
            $$=node_con("Stmt", 13);
            add_child($$,node_con("RETURN"));
            add_child($$,$2);
            add_child($$,node_con("SEMI"));
        }
        | IF LP Exp RP Stmt {
            $$=node_con("Stmt", 13);
            add_child($$,node_con("IF"));
            add_child($$,node_con("LP"));
            add_child($$,$3);
            add_child($$,node_con("RP"));
            add_child($$,$5);
        }
        | IF LP Exp RP Stmt ELSE Stmt {
            $$=node_con("Stmt", 13);
            add_child($$,node_con("IF"));
            add_child($$,node_con("LP"));
            add_child($$,$3);
            add_child($$,node_con("RP"));
            add_child($$,$5);
            add_child($$,node_con("ELSE"));
            add_child($$,$7);
        }
        | WHILE LP Exp RP Stmt {
            $$=node_con("Stmt", 13);
            add_child($$,node_con("WHILE"));
            add_child($$,node_con("LP"));
            add_child($$,$3);
            add_child($$,node_con("RP"));
            add_child($$,$5);
        }
        ;

DefList: Def DefList {
            $$=node_con("DefList", 11);
            add_child($$,$1);
            add_child($$,$2);
        }
        | {
            $$=node_con("DefList", 11);
            add_child($$,node_con(empty));
        }
    | error {;}
        ;
Def: Specifier DecList SEMI {
            $$=node_con("Def", 14);
            add_child($$,$1);
            add_child($$,$2);
            add_child($$,node_con("SEMI"));
        }
    | error {;}
    ;
DecList: Dec  {
            $$=node_con("DecList");
            add_child($$,$1);
        }
        | Dec COMMA DecList {
            $$=node_con("DecList");
            add_child($$,$1);
            add_child($$,node_con("COMMA"));
            add_child($$,$3);
        }
        ;
Dec: VarDec {
            $$=node_con("Dec");
            add_child($$,$1);
        }
    | VarDec ASSIGNOP Exp {
            $$=node_con("Dec");
            add_child($$,$1);
            add_child($$,node_con("ASSIGNOP"));
            add_child($$,$3);
        }
    ;

Exp: Exp ASSIGNOP Exp {
        $$=node_con("Exp", 15);
        add_child($$,$1);
        add_child($$,node_con("ASSIGNOP"));
        add_child($$,$3);
    }
    | Exp AND Exp {
        $$=node_con("Exp", 15);
        add_child($$,$1);
        add_child($$,node_con("AND"));
        add_child($$,$3);
    }
    | Exp OR Exp {
        $$=node_con("Exp", 15);
        add_child($$,$1);
        add_child($$,node_con("OR"));
        add_child($$,$3);
    }
    | Exp RELOP Exp{
        $$=node_con("Exp", 15);
        add_child($$,$1);
        strcpy(cat,"RELOP: ");
        add_child($$,node_con(strcat(cat,$2.name)));
        add_child($$,$3);
    }
    | Exp PLUS Exp {
        $$=node_con("Exp", 15);
        add_child($$,$1);
        add_child($$,node_con("PLUS"));
        add_child($$,$3);
    }
    | Exp MINUS Exp {
        $$=node_con("Exp", 15);
        add_child($$,$1);
        add_child($$,node_con("MINUS"));
        add_child($$,$3);
    }
    | Exp STAR Exp {
        $$=node_con("Exp", 15);
        add_child($$,$1);
        add_child($$,node_con("STAR"));
        add_child($$,$3);
    }
    | Exp DIV Exp {
        $$=node_con("Exp", 15);
        add_child($$,$1);
        add_child($$,node_con("DIV"));
        add_child($$,$3);
    }
    | LP Exp RP {
        $$=node_con("Exp", 15);
        add_child($$,node_con("LP"));
        add_child($$,$2);
        add_child($$,node_con("RP"));
    }
    | MINUS Exp {
        $$=node_con("Exp", 15);
        add_child($$,node_con("MINUS"));
        add_child($$,$2);
    }
    | NOT Exp {
        $$=node_con("Exp", 15);
        add_child($$,node_con("NOT"));
        add_child($$,$2);
    }
    | ID LP Args RP {
        if (is_in_symbol_table($1)){
            // TODO:
        }
        $$=node_con("Exp", 15);
        strcpy(cat,"ID: ");
        add_child($$,node_con(strcat(cat,$1.name)));
        add_child($$,node_con("LP"));
        add_child($$,$3);
        add_child($$,node_con("RP"));
    }
    | ID LP RP {
        if (is_in_symbol_table($1)){
            // TODO:
        }
        $$=node_con("Exp", 15);
        strcpy(cat,"ID: ");
        add_child($$,node_con(strcat(cat,$1.name)));
        add_child($$,node_con("LP"));
        add_child($$,node_con("RP"));
    }
    | Exp LB Exp RB {
        $$=node_con("Exp", 15);
        add_child($$,$1);
        add_child($$,node_con("LB"));
        add_child($$,$3);
        add_child($$,node_con("RB"));
    }
    | Exp DOT ID {
        if (is_in_symbol_table($3)){
            // TODO:
        }
            $$=node_con("Exp", 15);
            add_child($$,$1);
            add_child($$,node_con("DOT"));
            strcpy(cat,"ID: ");
            add_child($$,node_con(strcat(cat,$3.name)));
    }
    | ID {
        if (is_in_symbol_table($1)){
            // TODO:
        }
            $$=node_con("Exp", 15);
            strcpy(cat,"ID: ");
            add_child($$,node_con(strcat(cat,$1.name)));
    } 
    | INT {
            $$=node_con("Exp", 15);
            sprintf(cat,"INT: %d",yylval.val.ival);
            add_child($$,node_con(cat));
        }
    | FLOAT {
            $$=node_con("Exp", 15);
            sprintf(cat,"FLOAT: %f",$1.fval);
            add_child($$,node_con(cat));
        }
    | error {;}
    ;
Args: Exp COMMA Args {
        $$=node_con("Args");
        add_child($$,$1);
        add_child($$,node_con("COMMA"));
        add_child($$,$3);
    }
    | Exp {
        $$=node_con("Args");
        add_child($$,$1);
    }
    ;

%%

//void print_tree()

