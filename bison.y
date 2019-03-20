%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #include "bison.h"

    #include "syntax.tab.h"

    symbol_list* _symbol_table_start=NULL;

    void bison_error(const char*);
    node* node_con(char*);
    void add_child(node*,node*);
    int add_in2_symbol_table(const char*);
    int is_in_symbol_table(const char*);
    void print_tree(node*, int);
    char* empty="1o1";
    node* program_node;
    int yylex(void);
    void yyerror(char *);  
%}

%union{
    union value val;
    node* _node;
    char name[32];
}

%token WS
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
%token <name> TYPE
%token <name> RELOP

%type <_node> Program ExtDefList ExtDef ExtDecList 
%type <_node> Specifier StructSpecifier OptTag Tag
%type <_node> VarDec FunDec VarList ParamDec
%type <_node> CompSt StmtList Stmt
%type <_node> DefList Def DecList Dec
%type <_node> Exp Args

%%
Program: ExtDefList {
        $$=node_con(NULL);
        add_child($$,$1);
        program_node=$$;
        print_tree($$,0);
        //return 0;
    }
        ;
ExtDefList: ExtDef ExtDefList {
        $$=node_con(NULL);
        add_child($$,$1);
        add_child($$,$2);
    }
        | {
            $$=node_con(NULL);
            add_child($$,node_con(empty));
        }
        ;
ExtDef: Specifier ExtDecList SEMI {
        $$=node_con(NULL);
        add_child($$,$1);
        add_child($$,$2);
        add_child($$,node_con($3));
    }
        | Specifier SEMI {
        $$=node_con(NULL);
        add_child($$,$1);
        add_child($$,node_con($2));
    }
        | Specifier FunDec CompSt {
        $$=node_con(NULL);
        add_child($$,$1);
        add_child($$,$2);
        add_child($$,$3);
    }
        ;
ExtDecList: VarDec {
            $$=node_con(NULL);
            add_child($$,$1);
        }
        | VarDec COMMA ExtDecList {
            $$=node_con(NULL);
            add_child($$,$1);
            add_child($$,node_con($2));
            add_child($$,$3);
        }
            ;

Specifier: TYPE {
        $$=node_con(NULL);
        add_child($$,node_con($1));
        }
        | StructSpecifier {
        $$=node_con(NULL);
        add_child($$,$1);
    }
        ;
StructSpecifier: STRUCT OptTag LC DefList RC {
                    $$=node_con(NULL);
                    add_child($$,node_con($1));
                    add_child($$,$2);
                    add_child($$,node_con($3));
                    add_child($$,$4);
                    add_child($$,node_con($5));
                }
                | STRUCT Tag {
                    $$=node_con(NULL);
                    add_child($$,node_con($1));
                    add_child($$,$2);
                }
                ;
OptTag: ID {
        if (!add_in2_symbol_table($1)){
            // TODO: if symbol already exists}
        }
            $$=node_con(NULL);
            add_child($$,node_con($1));
        }
                    
        | {
            $$=node_con(NULL);
            add_child($$,node_con(empty));
        }
        ;
Tag: ID {
        if (!add_in2_symbol_table($1)){
            // TODO: if symbol already exists}
        }
            $$=node_con(NULL);
            add_child($$,node_con($1));
        }
    ;

VarDec: ID {
        if (!add_in2_symbol_table($1)){
            // TODO: if symbol already exists}
        }
            $$=node_con(NULL);
            add_child($$,node_con($1));
        }
        | VarDec LB INT RB {
            $$=node_con(NULL);
            add_child($$,($1));
            add_child($$,node_con($2));
            add_child($$,node_con($3));
            add_child($$,node_con($4));
        }
        ;
FunDec: ID LP VarList RP {
            if (!add_in2_symbol_table($1)){
                // TODO: if symbol already exists}
            }
            $$=node_con(NULL);
            add_child($$,node_con($1));
            add_child($$,node_con($2));
            add_child($$,$3);
            add_child($$,node_con($4));
        }
        | ID LP RP {
            if (!add_in2_symbol_table($1)){
                // TODO: if symbol already exists}
            }
            $$=node_con(NULL);
            add_child($$,node_con($1));
            add_child($$,node_con($2));
            add_child($$,node_con($3));
        }
        ;
VarList: ParamDec COMMA VarList {
            $$=node_con(NULL);
            add_child($$,$1);
            add_child($$,node_con($2));
            add_child($$,$3);
        }
        | ParamDec {
            $$=node_con(NULL);
            add_child($$,$1);
        }
        ;
ParamDec: Specifier VarDec {
            $$=node_con(NULL);
            add_child($$,$1);
            add_child($$,$2);
        }
        ;

CompSt: LC DefList StmtList RC {
            $$=node_con(NULL);
            add_child($$,node_con($1));
            add_child($$,$2);
            add_child($$,$3);
            add_child($$,node_con($4));
        }
        ;
StmtList: Stmt StmtList {
            $$=node_con(NULL);
            add_child($$,$1);
            add_child($$,$2);
            }
        | {
            $$=node_con(NULL);
            add_child($$,node_con(empty));
        }
        ;
Stmt: Exp SEMI {
            $$=node_con(NULL);
            add_child($$,$1);
            add_child($$,node_con($2));
        }
        | CompSt {
            $$=node_con(NULL);
            add_child($$,$1);
        }
        | RETURN Exp SEMI {
            $$=node_con(NULL);
            add_child($$,node_con($1));
            add_child($$,$2);
            add_child($$,node_con($3));
        }
        | IF LP Exp RP Stmt {
            $$=node_con(NULL);
            add_child($$,node_con($1));
            add_child($$,node_con($2));
            add_child($$,$3);
            add_child($$,node_con($4));
            add_child($$,$5);
        }
        | IF LP Exp RP Stmt ELSE Stmt {
            $$=node_con(NULL);
            add_child($$,node_con($1));
            add_child($$,node_con($2));
            add_child($$,$3);
            add_child($$,node_con($4));
            add_child($$,$5);
            add_child($$,node_con($6));
            add_child($$,$7);
        }
        | WHILE LP Exp RP Stmt {
            $$=node_con(NULL);
            add_child($$,node_con($1));
            add_child($$,node_con($2));
            add_child($$,$3);
            add_child($$,node_con($4));
            add_child($$,$5);
        }
        ;

DefList: Def DefList {
            $$=node_con(NULL);
            add_child($$,$1);
            add_child($$,$2);
        }
        | {
            $$=node_con(NULL);
            add_child($$,node_con(empty));
        }
        ;
Def: Specifier DecList SEMI {
            $$=node_con(NULL);
            add_child($$,$1);
            add_child($$,$2);
            add_child($$,node_con($3));
        }
    ;
DecList: Dec  {
            $$=node_con(NULL);
            add_child($$,$1);
        }
        | Dec COMMA DecList {
            $$=node_con(NULL);
            add_child($$,$1);
            add_child($$,node_con($2));
            add_child($$,$3);
        }
        ;
Dec: VarDec {
            $$=node_con(NULL);
            add_child($$,$1);
        }
    | VarDec ASSIGNOP Exp {
        printf("IN Dec\n");
            $$=node_con(NULL);
            add_child($$,$1);
            add_child($$,node_con($2));
            add_child($$,$3);
        }
    ;

Exp: Exp ASSIGNOP Exp {
        $$=node_con(NULL);
        add_child($$,$1);
        add_child($$,node_con($2));
        add_child($$,$3);
    }
    | Exp AND Exp {
        $$=node_con(NULL);
        add_child($$,$1);
        add_child($$,node_con($2));
        add_child($$,$3);
    }
    | Exp OR Exp {
        $$=node_con(NULL);
        add_child($$,$1);
        add_child($$,node_con($2));
        add_child($$,$3);
    }
    | Exp RELOP {
        $$=node_con(NULL);
        add_child($$,$1);
        add_child($$,node_con($2));
    }
    | Exp PLUS Exp {
        $$=node_con(NULL);
        add_child($$,$1);
        add_child($$,node_con($2));
        add_child($$,$3);
    }
    | Exp MINUS Exp {
        $$=node_con(NULL);
        add_child($$,$1);
        add_child($$,node_con($2));
        add_child($$,$3);
    }
    | Exp STAR Exp {
        $$=node_con(NULL);
        add_child($$,$1);
        add_child($$,node_con($2));
        add_child($$,$3);
    }
    | Exp DIV Exp {
        $$=node_con(NULL);
        add_child($$,$1);
        add_child($$,node_con($2));
        add_child($$,$3);
    }
    | LP Exp RP {
        $$=node_con(NULL);
        add_child($$,node_con($1));
        add_child($$,$2);
        add_child($$,node_con($3));
    }
    | MINUS Exp {
        $$=node_con(NULL);
        add_child($$,node_con($1));
        add_child($$,$2);
    }
    | NOT Exp {
        $$=node_con(NULL);
        add_child($$,node_con($1));
        add_child($$,$2);
    }
    | ID LP Args RP {
        if (is_in_symbol_table($1)){
            // TODO:
        }
        $$=node_con(NULL);
        add_child($$,node_con($1));
        add_child($$,node_con($2));
        add_child($$,$3);
        add_child($$,node_con($4));
    }
    | ID LP RP {
        if (is_in_symbol_table($1)){
            // TODO:
        }
        $$=node_con(NULL);
        add_child($$,node_con($1));
        add_child($$,node_con($2));
        add_child($$,node_con($3));
    }
    | Exp LB Exp RB {
        $$=node_con(NULL);
        add_child($$,$1);
        add_child($$,node_con($2));
        add_child($$,$3);
        add_child($$,node_con($4));
    }
    | Exp DOT ID {
        if (is_in_symbol_table($3)){
            // TODO:
        }
            $$=node_con(NULL);
            add_child($$,$1);
            add_child($$,node_con($2));
            add_child($$,node_con($3));
    }
    | ID {
        if (is_in_symbol_table($1)){
            // TODO:
        }
            $$=node_con(NULL);
            add_child($$,node_con($1));
    } 
    | INT {
            $$=node_con(NULL);
            add_child($$,node_con($1));
        }
    | FLOAT {
            $$=node_con(NULL);
            add_child($$,node_con($1));
        }
    ;
Args: Exp COMMA Args {
        $$=node_con(NULL);
        add_child($$,$1);
        add_child($$,node_con($2));
        add_child($$,$3);
    }
    | Exp {
        $$=node_con(NULL);
        add_child($$,$1);
    }
    ;

%%

//void print_tree()

node* node_con(char* str)
{
    node* new_node=(node *)malloc(sizeof(node));
    new_node->level=0;
    new_node->children=NULL;
    if (str!=NULL){
        printf("%s\n",str);
        new_node->code=strdup(str);
    }
    return new_node;
}

void add_child(node* parent, node* child)
{
    child_list* start=parent->children;
    while(start!=NULL){
        start=start->next;
    }
    start=(child_list*)malloc(sizeof(child_list));
    start->c=child;
    start->next=NULL;
}

int add_in2_symbol_table(const char* symbol_name)
{
    symbol_list* start=_symbol_table_start;
    while(start!=NULL){
        if(strcmp(start->symbol_name,symbol_name)==0)
            return 0;     // this ID already exists
        start=start->next;
    }
    start=(symbol_list*)malloc(sizeof(symbol_list));
    start->next=NULL;
    start->symbol_name=strdup(symbol_name);
    return 1;
}

int is_in_symbol_table(const char* symbol_name)
{
    symbol_list* start=_symbol_table_start;
    while(start!=NULL){
        if(strcmp(start->symbol_name,symbol_name)==0)
            return 1; 
    }
    return 0;
}

void print_tree(node* root, int level)
{
    if (root->children==NULL){
        printf("%*s",level*4,root->code);
    }
    else {
        child_list* start=root->children;
        while (start!=NULL){
            print_tree(start->c,level+1);
        }
    }
}

void yyerror (char *s) {
   fprintf (stderr, "%s\n", s);
 }

int main(int argc, char* argv[]) {
    /*int fd;
    if (argc>1&& (fd=open("sample.test",O_RDONLY))){
        perror(argv[1]);
        return 1;
    }
    dup2(fd,0);*/
	yyparse();
   // printf("%s\n",program_node->code);
	return 0;
}