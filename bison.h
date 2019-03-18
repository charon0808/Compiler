
typedef struct node
{
    int type;
    int level;
    struct node* child_list;
    char* code;
}node;

union value{
    int ival;
    float fval;
    char name[32];
}value;