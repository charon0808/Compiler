%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #include "bison.h"

    #include "syntax.tab.h"

    symbol_list* _symbol_table_start=NULL;

    void bison_error(const char*);
    node* node_con(char*);
    //node* add_node(const char*);
    int yylex(void);
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


Exp: Exp ASSIGNOP Exp {printf("exp=exp\n");}
    | Exp AND Exp {printf("exp && exp\n");}
    | Exp OR Exp {printf("exp || exp\n");}
    | Exp RELOP {printf("exp RELOP exp\n");}
    | Exp PLUS Exp {printf("exp + exp\n");}
    | Exp MINUS Exp {printf("exp - exp\n");}
    | Exp STAR Exp {printf("exp * exp\n");}
    | Exp DIV Exp {printf("exp / exp\n");}
    | LP Exp RP {printf("190\n");}
    | MINUS Exp {printf("121\n");}
    | NOT Exp {printf("132\n");}
    | ID LP Args RP {printf("134\n");}
    | ID LP RP {printf("145\n");}
    | Exp LB Exp RB {
        $$=node_con(NULL);
        add_child($$,$1);
        add_child($$,node_con($2));
        add_child($$,$3);
        add_child($$,node_con($4));
    }
    | Exp DOT ID {
        if (!add_in2_symbol_table($3){
            // TODO: if symbol already exists}
        }
        else{
            $$=node_con(NULL);
            add_child($$,$1);
            add_child($$,node_con($2));
            add_child($$,node_con($3));
        }
    }
    | ID {
        if (!add_in2_symbol_table($1){
            // TODO: if symbol already exists}
        }
        else
            $$=node_con($1);
    } 
    | INT {$$=node_con($1);}
    | FLOAT {$$=node_con($1);}
    ;
Args: Exp COMMA Args {printf("187\n");}
    | Exp {printf("198\n");}
    ;

%%

node* node_con(const char* str)
{
    node* new_node=(node *)malloc(sizeof(node));
    new_node->level=0;
    new_node->children=NULL;
    if (str!=NULL)
        new_node->code=strdup(str);
    return new_node;
}

void add_child(node* parent, node* child)
{
    child_list* start=parent->children;
    while(start!=NULL){
        start=start->next;
    }
    start->c=child;
    start->next=NULL;
}

int add_in2_symbol_table(const char* symbol_name)
{
    symbol_list* start=_symbol_table_start;
    while(start!=NUll){
        if(strcmp(start->symbol_name,symbol_name)==0)
            return 0;     // this ID already exists
        start=start->next;
    }
    start=(symbol_list*)malloc(sizeof(symbol_list));
    start->next=NULL;
    start->symbol_name=strdup(symbol_name);
    return 1;
}

node* add_node(char* str)
{
    return NULL;
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
	return 0;
}