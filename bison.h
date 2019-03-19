
typedef struct node
{
    int type;
    int level;
    child_list* children;
    char* code;
}node;

typedef struct child_list{
    struct node* c;
    struct child_list* next;
}child_list;

union value{
    int ival;
    float fval;
    char name[32];
}value;

typedef struct symbol_list{
    char* symbol_name;
    struct symbol_list* next;
}symbol_list;