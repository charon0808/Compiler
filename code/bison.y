%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #include "bison.h"
    #include "syntax.tab.h"

    #define YYERROR_VERBOSE 1 

    symbol_list* _symbol_table_start=NULL;

    void bison_error(const char*);
    node* node_con(char*);
    void add_child(node*,node*);
    int add_in2_symbol_table(const char*);
    int is_in_symbol_table(const char*);
    void print_tree(node*, int);
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

%start Program

%%
Program: ExtDefList {
        $$=node_con("Program");
        add_child($$,$1);
        program_node=$$;
        if (error)
            print_tree($$,0);
        //return 0;
    }
        ;
ExtDefList: ExtDef ExtDefList {
        $$=node_con("ExtDefList");
        add_child($$,$1);
        add_child($$,$2);
    }
        | {
            $$=node_con("ExtDefList");
            add_child($$,node_con(empty));
        }
        ;
ExtDef: Specifier ExtDecList SEMI {
        $$=node_con("ExtDef");
        add_child($$,$1);
        add_child($$,$2);
        strcpy(cat,"SEMI:");
        add_child($$,node_con(strcat(cat,$3)));
        child_node* start=$$->children;
    }
        | Specifier SEMI {
        $$=node_con("ExtDef");
        add_child($$,$1);
        strcpy(cat,"SEMI:");
        add_child($$,node_con(strcat(cat,$2)));
    }
        | Specifier FunDec CompSt {
        $$=node_con("ExtDef");
        add_child($$,$1);
        add_child($$,$2);
        add_child($$,$3);
    }
        ;
ExtDecList: VarDec {
            $$=node_con("ExtDecList");
            add_child($$,$1);
        }
        | VarDec COMMA ExtDecList {
            $$=node_con("ExtDecList");
            add_child($$,$1);
            strcpy(cat,"COMMA:");
            add_child($$,node_con(strcat(cat,$2)));
            add_child($$,$3);
        }
            ;

Specifier: TYPE {
        $$=node_con("Specifier");
        strcpy(cat,"TYPE:");
        add_child($$,node_con(strcat(cat,$1)));
        }
        | StructSpecifier {
        $$=node_con("Specifier");
        add_child($$,$1);
    }
        ;
StructSpecifier: STRUCT OptTag LC DefList RC {
                    $$=node_con("StructSpecifier");
                    add_child($$,node_con($1));
                    add_child($$,$2);
                    add_child($$,node_con("LC:{"));
                    add_child($$,$4);
                    add_child($$,node_con("RC:}"));
                }
                | STRUCT Tag {
                    $$=node_con("StructSpecifier");
                    add_child($$,node_con($1));
                    add_child($$,$2);
                }
                ;
OptTag: ID {
            if (!add_in2_symbol_table($1)){
                // TODO: if symbol already exists}
            }
            $$=node_con("OptTag");
            strcpy(cat,"ID:");
            add_child($$,node_con(strcat(cat,$1)));
        }              
        | {
            $$=node_con("OptTag");
            add_child($$,node_con(empty));
        }
        ;
Tag: ID {
            if (!add_in2_symbol_table($1)){
                // TODO: if symbol already exists}
            }
            $$=node_con("Tag");
            strcpy(cat,"ID:");
            add_child($$,node_con(strcat(cat,$1)));
        }
    ;

VarDec: ID {
        if (!add_in2_symbol_table($1)){
            // TODO: if symbol already exists}
        }
            $$=node_con("VarDec");
            strcpy(cat,"ID:");
            add_child($$,node_con(strcat(cat,$1)));
        }
        | VarDec LB INT RB {
            $$=node_con("VarDec");
            add_child($$,($1));
            add_child($$,node_con("LB:["));
            strcpy(cat,"INT:");
            add_child($$,node_con(strcat(cat,$3)));
            add_child($$,node_con("RB:]"));
        }
        ;
FunDec: ID LP VarList RP {
            if (!add_in2_symbol_table($1)){
                // TODO: if symbol already exists}
            }
            $$=node_con("FunDec");
            strcpy(cat,"ID:");
            add_child($$,node_con(strcat(cat,$1)));
            add_child($$,node_con("LP:("));
            add_child($$,$3);
            add_child($$,node_con("RP:)"));
        }
        | ID LP RP {
            if (!add_in2_symbol_table($1)){
                // TODO: if symbol already exists}
            }
            $$=node_con("FunDec");
            strcpy(cat,"ID:");
            add_child($$,node_con(strcat(cat,$1)));
            add_child($$,node_con("LP:("));
            add_child($$,node_con("RP:)"));
        }
        ;
VarList: ParamDec COMMA VarList {
            $$=node_con("VarList");
            add_child($$,$1);
            strcpy(cat,"COMMA:");
            add_child($$,node_con(strcat(cat,$2)));
            add_child($$,$3);
        }
        | ParamDec {
            $$=node_con(NULL);
            add_child($$,$1);
        }
        ;
ParamDec: Specifier VarDec {
            $$=node_con("ParamDec");
            add_child($$,$1);
            add_child($$,$2);
        }
        ;

CompSt: LC DefList StmtList RC {
            $$=node_con("CompSt");
            add_child($$,node_con("LC:{"));
            add_child($$,$2);
            add_child($$,$3);
            add_child($$,node_con("RC:}"));
        }
        ;
StmtList: Stmt StmtList {
            $$=node_con("StmtList");
            add_child($$,$1);
            add_child($$,$2);
            }
        | {
            $$=node_con("StmtList");
            add_child($$,node_con(empty));
        }
        ;
Stmt: Exp SEMI {
            $$=node_con("Stmt");
            add_child($$,$1);
            strcpy(cat,"SEMI:");
            add_child($$,node_con(strcat(cat,$2)));
        }
        | CompSt {
            $$=node_con("Stmt");
            add_child($$,$1);
        }
        | RETURN Exp SEMI {
            $$=node_con("Stmt");
            add_child($$,node_con($1));
            add_child($$,$2);
            strcpy(cat,"SEMI:");
            add_child($$,node_con(strcat(cat,$3)));
        }
        | IF LP Exp RP Stmt {
            $$=node_con("Stmt");
            add_child($$,node_con($1));
            add_child($$,node_con("LP:("));
            add_child($$,$3);
            add_child($$,node_con("RP:)"));
            add_child($$,$5);
        }
        | IF LP Exp RP Stmt ELSE Stmt {
            $$=node_con("Stmt");
            add_child($$,node_con($1));
            add_child($$,node_con("LP:("));
            add_child($$,$3);
            add_child($$,node_con("RP:)"));
            add_child($$,$5);
            add_child($$,node_con($6));
            add_child($$,$7);
        }
        | WHILE LP Exp RP Stmt {
            $$=node_con("Stmt");
            add_child($$,node_con($1));
            add_child($$,node_con("LP:("));
            add_child($$,$3);
            add_child($$,node_con("RP:)"));
            add_child($$,$5);
        }
        ;

DefList: Def DefList {
            $$=node_con("DefList");
            add_child($$,$1);
            add_child($$,$2);
        }
        | {
            $$=node_con("DefList");
            add_child($$,node_con(empty));
        }
        ;
Def: Specifier DecList SEMI {
            $$=node_con("Def");
            add_child($$,$1);
            add_child($$,$2);
            strcpy(cat,"SEMI:");
            add_child($$,node_con(strcat(cat,$3)));
        }
    ;
DecList: Dec  {
            $$=node_con("DecList");
            add_child($$,$1);
        }
        | Dec COMMA DecList {
            $$=node_con("DecList");
            add_child($$,$1);
            strcpy(cat,"COMMA:");
            add_child($$,node_con(strcat(cat,$2)));
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
            strcpy(cat,"ASSIGNOP:");
            add_child($$,node_con(strcat(cat,$2)));
            add_child($$,$3);
        }
    ;

Exp: Exp ASSIGNOP Exp {
        $$=node_con("Exp");
        add_child($$,$1);
        strcpy(cat,"ASSIGNOP:");
        add_child($$,node_con(strcat(cat,$2)));
        add_child($$,$3);
    }
    | Exp AND Exp {
        $$=node_con("Exp");
        add_child($$,$1);
        add_child($$,node_con("AND:&&"));
        add_child($$,$3);
    }
    | Exp OR Exp {
        $$=node_con("Exp");
        add_child($$,$1);
        add_child($$,node_con("OR:||"));
        add_child($$,$3);
    }
    | Exp RELOP Exp{
        $$=node_con("Exp");
        add_child($$,$1);
        strcpy(cat,"RELOP:");
        add_child($$,node_con(strcat(cat,$2)));
        add_child($$,$3);
    }
    | Exp PLUS Exp {
        $$=node_con("Exp");
        add_child($$,$1);
        strcpy(cat,"PLUS:");
        add_child($$,node_con(strcat(cat,$2)));
        add_child($$,$3);
    }
    | Exp MINUS Exp {
        $$=node_con("Exp");
        add_child($$,$1);
        strcpy(cat,"MINUS:");
        add_child($$,node_con(strcat(cat,$2)));
        add_child($$,$3);
    }
    | Exp STAR Exp {
        $$=node_con("Exp");
        add_child($$,$1);
        strcpy(cat,"STAR");
        add_child($$,node_con(strcat(cat,$2)));
        add_child($$,$3);
    }
    | Exp DIV Exp {
        $$=node_con("Exp");
        add_child($$,$1);
        add_child($$,node_con("DIV:/"));
        add_child($$,$3);
    }
    | LP Exp RP {
        $$=node_con("Exp");
        add_child($$,node_con("LP:("));
        add_child($$,$2);
        add_child($$,node_con("RP:)"));
    }
    | MINUS Exp {
        $$=node_con("Exp");
        strcpy(cat,"MINUS:");
        add_child($$,node_con(strcat(cat,$1)));
        add_child($$,$2);
    }
    | NOT Exp {
        $$=node_con("Exp");
        add_child($$,node_con("NOT:!"));
        add_child($$,$2);
    }
    | ID LP Args RP {
        if (is_in_symbol_table($1)){
            // TODO:
        }
        $$=node_con("Exp");
        strcpy(cat,"ID:");
        add_child($$,node_con(strcat(cat,$1)));
        add_child($$,node_con("LP:("));
        add_child($$,$3);
        add_child($$,node_con("RP:)"));
    }
    | ID LP RP {
        if (is_in_symbol_table($1)){
            // TODO:
        }
        $$=node_con("Exp");
        strcpy(cat,"ID:");
        add_child($$,node_con(strcat(cat,$1)));
        add_child($$,node_con("LP:("));
        add_child($$,node_con("RP:)"));
    }
    | Exp LB Exp RB {
        $$=node_con("Exp");
        add_child($$,$1);
        add_child($$,node_con("LB:["));
        add_child($$,$3);
        add_child($$,node_con("RB:]"));
    }
    | Exp DOT ID {
        if (is_in_symbol_table($3)){
            // TODO:
        }
            $$=node_con("Exp");
            add_child($$,$1);
            add_child($$,node_con("DOT:."));
            strcpy(cat,"ID:");
            add_child($$,node_con(strcat(cat,$3)));
    }
    | ID {
        if (is_in_symbol_table($1)){
            // TODO:
        }
            $$=node_con("Exp");
            strcpy(cat,"ID:");
            add_child($$,node_con(strcat(cat,$1)));
    } 
    | INT {
            $$=node_con("Exp");
            strcpy(cat,"INT:");
            add_child($$,node_con(strcat(cat,$1)));
        }
    | FLOAT {
            $$=node_con("Exp");
            strcpy(cat,"FLOAT:");
            add_child($$,node_con(strcat(cat,$1)));
        }
    ;
Args: Exp COMMA Args {
        $$=node_con("Args");
        add_child($$,$1);
        strcpy(cat,"COMMA:");
        add_child($$,node_con(strcat(cat,$2)));
        add_child($$,$3);
    }
    | Exp {
        $$=node_con("Args");
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
        //printf("%s\n",str);
        new_node->code=strdup(str);
    }
    return new_node;
}

void add_child(node* parent, node* child)
{
    child_node* start=parent->children;
    while(start!=NULL&&start->next!=NULL){
        start=start->next;
    }
    if (start==NULL)
        start=parent->children=(child_node*)malloc(sizeof(child_node));
    else{
        start->next=(child_node*)malloc(sizeof(child_node));
        start=start->next;
    }
    start->c=child;
    start->next=NULL;
    /*printf("child:[%s] added into parent:[%s]\n",child->code,parent->code);
    start=parent->children;
    printf("parent [%s] children:\n",parent->code);
    for (int i=0;start!=NULL;i++,start=start->next){
        printf("child %d is [%s]\n",i,start->c->code);
    }*/
}

void print_tree(node* root, int level)
{
    if (root->children!=NULL&&strcmp(root->children->c->code,"\"empty\"")==0){
        //printf("---This is empty---\n");
        return;
    }
    for (int i=0;i<level;i++)
        printf("  ");
    printf("%s\n",root->code);
    if (root->children!=NULL){
        child_node* start=root->children;
        while (start!=NULL){
            print_tree(start->c,level+1);
            start=start->next;
        }
    }
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


void yyerror (const char *s) {
    error=0;
    fprintf (stderr, "Error type B at line %d: %s\n",yylineno, s);
    //yyparse();
}

int main(int argc, char* argv[]) {
    if (argc>1)
        if ((f=freopen(argv[1],"r",stdin))==NULL){
            perror(argv[1]);
            return 1;
        }
    cat=(char*)malloc(sizeof(char)*64);
	yyparse();
	return 0;
}