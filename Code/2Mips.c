#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bison.h"
#include "errortype.h"

static const char *head_code = ".data\n_prompt: .asciiz \"Enter an integer:\"\n_ret: .asciiz \"\n\"\n.globl main\n.text\n";
static const char *read_mips = "read:\nli $v0, 4\nla $a0, _prompt\nsyscall\nli $v0, 5\nsyscall\njr $ra\n";
static const char *write_mips = "write:\nli $v0, 1\nsyscall\nli $v0, 4\nla $a0, _ret\nsyscall\nmove $v0, $0\njr $ra\n";
static const char *regs[] = {"$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$t8", "$t9"};

extern char *mid_code;
static char *mid_code_array[10000];
static char *mips_code;

extern symbol_list *_func_symbol_table_start;

static int mid_code_2_array()
{
    int cc = 0;
    mid_code_array[cc++] = mid_code;
    int len = strlen(mid_code);
    for (int i = 0; i < len; i++)
    {
        if (mid_code[i] == '\n')
        {
            mid_code[i] = '\0';
            mid_code_array[cc++] = mid_code + i + 1;
        }
    }
    return cc;
}

static void print_func_var_test()
{
    symbol_list *func = _func_symbol_table_start;
    while (func != NULL)
    {
        printf("func %s argv_len: %d\n", func->symbol_name, func->argv_list_len);
        local_var *lv = func->local_var_list;
        while (lv != NULL)
        {
            printf("func: %s, var:%s, size: %d\n", func->symbol_name, lv->var_name, lv->size);
            lv = lv->next;
        }
        printf("\n\n");
        func = func->next;
    }
}

void gen_target_code()
{
    int cc = mid_code_2_array();
    mips_code = (char *)malloc(sizeof(char) * 102400);
    memset(mips_code, 0, sizeof(char) * 102400);
    print_func_var_test();
    /*
    for (int i = 0; i < cc; i++)
    {
        char *mm = (char *)malloc(sizeof(char) * 128);
        if (mid_code_array[i][0] == '\0')
            continue;
        char *tmp;
        if ((tmp = strstr(mid_code_array[i], "GOTO")) != NULL)
        {
            sprintf(mm, "j %s\n", tmp + 4);
        }
        else if ((tmp = strstr(mid_code_array[i], "LABEL")) != NULL)
        {
            sprintf(mm, "%s\n", tmp + 5);
        }
        else if ((tmp = strstr(mid_code_array[i], "+")) != NULL)
        { // x := y + z, x := y + #1
            char *tmp1 = strstr(":=", mid_code_array[i]);
            char *s1 = mid_code_array[i];
            char *s2 = tmp1 + 2;
            tmp1[0] = tmp1[1] = '\0';
            char *s3 = tmp + 1;
            tmp[0] = '\0';
            if (strstr(s3, "#") == NULL)
            { // x := y + z
                sprintf(mm, "add reg(%s), reg(%s), reg(%s)");
            }
            else
            { // x := y + #1
            }
        }
    }
    */
}