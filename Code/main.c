
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bison.h"
#include "syntax.tab.h"

extern int yylineno;
extern symbol_list *_var_symbol_table_start;
extern symbol_list *_fun_symbol_table_start;
extern int error;
extern FILE *f;
extern char *cat;
extern int yylex(void);
extern void yyerror(const char *);
extern char *strdup(const char *s);

node *node_con(char *str, int tno)
{
    node *new_node = (node *)malloc(sizeof(node));
    char *tmp;
    if ((tmp = strstr(str, "^")) != NULL)
    { // line^SYMBOL

        tmp[0] = '\0';
        new_node->lineno = atoi(str);
        str = &tmp[1];
    }
    else
        new_node->lineno = yylineno;
    new_node->level = 0;
    new_node->children = NULL;
    new_node->code = strdup(str);
    new_node->typeno = tno;
    return new_node;
}

void add_child(node *parent, node *child)
{
    child_node *start = parent->children;
    while (start != NULL && start->next != NULL)
    {
        start = start->next;
    }
    if (start == NULL)
        start = parent->children = (child_node *)malloc(sizeof(child_node));
    else
    {
        start->next = (child_node *)malloc(sizeof(child_node));
        start = start->next;
    }
    start->c = child;
    start->next = NULL;
}

int _min;
int tree_find_min(node *root)
{
    if (root->lineno < _min)
    {
        //printf("\nnode: %s, lineno:%d\n",root->code,root->lineno);
        _min = root->lineno;
    }
    if (root->children != NULL)
    {
        child_node *start = root->children;
        while (start != NULL)
        {
            tree_find_min(start->c);
            start = start->next;
        }
    }
    return _min;
}

void print_tree(node *root, int level)
{
    if (root->children != NULL && strcmp(root->children->c->code, "\"empty\"") == 0)
    {
        //printf("---This is empty---\n");
        return;
    }

    for (int i = 0; i < level; i++)
        printf("  ");
    printf("%s", root->code);

    if (root->children != NULL)
    {
        _min = 0x3f3f3f3f;
        root->lineno = tree_find_min(root);
        printf(" (%d)", root->lineno);
    }
    printf("\n");

    if (root->children != NULL)
    {
        child_node *start = root->children;
        while (start != NULL)
        {
            print_tree(start->c, level + 1);
            start = start->next;
        }
    }
}

int add_in2_symbol_table(struct value symbol, int which_table /* 0 for var table, 1 for fun*/)
{
    char *symbol_name = symbol.name;
    symbol_list *start = which_table == 0 ? _var_symbol_table_start : _fun_symbol_table_start;
    while (start != NULL)
    {
        if (strcmp(start->symbol_name, symbol_name) == 0)
            return 0; // this ID already exists
        start = start->next;
    }
    start = (symbol_list *)malloc(sizeof(symbol_list));
    start->next = NULL;
    start->symbol_name = strdup(symbol_name);
    return 1;
}

int is_in_symbol_table(struct value symbol, int which_table /* 0 for var table, 1 for fun*/)
{
    char *symbol_name = symbol.name;
    symbol_list *start = which_table == 0 ? _var_symbol_table_start : _fun_symbol_table_start;
    while (start != NULL)
    {
        if (strcmp(start->symbol_name, symbol_name) == 0)
            return 1;
    }
    return 0;
}

void free_all(node *root)
{
    if (root->children != NULL)
    {
        child_node *start = root->children;
        while (start != NULL)
        {
            free_all(start->c);
            start = start->next;
        }
    }
    free(root->code);
    free(root);
}

void yyerror(const char *s)
{
    error = 0;
    fprintf(stderr, "Error type B at line %d: %s\n", yylineno, s);
    //yyparse();
}

int main(int argc, char *argv[])
{
    if (argc > 1)
        if ((f = freopen(argv[1], "r", stdin)) == NULL)
        {
            perror(argv[1]);
            return 1;
        }
    cat = (char *)malloc(sizeof(char) * 64);
    yyparse();
    return 0;
}