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
char *translate_VARDEC_STRUCTSPECIFIER(node *, node *);
char *translate_FUNDEC(node *);
char *translate_DEFLIST(node *, char *);
char *translate_DEC(node *);
void translate(node *);
char *args_list_2_string(args_list *, char *);
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
    if (exp_node->child_num == 1)
    {
        if (strstr(exp_node->children->c->code, "INT:") != NULL)
        { // INT
            node *INT_node = exp_node->children->c;
            char *ret = (char *)malloc(sizeof(char) * (strlen(place) + strlen(INT_node->code) + 64));
            sprintf(ret, "%s := #%s", place, INT_node->code + 5);

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
            if (exp1_node->child_num == 1 && strstr(exp1_node->children->c->code, "ID:") != NULL &&
                exp2_node->child_num == 1)
            {
                char *ret = (char *)malloc(sizeof(char) * 128);
                if (strstr(exp2_node->children->c->code, "ID:") != NULL)
                {
                    sprintf(ret, "%s := %s", exp1_node->children->c->code + 4, exp2_node->children->c->code + 4);
                }
                else
                {
                    sprintf(ret, "%s := #%s", exp1_node->children->c->code + 4, strstr(exp2_node->children->c->code, ":") + 2);
                }
                return ret;
            }
            if (exp1_node->child_num == 1 && strstr(exp1_node->children->c->code, "ID:") != NULL)
            { // Exp1 -> ID
                node *ID_node = exp1_node->children->c;
                symbol_list *sl = is_in_symbol_table(ID_node->code + 4, 0);
                if (sl == NULL)
                {
                    // TODO: symbol not found error
                    printf("not in symbol_table!!!\n");
                    exit(-1);
                }
                char *t1 = (char *)malloc(sizeof(char) * 64);
                sprintf(t1, "%s", ID_node->code + 4);

                char *code1 = translate_EXP(exp2_node, t1);
                return code1;
            }
            else if (exp1_node->child_num == 3 && strcmp(exp1_node->children->next->c->code, "DOT") == 0)
            { // Exp1 -> Exp12 DOT ID
                // Exp12 -> ID
                char *code2;
                char *t1 = NULL;
                if (exp2_node->child_num != 1)
                {
                    t1 = new_tmp();
                    code2 = translate_EXP(exp2_node, t1);
                }
                else
                {
                    if (strstr(exp2_node->children->c->code, "ID") != NULL)
                    {
                        code2 = strdup(exp2_node->children->c->code + 4);
                    }
                    else
                    {
                        code2 = (char *)malloc(sizeof(char) * 128);
                        sprintf(code2, "#%s", strstr(exp2_node->children->c->code, ":") + 2);
                    }
                }
                char *struct_id = exp1_node->children->c->children->c->code + 4;
                symbol_list *sl = is_in_symbol_table(struct_id, 0);
                struct_typedef *st = find_struct_by_id(sl->type);
                if (st == NULL)
                {
                    printf("error, struct: %s not found!!!\n", struct_id);
                    exit(-1);
                }
                char *field_name = exp1_node->children->next->next->c->code + 4;
                field_list *fl = find_field_in_struct(st, field_name);
                if (fl == NULL)
                {
                    printf("error, field: %s not found in struct: %s!!!\n", field_name, st->symbol_name);
                    exit(-1);
                }
                char *ret;
                if (fl->start_location == 0)
                {
                    ret = (char *)malloc(sizeof(char) * (strlen(code2) + 128));
                    char *t2 = new_tmp();
                    if (t1 == NULL)
                        sprintf(ret, "%s := &%s\n*%s := %s", t2, struct_id, t2, code2);
                    else
                    {
                        sprintf(ret, "%s := &%s\n%s\n*%s := %s", t2, struct_id, code2, t2, t1);
                    }
                    free(code2);
                    return ret;
                }
                else
                {
                    ret = (char *)malloc(sizeof(char) * (strlen(code2) + 128));
                    char *t2 = new_tmp();
                    if (t1 == NULL)
                        sprintf(ret, "%s := &%s + #%d\n*%s := %s", t2, struct_id, fl->start_location, t2, code2);
                    else
                    {
                        sprintf(ret, "%s := &%s + #%d\n%s\n*%s := %s", t2, struct_id, fl->start_location, code2, t2, t1);
                    }
                    free(code2);
                    return ret;
                }
                free(t1);
            }
            else if (exp1_node->child_num == 4 && strcmp(exp1_node->children->next->c->code, "LB") == 0)
            {
                printf("Cannot translate: Code contains variables of multi-dimensional array type or parameters of array type.\n");
                exit(0);
            }
            else
            {
                printf("invalid exp1 for exp1 = exp2!!!\n");
                exit(-1);
            }
        }
        else if (strcmp(exp_node->children->next->c->code, "PLUS") == 0 ||
                 strcmp(exp_node->children->next->c->code, "MINUS") == 0 ||
                 strcmp(exp_node->children->next->c->code, "STAR") == 0 ||
                 strcmp(exp_node->children->next->c->code, "DIV") == 0)
        { // Exp PLUS/MINUS/STAR/DIV Exp
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
                free(code1);
                free(code2);
                return ret;
            }
            else if (exp1_node->child_num == 1)
            {
                char *t1 = new_tmp();
                char *code1 = translate_EXP(exp2_node, t1);
                char *ret = (char *)malloc(sizeof(char) * (strlen(code1) + 64));
                if (strstr(exp1_node->children->c->code, "ID:") != NULL)
                    sprintf(ret, "%s\n%s := %s %c %s", code1, place, strstr(exp1_node->children->c->code, ":") + 2, op, t1);
                else
                    sprintf(ret, "%s\n%s := %s %c #%s", code1, place, strstr(exp1_node->children->c->code, ":") + 2, op, t1);
                free(t1);
                free(code1);
                return ret;
            }
            else if (exp2_node->child_num == 1)
            {
                char *t1 = new_tmp();
                char *code1 = translate_EXP(exp1_node, t1);
                char *ret = (char *)malloc(sizeof(char) * (strlen(code1) + 64));
                if (strstr(exp2_node->children->c->code, "ID:") != NULL)
                    sprintf(ret, "%s\n%s := %s %c %s", code1, place, t1, op, strstr(exp2_node->children->c->code, ":") + 2);
                else
                    sprintf(ret, "%s\n%s := %s %c #%s", code1, place, t1, op, strstr(exp2_node->children->c->code, ":") + 2);
                free(t1);
                free(code1);
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
            free(t1);
            free(t2);
            free(code1);
            free(code2);
            free(code3);
            return ret;
        }
    }

    if (exp_node->child_num == 2 && strcmp(exp_node->children->c->code, "MINUS") == 0)
    { // MINUS EXP1
        node *exp1_node = exp_node->children->next->c;
        if (exp1_node->child_num == 1)
        { // Exp1 -> ID / INT / FLOAT
            char *ret = (char *)malloc(sizeof(char) * 128);
            if (strstr(exp1_node->children->c->code, "ID:") != NULL)
                sprintf(ret, "%s := #0 - %s", place, strstr(exp1_node->children->c->code, ":") + 2);
            else
                sprintf(ret, "%s := #0 - #%s", place, strstr(exp1_node->children->c->code, ":") + 2);
            return ret;
        }
        char *t1 = new_tmp();
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
        char *ret = (char *)malloc(sizeof(char) * (strlen(code0) + strlen(code1) + 64));
        sprintf(ret, "%s\n%s\nLABEL %s :\n%s := #1\nLABEL %s :", code0, code1, label1, place, label2);
        free(label1);
        free(label2);
        free(code0);
        free(code1);
        return ret;
    }
    else if (exp_node->child_num == 3 && strcmp(exp_node->children->next->c->code, "LP") == 0 && strcmp(exp_node->children->next->next->c->code, "RP") == 0)
    { // ID LP RP
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
        args_list *al = (args_list *)malloc(sizeof(args_list));
        al->next = NULL;
        node *args_node = exp_node->children->next->next->c;
        char *code1 = translate_ARGS(args_node, al);
        if (strcmp(exp_node->children->c->code + 4, "write") == 0)
        {
            char *ret = (char *)malloc(sizeof(char) * (strlen(code1) + 64));
            sprintf(ret, "%s\nWRITE %s", code1, al->next->symbol_name);
            free(code1);
            return ret;
        }
        symbol_list *sl = is_in_symbol_table(exp_node->children->c->code + 4, 1);

        char *code2 = (char *)malloc(sizeof(char) * 256);
        code2[0] = '\0';
        code2 = args_list_2_string(al->next, code2);
        code2[strlen(code2) - 1] = '\0';
        char *ret = (char *)malloc(sizeof(char) * (strlen(code1) + strlen(code2) + 64));
        sprintf(ret, "%s\n%s\n%s := CALL %s", code1, code2, place, sl->symbol_name);
        free(code1);
        free(code2);
        return ret;
    }
    else if (exp_node->child_num == 3 && strcmp(exp_node->children->c->code, "LP") == 0)
    { // Exp -> LP Exp1 RP
        return translate_EXP(exp_node->children->next->c, place);
    }
    else if (exp_node->child_num == 3 && strcmp(exp_node->children->next->c->code, "DOT") == 0)
    { // Exp -> Exp1 DOT ID
        node *exp1_node = exp_node->children->c;
        char *struct_id = exp1_node->children->c->code + 4;
        symbol_list *sl = is_in_symbol_table(struct_id, 0);
        struct_typedef *st = find_struct_by_id(sl->type);
        char *id = exp_node->children->next->next->c->code + 4;
        field_list *fl = find_field_in_struct(st, id);
        int sll = fl->start_location;
        if (sll == 0)
        {
            char *ret = (char *)malloc(sizeof(char) * 128);
            sprintf(ret, "%s := *%s", place, struct_id);
            return ret;
        }
        else
        {
            char *t1 = new_tmp();
            char *code1 = (char *)malloc(sizeof(char) * 128);
            sprintf(code1, "%s := %s + #%d", t1, struct_id, sll);
            char *ret = (char *)malloc(sizeof(char) * (strlen(code1) + 128));
            sprintf(ret, "%s\n%s := *%s", code1, place, t1);
            free(t1);
            free(code1);
            return ret;
        }
    }
    else if (exp_node->child_num == 4 && strcmp(exp_node->children->next->c->code, "LB") == 0)
    { // Exp -> Exp1 LB Exp2 RB
        printf("Cannot translate: Code contains variables of multi-dimensional array type or parameters of array type.\n");
        exit(0);
        // Exp1 -> ID
        node *exp1_node = exp_node->children->c;
        if (exp1_node->child_num == 1)
        {
            symbol_list *sl = is_in_symbol_table(exp1_node->children->c->code + 4, 0);
            printf("%s: ", sl->symbol_name);
            int *width = sl->array_width;
            int width_len = 0;
            while (width[width_len] != -1)
                width_len++;
            node *exp2_node = exp_node->children->next->next->c;
            node *tmp = exp1_node;
            while (tmp != NULL && strcmp(tmp->parent->children->next->c->code, "LB") == 0)
            {
                tmp = tmp->parent;
            }
        }
        return "\ntemmmmppp\n";
    }
}

char *translate_STMT(node *stmt_node)
{
    if (stmt_node->child_num == 2 && strcmp(stmt_node->children->next->c->code, "SEMI") == 0)
    { // Stmt -> Exp SEMI

        char *code1 = translate_EXP(stmt_node->children->c, NULL);

        char *tmp;
        if ((tmp = strstr(code1, "(null)")) != NULL)
        {
            *(--tmp) = '\0';
        }

        return code1;
    }
    else if (stmt_node->child_num == 1 && strcmp(stmt_node->children->c->code, "CompSt") == 0)
    { // Stmt -> CompSt

        return translate_COMPST(stmt_node->children->c);
    }
    else if (stmt_node->child_num == 3)
    { // RETURN Exp SEMI

        node *exp1_node = stmt_node->children->next->c;
        char *t1;
        char *code1 = NULL;
        if (exp1_node->child_num == 1)
        { // Exp1 -> ID / INT / FLOAT
            t1 = (char *)malloc(sizeof(char) * 64);
            char *ret = (char *)malloc(sizeof(char) * 128);
            if (strstr(exp1_node->children->c->code, "ID:") != NULL)
                sprintf(t1, "%s", strstr(exp1_node->children->c->code, ":") + 2);
            else
                sprintf(t1, "#%s", strstr(exp1_node->children->c->code, ":") + 2);
        }
        else
        {
            t1 = new_tmp();
            code1 = translate_EXP(stmt_node->children->next->c, t1);
        }

        char *ret;
        if (code1 != NULL)
        {
            ret = (char *)malloc(sizeof(char) * (strlen(code1) + 64));
            sprintf(ret, "%s\nRETURN %s", code1, t1);
        }
        else
        {
            ret = (char *)malloc(sizeof(char) * (128));
            sprintf(ret, "RETURN %s", t1);
        }
        free(t1);
        free(code1);
        return ret;
    }
    else if (strcmp(stmt_node->children->c->code, "IF") == 0)
    {
        if (stmt_node->child_num == 5)
        { // IF LP Exp RP Stmt1
            node *exp_node = stmt_node->children->next->next->c;
            node *stmt1_node = stmt_node->children->next->next->next->next->c;
            char *label1 = new_label(); // label true
            char *label2 = new_label(); // label end
            char *code1 = translate_COND(exp_node, label1, label2);
            char *code2 = translate_STMT(stmt1_node);
            char *ret = (char *)malloc(sizeof(char) * (strlen(code1) + strlen(code2) + 64));
            //sprintf(ret, "%s\nLABEL %s :\n%s\nLABEL %s :", code1, label1, code2, label2);
            sprintf(ret, "%s\nGOTO %s\nLABEL %s :\n%s\nLABEL %s :", code1, label2, label1, code2, label2);
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
            char *label1 = new_label(); // label true
            char *label2 = new_label(); // lable false
            char *label3 = new_label(); // label end
            char *code1 = translate_COND(exp_node, label1, label2);
            char *code2 = translate_STMT(stmt1_node);
            char *code3 = translate_STMT(stmt2_node);
            char *ret = (char *)malloc(sizeof(char) * (strlen(code1) + strlen(code2) + strlen(code3) + 128));
            //sprintf(ret, "%s\nLABEL %s :\n%s\nGOTO %s\nLABEL %s :\n%s\nLABEL %s :", code1, label1, code2, label3, label2, code3, label3);
            sprintf(ret, "%s\n%s\nGOTO %s\nLABEL %s :\n%s\nLABEL %s :", code1, code3, label3, label1, code2, label3);
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
        sprintf(ret, "LABEL %s :\n%s\nLABEL %s :\n%s\nGOTO %s\nLABEL %s :", label1, code1, label2, code2, label1, label3);
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
        char *op = cond_node->children->next->c->code + 6;
        int flag = 0;
        char *code1 = NULL;
        char *relop_code;
        /*******/
        if (exp1_node->child_num == 1 && exp2_node->child_num == 1)
        {
            flag = 1;
            char *c1 = (char *)malloc(sizeof(char) * 64);
            char *c2 = (char *)malloc(sizeof(char) * 64);
            if (strstr(exp1_node->children->c->code, "ID") != NULL)
            {
                sprintf(c1, "%s", strstr(exp1_node->children->c->code, ":") + 2);
            }
            else
            {
                sprintf(c1, "#%s", strstr(exp1_node->children->c->code, ":") + 2);
            }
            if (strstr(exp2_node->children->c->code, "ID") != NULL)
            {
                sprintf(c2, "%s", strstr(exp2_node->children->c->code, ":") + 2);
            }
            else
            {
                sprintf(c2, "#%s", strstr(exp2_node->children->c->code, ":") + 2);
            }
            relop_code = (char *)malloc(sizeof(char) * (strlen(c1) + strlen(c2) + 64));
            sprintf(relop_code, "%s %s %s", c1, op, c2);
            free(c1);
            free(c2);
        }
        else if (exp1_node->child_num == 1)
        {
            flag = 1;
            char *t1 = new_tmp();
            code1 = translate_EXP(exp2_node, t1);
            relop_code = (char *)malloc(sizeof(char) * (strlen(code1) + 64));
            sprintf(relop_code, "%s %s %s", strstr(exp1_node->children->c->code, ":") + 1, op, t1);
            free(t1);
        }
        else if (exp2_node->child_num == 1)
        {
            flag = 1;
            char *t1 = new_tmp();
            code1 = translate_EXP(exp1_node, t1);
            relop_code = (char *)malloc(sizeof(char) * (strlen(code1) + 64));
            sprintf(relop_code, "%s %s %s", t1, op, strstr(exp2_node->children->c->code, ":") + 1);
            free(t1);
        }
        /*******/
        if (flag)
        {
            char *ret = (char *)malloc(sizeof(char) * (256));
            if (code1 != NULL)
                sprintf(ret, "%sIF %s GOTO %s", code1, relop_code, lable_true);
            else
                sprintf(ret, "IF %s GOTO %s", relop_code, lable_true);
            free(code1);
            free(relop_code);
            return ret;
        }
        else
        {
            node *exp1_node = cond_node->children->c;
            node *exp2_node = cond_node->children->next->next->c;
            char *t1 = new_tmp();
            char *t2 = new_tmp();
            char *op = cond_node->children->next->c->code + 6;
            char *code1 = translate_EXP(exp1_node, t1);
            char *code2 = translate_EXP(exp2_node, t2);
            char *ret = (char *)malloc(sizeof(char) * (strlen(code1) + strlen(code2) + 128));
            // sprintf(ret, "%s\n%s\nIF %s %s %s GOTO %s\nGOTO %s", code1, code2, t1, op, t2, lable_true, label_false);

            sprintf(ret, "%s\n%s\nIF %s %s %s GOTO %s", code1, code2, t1, op, t2, lable_true);
            free(t1);
            free(t2);
            free(code1);
            free(code2);
            return ret;
        }
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
        sprintf(ret, "%s\nLABEL %s :\n%s", code1, label1, code2);
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
        sprintf(ret, "%s\nLABEL %s :\n%s", code1, label1, code2);
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

char *translate_ARGS(node *args_node, args_list *al)
{
    node *exp_node = args_node->children->c;
    char *t1;
    char *code1;
    if (exp_node->child_num == 1)
    {
        t1 = (char *)malloc(sizeof(char) * 128);
        code1 = (char *)malloc(sizeof(char) * 64);
        code1[0] = '\0';
        if (strstr(exp_node->children->c->code, "ID") != NULL)
        {
            sprintf(t1, "%s", strstr(exp_node->children->c->code, ":") + 2);
        }
        else
        {
            sprintf(t1, "#%s", strstr(exp_node->children->c->code, ":") + 2);
        }
    }
    else
    {
        t1 = new_tmp();
        code1 = translate_EXP(exp_node, t1);
    }
    args_list *new_al = (args_list *)malloc(sizeof(args_list));
    new_al->symbol_name = strdup(t1);
    new_al->next = NULL;
    args_list *tmp = al;
    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    tmp->next = new_al;
    free(t1);
    if (args_node->child_num == 1 && strcmp(args_node->children->c->code, "Exp") == 0)
    { // Exp
        return code1;
    }
    else if (args_node->child_num == 3)
    { // Exp COMMA Args1
        node *args1_node = args_node->children->next->next->c;
        char *code2 = translate_ARGS(args1_node, al);
        char *ret = (char *)malloc(sizeof(char) * (strlen(code1) + strlen(code2) + 16));
        if (code1 != NULL)
            sprintf(ret, "%s\n%s", code1, code2);
        else
            sprintf(ret, "%s", code2);
        free(code1);
        free(code2);
        return ret;
    }
}

char *translate_COMPST(node *compst_node)
{
    // CompSt -> LC DefList StmtList RC
    node *deflist_node = compst_node->children->next->c;
    char *code1 = (char *)malloc(sizeof(char) * 256);
    code1[0] = '\0';
    code1 = translate_DEFLIST(deflist_node, code1);
    char *code2 = translate_STMTLIST(compst_node->children->next->next->c);
    char *ret = (char *)malloc(sizeof(char) * (strlen(code1) + strlen(code2) + 128));
    sprintf(ret, "%s\n%s", code1, code2);
    free(code1);
    free(code2);
    return ret;
}

char *translate_DEFLIST(node *deflist_node, char *s)
{
    node *root = deflist_node;
    if (root->typeno == Dec)
    {
        if (root->child_num == 3)
        {
            strcat(s, translate_DEC(root));
            strcat(s, "\n");
        }
    }
    if (root->children != NULL)
    {
        child_node *__start = root->children;
        while (__start != NULL)
        {
            if (__start->c->children != NULL)
                translate_DEFLIST(__start->c, s);
            __start = __start->next;
        }
    }
    return s;
}

char *translate_STMTLIST(node *stmtlist_node)
{
    if (stmtlist_node->child_num == 2)
    { // StmtList -> Stmt StmtList1
        node *stmt_node = stmtlist_node->children->c;
        node *stmtlist1_node = stmtlist_node->children->next->c;
        char *code1 = translate_STMT(stmt_node);
        char *code2 = translate_STMTLIST(stmtlist1_node);
        char *ret = (char *)malloc(sizeof(char) * (strlen(code1) + strlen(code2) + 128));
        sprintf(ret, "%s\n%s", code1, code2);
        free(code1);
        free(code2);
        return ret;
    }
    else
    { // %empty
        char *ret = (char *)malloc(sizeof(char) * 4);
        memset(ret, '\0', sizeof(char) * 4);
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
    free(code1);
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
        free(code1);
        free(code2);
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
        free(code1);
        free(code2);
        return ret;
    }
    else
    { // FunDec -> ID LP RP
        char *code1 = (char *)malloc(sizeof(char) * 64);
        sprintf(code1, "FUNCTION %s :", funcdec_node->children->c->code + 4);
        return code1;
    }
}

char *translate_VARDEC_STRUCTSPECIFIER(node *vardec_node, node *structspecifier_node)
{ // VarDec -> ID  // struct
    if (structspecifier_node->child_num == 5)
    { // StructSpecifier -> STRUCT OptTag LC DefList RC
        // TODO:
        printf("TODO in t_V_S\n");
        exit(-1);
    }
    else
    { // StructSpecifier -> STRUCT Tag
        node *tag_node = structspecifier_node->children->next->c;
        struct_typedef *st = find_struct(tag_node->children->c->code + 4);
        if (st == NULL)
        {
            printf("error, struct: %s not found!!!\n", tag_node->children->c->code + 4);
            exit(-1);
        }
        char *ret = (char *)malloc(sizeof(char) * 128);
        sprintf(ret, "DEC %s %d", vardec_node->children->c->code + 4, st->total_size);
        return ret;
    }
}

char *translate_DEC(node *dec_node)
{ // Dec -> VarDec ASSIGNOP Exp
    node *vardec_node = dec_node->children->c;
    node *exp_node = dec_node->children->next->next->c;
    if (vardec_node->child_num != 1)
    {
        printf("Cannot translate: Code contains variables of multi-dimensional array type or parameters of array type.\n");
        exit(0);
    }
    if (exp_node->child_num == 1)
    {
        char *ret = (char *)malloc(sizeof(char) * 128);
        if (strstr(exp_node->children->c->code, "ID:") != NULL)
            sprintf(ret, "%s := %s", vardec_node->children->c->code + 4, exp_node->children->c->code + 4);
        else
            sprintf(ret, "%s := #%s", vardec_node->children->c->code + 4, strstr(exp_node->children->c->code, ":") + 2);
        return ret;
    }
    else
    {
        char *t1 = new_tmp();
        char *code1 = translate_EXP(exp_node, t1);
        char *ret = (char *)malloc(sizeof(char) * (strlen(code1) + 128));
        sprintf(ret, "%s\n%s := %s", code1, vardec_node->children->c->code + 4, t1);
        free(t1);
        free(code1);
        return ret;
    }
}

void translate(node *root)
{
    switch (root->typeno)
    {
    case FunDec:
    {
        char *o = translate_FUNDEC(root);
        write_file(o);
        break;
    }
    case CompSt:
    {
        char *oo = translate_COMPST(root);
        write_file(oo);
        break;
    }
    case VarDec:
    {
        if (root->child_num != 1)
            break;
        node *tmp = root;
        while (tmp != NULL && strcmp(tmp->code, "ParamDec") != 0 && strcmp(tmp->code, "ExtDef") != 0 && strcmp(tmp->code, "Def") != 0)
        {
            tmp = tmp->parent;
        }
        if (strcmp(tmp->code, "ParamDec") == 0)
            break;
        if (tmp == NULL)
        {
            printf("error in translate_V_S\n");
            exit(-1);
        }
        node *specifier_node = tmp->children->c;
        if (strcmp(specifier_node->children->c->code, "StructSpecifier") == 0)
        {
            char *ooo = translate_VARDEC_STRUCTSPECIFIER(root, specifier_node->children->c);
            write_file(ooo);
        }
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
        symbol_list *sl = is_in_symbol_table(al->symbol_name, 0);
        if (sl != NULL && sl->type >= TYPE_struct)
            strcat(s, "ARG &");
        else
            strcat(s, "ARG ");
        strcat(s, al->symbol_name);
        strcat(s, "\n");
    }
    return s;
}