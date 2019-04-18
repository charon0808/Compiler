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
    struct node *parent;
    int child_num;
    char *code;
    int lineno;
    int typeno;
    int struct_type;
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
    node *tree_node;
    int type;
    int varlist[32];
} symbol_list;

typedef struct n_list
{
    char *symbol_name;
    struct name_list *next;
} n_list;

typedef struct struct_typedef
{
    char *symbol_name;
    struct struct_typedef *next;
    n_list *name_list;
} struct_typedef;

#define _BISON_A_H_
#endif