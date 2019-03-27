

typedef struct child_node
{
    struct node *c;
    struct child_node *next;
} child_node;

typedef struct node
{
    int type;
    int level;
    child_node *children;
    char *code;
    int lineno;
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
} symbol_list;