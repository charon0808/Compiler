#ifndef _TRANSLATE_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "bison.h"
#include "errortype.h"

static char *new_tmp();
static char *new_label();
static char *translate_EXP(node *, char *);
static char *translate_STMT(node *);
static char *translate_COND(node *, char *, char *);
static char *translate_COMPST(node *);
static char *translate_ARGS(node *, args_list *);
static char *args_list_2_string(args_list *,char *);
static int tmp_count = 0;
static int label_count = 0;

static char *new_tmp()
{
    char *ret = (char *)malloc(sizeof(char) * 16);
    sprintf(ret, "_T_%d", tmp_count++);
    return ret;
}

static char *new_label()
{
    char *ret = (char *)malloc(sizeof(char) * 16);
    sprintf(ret, "_L_%d", label_count++);
    return ret;
}

static char *translate_EXP(node *exp_node, char *place)
{
    if (exp_node->child_num == 1)
    {
        if (strstr(exp_node->children->c->code, "INT:") != NULL)
        { // INT
            node *INT_node = exp_node->children->c;
            char *ret = (char *)malloc(sizeof(char) * (strlen(place) + strlen(INT_node->code) + 5));
            sprintf(ret, "%s := #%s", place, INT_node->code + 4);
            return ret;
        }
        else if (strstr(exp_node->children->c->code, "ID:") != NULL)
        { // ID
            node *ID_node = exp_node->children->c;
            char *ret = (char *)malloc(sizeof(char) * (strlen(place) + strlen(ID_node->code) + 5));
            sprintf(ret, "%s := %s", place, ID_node->code + 4);
            return ret;
        }
    }
    else if (exp_node->child_num >= 2)
    {
        if (strcmp(exp_node->children->next->c->code, "ASSIGNOP") == 0)
        { // Exp1 ASSIGNOP Exp2
            node *exp1_node = exp_node->children->c;
            node *exp2_node = exp_node->children->next->next->c;
            // TODO: current only for Exp1 -> ID
            if (strstr(exp1_node->code, "ID:") != NULL)
            {
                node *ID_node = exp1_node->children->c;
                symbol_list *sl = is_in_symbol_table(ID_node->code + 4, 0);
                if (sl == NULL)
                {
                    // TODO: symbol not found error
                }
                char *t1 = new_tmp();
                char *code1 = translate_EXP(exp1_node, t1);
                char *code2 = (char *)malloc(sizeof(char) * 128);
                sprintf(code2, "%s := %s\n%s := %s", sl->symbol_name, t1, place, sl->symbol_name);
                char *ret = (char *)malloc(sizeof(char) * (strlen(code1) + strlen(code2) + 64));
                sprintf(ret, "%s\n%s", code1, code2);
                free(t1);
                free(code1);
                free(code2);
                return ret;
            }
            else
            {
                printf("Exp1 ASSIGNOP Exp2, Exp1 is not ID\n");
            }
        }
        else if (strcmp(exp_node->children->next->c->code, "PLUS") == 0 ||
                 strcmp(exp_node->children->next->c->code, "MINUS") == 0 ||
                 strcmp(exp_node->children->next->c->code, "STAR") == 0 ||
                 strcmp(exp_node->children->next->c->code, "DIV") == 0)
        { // Exp PLUS/MINUS/STAR/DIV Exp
            node *exp1_node = exp_node->children->c;
            node *exp2_node = exp_node->children->next->next->c;
            char *t1 = new_tmp();
            char *t2 = new_tmp();
            char *code1 = translate_EXP(exp1_node, t1);
            char *code2 = translate_EXP(exp2_node, t2);
            char *code3 = (char *)malloc(sizeof(char) * 128);
            char op;
            switch (exp_node->children->next->c->code[0])
            {
            case 'P':
                op = '+';
                break;
            case 'M':
                op = '-';
                break;
            case 'S':
                op = '*';
                break;
            case 'D':
                op = '/';
                breal;
            default:
                break;
            }
            sprintf(code3, "%s := %s %c %s", place, t1, op, t2);
            char *ret = (char *)malloc(sizeof(char) * (strlen(code1) + strlen(code2) + strlen(code3) + 64));
            sprintf(ret, "%s\n%s\n%s", code1, code2, code3);
            free(t1);
            free(t2);
            free(code1);
            free(code2);
            free(code3);
            return ret;
        }
    }
    if (exp_node->child_num == 2 && strcmp(exp_node->children->c->code, "MINUS") == 0)
    { // MINUS EXP
        char *t1 = new_tmp();
        node *exp1_node = exp_node->children->next->c;
        char *code1 = translate_EXP(exp1_node, t1);
        char *code2 = (char *)malloc(sizeof(char) * 128);
        sprintf(code2, "%s := #0 - %s", place, t1);
        char *ret = (char *)malloc(sizeof(char) * (strlen(code1) + strlen(code2) + 64));
        sprintf(ret, "%s\n%s", code1, code2);
        free(t1);
        free(code1);
        free(code2);
        return ret;
    }
    else if (exp_node->child_num >= 2 && (strcmp(exp_node->children->c->code, "NOT") == 0 ||
                                          strstr(exp_node->children->next->c->code, "RELOP") != NULL ||
                                          strcmp(exp_node->children->next->c->code, "AND") == 0 ||
                                          strcmp(exp_node->children->next->c->code, "OR") == 0))
    { // NOT Exp / Exp RELOP/AND/OR Exp
        char *label1 = new_label();
        char *label2 = new_label();
        char *code0 = (char *)malloc(sizeof(char) * 128);
        sprintf(code0, "%s := #0", place);
        char *code1 = translate_COND(exp_node, label1, label2);
            char *ret = (char *)malloc(sizeof(char) * (strlen(code0)+strlen(code1)+64);
            sprintf(ret, "%s\n%s\nLABEL %s\n%s := #1\nLABEL %s", code0, code1, label1, place, label2);
            free(label1);
            free(label2);
            free(code0);
            free(code1);
            return ret;
    }
    else if (exp_node->child_num == 3 && strcmp(exp_node->children->next->next->c->code, "LP") == 0)
    { // ID LP RP
        if (strcmp(exp_node->children->c->code + 4, "read") == 0)
        {
            char *ret = (char *)malloc(sizeof(char) * 32);
            sprintf(ret, "read %s", place);
            return ret;
        }
        symbol_list *sl = is_in_symbol_table(exp_node->children->c->code + 4, 1);
        if (sl == NULL)
        {
            // TODO: function symbol not found error
        }
        char *ret = (char *)malloc(sizeof(char) * 64);
        sprintf("%s := CALL %s", place, sl->symbol_name);
        return ret;
    }
    else if (exp_node->child_num == 4 && strcmp(exp_node->children->next->next->c->code, "LP") == 0)
    { // ID LP Args RP
        args_list *al = NULL;
        node *args_node=exp_node->children->next->next->c;
        char *code1=translate_ARGS(args_node,al);
        if (strcmp(exp_node->children->c->code + 4, "write") == 0)
        {
            char *ret=(char *)malloc(sizeof(char)*(strlen(code1)+64));
            sprintf(ret,"%s\nWRITE %s",code1,al->symbol_name);
            free(code1);
            return ret;
        }
        symbol_list *sl=is_in_symbol_table(exp_node->children->c->code,1);
        char *code2=(char *)malloc(sizeof(char)*256);
        memset(code2,0,sizeof(char)*256);
        code2=args_list_2_string(al,code2);
        char *ret=(char *)malloc(sizeof(char)*(strlen(code1)+strlen(code2)+64));
    }
}

char *translate_STMT(node *stmt_node)
{
    if (stmt_node->child_num == 2 && strcmp(stmt_node->children->next->c->code, "SEMI") == 0)
    { // Stmt -> Exp SEMI
        return translate_EXP(stmt_node->children->c, NULL);
    }
    else if (stmt_node->child_num == 1 && strcmp(stmt_node->children->c->code, "CompSt") == 0)
    { // Stmt -> CompSt
        return translate_COMPST(stmt_node->children->c);
    }
    else if (stmt_node->child_num == 3)
    { // RETURN Exp SEMI
        char *t1 = new_tmp();
        char *code1 = translate_EXP(stmt_node->children->next->c, t1);
        char *ret = (char *)malloc(sizeof(char) * (strlen(code1) + 64));
        sprintf(ret, "%s\nRETURN %s", code1, t1);
        free(t1);
        free(code1);
        return ret;
    }
    else if (strcmp(stmt_node->children->c->code, "IF"))
    {
        if (stmt_node->child_num == 5)
        { // IF LP Exp RP Stmt1
            node *exp_node = stmt_node->children->next->next->c;
            node *stmt1_node = stmt_node->children->next->next->next->next->c;
            char *label1 = new_label();
            char *label2 = new_label();
            char *code1 = translate_COND(exp_node, label1, label2);
            char *code2 = translate_STMT(stmt1_node);
            char *ret = (char *)malloc(sizeof(char) * (strlen(code1) + strlen(code2) + 64));
            sprintf(ret, "%s\nLABEL %s\n%s\nLABEL %s", code1, label1, code2, label2);
            free(label1);
            free(label2);
            free(code1);
            free(code2);
            return ret;
        }
        else if (stmt_node->child_num == 7)
        { // IF LP Exp RP Stmt1 ELSE Stmt2
            node *exp_node = stmt_node->children->next->next->c;
            node *stmt1_node = stmt_node->children->next->next->next->next->c;
            node *stmt2_node = stmt_node->children->next->next->next->next->next->next->c;
            char *label1 = new_label();
            char *label2 = new_label();
            char *label3 = new_label();
            char *code1 = translate_COND(exp_node, label1, label2);
            char *code2 = translate_STMT(stmt1_node);
            char *code3 = translate_STMT(stmt2_node);
            char *ret = (char *)malloc(sizeof(char) * (strlen(code1) + strlen(code2) + strlen(code3) + 128));
            sprintf(ret, "%s\nLABEL %s\n%s\nGOTO %s\nLABEL %s\n%s\nLABEL %s", code1, label1, code2, label3, label2, code3, label3);
            free(label1);
            free(label2);
            free(label3);
            free(code1);
            free(code2);
            free(code3);
            return ret;
        }
    }
    else if (stmt_node->child_num == 5)
    { // WHILE LP Exp RP Stmt1
        char *label1 = new_label();
        char *label2 = new_label();
        char *label3 = new_label();
        node *exp_node = stmt_node->children->next->next->c;
        node *stmt1_node = stmt_node->children->next->next->next->next->c;
        char *code1 = translate_COND(exp_node, label2, label3);
        char *code2 = translate_STMT(stmt1_node);
        char *ret = (char *)malloc(sizeof(char) * (strlen(code1) + strlen(code2) + 128));
        sprintf(ret, "LABEL %s\n%s\nLABEL %s\n%s\nGOTO %s\nLABEL %s", label1, code1, label2, code2, label1, label3);
        free(label1);
        free(label2);
        free(label3);
        free(code1);
        free(code2);
        return ret;
    }
}

char *translate_COND(node *cond_node, char *lable_true, char *label_false)
{
    if (cond_node->child_num == 3 && strstr(cond_node->children->next->c->code, "RELOP:") != NULL)
    { // Exp1 RELOP Exp2
        node *exp1_node = cond_node->children->c;
        node *exp2_node = cond_node->children->next->next->c;
        char *t1 = new_tmp();
        char *t2 = new_tmp();
        char *op = cond_node->children->next->c->code + 6;
        char *code1 = translate_EXP(exp1_node, t1);
        char *code2 = translate_EXP(exp2_node, t2);
        char *ret = (char *)malloc(sizeof(char) * (strlen(code1) + strlen(code2) + 128));
        sprintf(ret, "%s\n%s\nIF %s %s %s GOTO %s\nGOTO %s", code1, code2, t1, op, t2, lable_true, label_false);
        free(t1);
        free(t2);
        free(code1);
        free(code2);
        return ret;
    }
    else if (cond_node->child_num == 2 && strcmp(cond_node->children->c->code, "NOT") == 0)
    { // NOT Exp1
        node *exp1_node = cond_node->children->next->c;
        return translate_COND(exp1_node, label_false, lable_true);
    }
    else if (cond_node->child_num == 3 && strcmp(cond_node->children->next->c->code, "AND") == 0)
    { // Exp1 AND Exp2
        node *exp1_node = cond_node->children->c;
        node *exp2_node = cond_node->children->next->next->c;
        char *label1 = new_label();
        char *code1 = translate_COND(exp1_node, label1, label_false);
        char *code2 = translate_COND(exp2_node, lable_true, label_false);
        char *ret = (char *)malloc(sizeof(char) * (strlen(code1) + strlen(code2) + 128));
        sprintf(ret, "%s\nLABEL %s\n%s", code1, label1, code2);
        free(label1);
        free(code1);
        free(code2);
        return ret;
    }
    else if (cond_node->child_num == 3 && strcmp(cond_node->children->next->c->code, "AND") == 0)
    { // Exp1 OR Exp2
        node *exp1_node = cond_node->children->c;
        node *exp2_node = cond_node->children->next->next->c;
        char *label1 = new_label();
        char *code1 = translate_COND(exp1_node, lable_true, label1);
        char *code2 = translate_COND(exp2_node, lable_true, label_false);
        char *ret = (char *)malloc(sizeof(char) * (strlen(code1) + strlen(code2) + 128));
        sprintf(ret, "%s\nLABEL %s\n%s", code1, label1, code2);
        free(label1);
        free(code1);
        free(code2);
        return ret;
    }
    else
    {
        char *t1 = new_tmp();
        char *code1 = translate_EXP(cond_node, t1);
        char *ret = (char *)malloc(sizeof(char) * (strlen(code1) + 128));
        sprintf(ret, "%s\nIF %s != #0 GOTO %s\nGOTO %s", code1, t1, lable_true, label_false);
    }
}

static char *args_list_2_string(args_list *al,char *s)
{
    if (al!=NULL)
        args_list_2_string(al->next);
    strcar(s,"ARG ");
    strcat(s,al->symbol_name);
    strcat(s,"\n");
    return s;
}

#define _TRANSLATE_H_
#endif