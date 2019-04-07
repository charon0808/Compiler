#ifndef _BISON_A_H_
typedef struct child_node
{
    struct node *c;
    struct child_node *next;
} child_node;

typedef struct node
{
    int level;
    child_node *children;
    int child_num;
    char *code;
    int lineno;
    int typeno;
} node;

struct value
{
    union {
        int ival;
        float fval;
        char name[32];
    };
    int lineno;
};

typedef struct symbol_list
{
    char *symbol_name;
    struct symbol_list *next;
    node* tree_node;
} symbol_list;

#define _BISON_A_H_
#endif