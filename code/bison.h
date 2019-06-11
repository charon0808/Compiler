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

typedef struct _local_var
{
    char *var_name;
    int size;
    struct _local_var *next;
    int offset;
} local_var;

typedef struct symbol_list
{
    char *symbol_name;
    struct symbol_list *next;
    node *tree_node;
    int type;
    int varlist[32];
    int dimension;
    int *array_width;
    local_var *local_var_list;
    int argv_list_len;
} symbol_list;

typedef struct field_list
{
    char *symbol_name;
    int type;
    int start_location;
    int size;
    struct field_list *next;
} field_list;

typedef struct field_list args_list;

typedef struct struct_typedef
{
    char *symbol_name;
    struct struct_typedef *next;
    field_list *name_list;
    int total_size;
    int id;
} struct_typedef;

#define _BISON_A_H_
#endif