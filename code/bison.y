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
    int add_in2_symbol_table(struct value);
    int is_in_symbol_table(struct value);
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
    struct value val;
    node* _node;
    char name[32];
}

%token WS
%token <val> INT FLOAT
%token <val> ID
%token <val> SEMI COMMA ASSIGNOP
%token <val> LT LE EQ NE GT GE
%token <val> PLUS MINUS
%token <val> STAR
%token <val> DIV AND OR DOT NOT
%token <val> LP RP LB RB LC RC
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
        $$=node_con("Program");
        add_child($$,$1);
        program_node=$$;
        if (error)
            print_tree($$,0);
    }
    | error {;}
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
    | error {;}
        ;
ExtDef: Specifier ExtDecList SEMI {
        $$=node_con("ExtDef");
        add_child($$,$1);
        add_child($$,$2);
        strcpy(cat,"SEMI:");
        add_child($$,node_con(strcat(cat,$3.name)));
        child_node* start=$$->children;
    }
        | Specifier SEMI {
        $$=node_con("ExtDef");
        add_child($$,$1);
        strcpy(cat,"SEMI:");
        add_child($$,node_con(strcat(cat,$2.name)));
    }
        | Specifier FunDec CompSt {
        $$=node_con("ExtDef");
        add_child($$,$1);
        add_child($$,$2);
        add_child($$,$3);
    }
    | error {;}
        ;
ExtDecList: VarDec {
            $$=node_con("ExtDecList");
            add_child($$,$1);
        }
        | VarDec COMMA ExtDecList {
            $$=node_con("ExtDecList");
            add_child($$,$1);
            strcpy(cat,"COMMA:");
            add_child($$,node_con(strcat(cat,$2.name)));
            add_child($$,$3);
        }
    | error {;}
            ;

Specifier: TYPE {
        $$=node_con("Specifier");
        strcpy(cat,"TYPE:");
        add_child($$,node_con(strcat(cat,$1.name)));
        }
        | StructSpecifier {
        $$=node_con("Specifier");
        add_child($$,$1);
    }
    | error {;}
        ;
StructSpecifier: STRUCT OptTag LC DefList RC {
                    $$=node_con("StructSpecifier");
                    add_child($$,node_con($1.name));
                    add_child($$,$2);
                    add_child($$,node_con("LC"));
                    add_child($$,$4);
                    add_child($$,node_con("RC"));
                }
                | STRUCT Tag {
                    $$=node_con("StructSpecifier");
                    add_child($$,node_con($1.name));
                    add_child($$,$2);
                }
                ;
OptTag: ID {
            if (!add_in2_symbol_table($1)){
                // TODO: if symbol already exists}
            }
            $$=node_con("OptTag");
            strcpy(cat,"ID:");
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
            strcpy(cat,"ID:");
            add_child($$,node_con(strcat(cat,$1.name)));
        }
    | error {;}
    ;

VarDec: ID {
        if (!add_in2_symbol_table($1)){
            // TODO: if symbol already exists}
        }
            $$=node_con("VarDec");
            strcpy(cat,"ID:");
            add_child($$,node_con(strcat(cat,$1.name)));
        }
        | VarDec LB INT RB {
            $$=node_con("VarDec");
            add_child($$,($1));
            add_child($$,node_con("LB"));
            strcpy(cat,"INT:");
            add_child($$,node_con(strcat(cat,$3.name)));
            add_child($$,node_con("RB"));
        }
    | error {;}
        ;
FunDec: ID LP VarList RP {
            if (!add_in2_symbol_table($1)){
                // TODO: if symbol already exists}
            }
            $$=node_con("FunDec");
            strcpy(cat,"ID:");
            add_child($$,node_con(strcat(cat,$1.name)));
            add_child($$,node_con("LP"));
            add_child($$,$3);
            add_child($$,node_con("RP"));
        }
        | ID LP RP {
            if (!add_in2_symbol_table($1)){
                // TODO: if symbol already exists}
            }
            $$=node_con("FunDec");
            strcpy(cat,"ID:");
            add_child($$,node_con(strcat(cat,$1.name)));
            add_child($$,node_con("LP"));
            add_child($$,node_con("RP"));
        }
    | error {;}
        ;
VarList: ParamDec COMMA VarList {
            $$=node_con("VarList");
            add_child($$,$1);
            strcpy(cat,"COMMA:");
            add_child($$,node_con(strcat(cat,$2.name)));
            add_child($$,$3);
        }
        | ParamDec {
            $$=node_con(NULL);
            add_child($$,$1);
        }
    | error {;}
        ;
ParamDec: Specifier VarDec {
            $$=node_con("ParamDec");
            add_child($$,$1);
            add_child($$,$2);
        }
    | error {;}
        ;

CompSt: LC DefList StmtList RC {
            $$=node_con("CompSt");
            sprintf(cat,"%d^LC",$1.lineno);
            add_child($$,node_con(cat));
            add_child($$,$2);
            add_child($$,$3);
            add_child($$,node_con("RC"));
        }
    | error {;}
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
            add_child($$,node_con(strcat(cat,$2.name)));
        }
        | CompSt {
            $$=node_con("Stmt");
            add_child($$,$1);
        }
        | RETURN Exp SEMI {
            $$=node_con("Stmt");
            add_child($$,node_con($1.name));
            add_child($$,$2);
            strcpy(cat,"SEMI:");
            add_child($$,node_con(strcat(cat,$3.name)));
        }
        | IF LP Exp RP Stmt {
            $$=node_con("Stmt");
            add_child($$,node_con($1.name));
            add_child($$,node_con("LP"));
            add_child($$,$3);
            add_child($$,node_con("RP"));
            add_child($$,$5);
        }
        | IF LP Exp RP Stmt ELSE Stmt {
            $$=node_con("Stmt");
            add_child($$,node_con($1.name));
            add_child($$,node_con("LP"));
            add_child($$,$3);
            add_child($$,node_con("RP"));
            add_child($$,$5);
            add_child($$,node_con($6.name));
            add_child($$,$7);
        }
        | WHILE LP Exp RP Stmt {
            $$=node_con("Stmt");
            add_child($$,node_con($1.name));
            add_child($$,node_con("LP"));
            add_child($$,$3);
            add_child($$,node_con("RP"));
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
    | error {;}
        ;
Def: Specifier DecList SEMI {
            $$=node_con("Def");
            add_child($$,$1);
            add_child($$,$2);
            strcpy(cat,"SEMI:");
            add_child($$,node_con(strcat(cat,$3.name)));
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
            strcpy(cat,"COMMA:");
            add_child($$,node_con(strcat(cat,$2.name)));
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
            add_child($$,node_con(strcat(cat,$2.name)));
            add_child($$,$3);
        }
    ;

Exp: Exp ASSIGNOP Exp {
        $$=node_con("Exp");
        add_child($$,$1);
        strcpy(cat,"ASSIGNOP:");
        add_child($$,node_con(strcat(cat,$2.name)));
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
        add_child($$,node_con(strcat(cat,$2.name)));
        add_child($$,$3);
    }
    | Exp PLUS Exp {
        $$=node_con("Exp");
        add_child($$,$1);
        strcpy(cat,"PLUS:");
        add_child($$,node_con(strcat(cat,$2.name)));
        add_child($$,$3);
    }
    | Exp MINUS Exp {
        $$=node_con("Exp");
        add_child($$,$1);
        strcpy(cat,"MINUS:");
        add_child($$,node_con(strcat(cat,$2.name)));
        add_child($$,$3);
    }
    | Exp STAR Exp {
        $$=node_con("Exp");
        add_child($$,$1);
        strcpy(cat,"STAR");
        add_child($$,node_con(strcat(cat,$2.name)));
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
        add_child($$,node_con("LP"));
        add_child($$,$2);
        add_child($$,node_con("RP"));
    }
    | MINUS Exp {
        $$=node_con("Exp");
        strcpy(cat,"MINUS:");
        add_child($$,node_con(strcat(cat,$1.name)));
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
        add_child($$,node_con(strcat(cat,$1.name)));
        add_child($$,node_con("LP"));
        add_child($$,$3);
        add_child($$,node_con("RP"));
    }
    | ID LP RP {
        if (is_in_symbol_table($1)){
            // TODO:
        }
        $$=node_con("Exp");
        strcpy(cat,"ID:");
        add_child($$,node_con(strcat(cat,$1.name)));
        add_child($$,node_con("LP"));
        add_child($$,node_con("RP"));
    }
    | Exp LB Exp RB {
        $$=node_con("Exp");
        add_child($$,$1);
        add_child($$,node_con("LB"));
        add_child($$,$3);
        add_child($$,node_con("RB"));
    }
    | Exp DOT ID {
        if (is_in_symbol_table($3)){
            // TODO:
        }
            $$=node_con("Exp");
            add_child($$,$1);
            add_child($$,node_con("DOT:."));
            strcpy(cat,"ID:");
            add_child($$,node_con(strcat(cat,$3.name)));
    }
    | ID {
        if (is_in_symbol_table($1)){
            // TODO:
        }
            $$=node_con("Exp");
            strcpy(cat,"ID:");
            add_child($$,node_con(strcat(cat,$1.name)));
    } 
    | INT {
            $$=node_con("Exp");
            //strcpy(cat,"INT:");
            sprintf(cat,"INT:%s:%d",$1,yylval.val.ival);
            add_child($$,node_con(cat));
        }
    | FLOAT {
            $$=node_con("Exp");
            strcpy(cat,"FLOAT:");
            add_child($$,node_con(strcat(cat,$1.name)));
        }
    | error {;}
    ;
Args: Exp COMMA Args {
        $$=node_con("Args");
        add_child($$,$1);
        strcpy(cat,"COMMA:");
        add_child($$,node_con(strcat(cat,$2.name)));
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
    char* tmp;
    if ((tmp=strstr(str,"^"))!=NULL){  // line^SYMBOL

        tmp[0]='\0';
        new_node->lineno=atoi(str);
        str=&tmp[1];
    }
    else new_node->lineno=yylineno;
    new_node->level=0;
    new_node->children=NULL;
    new_node->code=strdup(str);
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
}


int _min;
int tree_find_min(node* root)
{
    if (root->lineno<_min){
        //printf("\nnode: %s, lineno:%d\n",root->code,root->lineno);
        _min=root->lineno;
    }
    if (root->children!=NULL){
        child_node* start=root->children;
        while (start!=NULL){
            tree_find_min(start->c);
            start=start->next;
        }
    }
    return _min;
}

void print_tree(node* root, int level)
{
    if (root->children!=NULL&&strcmp(root->children->c->code,"\"empty\"")==0){
        //printf("---This is empty---\n");
        return;
    }

    for (int i=0;i<level;i++)
        printf("  ");
    printf("%s",root->code);
    
    if (root->children!=NULL){
        _min=0x3f3f3f3f;
        root->lineno=tree_find_min(root);
        printf("(%d)",root->lineno);
    }
    printf("\n");

    if (root->children!=NULL){
        child_node* start=root->children;
        while (start!=NULL){
            print_tree(start->c,level+1);
            start=start->next;
        }
    }
}

int add_in2_symbol_table(struct value symbol)
{
    char* symbol_name=symbol.name;
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

int is_in_symbol_table(struct value symbol)
{
    char* symbol_name=symbol.name;
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