#ifndef _ERRORTYPE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bison.h"
#include "syntax.tab.h"

#define DEBUG

#define Program 0
#define ExtDefList 1
#define ExtDef 2
#define ExtDecList 3
#define Specifier 4
#define StructSpecifier 5
#define OptTag 19
#define Tag 18
#define VarDec 6
#define FunDec 7
#define VarList 8
#define ParamDec 9
#define CompSt 10
#define StmtList 12
#define Stmt 13
#define DefList 11
#define Def 14
#define DecList 17
#define Dec 20
#define Exp 15
#define Args 16

#define TYPE_int 101
#define TYPE_float 102
#define TYPE_struct 103

static const enum {
    undefined_var = 1,
    undefined_func,
    redefined_var,
    redefined_func,
    type_mismatch,
    left_hand_must_var,
    type_mismatch_operands,
    type_mismatch_return,
    func_not_applicable,
    var_not_an_array,
    var_not_a_func,
    not_an_integer,
    illegal_use_of_dot,
    not_exist_field,
    redefined_field,
    duplicated_name,
    undefined_struct
} error_n;

static const char *error_str[] = {"error_str", "Undefined variable \"%s\".", "Undefined function \"%s\".", "Redefined variable \"%s\".",
                                  "Redefined function \"%s\".", "Type mismatched for assignment.", "The left-hand side of an assignment must be a variable.",
                                  "Type mismatched for operands.", "Type mismatched for return.", "Function \"%s\" is not applicable for arguments \"%s\".",
                                  "\"%s\" is not an array.", "\"%s\" is not a function.", "\"%s\" is not an integer.", "Illegal use of \".\"", "Non-existent field \"%s\".",
                                  "Redefined field \"%s\".", "Duplicated name \"%s\".", "Undefined structure \"%s\"."};

extern symbol_list *_var_symbol_table_start;
extern symbol_list *_func_symbol_table_start;
extern struct_typedef *_struct_typedef_table_start;
extern char *strdup(const char *s);
extern void print_tree(node *, int);
extern char *translate_COMPST(node *);

static int struct_typedef_num = 104;

/*
 * 将新声明的符号添加到符号表中（变量符号表或者函数符号表）
 * parameters: char *symbol_name, int which_table, node *_node, int type, int dimension
 * symbol_name: 变量名, which_table: 指明需要添加到变量符号表（0）还是函数符号表（1）
 * _node: 变量声明处对应的语法树节点，目前没有用到, type: 变量的类型(TYPE_int, TYPE_float, TYPE_struct+i)
 * dimension: 变量的维数，对于数组变量为数组的维数，普通变量为0 
 * return: 返回值为0或1，表示当前变量是否已经在变量表中 
 * */
static int add_in2_symbol_table(char *, int /* 0 for var table, 1 for fun*/, node *, int, int);

/* 
 * 判断变量是否在符号表中（变量符号表或者函数符号表）
 * parameters: char *symbol_name, int which_table
 * symbol_name: 变量名, which_table: 指明需要添加到变量符号表（0）还是函数符号表（1）
 * return: 如果变量在符号表中，返回对应的符号表节点（symbol_list *），负责返回 NULL
 * */
static symbol_list *is_in_symbol_table(char *, int /* 0 for var table, 1 for fun*/);

/*
 * 打印错误信息 
 * parameter: int error_no, int error_line, char *msg0, char *msg1
 * error_no: 错误号，在实验中为1 ~ 17, 38行定义的枚举类型对应这17个错误码, error_line: 输入程序中发生错误的行号
 * msg0, msg1, 错误信息, 58行定义的error_str字符串数组分别对应17中错误信息的printf的格式化字符串, 
 * msg0和msg1用于填充格式化字符串，如没有参数设置为NULL如 
 * */
static void print_error(int, int, char *, char *);

/*
 * 遍历语法树的主程序，在创建完成语法树后调用
 * parameter: node *root
 * root: 语法树开始遍历的根节点
 * */
static void func(node *);

/*
 * 递归确定 Exp 变量类型
 * parameter: node *root
 * root: Exp对应的节点 
 * return: TYPE_int, TYPE_float, TYPE_struct+i 或 -1（有错误发生）
 * TYPE_struct+i 没定义一个struct结构体就为其分配一个类型号用于唯一标识这种结构体，从TYPE_struct+1开始分配
 * */
static int find_exp_type(node *);

/*
 * 变量定义时在语法树中确定变量类型
 * 参数与返回值同 find_exp_type 
 * */
static int find_var_type(node *);

/*
 * 用于确认赋值语句中等号左边是否为可赋值的左值
 * parameter: node *root
 * root: 等式左边部分对应的语法树中的节点
 * return: 0或1，分别表示是左值和不是左值
 * */
static int is_left_value(node *);

/*
 * 将新定义的stuct信息添加到struct表中 
 * parameter: char *struct_name, node *root
 * struct_name: 结构体名，如果没有名字用 "%i"代替, i为结构体的类型号
 * root 定义结构体对应的语法树的节点
 * return: 结构体编号
 * */
static int add_struct_typedef(char *, node *);

/*
 * 判断结构体是否已经被定义过
 * parameter: char *struct_name
 * struct_name: 结构体名
 * return: 如果存在返回结构体编号，否则返回-1
 * */
static int is_in_struct_typedef_table(char *);

/*
 * 确认函数定义时所有参数的类型 
 * parameter: int *symbol_type, node *args_node
 * symbol_type: 用于存储参数列表中所有参数类型的数组，以0结尾
 * args_node: 参数对应的语法树节点
 * */
static void match_func_varlist(int *, node *);

/*
 * 根据参数类型号返回参数类型名
 * parameter: int type
 * type: 参数类型号
 * return: 对应的类型名 
 * */
static char *find_symbol_type_name(int);

static int add_func_varlist(char *, int);
static int add_struct_fields(char *, int, struct_typedef *);
static char *find_exp_id_name(node *);
static int find_exp_arr_dimension(node *);
static char *find_exp_code(node *, char *);
static struct_typedef *find_struct(char *);
static struct_typedef *find_struct_by_id(int);
static int is_in_struct_field(char *, struct_typedef *);
static int is_field_in_struct(char *, int);
static void init();

static int add_in2_symbol_table(char *symbol_name, int which_table /* 0 for var table, 1 for fun*/, node *_node, int type, int dimension)
{
    //#ifdef DEBUG
    //printf("In add_in2_symbol_table, symbol_name:%s, type=%d\n", symbol_name, type);
    //#endif
    symbol_list *_start = which_table == 0 ? _var_symbol_table_start : _func_symbol_table_start;
    while (_start != NULL && _start->next != NULL)
    {
        if (strcmp(_start->symbol_name, symbol_name) == 0)
            return 0; // this ID already exists
        _start = _start->next;
    }
    if (_start == NULL)
    {
        if (which_table == 0)
        {
            _var_symbol_table_start = (symbol_list *)malloc(sizeof(symbol_list));
            _start = _var_symbol_table_start;
        }
        else
        {
            _func_symbol_table_start = (symbol_list *)malloc(sizeof(symbol_list));
            _start = _func_symbol_table_start;
        }
    }
    else
    {
        if (strcmp(_start->symbol_name, symbol_name) == 0)
            return 0; // this ID already exists
        _start->next = (symbol_list *)malloc(sizeof(symbol_list));
        _start = _start->next;
    }
    _start->next = NULL;
    _start->symbol_name = strdup(symbol_name);
    _start->tree_node = _node;
    _start->type = type;
    _start->dimension = dimension;
    memset(_start->varlist, 0xff, sizeof(_start->varlist));
    return 1;
}

static symbol_list *is_in_symbol_table(char *symbol_name, int which_table /* 0 for var table, 1 for func table */)
{
    symbol_list *_start = which_table == 0 ? _var_symbol_table_start : _func_symbol_table_start;
    while (_start != NULL)
    {
        if (strcmp(_start->symbol_name, symbol_name) == 0)
        {
#ifdef DEBUG
            printf("In is_in_symbol_table, symbol name:%s, type:%d\n", _start->symbol_name, _start->type);
#endif
            return _start;
        }
        _start = _start->next;
    }
    return NULL;
}

static int add_func_varlist(char *func_name, int type)
{
    symbol_list *_start = _func_symbol_table_start;
    while (_start != NULL)
    {
        if (strcmp(_start->symbol_name, func_name) == 0)
        {
            break;
        }
        _start = _start->next;
    }
    if (_start == NULL)
    {
        // func name not found error
        return -1;
    }
    int i;
    for (i = 0; i < 32 && _start->varlist[i] != -1; i++)
        ;
    _start->varlist[i] = type;
    return 0;
}

static int add_struct_typedef(char *struct_name, node *root)
{
    //#ifdef DEBUG
    //printf("In add_struct_typedef, struct_name=%s\n", struct_name);
    //#endif
    struct_typedef *_start = _struct_typedef_table_start;
    while (_start != NULL && _start->next != NULL)
    {
        printf("In add_struct_typedef, struct_name=%s, _start->symbol_name=%s\n", struct_name, _start->symbol_name);
        if (strcmp(struct_name, _start->symbol_name) == 0)
            return -1; // already exists error
        _start = _start->next;
    }
    if (_start == NULL)
    {
        _struct_typedef_table_start = (struct_typedef *)malloc(sizeof(struct_typedef));
        _start = _struct_typedef_table_start;
    }
    else
    {
        if (strcmp(struct_name, _start->symbol_name) == 0)
            return -1; // already exists error
        _start->next = (struct_typedef *)malloc(sizeof(struct_typedef));
        _start = _start->next;
    }
    _start->symbol_name = strdup(struct_name);
    _start->id = struct_typedef_num;
    struct_typedef_num++;
    return _start->id;
}

static int is_in_struct_typedef_table(char *struct_name)
{
    struct_typedef *_start = _struct_typedef_table_start;
    for (int i = 0; _start != NULL; i++)
    {
        if (strcmp(_start->symbol_name, struct_name) == 0)
            return TYPE_struct + i + 1;
        _start = _start->next;
    }
    return -1; // not found error
}

static void init()
{
    char *r = (char *)malloc(sizeof(char) * 6);
    sprintf(r, "read");
    add_in2_symbol_table(r, 1, NULL, TYPE_int, -1);
    char *w = (char *)malloc(sizeof(char) * 6);
    sprintf(r, "write");
    add_in2_symbol_table(w, 1, NULL, TYPE_int, -1);
    add_func_varlist("write", TYPE_int);
}

static void func(node *root)
{
#ifdef DEBUG
    printf("node: %s, node_type_no: %d\n", root->code, root->typeno);
#endif
    switch (root->typeno)
    {
    case Program:
    {
        break;
    }
    case ExtDefList:
    {
        break;
    }
    case ExtDef:
    {
        break;
    }
    case ExtDecList:
    {
        break;
    }
    case Specifier:
    {
        break;
    }
    case StructSpecifier:
    {
        if (root->child_num == 5)
        { // StructSpecifier -> STRUCT OptTag LC DefList RC
            node *opttag_node = root->children->next->c;
            if (strstr(opttag_node->children->c->code, "ID") != NULL)
            { // OptTag -> ID
                int type;
                if ((type = add_struct_typedef(opttag_node->children->c->code + 4, opttag_node->children->c)) < 0)
                {
                    // TODO: error
                }
                if (type == -1)
                { // already exists
                    print_error(duplicated_name, root->lineno, opttag_node->children->c->code + 4, NULL);
                }
                root->struct_type = type;
#ifdef DEBUG
                printf("In StructSpecifier, struct name:%s, type=%d\n", root->children->next->c->children->c->code, type);
#endif
            }
            else
            { // OptTag -> empty
                char *_tmp = (char *)malloc(16);
                sprintf(_tmp, "$%d", struct_typedef_num);
                int type;
                if ((type = add_struct_typedef(_tmp, opttag_node->children->c)) < 0)
                {
                    // TODO: error
                }
                root->struct_type = type;
#ifdef DEBUG
                printf("In StructSpecifier, struct name:%s, type=%d\n", _tmp, type);
#endif
            }
        }
        else if (root->child_num == 2)
        { // StructSpecifier -> STRUCT Tag
            root->struct_type = is_in_struct_typedef_table(root->children->next->c->children->c->code + 4);
        }
        break;
    }
    case VarDec:
    {
        int is_in_struct_fields_flag = 0;
        int struct_type;
        int is_redeffield_not_redefvar = 0;
        if (root->child_num == 1)
        {
            /*
                如果该变量定义在结构体中，则添加到结构体中。
                varDec -> ID
            */
            node *_start = root;
            while (_start != NULL)
            {
                if (strcmp(_start->code, "StructSpecifier") == 0)
                {
                    is_in_struct_fields_flag = 1;
                    break;
                }
                _start = _start->parent;
            }
            if (is_in_struct_fields_flag)
            {
                struct_type = _start->struct_type;
                if (struct_type == -1)
                { // means redefined struct
                    is_in_struct_fields_flag = 0;
                    break;
                }
                struct_typedef *st = find_struct_by_id(struct_type);
#ifdef DEBUG
                printf("in varDec -> ID, struct_name:%s, type=%d\n", st->symbol_name, struct_type);
#endif
                if (is_in_struct_field(root->children->c->code, st))
                {
                    print_error(redefined_field, root->lineno, root->children->c->code + 4, NULL);
                    is_redeffield_not_redefvar = 1;
                }
                add_struct_fields(root->children->c->code, struct_type, st);
            }
        }

        int this_type;
        if (root->child_num == 1)
        {
            /*
                定义变量
                varDec -> ID
            */
            node *child_id = root->children->c;
#ifdef DEBUG
            printf("in VarDec, child_id:%s\n", child_id->code);
#endif
            if (!is_in_struct_fields_flag && is_in_symbol_table(child_id->code + 4, 0) != NULL)
            {
                // TODO: var already exists error
                print_error(redefined_var, child_id->lineno, child_id->code + 4, NULL);
            }
            else if (is_in_struct_fields_flag && !is_redeffield_not_redefvar && is_in_symbol_table(child_id->code + 4, 0) != NULL)
            {
                print_error(redefined_var, child_id->lineno, child_id->code + 4, NULL);
            }
            else
            {
                int type = 0;
                node *tmp = root;
                while (tmp != NULL && (strcmp(tmp->code, "Def") != 0 && strcmp(tmp->code, "ExtDef") != 0))
                {
                    tmp = tmp->parent;
                }
                if (tmp != NULL)
                {
                    if (strcmp(tmp->children->c->children->c->code, "StructSpecifier") == 0)
                    {
                        type = tmp->children->c->children->c->struct_type;
                    }
                }
                if (type == 0 && (type = find_var_type(root)) < 0)
                {
                    // TODO: error
                }
                else
                {
                    int dimension = 0;
                    node *_start = root;
                    while (strcmp(_start->parent->code, "VarDec") == 0)
                    {
                        _start = _start->parent;
                        dimension++;
                    }
#ifdef DEBUG
                    printf("in VarDec, name: %s, type: %d\n", child_id->code + 4, type);
#endif
                    add_in2_symbol_table(child_id->code + 4, 0, child_id, type, dimension);
                }
                this_type = type;
            }
        }

        break;
    }
    case FunDec:
    {
        /*
            FunDec -> ID LP VarList RP
                    | ID LP RP
        */
        node *child_id = root->children->c;
        if (is_in_symbol_table(child_id->code + 4, 1) != NULL)
        {
            // TODO: func already exists error
            print_error(redefined_func, child_id->lineno, child_id->code + 4, NULL);
        }
        else
            add_in2_symbol_table(child_id->code + 4, 1, child_id, find_var_type(root), -1);
        break;
    }
    case VarList:
    {
        char *func_name = root->parent->children->c->code + 4;
        // VarList -> ParamDec COMMA VarList
        // VarList -> ParamDec
        add_func_varlist(func_name, find_var_type(root->children->c));
        break;
    }
    case ParamDec:
    {
        break;
    }
    case CompSt:
    {
        break;
    }
    case DefList:
    {
        if (strcmp(root->parent->code, "DefList") == 0)
            break;
        int struct_type = root->parent->struct_type;
        struct_typedef *st = find_struct_by_id(struct_type);
        break;
    }
    case StmtList:
    {
        break;
    }
    case Stmt:
    {
        if (root->child_num == 3)
        { // Stmt -> RETURN Exp SEMI
            int t1, t2;
            if ((t1 = find_exp_type(root->children->next->c)) != (t2 = find_var_type(root)))
            {
                print_error(type_mismatch_return, root->children->c->lineno, NULL, NULL);
            }
        }
        break;
    }
    case Def:
    {
        break;
    }
    case Exp:
    {
        // int exp_type = find_exp_type(root);

        if (root->child_num != 0 && strstr(root->children->c->code, "ID") != NULL) //|| (root->child_num == 3 && strcmp(root->children->next->c->code, "DOT") == 0))
        /*
            Exp -> ID LP Args RP
                | ID LP RP
                // | Exp DOT ID
                | ID
        */
        {
            node *child_id = root->children->c;
            int flag = root->child_num == 1 || strstr(child_id->code, "ID:") == NULL;
            if (child_id->code != NULL && root->child_num >= 3 && strstr(child_id->code, "ID:") == NULL)
                child_id = root->children->next->next->c; // Exp -> Exp DOT ID
            if (child_id->code != NULL && strstr(child_id->code, "ID:") != NULL && is_in_symbol_table(child_id->code + 4, 0) == NULL && is_in_symbol_table(child_id->code + 4, 1) == NULL)
                print_error(flag ? undefined_var : undefined_func, child_id->lineno, child_id->code + 4, NULL);
        }
        else if (root->child_num == 3 && strcmp(root->children->next->c->code, "ASSIGNOP") == 0)
        /*
            Exp -> Exp ASSIGNOP Exp
        */
        {
            if (!is_left_value(root->children->c))
                print_error(left_hand_must_var, root->lineno, NULL, NULL);
            else
            {
                int t1, t2;
                if ((t1 = find_exp_type(root->children->c)) != (t2 = find_exp_type(root->children->next->next->c)) && t1 != -2) // t1==-2 means left var not defeined
                    print_error(type_mismatch, root->lineno, NULL, NULL);
#ifdef DEBUG
                printf("t1=%d, t2=%d\n", t1, t2);
#endif
            }
        }
        else if (root->child_num == 3 && (strcmp(root->children->next->c->code, "PLUS") == 0 ||
                                          strcmp(root->children->next->c->code, "MIBUS") == 0 ||
                                          strcmp(root->children->next->c->code, "STAR") == 0 ||
                                          strcmp(root->children->next->c->code, "DIV") == 0 ||
                                          strcmp(root->children->next->c->code, "RELOP") == 0))
        /* Exp PLUS/MINUS/STAR/DIV/RELOP Exp*/
        {
#ifdef DEBUG
            int t1 = find_exp_type(root->children->c);
            int t2 = find_exp_type(root->children->next->next->c);
            printf("%s:%d, %s:%d\n", root->children->c->code, t1, root->children->next->next->c->code, t2);
            if (t1 != t2)
#endif
#ifndef DEBUG
                if (find_exp_type(root->children->c) != find_exp_type(root->children->next->next->c))
#endif
                {
                    print_error(type_mismatch_operands, root->lineno, NULL, NULL);
                }
        }
        else if (root->child_num == 3 && (strcmp(root->children->next->c->code, "AND") == 0 ||
                                          strcmp(root->children->next->c->code, "OR") == 0))
        /* Exp AND/OR Exp */
        {
            if (find_exp_type(root->children->c) != TYPE_int || find_exp_type(root->children->next->next->c) != TYPE)
            {
                print_error(type_mismatch_operands, root->lineno, NULL, NULL);
            }
        }
        else if (root->child_num == 4 && strcmp(root->children->next->c->code, "LB") == 0)
        { // Exp -> Exp LB Exp RB
            if (find_exp_type(root->children->next->next->c) != TYPE_int)
            {
                char *str = (char *)malloc(512 * sizeof(char));
                str[0] = '\0';
                find_exp_code(root->children->next->next->c, str);
                print_error(not_an_integer, root->lineno, str, NULL);
                free(str);
            }
            if (root->parent->parent->child_num >= 2 && strcmp(root->parent->parent->children->next->c->code, "LB") == 0)
                break;
#ifdef DEBUG
            printf("Exp -> Exp LB Exp RB\n");
#endif
            char *id_name = find_exp_id_name(root);
            symbol_list *sl = is_in_symbol_table(id_name, 0);
            if (sl->dimension == 0 && find_exp_arr_dimension(root) != 0)
            {
                print_error(var_not_an_array, root->lineno, id_name, NULL);
            }
        }
        if (root->child_num >= 3 && strcmp(root->children->next->c->code, "LP") == 0)
        /* Exp -> ID LP Args RP
               |  ID LP RP */
        {
            int symbol_type[32];
            memset(symbol_type, 0xff, sizeof(symbol_type));
            match_func_varlist(symbol_type, root->children->next->next->c);
            symbol_list *symbol_func = is_in_symbol_table(root->children->c->code + 4, 1);
            if (symbol_func == NULL && is_in_symbol_table(root->children->c->code + 4, 0) != NULL)
            {
                print_error(var_not_a_func, root->lineno, root->children->c->code + 4, NULL);
            }
            else if (symbol_func == NULL)
            { // func not defined
                break;
            }
            else
            {
                int flag = 0;
                for (int i = 0; i < 32 && (symbol_type[i] != -1 || symbol_func->varlist[i] != -1) && !flag; i++)
                {
                    if (symbol_type[i] != symbol_func->varlist[i])
                        flag = 1;
                }
                if (flag)
                { // func varlist unmatch error
                    char *s1 = (char *)malloc(1024 * sizeof(char));
                    char *s2 = (char *)malloc(1024 * sizeof(char));
                    strcat(s1, "(");
                    strcat(s2, root->children->c->code + 4);
                    strcat(s2, "(");
                    for (int i = 0; i < 32 && symbol_type[i] >= TYPE_int; i++)
                    {
                        if (i)
                            strcat(s1, ", ");
                        strcat(s1, find_symbol_type_name(symbol_type[i]));
                    }
                    for (int i = 0; i < 32 && symbol_func->varlist[i] >= TYPE_int; i++)
                    {
                        if (i)
                            strcat(s2, ", ");
                        strcat(s2, find_symbol_type_name(symbol_func->varlist[i]));
                    }
                    strcat(s1, ")");
                    strcat(s2, ")");
                    print_error(func_not_applicable, root->lineno, s2, s1);
                }
            }
        }
        if (root->child_num == 3 && strcmp(root->children->next->c->code, "DOT") == 0)
        /* Exp -> Exp DOT ID */
        {
            int type;
            if ((type = find_exp_type(root->children->c)) < TYPE_struct)
                print_error(illegal_use_of_dot, root->lineno, NULL, NULL);
            //#ifdef DEBUG
            //printf("int Exp DOT ID, %s.type=%d\n", root->children->c->code, type);
            //#endif
            struct_typedef *st = find_struct_by_id(type);
            if (!is_in_struct_field(root->children->next->next->c->code, st))
            {
                print_error(not_exist_field, root->lineno, root->children->next->next->c->code + 4, NULL);
            }
        }
        break;
    }
    case Args:
    {
        break;
    }
    case DecList:
    {
        break;
    }
    case Tag:
    {
        /*
            Tag -> ID
        */
        node *child_id = root->children->c;
        if (strcmp(child_id->code, "\"empty\"") != 0)
        {
            int ss = is_in_struct_typedef_table(root->children->c->code + 4);
            if (ss == -1)
                print_error(undefined_struct, child_id->lineno, child_id->code + 4, NULL);
        }
        break;
    }
    case OptTag:
    {
        break;
    }
    case Dec:
    {
        break;
    }
    default:
        break;
    }
    if (root->children != NULL)
    {
        child_node *__start = root->children;
        while (__start != NULL)
        {
            if (__start->c->children != NULL)
                func(__start->c);
            __start = __start->next;
        }
    }
}

static int is_left_value(node *root)
/*  判断左右值 */
{
    if (root->child_num == 1 && strstr(root->children->c->code, "ID") != NULL)
    { // ID
        return 1;
    }
    else if (root->child_num == 3 && strcmp(root->children->c->code, "LP") == 0)
    { // LP EXP RP
        return 1 && is_left_value(root->children->next->c);
    }
    else if (root->child_num == 3 && strcmp(root->children->next->c->code, "DOT") == 0)
    { // Exp DOT ID
#ifdef DEBUG
        printf("In is_left_value, Exp DOT ID, %s\n", root->children->next->next->c->code);
#endif
        return 1;
    }
    else if (root->child_num == 4 && strcmp(root->children->next->c->code, "LB") == 0)
    { // Exp LB Exp RB
        return 1;
    }
    else
        return 0;
}

static void print_error(int error_no, int error_line, char *msg0, char *msg1)
{
    printf("Error type %d at Line %d: ", error_no, error_line);
    printf(error_str[error_no], msg0, msg1);
    printf("\n");
}

static int find_exp_type(node *root)
{
#ifdef DEBUG
    printf("In find_exp_type\n");
    printf("Hah, child_num=%d, root->code:%s\n", root->child_num, root->code);
    print_tree(root, 0);
#endif
    /* INT:-1, FLOAT:-2 */
    if (root->child_num == 3 && root->children->next->c->typeno == -2)
    { // Exp ASSIGNOP Exp
    }
    else if (root->child_num == 3 && root->children->next->c->typeno == -3)
    { // AND or OR or RELOP or NOT
        return TYPE_int;
    }
    else if (root->child_num == 3 && root->children->next->c->typeno == -4)
    { // PLUS or MINUS or STAR or DIV
        if (find_exp_type(root->children->next->next->c) == TYPE_float || find_exp_type(root->children->c) == TYPE_float)
            return TYPE_float;
        else
            return TYPE_int;
    }
    else if (root->child_num == 3 && strcmp(root->children->c->code, "LP") == 0)
    { // ( EXP )
        return find_exp_type(root->children->next->c);
    }
    else if (root->child_num == 2 && strcmp(root->children->c->code, "MINUS") == 0)
    { // MINUS EXP
        return find_exp_type(root->children->next->c);
    }
    else if (root->child_num == 4 && strcmp(root->children->c->code, "Exp") == 0)
    { // Exp [ Exp ] 数组
        return find_exp_type(root->children->c);
    }
    else if (root->child_num == 3 && root->children->next->c->typeno == -5)
    { // Exp DOT ID
        int type;
        symbol_list *sl = is_in_symbol_table(root->children->next->next->c->code + 4, 0);
        if (sl == NULL)
        {
            // TODO: symbol not found error
            return -1;
        }
        else
            return sl->type;
#ifdef DEBUG
        printf("In find_exp_type, name: %s, type: %d", root->children->next->next->c->code + 4, sl->type);
#endif
    }
    else if (root->child_num == 1 && root->children->c->typeno == -6)
    { // INT
        return TYPE_int;
    }
    else if (root->child_num == 1 && root->children->c->typeno == -7)
    { // FLOAT
        return TYPE_float;
    }
    else if (root->child_num == 1)
    { // ID
        int type;
        symbol_list *sl = is_in_symbol_table(root->children->c->code + 4, 0);
        //printf("%s.type:%d", sl->symbol_name, sl->type);
        if (sl == NULL)
        {
            // TODO: symbol not found error
            return -2;
        }
        else
            return sl->type;
    }
    else if ((root->child_num == 3 || root->child_num == 4) && strstr(root->children->c->code, "ID") != NULL)
    { // ID ( Args ) or ID ( )  Func
        int type;
        symbol_list *sl = is_in_symbol_table(root->children->c->code + 4, 1);
        if (sl == NULL)
        {
            // TODO: symbol not found error
        }
        else
            return sl->type;
    }
    return -1; // error
}

static int find_var_type(node *root)
/* 变量定义时在语法树中确认变量类型 */
{
    node *_root = root;
    while (root != NULL && (strcmp(root->code, "ParamDec") != 0 && strcmp(root->code, "ExtDef") != 0) && strcmp(root->code, "Def") != 0)
        root = root->parent;
    node *specifier_node = root->children->c;
    if (specifier_node == NULL)
        return -1; // error
    if (strstr(specifier_node->children->c->code, "int") != NULL)
    {
#ifdef DEBUG
        printf("INT: find var type for %s\n", _root->children->c->code);
#endif
        return TYPE_int; // INT
    }
    else if (strstr(specifier_node->children->c->code, "float") != NULL)
    {
#ifdef DEBUG
        printf("FLOAT: find var type for %s\n", _root->children->c->code);
#endif
        return TYPE_float; // FLOAT
    }
    else if (strcmp(specifier_node->children->c->code, "StructSpecifier") == 0)
    {
#ifdef DEBUG
        printf("STRUCT: find var type for %s\n", _root->children->c->code);
#endif
        int type;
        if (specifier_node->children->c->child_num == 2)
        { // StructSpecifier -> Struct Tag
            type = is_in_struct_typedef_table(specifier_node->children->c->children->next->c->children->c->code + 4);
        }
#ifdef DEBUG
        printf("In find_var_type, StructSpecifier struct:%s, struct_type:%d\n", specifier_node->children->c->children->next->c->children->c->code, type);
#endif
        return type;
        return specifier_node->children->c->struct_type;
    }
    else
    {
        return -2; // error
    }
}

static void match_func_varlist(int *symbol_type, node *args_node)
{
    if (args_node == NULL)
    { // means no args
        *symbol_type = 0;
    }
    *symbol_type = find_exp_type(args_node->children->c);
    if (args_node->child_num == 3)
    { // Args -> Exp COMMA Args
        match_func_varlist(symbol_type + 1, args_node->children->next->next->c);
    }
    else if (args_node->child_num == 1)
    { // Args -> Exp
    }
}

static char *find_symbol_type_name(int type)
{
    if (type == TYPE_int)
    {
        return "int";
    }
    else if (type == TYPE_float)
    {
        return "float";
    }
    else
    {
        struct_typedef *_start = _struct_typedef_table_start;
        int n = type - TYPE_struct - 1;
        while (_start != NULL && n--)
        {
            _start = _start->next;
        }
        if (_start == NULL)
        {
            return NULL;
        }
        char *tmp = (char *)malloc(32 * sizeof(char));
        sprintf(tmp, "%s", "struct ");
        return strcat(tmp, _start->symbol_name);
    }
}

static char *find_exp_id_name(node *root)
/* only for Exp -> Exp LB Exp RB */
{
#ifdef DEBUG
    printf("In find_exp_id_name, root->symbol_name:%s, root->child_num:%d\n", root->code, root->child_num);
#endif
    node *_start = root;
    if (_start->child_num == 3 && strcmp(_start->children->c->code, "LP") == 0)
    { // Exp -> LP Exp RP
        return find_exp_id_name(_start->children->next->c);
    }
    else if (_start->child_num == 3 && strcmp(_start->children->next->c->code, "DOT") == 0)
    { // Exp -> Exp DOT ID
        return _start->children->next->next->c->code + 4;
    }
    else if (_start->child_num == 1 && strstr(_start->children->c->code, "ID") != NULL)
    { // Exp -> ID
        return _start->children->c->code + 4;
    }
    else if (_start->child_num == 4 && strcmp(_start->children->next->c->code, "LB") == 0)
    {
        return find_exp_id_name(_start->children->c);
    }
    return NULL;
}

static int find_exp_arr_dimension(node *root)
{
#ifdef DEBUG
    printf("In find_exp_arr_dimension\n");
#endif
    if (root->child_num == 4 && strcmp(root->children->next->c->code, "LB") == 0)
    { // Exp -> Exp LB Exp RB
        return 1 + find_exp_arr_dimension(root->children->c);
    }
    else
        return 0;
}

static char *find_exp_code(node *root, char *str)
{
    //printf("in find_exp_code, code:%s\n", root->code);
    if (root->children != NULL)
    {
        child_node *_start = root->children;
        while (_start != NULL)
        {
            find_exp_code(_start->c, str);
            _start = _start->next;
        }
    }
    else
        strcat(str, strstr(root->code, "FLOAT") != NULL ? root->code + 7 : root->code + 4);
}

static struct_typedef *find_struct(char *struct_name)
{
    struct_typedef *_start = _struct_typedef_table_start;
    while (_start != NULL)
    {
        if (strcmp(_start->symbol_name, struct_name) == 0)
            return _start;
        _start = _start->next;
    }
    return NULL;
}

static struct_typedef *find_struct_by_id(int struct_id)
{
    struct_typedef *_start = _struct_typedef_table_start;
    int times = struct_id - TYPE_struct - 1;
    while (_start != NULL && times)
    {
        _start = _start->next;
        if (_start == NULL)
            return NULL;
        times--;
    }
    return _start;
}

static int add_struct_fields(char *name, int type, struct_typedef *struct_node)
{
    field_list *_start = struct_node->name_list;
    while (_start != NULL && _start->next != NULL)
    {
        _start = _start->next;
    }
    if (_start == NULL)
    {
        struct_node->name_list = (field_list *)malloc(sizeof(field_list));
        _start = struct_node->name_list;
    }
    else
    {
        _start->next = (field_list *)malloc(sizeof(field_list));
        _start = _start->next;
    }
    _start->symbol_name = strdup(name);
    _start->type = type;
    _start->next = NULL;
    return 1;
}

static int is_in_struct_field(char *name, struct_typedef *struct_node)
{
    if (struct_node == NULL)
        return -1;
    //printf("in is_in_struct_field, error, name:%s\n",name);
    field_list *_start = struct_node->name_list;
    while (_start != NULL)
    {
        //printf("in is_in_struct_field, _start->symbol_name: %s, name: %s\n", _start->symbol_name + 4, name);
        if (strcmp(_start->symbol_name, name) == 0)
        {
            printf("\n\n");
            return 1;
        }
        _start = _start->next;
    }
    return 0;
}

static int is_field_in_struct(char *field_name, int struct_type_id)
{
    struct_typedef *st = find_struct_by_id(struct_type_id);
    if (st == NULL)
    {
        // TODO: struct not found error
        return -1;
    }
    field_list *_start = st->name_list;
    while (_start != NULL)
    {
        if (strcmp(_start->symbol_name, field_name) == 0)
            return 1;
        _start = _start->next;
    }
    return 0;
}

#define _ERRORTYPE_H_
#endif