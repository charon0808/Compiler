#ifndef _TRANSLATE_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "bison.h"
#include "errortype.h"

static char *new_tmp();
static char *translate_EXP(node *, char *);
static int count = 0;

static char *new_tmp()
{
    char *ret = (char *)malloc(sizeof(char) * 16);
    sprintf(ret, "_T_%d", count++);
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
        }
    }
    else if (exp_node->child_num >= 2)
    {
        if (strcmp(exp_node->children->next->c->code, "ASSIGNOP") == 0)
        { // Exp ASSIGNOP Exp
        }
        else if (strcmp(exp_node->children->next->c->code, "PLUS") == 0 ||
                 strcmp(exp_node->children->next->c->code, "MINUS") == 0 ||
                 strcmp(exp_node->children->next->c->code, "STAR") == 0 ||
                 strcmp(exp_node->children->next->c->code, "DIV") == 0)
        { // Exp PLUS/MINUS/STAR/DIV Exp
        }
    }
    if (exp_node->child_num == 2 && strcmp(exp_node->children->c->code, "MINUS") == 0)
    { // MINUS EXP
    }
    else if (exp_node->child_num >= 2)
    {
        if (strcmp(exp_node->children->c->code, "NOT") == 0)
        { // NOT Exp
        }
        else if (strcmp(exp_node->children->next->c->code, "RELOP") == 0 ||
                 strcmp(exp_node->children->next->c->code, "AND") == 0 ||
                 strcmp(exp_node->children->next->c->code, "OR") == 0)
        { // Exp RELOP/AND/OR Exp
        }
    }
}

#define _TRANSLATE_H_
#endif