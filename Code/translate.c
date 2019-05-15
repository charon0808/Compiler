#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "bison.h"
#include "errortype.h"

char *new_tmp();
char *new_label();
char *translate_EXP(node *, char *);
char *translate_STMT(node *);
char *translate_COND(node *, char *, char *);
char *translate_COMPST(node *);
char *translate_ARGS(node *, args_list *);
char *translate_STMTLIST(node *);
char *args_list_2_string(args_list *, char *);
char *translate_FUNDEC(node *);
void translate(node *);
int tmp_count = 0;
int label_count = 0;

extern char *strdup(const char *s);
extern void write_file(char *);

char *new_tmp()
{
    char *ret = (char *)malloc(sizeof(char) * 16);
    sprintf(ret, "iamt%d", tmp_count++);
    return ret;
}

char *new_label()
{
    char *ret = (char *)malloc(sizeof(char) * 16);
    sprintf(ret, "iamlabel%d", label_count++);
    return ret;
}

char *translate_EXP(node *exp_node, char *place)
{
    // printf("in translate_exp, tree=\n");
    // print_tree(exp_node,0);
    // printf("place=%s\n",place);
    if (exp_node->child_num == 1)
    {
        // printf("translate_EXP 1\n");
        if (strstr(exp_node->children->c->code, "INT:") != NULL)
        { // INT
            node *INT_node = exp_node->children->c;
            char *ret = (char *)malloc(sizeof(char) * (strlen(place) + strlen(INT_node->code) + 64));
            sprintf(ret, "%s := #%s", place, INT_node->code + 5);
            // printf("ret=\n%s\n", ret);
            return ret;
        }
        else if (strstr(exp_node->children->c->code, "ID:") != NULL)
        { // ID
            // printf("translate_EXP 1.1\n");
            node *ID_node = exp_node->children->c;
            char *ret = (char *)malloc(sizeof(char) * (strlen(place) + strlen(ID_node->code) + 5));
            sprintf(ret, "%s := %s", place, ID_node->code + 4);
            return ret;
        }
    }
    else if (exp_node->child_num >= 2)
    {
        // printf("translate_EXP 2212\n");
        if (strcmp(exp_node->children->next->c->code, "ASSIGNOP") == 0)
        { // Exp1 ASSIGNOP Exp2
            // printf("translate_EXP 2.3\n");
            node *exp1_node = exp_node->children->c;
            node *exp2_node = exp_node->children->next->next->c;
            // TODO: current only for Exp1 -> ID
            if (strstr(exp1_node->children->c->code, "ID:") != NULL)
            {
                node *ID_node = exp1_node->children->c;
                symbol_list *sl = is_in_symbol_table(ID_node->code + 4, 0);
                if (sl == NULL)
                {
                    // TODO: symbol not found error
                    printf("not in symbol_table!!!\n");
                }
                // char *t1 = new_tmp();
                char *t1 = (char *)malloc(sizeof(char) * 64);
                sprintf(t1, "%s", ID_node->code + 4);
                // printf("t1=%s\n",t1);
                char *code1 = translate_EXP(exp2_node, t1);
                return code1;

                /*char *code2 = (char *)malloc(sizeof(char) * (strlen(code1) + 128));
                // printf("\n\ncode1=%s\n\ncode2=%s\n\n\n", code1, code2);
                sprintf(code2, "%s := %s\n%s := %s", sl->symbol_name, t1, place, sl->symbol_name);
                // printf("translate_EXP 1.2\n");
                char *ret = (char *)malloc(sizeof(char) * (strlen(code1) + strlen(code2) + 64));
                sprintf(ret, "%s\n%s", code1, code2);
                // free(t1);
                // free(code1);
                // free(code2);
                return ret;*/
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
            // printf("translate_EXP 3\n");
            node *exp1_node = exp_node->children->c;
            node *exp2_node = exp_node->children->next->next->c;
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
                break;
            default:
                break;
            }

            if (exp1_node->child_num == 1 && exp2_node->child_num == 1)
            {
                char *code1 = (char *)malloc(sizeof(char) * 64);
                char *code2 = (char *)malloc(sizeof(char) * 64);
                if (strstr(exp1_node->children->c->code, "ID") != NULL)
                {
                    sprintf(code1, "%s", strstr(exp1_node->children->c->code, ":") + 2);
                }
                else
                {
                    sprintf(code1, "#%s", strstr(exp1_node->children->c->code, ":") + 2);
                }
                if (strstr(exp2_node->children->c->code, "ID") != NULL)
                {
                    sprintf(code2, "%s", strstr(exp2_node->children->c->code, ":") + 2);
                }
                else
                {
                    sprintf(code2, "#%s", strstr(exp2_node->children->c->code, ":") + 2);
                }
                char *ret = (char *)malloc(sizeof(char) * (strlen(code1) + strlen(code2) + 64));
                sprintf(ret, "%s := %s %c %s", place, code1, op, code2);
                // free(code1);
                // free(code2);
                return ret;
            }
            else if (exp1_node->child_num == 1)
            {
                char *t1 = new_tmp();
                char *code1 = translate_EXP(exp2_node, t1);
                char *ret = (char *)malloc(sizeof(char) * (strlen(code1) + 64));
                sprintf(ret, "%s\n%s := %s %c %s", code1, place, strstr(exp1_node->children->c->code, ":") + 1, op, t1);
                // free(t1);
                // free(code1);
                return ret;
            }
            else if (exp2_node->child_num == 1)
            {
                char *t1 = new_tmp();
                char *code1 = translate_EXP(exp1_node, t1);
                char *ret = (char *)malloc(sizeof(char) * (strlen(code1) + 64));
                sprintf(ret, "%s\n%s := %s op %s", code1, place, t1, strstr(exp2_node->children->c->code, ":") + 1);
                // free(t1);
                // free(code1);
                return ret;
            }

            char *t1 = new_tmp();
            char *t2 = new_tmp();
            char *code1 = translate_EXP(exp1_node, t1);
            char *code2 = translate_EXP(exp2_node, t2);
            char *code3 = (char *)malloc(sizeof(char) * 128);

            sprintf(code3, "%s := %s %c %s", place, t1, op, t2);
            char *ret = (char *)malloc(sizeof(char) * (strlen(code1) + strlen(code2) + strlen(code3) + 64));
            sprintf(ret, "%s\n%s\n%s", code1, code2, code3);
            // free(t1);
            // free(t2);
            // free(code1);
            // free(code2);
            // free(code3);
            return ret;
        }
    }
    // printf("exphah\n");
    if (exp_node->child_num == 2 && strcmp(exp_node->children->c->code, "MINUS") == 0)
    { // MINUS EXP1
        // printf("translate_EXP 4\n");
        node *exp1_node = exp_node->children->next->c;
        if (exp1_node->child_num == 1)
        { // Exp1 -> ID / INT / FLOAT
            char *ret = (char *)malloc(sizeof(char) * 128);
            sprintf(ret, "%s := #0 - %s", place, strstr(exp1_node->code, ":") + 2);
            return ret;
        }
        char *t1 = new_tmp();
        char *code1 = translate_EXP(exp1_node, t1);
        char *code2 = (char *)malloc(sizeof(char) * 128);
        sprintf(code2, "%s := #0 - %s", place, t1);
        char *ret = (char *)malloc(sizeof(char) * (strlen(code1) + strlen(code2) + 64));
        sprintf(ret, "%s\n%s", code1, code2);
        // free(t1);
        // free(code1);
        // free(code2);
        return ret;
    }
    else if (exp_node->child_num >= 2 && (strcmp(exp_node->children->c->code, "NOT") == 0 ||
                                          strstr(exp_node->children->next->c->code, "RELOP") != NULL ||
                                          strcmp(exp_node->children->next->c->code, "AND") == 0 ||
                                          strcmp(exp_node->children->next->c->code, "OR") == 0))
    { // NOT Exp / Exp RELOP/AND/OR Exp
        // printf("translate_EXP 5\n");
        char *label1 = new_label();
        char *label2 = new_label();
        char *code0 = (char *)malloc(sizeof(char) * 128);
        sprintf(code0, "%s := #0", place);
        char *code1 = translate_COND(exp_node, label1, label2);
        char *ret = (char *)malloc(sizeof(char) * (strlen(code0) + strlen(code1) + 64));
        sprintf(ret, "%s\n%s\nLABEL %s :\n%s := #1\nLABEL %s :", code0, code1, label1, place, label2);
        // free(label1);
        // free(label2);
        // free(code0);
        // free(code1);
        return ret;
    }
    else if (exp_node->child_num == 3 && strcmp(exp_node->children->next->c->code, "LP") == 0 && strcmp(exp_node->children->next->next->c->code, "RP") == 0)
    { // ID LP RP
        // printf("translate_EXP 6\n");
        // printf("id=%s\n", exp_node->children->c->code);
        if (strcmp(exp_node->children->c->code + 4, "read") == 0)
        {
            char *ret = (char *)malloc(sizeof(char) * 32);
            sprintf(ret, "READ %s", place);
            return ret;
        }
        symbol_list *sl = is_in_symbol_table(exp_node->children->c->code + 4, 1);
        if (sl == NULL)
        {
            // TODO: function symbol not found error
        }
        char *ret = (char *)malloc(sizeof(char) * 64);
        sprintf(ret, "%s := CALL %s", place, sl->symbol_name);
        return ret;
    }
    else if (exp_node->child_num == 4 && strcmp(exp_node->children->next->c->code, "LP") == 0)
    { // ID LP Args RP
        // printf("translate_EXP 7\n");
        args_list *al = (args_list *)malloc(sizeof(args_list));
        al->next = NULL;
        node *args_node = exp_node->children->next->next->c;
        char *code1 = translate_ARGS(args_node, al);
        if (strcmp(exp_node->children->c->code + 4, "write") == 0)
        {
            char *ret = (char *)malloc(sizeof(char) * (strlen(code1) + 64));
            sprintf(ret, "%s\nWRITE %s", code1, al->next->symbol_name);
            // free(code1);
            return ret;
        }
        // printf("translate_EXP 7.1\n");
        symbol_list *sl = is_in_symbol_table(exp_node->children->c->code + 4, 1);
        // printf("sl->symbol_name=%s\n",sl->symbol_name);
        char *code2 = (char *)malloc(sizeof(char) * 256);
        code2[0] = '\0';
        code2 = args_list_2_string(al->next, code2);
        code2[strlen(code2) - 1] = '\0';
        char *ret = (char *)malloc(sizeof(char) * (strlen(code1) + strlen(code2) + 64));
        sprintf(ret, "%s\n%s\n%s := CALL %s", code1, code2, place, sl->symbol_name);
        // free(code1);
        // free(code2);
        return ret;
    }
    else if (exp_node->child_num == 3 && strcmp(exp_node->children->c->code, "LP") == 0)
    { // Exp -> LP Exp1 RP
        return translate_EXP(exp_node->children->next->c, place);
    }
    // printf("???tree=\n");
    // print_tree(exp_node, 0);
    // printf("translate_EXP ???\n");
}

char *translate_STMT(node *stmt_node)
{
    //// printf("int translate_STMT\n");
    if (stmt_node->child_num == 2 && strcmp(stmt_node->children->next->c->code, "SEMI") == 0)
    { // Stmt -> Exp SEMI
        // printf("translate_STMT 8\n");
        char *code1 = translate_EXP(stmt_node->children->c, NULL);
        // printf("in stmt, code1=%s\n\n",code1);
        char *tmp;
        if ((tmp = strstr(code1, "(null)")) != NULL)
        {
            *(--tmp) = '\0';
        }

        return code1;
    }
    else if (stmt_node->child_num == 1 && strcmp(stmt_node->children->c->code, "CompSt") == 0)
    { // Stmt -> CompSt
        // printf("translate_STMT 9\n");
        return translate_COMPST(stmt_node->children->c);
    }
    else if (stmt_node->child_num == 3)
    { // RETURN Exp SEMI
        // printf("translate_STMT 10\n");
        char *t1 = new_tmp();
        char *code1 = translate_EXP(stmt_node->children->next->c, t1);
        // printf("\n\ncode1=%s\n\n\n", code1);
        char *ret = (char *)malloc(sizeof(char) * (strlen(code1) + 64));
        sprintf(ret, "%s\nRETURN %s", code1, t1);
        // free(t1);
        // free(code1);
        return ret;
    }
    else if (strcmp(stmt_node->children->c->code, "IF") == 0)
    {
        if (stmt_node->child_num == 5)
        { // IF LP Exp RP Stmt1
            // printf("translate_STMT 11\n");
            node *exp_node = stmt_node->children->next->next->c;
            node *stmt1_node = stmt_node->children->next->next->next->next->c;
            char *label1 = new_label();
            char *label2 = new_label();
            char *code1 = translate_COND(exp_node, label1, label2);
            char *code2 = translate_STMT(stmt1_node);
            char *ret = (char *)malloc(sizeof(char) * (strlen(code1) + strlen(code2) + 64));
            sprintf(ret, "%s\nLABEL %s :\n%s\nLABEL %s :", code1, label1, code2, label2);
            // free(label1);
            // free(label2);
            // free(code1);
            // free(code2);
            return ret;
        }
        else if (stmt_node->child_num == 7)
        { // IF LP Exp RP Stmt1 ELSE Stmt2
            // printf("translate_STMT 12\n");
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
            sprintf(ret, "%s\nLABEL %s :\n%s\nGOTO %s\nLABEL %s :\n%s\nLABEL %s :", code1, label1, code2, label3, label2, code3, label3);
            // free(label1);
            // free(label2);
            // free(label3);
            // free(code1);
            // free(code2);
            // free(code3);
            return ret;
        }
    }
    else if (stmt_node->child_num == 5)
    { // WHILE LP Exp RP Stmt1
        // printf("translate_STMT 13\n");
        char *label1 = new_label();
        char *label2 = new_label();
        char *label3 = new_label();
        node *exp_node = stmt_node->children->next->next->c;
        node *stmt1_node = stmt_node->children->next->next->next->next->c;
        char *code1 = translate_COND(exp_node, label2, label3);
        char *code2 = translate_STMT(stmt1_node);
        char *ret = (char *)malloc(sizeof(char) * (strlen(code1) + strlen(code2) + 128));
        sprintf(ret, "LABEL %s :\n%s\nLABEL %s :\n%s\nGOTO %s\nLABEL %s :", label1, code1, label2, code2, label1, label3);
        // free(label1);
        // free(label2);
        // free(label3);
        // free(code1);
        // free(code2);
        return ret;
    }
}

char *translate_COND(node *cond_node, char *lable_true, char *label_false)
{
    if (cond_node->child_num == 3 && strstr(cond_node->children->next->c->code, "RELOP:") != NULL)
    { // Exp1 RELOP Exp2
        // printf("translate_COND 14\n");
        node *exp1_node = cond_node->children->c;
        node *exp2_node = cond_node->children->next->next->c;
        char *t1 = new_tmp();
        char *t2 = new_tmp();
        char *op = cond_node->children->next->c->code + 6;
        char *code1 = translate_EXP(exp1_node, t1);
        char *code2 = translate_EXP(exp2_node, t2);
        char *ret = (char *)malloc(sizeof(char) * (strlen(code1) + strlen(code2) + 128));
        sprintf(ret, "%s\n%s\nIF %s %s %s GOTO %s\nGOTO %s", code1, code2, t1, op, t2, lable_true, label_false);
        // free(t1);
        // free(t2);
        // free(code1);
        // free(code2);
        return ret;
    }
    else if (cond_node->child_num == 2 && strcmp(cond_node->children->c->code, "NOT") == 0)
    { // NOT Exp1
        // printf("translate_COND 15\n");
        node *exp1_node = cond_node->children->next->c;
        return translate_COND(exp1_node, label_false, lable_true);
    }
    else if (cond_node->child_num == 3 && strcmp(cond_node->children->next->c->code, "AND") == 0)
    { // Exp1 AND Exp2
        // printf("translate_COND 16\n");
        node *exp1_node = cond_node->children->c;
        node *exp2_node = cond_node->children->next->next->c;
        char *label1 = new_label();
        char *code1 = translate_COND(exp1_node, label1, label_false);
        char *code2 = translate_COND(exp2_node, lable_true, label_false);
        char *ret = (char *)malloc(sizeof(char) * (strlen(code1) + strlen(code2) + 128));
        sprintf(ret, "%s\nLABEL %s :\n%s", code1, label1, code2);
        // free(label1);
        // free(code1);
        // free(code2);
        return ret;
    }
    else if (cond_node->child_num == 3 && strcmp(cond_node->children->next->c->code, "AND") == 0)
    { // Exp1 OR Exp2
        // printf("translate_COND 17\n");
        node *exp1_node = cond_node->children->c;
        node *exp2_node = cond_node->children->next->next->c;
        char *label1 = new_label();
        char *code1 = translate_COND(exp1_node, lable_true, label1);
        char *code2 = translate_COND(exp2_node, lable_true, label_false);
        char *ret = (char *)malloc(sizeof(char) * (strlen(code1) + strlen(code2) + 128));
        sprintf(ret, "%s\nLABEL %s :\n%s", code1, label1, code2);
        // free(label1);
        // free(code1);
        // free(code2);
        return ret;
    }
    else
    {
        // printf("1\n");
        char *t1 = new_tmp();
        char *code1 = translate_EXP(cond_node, t1);
        char *ret = (char *)malloc(sizeof(char) * (strlen(code1) + 128));
        sprintf(ret, "%s\nIF %s != #0 GOTO %s\nGOTO %s", code1, t1, lable_true, label_false);
    }
}

char *translate_ARGS(node *args_node, args_list *al)
{

    // printf("translate_ARGS 18\n");
    node *exp_node = args_node->children->c;
    char *t1 = new_tmp();
    char *code1 = translate_EXP(exp_node, t1);
    args_list *new_al = (args_list *)malloc(sizeof(args_list));
    new_al->symbol_name = strdup(t1);
    new_al->next = NULL;
    args_list *tmp = al;
    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    tmp->next = new_al;
    // free(t1);
    if (args_node->child_num == 1 && strcmp(args_node->children->c->code, "Exp") == 0)
    { // Exp
        return code1;
    }
    else if (args_node->child_num == 3)
    { // Exp COMMA Args1
        node *args1_node = args_node->children->next->next->c;
        char *code2 = translate_ARGS(args1_node, al);
        char *ret = (char *)malloc(sizeof(char) * (strlen(code1) + strlen(code2) + 16));
        sprintf(ret, "%s\n%s", code1, code2);
        // free(code1);
        // free(code2);
        return ret;
    }
}

char *translate_COMPST(node *compst_node)
{
    // printf("translate_COMPST 19\n");
    // CompSt -> LC DefList StmtList RC
    return translate_STMTLIST(compst_node->children->next->next->c);
}

char *translate_STMTLIST(node *stmtlist_node)
{
    if (stmtlist_node->child_num == 2)
    { // StmtList -> Stmt StmtList1
        // printf("translate_STMTLIST 20\n");
        node *stmt_node = stmtlist_node->children->c;
        node *stmtlist1_node = stmtlist_node->children->next->c;
        char *code1 = translate_STMT(stmt_node);
        char *code2 = translate_STMTLIST(stmtlist1_node);
        // printf("translate_STMTLIST 20.1\n");
        // printf("\ncode1=\n%s\n\ncode2=%s\n\n", code1, code2);
        char *ret = (char *)malloc(sizeof(char) * (strlen(code1) + strlen(code2) + 128));
        sprintf(ret, "%s\n%s", code1, code2);
        // printf("\n\nret=\n%s\n\n\n", ret);
        // free(code1);
        // free(code2);
        // printf("translate_STMTLIST 20.2\n");
        return ret;
    }
    else
    { // %empty
        // printf("translate_STMTLIST 21\n");
        char *ret = (char *)malloc(sizeof(char) * 4);
        memset(ret, '\0', sizeof(char) * 4);
        // printf("translate_STMTLIST 21.1\n");
        return ret;
    }
}

char *translate_PARAMDEC(node *paramdec_node)
{ // ParamDec -> Specifier VarDec
    node *vardec_node = paramdec_node->children->next->c;
    while (vardec_node->child_num != 1)
        vardec_node = vardec_node->children->c;
    char *code1 = strdup(vardec_node->children->c->code + 4);
    char *ret = (char *)malloc(sizeof(char) * (strlen(code1) + 64));
    sprintf(ret, "PARAM %s", code1);
    // free(code1);
    return ret;
}

char *translate_VARLIST(node *varlist_node)
{
    if (varlist_node->child_num == 3)
    { // VarList -> ParamDec COMMA VarList1
        node *paramdec_node = varlist_node->children->c;
        node *varlist1_node = varlist_node->children->next->next->c;
        char *code1 = translate_PARAMDEC(paramdec_node);
        char *code2 = translate_VARLIST(varlist1_node);
        char *ret = (char *)malloc(sizeof(char) * (strlen(code1) + strlen(code2) + 64));
        sprintf(ret, "%s\n%s", code1, code2);
        // free(code1);
        // free(code2);
        return ret;
    }
    else
    { // VarList -> ParamDec
        node *paramdec_node = varlist_node->children->c;
        return translate_PARAMDEC(paramdec_node);
    }
}

char *translate_FUNDEC(node *funcdec_node)
{
    if (funcdec_node->child_num == 4)
    { // FunDec -> ID LP VarList RP
        node *varlist_node = funcdec_node->children->next->next->c;
        char *code1 = (char *)malloc(sizeof(char) * 64);
        sprintf(code1, "FUNCTION %s :", funcdec_node->children->c->code + 4);
        char *code2 = translate_VARLIST(varlist_node);
        char *ret = (char *)malloc(sizeof(char) * (strlen(code1) + strlen(code2) + 64));
        sprintf(ret, "%s\n%s", code1, code2);
        // free(code1);
        // free(code2);
        return ret;
    }
    else
    { // FunDec -> ID LP RP
        char *code1 = (char *)malloc(sizeof(char) * 64);
        sprintf(code1, "FUNCTION %s :", funcdec_node->children->c->code + 4);
        return code1;
    }
}

void translate(node *root)
{
    // printf("in hah\n");
    switch (root->typeno)
    {
    case FunDec:
    {
        char *o = translate_FUNDEC(root);
        printf("%s\n", o);
        write_file(o);
        break;
    }
    case CompSt:
    {
        char *oo = translate_COMPST(root);
        printf("%s\n", oo);
        write_file(oo);
        break;
    }
    }
    if (root->children != NULL)
    {
        child_node *__start = root->children;
        while (__start != NULL)
        {
            if (__start->c->children != NULL)
                translate(__start->c);
            __start = __start->next;
        }
    }
}

char *args_list_2_string(args_list *al, char *s)
{
    if (al != NULL)
    {
        args_list_2_string(al->next, s);
        strcat(s, "ARG ");
        strcat(s, al->symbol_name);
        strcat(s, "\n");
    }
    return s;
}