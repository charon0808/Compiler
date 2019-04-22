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
    int dimension;
} symbol_list;

typedef struct field_list
{
    char *symbol_name;
    int type;
    struct field_list *next;
} field_list;

typedef struct struct_typedef
{
    char *symbol_name;
    struct struct_typedef *next;
    field_list *name_list;
    int id;
} struct_typedef;

#define _BISON_A_H_
#endif