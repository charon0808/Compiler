
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errortype.h"
#include "bison.h"
#include "syntax.tab.h"

extern int yylineno;
extern symbol_list *_var_symbol_table_start;
extern symbol_list *_func_symbol_table_start;
extern struct_typedef *_struct_symbol_table_start;
extern int error;
extern FILE *input_file;
extern FILE *output_file;
extern char *cat;
extern int yylex(void);
extern void yyerror(const char *);
extern char *strdup(const char *s);
extern char *mid_code;

extern void gen_target_code();

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
    new_node->child_num = 0;
    new_node->parent = NULL;
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
    parent->child_num++;
    start->c = child;
    child->parent = parent;
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

char *last_one = NULL;
void gen_mid_code(char *s)
{
    //printf("%s\n", s);
    if (last_one != NULL)
    {
        if (strstr(s, "DEC") != NULL)
        {
            //fprintf(output_file, "%s\n", s);
            //fprintf(output_file, "%s\n", last_one);
            strcat(mid_code, s);
            strcat(mid_code, "\n");
            strcat(mid_code, last_one);
            strcat(mid_code, "\n");
            // printf("%s\n", s);
            // printf("%s\n", last_one);
            //printf("hah\n\n");
            last_one = NULL;
        }
        else
        {
            //fprintf(output_file, "%s\n", last_one);
            strcat(mid_code, last_one);
            strcat(mid_code, "\n");
            //fprintf(output_file, "%s\n", s);
            last_one = s;
            //printf("%s\n", last_one);
            // printf("%s\n", s);
        }
    }
    else
    {
        last_one = s;
    }
}

void write_file(char *s)
{
    fprintf(output_file, "%s", s);
}

int main(int argc, char *argv[])
{
    if (argc == 3)
    {
        mid_code = (char *)malloc(sizeof(char) * 102400);
        memset(mid_code, 0, sizeof(char) * 102400);
        if ((input_file = freopen(argv[1], "r", stdin)) == NULL)
        {
            perror(argv[1]);
            return 1;
        }
        cat = (char *)malloc(sizeof(char) * 64);
        output_file = fopen(argv[2], "w+");
        if (output_file == NULL)
        {
            perror(argv[2]);
            return -1;
        }
        yyparse();
        if (last_one != NULL)
        {
            //fprintf(output_file, "%s\n", last_one);
            strcat(mid_code, last_one);
            strcat(mid_code, "\n");
        }
        gen_target_code();
        fclose(output_file);
    }
    else
    {
        printf("Usage: ./parser inputfile outputfile\n");
    }
    return 0;
}