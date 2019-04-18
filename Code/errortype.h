#ifndef _ERRORTYPE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bison.h"
#include "syntax.tab.h"

//#define DEBUG

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
extern char *strdup(const char *s);

static int add_in2_symbol_table(char *, int /* 0 for var table, 1 for fun*/, node *, int);
static int is_in_symbol_table(char *, int /* 0 for var table, 1 for fun*/);
static void print_error(int, int, char *, char *);
static void func(node *);
static int find_exp_type(node *);
static int find_var_type(node *);
static int is_left_value(node *);

static int add_in2_symbol_table(char *symbol_name, int which_table /* 0 for var table, 1 for fun*/, node *_node, int type)
{
    symbol_list *start = which_table == 0 ? _var_symbol_table_start : _func_symbol_table_start;
    while (start != NULL && start->next != NULL)
    {
        if (strcmp(start->symbol_name, symbol_name) == 0)
            return 0; // this ID already exists
        start = start->next;
    }
    if (start == NULL)
    {
        if (which_table == 0)
        {
            _var_symbol_table_start = (symbol_list *)malloc(sizeof(symbol_list));
            start = _var_symbol_table_start;
        }
        else
        {
            _func_symbol_table_start = (symbol_list *)malloc(sizeof(symbol_list));
            start = _func_symbol_table_start;
        }
    }
    else
    {
        start->next = (symbol_list *)malloc(sizeof(symbol_list));
        start = start->next;
    }
    start->next = NULL;
    start->symbol_name = strdup(symbol_name);
    start->tree_node = _node;
    start->type = type;
    return 1;
}

static int is_in_symbol_table(char *symbol_name, int which_table /* 0 for var table, 1 for func table */)
{
    symbol_list *start = which_table == 0 ? _var_symbol_table_start : _func_symbol_table_start;
    while (start != NULL)
    {
        // printf("in is_in_symbol_table, table_symbol:%s, symbol:%s\n", start->symbol_name, symbol_name);
        if (strcmp(start->symbol_name, symbol_name) == 0)
        {
#ifdef DEBUG
            printf("In is_in_symbol_table, symbol name:%s, type:%d\n", start->symbol_name, start->type);
#endif
            return start->type;
        }
        start = start->next;
    }
    return 0;
}

static void func(node *root)
{
    // printf("node: %s, node_type_no: %d\n",root->code,root->typeno);
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
        break;
    }
    case VarDec:
    {
        if (root->child_num == 1)
        {
            /*
                定义变量
                varDec -> ID
            */
            node *child_id = root->children->c;
            // printf("in VarDec, child_id:%s\n", child_id->code);
            if (is_in_symbol_table(child_id->code, 0))
            {
                // TODO: var already exists error
                print_error(redefined_var, child_id->lineno, child_id->code + 4, NULL);
            }
            else
            {
                int type;
                if ((type = find_var_type(root)) < 0)
                {
                    // TODO: error
                }
                else
                    add_in2_symbol_table(child_id->code, 0, child_id, type);
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
        if (is_in_symbol_table(child_id->code, 1))
        {
            // TODO: func already exists error
            print_error(redefined_func, child_id->lineno, child_id->code + 4, NULL);
        }
        else
            add_in2_symbol_table(child_id->code, 1, child_id, find_var_type(root));
        break;
    }
    case VarList:
    {
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
        break;
    }
    case StmtList:
    {
        break;
    }
    case Stmt:
    {
        break;
    }
    case Def:
    {
        break;
    }
    case Exp:
    {
        // int exp_type = find_exp_type(root);

        /*
            Exp -> ID LP Args RP
                | ID LP RP
                | Exp DOT ID
                | ID
        */
        node *child_id = root->children->c;
        int flag = root->child_num == 1 || strstr(child_id->code, "ID:") == NULL;
        if (child_id->code != NULL && root->child_num >= 3 && strstr(child_id->code, "ID:") == NULL)
            child_id = root->children->next->next->c; // Exp -> Exp DOT ID
        if (child_id->code != NULL && strstr(child_id->code, "ID:") != NULL && !is_in_symbol_table(child_id->code, 0))
            print_error(flag ? undefined_var : undefined_func, child_id->lineno, child_id->code + 4, NULL);
        /*
            Exp -> Exp ASSIGNOP Exp
        */
        else if (root->child_num == 3 && strcmp(root->children->next->c->code, "ASSIGNOP") == 0)
        {
            if (!is_left_value(root->children->c))
                print_error(left_hand_must_var, root->lineno, NULL, NULL);
            else
            {
                int t1, t2;
                if ((t1 = find_exp_type(root->children->c)) != (t2 = find_exp_type(root->children->next->next->c)))
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
            printf("%s:%d, %s:%d\n", root->children->c->children->c->code, t1, root->children->next->next->c->children->c->code, t2);
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
    case OptTag:
    {
        /*
            OptTag -> ID
                    | "empty"
            Tag -> ID   
        */
        node *child_id = root->children->c;
        if (strcmp(child_id->code, "\"empty\"") != 0)
            if (!is_in_symbol_table(child_id->code, 0))
                print_error(undefined_var, child_id->lineno, child_id->code + 4, NULL);
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
        child_node *start = root->children;
        while (start != NULL)
        {
            if (start->c->children != NULL)
                func(start->c);
            start = start->next;
        }
    }
}

static int is_left_value(node *root)
/*  判断左右值 */
{
    if (root->child_num == 1 && strstr(root->children->c->code, "ID") !=NULL)
    {
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
    printf("Hah, child_num=%d\n", root->child_num);
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
        if ((type = is_in_symbol_table(root->children->next->next->c->code, 0)) == 0)
        {
            // TODO: symbol not found error
            return -1;
        }
        else
            return type;
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
        if ((type = is_in_symbol_table(root->children->c->code, 0)) == 0)
        {
            // TODO: symbol not found error
            return -1;
        }
        else
            return type;
    }
    else if ((root->child_num == 3 || root->child_num == 4) && strstr(root->children->c->code, "ID") != NULL)
    { // ID ( Args ) or ID ( )  Func
        int type;
        if ((type = is_in_symbol_table(root->children->c->code, 1)) == 0)
        {
            // TODO: symbol not found error
        }
        else
            return type;
    }
    return -1; // error
}

static int find_var_type(node *root)
/* 变量定义时在语法树中确认变量类型 */
{
#ifdef DEBUG
    printf("find var type for %s\n", root->code);
#endif
    while (root != NULL && (strcmp(root->code, "ParamDec") != 0 && strcmp(root->code, "ExtDef") != 0) && strcmp(root->code, "Def") != 0)
        root = root->parent;
    node *specifier_node = root->children->c;
    if (specifier_node == NULL)
        return -1; // error
    if (strstr(specifier_node->children->c->code, "int") != NULL)
    {
        return TYPE_int; // INT
    }
    else if (strstr(specifier_node->children->c->code, "float") != NULL)
    {
        return TYPE_float; // FLOAT
    }
    else if (strcmp(specifier_node->children->c->code, "StructSpecifier") == 0)
    {
        return TYPE_struct; // struct
    }
    else
    {
        return -2; // error
    }
}

#define _ERRORTYPE_H_

#endif