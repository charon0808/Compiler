#ifndef _ERRORTYPE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bison.h"
#include "syntax.tab.h"

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

static int add_in2_symbol_table(char *, int /* 0 for var table, 1 for fun*/, node *);
static int is_in_symbol_table(char *, int /* 0 for var table, 1 for fun*/);
static void print_error(int, int, char *, char *);
static void func(node *);

static int add_in2_symbol_table(char *symbol_name, int which_table /* 0 for var table, 1 for fun*/, node *_node)
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
    return 1;
}

static int is_in_symbol_table(char *symbol_name, int which_table /* 0 for var table, 1 for fun*/)
{
    symbol_list *start = which_table == 0 ? _var_symbol_table_start : _func_symbol_table_start;
    while (start != NULL)
    {
        // printf("in is_in_symbol_table, table_symbol:%s, symbol:%s\n", start->symbol_name, symbol_name);
        if (strcmp(start->symbol_name, symbol_name) == 0)
            return 1;
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
                add_in2_symbol_table(child_id->code, 0, child_id);
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
            add_in2_symbol_table(child_id->code, 1, child_id);
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
        /*
            Exp -> ID LP Args RP
                | ID LP RP
                | Exp DOT ID
                | ID
        */
        node *child_id = root->children->c;
        // printf("In Exp, child_id_code: %s\n", child_id->code);
        if (child_id->code != NULL && root->child_num>=3 && strstr(child_id->code, "ID:") == NULL)
            child_id = root->children->next->next->c; // Exp -> Exp DOT ID
        if (child_id->code != NULL && strstr(child_id->code, "ID:") != NULL && !is_in_symbol_table(child_id->code, 0))
            print_error(undefined_var, child_id->lineno, child_id->code + 4, NULL);
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

static void print_error(int error_no, int error_line, char *msg0, char *msg1)
{
    printf("Error type %d at Line %d: ", error_no, error_line);
    printf(error_str[error_no], msg0, msg1);
    printf("\n");
}

#define _ERRORRYPE_H_

#endif