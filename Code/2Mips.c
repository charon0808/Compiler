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
static char *_current_func;

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

static char *string_trim(char *s)
{
    //printf("(%s)\n", s);
    while (*s == ' ')
        s++;
    while (s[strlen(s) - 1] == ' ')
        s[strlen(s) - 1] = '\0';
    return s;
}

static int gen_var_dec_mips_code(char *func_name, char *code)
{
    func_name = string_trim(func_name);
    code = string_trim(code);
    int total_offset;
    symbol_list *func = is_in_symbol_table(func_name, 1);
    int count;
    while (func != NULL)
    {
        count = 0;
        total_offset = 0;
        local_var *lv = func->local_var_list;
        int rest_offset = 0;
        while (lv != NULL)
        {
            lv->offset = total_offset;
            if (count < func->argv_list_len)
            {
                char *tmp = (char *)malloc(sizeof(char) * 256);
                sprintf(tmp, "addi $sp, $sp, -4\nlw %s, %d($fp)\nsw %s, 0($sp)\n", regs[0], count * 4, regs[0]);
                strcat(code, tmp);
                total_offset += 4;
            }
            else
            {
                rest_offset += lv->size;
                total_offset += lv->size;
            }
            count++;
            lv = lv->next;
        }
        char *tmp = (char *)malloc(sizeof(char) * 256);
        sprintf(tmp, "addi $sp, $sp, -%d\n", rest_offset);
        strcat(code, tmp);
        strcat(code, "\n\n");
        func = func->next;
    }
    printf(code);
}

static int find_var_offset_2_fp(char *var_name)
{
    var_name = string_trim(var_name);
    symbol_list *func = is_in_symbol_table(_current_func, 1);
    if (func == NULL)
    {
        printf("func: %s can not be found in symbol table!\n", _current_func);
        exit(-1);
    }
    local_var *lv = func->local_var_list;
    while (lv != NULL)
    {
        if (strcmp(lv->var_name, var_name) == 0)
        {
            return -8 - lv->offset;
        }
        lv = lv->next;
    }
    return 10086;
}

void gen_target_code()
{
    int cc = mid_code_2_array();
    mips_code = (char *)malloc(sizeof(char) * 102400);
    memset(mips_code, 0, sizeof(char) * 102400);
    print_func_var_test();
    for (int i = 0; i < cc; i++)
    {
        printf("%s\n", mid_code_array[i]);
        char *mm = (char *)malloc(sizeof(char) * 128);
        memset(mm, 0, sizeof(char) * 128);
        if (mid_code_array[i][0] == '\0')
            continue;
        char *tmp;
        if ((tmp = strstr(mid_code_array[i], "FUNCTION")) != NULL)
        {
            _current_func = strdup(tmp + 9);
            while (_current_func[strlen(_current_func) - 1] == ' ' || _current_func[strlen(_current_func) - 1] == ':')
            {
                _current_func[strlen(_current_func) - 1] = '\0';
            }
            sprintf(mm, "%s\n", _current_func);
            gen_var_dec_mips_code(_current_func, mips_code);
        }
        else if ((tmp = strstr(mid_code_array[i], "IF")) == NULL && (tmp = strstr(mid_code_array[i], "GOTO")) != NULL)
        {
            sprintf(mm, "j %s\n", tmp + 4);
        }
        else if ((tmp = strstr(mid_code_array[i], "LABEL")) != NULL)
        {
            sprintf(mm, "%s\n", tmp + 5);
        }
        else if ((tmp = strstr(mid_code_array[i], ":=")) != NULL && tmp[3] == '#' && strstr(tmp + 4, "#") == NULL)
        { // x := #1
            char *s1 = mid_code_array[i];
            tmp[0] = '\0';
            char *ttmp = (char *)malloc(sizeof(char) * 128);
            sprintf(ttmp, "li %s, %s\n", regs[0], tmp + 4);
            strcat(mm, ttmp);
            sprintf(ttmp, "sw %s, %d($fp)\n", regs[0], find_var_offset_2_fp(s1));
            strcat(mm, ttmp);
        }
        else if ((tmp = strstr(mid_code_array[i], "+")) != NULL)
        { // x := y + z, x := y + #1
            char *tmp1 = strstr(mid_code_array[i], ":=");
            char *s1 = mid_code_array[i];
            char *s2 = tmp1 + 2;
            tmp1[0] = tmp1[1] = '\0';
            char *s3 = tmp + 1;
            tmp[0] = '\0';
            if (strstr(s3, "#") == NULL)
            { // x := y + z
                char *ttmp = (char *)malloc(sizeof(char) * 128);
                if ((tmp = strstr(s2, "#")) == NULL)
                    sprintf(ttmp, "lw %s, %d($fp)\n", regs[0], find_var_offset_2_fp(s2)); // y
                else if ((tmp = strstr(s2, "#")) != NULL)
                    sprintf(ttmp, "li %s, %s\n", regs[0], tmp + 1);
                strcat(mm, ttmp);
                sprintf(ttmp, "lw %s, %d($fp)\n", regs[1], find_var_offset_2_fp(s3)); // z
                strcat(mm, ttmp);
                sprintf(ttmp, "addi %s, %s, %s\n", regs[0], regs[0], regs[1]);
                strcat(mm, ttmp);
                sprintf(ttmp, "sw %s, %d($fp)\n", regs[0], find_var_offset_2_fp(s1));
                strcat(mm, ttmp);
            }
            else
            { // x := y + #1
                char *ttmp = (char *)malloc(sizeof(char) * 128);
                if ((tmp = strstr(s2, "#")) == NULL)
                    sprintf(ttmp, "lw %s, %d($fp)\n", regs[0], find_var_offset_2_fp(s2)); // y
                else if ((tmp = strstr(s2, "#")) != NULL)
                    sprintf(ttmp, "li %s, %s\n", regs[0], tmp + 1);
                strcat(mm, ttmp);
                sprintf(ttmp, "addi %s, %s, %s\n", regs[0], regs[0], s3 + 1);
                strcat(mm, ttmp);
                sprintf(ttmp, "sw %s, %d($fp)\n", regs[0], find_var_offset_2_fp(s1));
                strcat(mm, ttmp);
            }
        }
        else if ((tmp = strstr(mid_code_array[i], "-")) != NULL)
        { // x := y - z, x := y - #1
            char *tmp1 = strstr(mid_code_array[i], ":=");
            char *s1 = mid_code_array[i];
            char *s2 = tmp1 + 3;
            tmp1[0] = tmp1[1] = '\0';
            char *s3 = tmp + 1;
            tmp[0] = '\0';
            s1 = string_trim(s1);
            s2 = string_trim(s2);
            s3 = string_trim(s3);
            printf("s1=_%s_, s2=_%s_, s3=_%s_\n", s1, s2, s3);
            if (strstr(s3, "#") == NULL)
            { // x := y - z
                char *ttmp = (char *)malloc(sizeof(char) * 128);
                if ((tmp = strstr(s2, "#")) == NULL)
                    sprintf(ttmp, "lw %s, %d($fp)\n", regs[0], find_var_offset_2_fp(s2)); // y
                else if ((tmp = strstr(s2, "#")) != NULL)
                    sprintf(ttmp, "li %s, %s\n", regs[0], tmp + 1);
                strcat(mm, ttmp);
                sprintf(ttmp, "lw %s, %d($fp)\n", regs[1], find_var_offset_2_fp(s3)); // z
                strcat(mm, ttmp);
                sprintf(ttmp, "sub %s, %s, %s\n", regs[0], regs[0], regs[1]);
                strcat(mm, ttmp);
                sprintf(ttmp, "sw %s, %d($fp)\n", regs[0], find_var_offset_2_fp(s1));
                strcat(mm, ttmp);
            }
            else
            { // x := y - #1
                char *ttmp = (char *)malloc(sizeof(char) * 128);
                if ((tmp = strstr(s2, "#")) == NULL)
                    sprintf(ttmp, "lw %s, %d($fp)\n", regs[0], find_var_offset_2_fp(s2)); // y
                else if ((tmp = strstr(s2, "#")) != NULL)
                    sprintf(ttmp, "li %s, %s\n", regs[0], tmp + 1);
                strcat(mm, ttmp);
                sprintf(ttmp, "addi %s, %s, -%s\n", regs[0], regs[0], s3 + 1);
                strcat(mm, ttmp);
                sprintf(ttmp, "sw %s, %d($fp)\n", regs[0], find_var_offset_2_fp(s1));
                strcat(mm, ttmp);
            }
        }
        else if ((tmp = strstr(mid_code_array[i], "*")) != NULL)
        { // x := y * z, x := y * #1
            char *tmp1 = strstr(mid_code_array[i], ":=");
            char *s1 = mid_code_array[i];
            char *s2 = tmp1 + 2;
            tmp1[0] = tmp1[1] = '\0';
            char *s3 = tmp + 1;
            tmp[0] = '\0';
            if (strstr(s3, "#") == NULL)
            { // x := y * z
                char *ttmp = (char *)malloc(sizeof(char) * 128);
                if ((tmp = strstr(s2, "#")) == NULL)
                    sprintf(ttmp, "lw %s, %d($fp)\n", regs[0], find_var_offset_2_fp(s2)); // y
                else if ((tmp = strstr(s2, "#")) != NULL)
                    sprintf(ttmp, "li %s, %s\n", regs[0], tmp + 1);
                strcat(mm, ttmp);
                sprintf(ttmp, "lw %s, %d($fp)\n", regs[1], find_var_offset_2_fp(s3)); // z
                strcat(mm, ttmp);
                sprintf(ttmp, "mul %s, %s, %s\n", regs[0], regs[0], regs[1]);
                strcat(mm, ttmp);
                sprintf(ttmp, "sw %s, %d($fp)\n", regs[0], find_var_offset_2_fp(s1));
                strcat(mm, ttmp);
            }
            else
            { // x := y * #1
                char *ttmp = (char *)malloc(sizeof(char) * 128);
                if ((tmp = strstr(s2, "#")) == NULL)
                    sprintf(ttmp, "lw %s, %d($fp)\n", regs[0], find_var_offset_2_fp(s2)); // y
                else if ((tmp = strstr(s2, "#")) != NULL)
                    sprintf(ttmp, "li %s, %s\n", regs[0], tmp + 1);
                strcat(mm, ttmp);
                sprintf(ttmp, "li %s, %d\n", regs[1], s3 + 1); // #1
                strcat(mm, ttmp);
                sprintf(ttmp, "mul %s, %s, %s\n", regs[0], regs[0], regs[1]);
                strcat(mm, ttmp);
                sprintf(ttmp, "sw %s, %d($fp)\n", regs[0], find_var_offset_2_fp(s1));
                strcat(mm, ttmp);
            }
        }
        else if ((tmp = strstr(mid_code_array[i], "/")) != NULL)
        { // x := y / z, x := y / #1
            char *tmp1 = strstr(mid_code_array[i], ":=");
            char *s1 = mid_code_array[i];
            char *s2 = tmp1 + 2;
            tmp1[0] = tmp1[1] = '\0';
            char *s3 = tmp + 1;
            tmp[0] = '\0';
            if (strstr(s3, "#") == NULL)
            { // x := y / z
                char *ttmp = (char *)malloc(sizeof(char) * 128);
                if ((tmp = strstr(s2, "#")) == NULL)
                    sprintf(ttmp, "lw %s, %d($fp)\n", regs[0], find_var_offset_2_fp(s2)); // y
                else if ((tmp = strstr(s2, "#")) != NULL)
                    sprintf(ttmp, "li %s, %s\n", regs[0], tmp + 1);
                strcat(mm, ttmp);
                sprintf(ttmp, "lw %s, %d($fp)\n", regs[1], find_var_offset_2_fp(s3)); // z
                strcat(mm, ttmp);
                sprintf(tmp, "div %s, %s\nmflo %s\n", regs[0], regs[1], regs[0]); // y/z
                strcat(mm, ttmp);
                sprintf(ttmp, "sw %s, %d($fp)\n", regs[0], find_var_offset_2_fp(s1));
                strcat(mm, ttmp);
            }
            else
            { // x := y / #1
                char *ttmp = (char *)malloc(sizeof(char) * 128);
                if ((tmp = strstr(s2, "#")) == NULL)
                    sprintf(ttmp, "lw %s, %d($fp)\n", regs[0], find_var_offset_2_fp(s2)); // y
                else if ((tmp = strstr(s2, "#")) != NULL)
                    sprintf(ttmp, "li %s, %s\n", regs[0], tmp + 1);
                strcat(mm, ttmp);
                sprintf(mm, "li %s, %d\n", regs[1], s3 + 1); // #1
                strcat(mm, ttmp);
                sprintf(ttmp, "div %s, %s\nmflo", regs[0], regs[1], regs[0]); // y/#1
                strcat(mm, ttmp);
                sprintf(ttmp, "sw %s, %d($fp)\n", regs[0], find_var_offset_2_fp(s1));
                strcat(mm, ttmp);
            }
        }
        else if ((tmp = strstr(mid_code_array[i], ":=")) != NULL && tmp[3] == '*')
        {                   // x := *y
            char *s1 = tmp; // x
            tmp[0] = '\0';
            char *s2 = tmp + 4;
            char *ttmp = (char *)malloc(sizeof(char) * 128);                      // y
            sprintf(ttmp, "lw %s, %d($fp)\n", regs[1], find_var_offset_2_fp(s2)); // y
            strcat(mm, ttmp);
            sprintf(ttmp, "lw %s, 0(%s)", regs[0], regs[1]);
            strcat(mm, ttmp);
            sprintf(ttmp, "sw %s, %d($fp)\n", regs[0], find_var_offset_2_fp(s1));
            strcat(mm, ttmp);
        }
        else if ((tmp = strstr(mid_code_array[i], ":=")) != NULL && mid_code_array[i][0] == '*')
        { // *x := y
            char *s1 = mid_code_array[i] + 1;
            tmp[0] = '\0';
            char *s2 = tmp + 3; // y
            char *ttmp = (char *)malloc(sizeof(char) * 128);
            sprintf(ttmp, "lw %s, %d($fp)\n", regs[0], find_var_offset_2_fp(s1)); // x
            strcat(mm, ttmp);
            sprintf(ttmp, "lw %s, %d($fp)\n", regs[1], find_var_offset_2_fp(s2)); // y
            strcat(mm, ttmp);
            sprintf(ttmp, "sw %s, 0(%s)\n", regs[1], regs[0]);
            strcat(mm, ttmp);
        }
        else if ((tmp = strstr(mid_code_array[i], "CALL")) != NULL)
        { // x := CALL f
            char *s1 = tmp;
            tmp[-4] = '\0';
            char *s2 = tmp + 5;
            char *ttmp = (char *)malloc(sizeof(char) * 128);
            sprintf(ttmp, "lw %s, %d($fp)\n", regs[0], find_var_offset_2_fp(s1)); // x
            strcat(mm, ttmp);
            sprintf(ttmp, "jal %s\nmove %s, $v0\n", s2, regs[0]);
            strcat(mm, ttmp);
        }
        else if ((tmp = strstr(mid_code_array[i], "RETURN")) != NULL)
        {                       // RETURN x
            char *s1 = tmp + 7; // x
            char *ttmp = (char *)malloc(sizeof(char) * 128);
            sprintf(ttmp, "lw %s, %d($fp)\n", regs[0], find_var_offset_2_fp(s1)); // x
            strcat(mm, ttmp);
            sprintf(ttmp, "move $v0, %s\njr $ra\n", regs[0]);
            strcat(mm, ttmp);
        }
        else if ((tmp = strstr(mid_code_array[i], "IF")) != NULL && (tmp = strstr(mid_code_array[i], "GOTO")) != NULL)
        { // IF x relop y GOTO z, relop -> == | != | > | < | >= | <=
            char *b_code[] = {"beq", "bne", "bgt", "blt", "bge", "ble"};
            int label;
            if (strstr(mid_code_array[i], "==") != NULL)
            {
                label = 0;
            }
            else if (strstr(mid_code_array[i], "!=") != NULL)
            {
                label = 1;
            }
            else if (strstr(mid_code_array[i], ">=") != NULL)
            {
                label = 4;
            }
            else if (strstr(mid_code_array[i], "<=") != NULL)
            {
                label = 5;
            }
            else if (strstr(mid_code_array[i], ">") != NULL)
            {
                label = 2;
            }
            else if (strstr(mid_code_array[i], "<") != NULL)
            {
                label = 3;
            }
            char *s1 = mid_code_array[i] + 3;
            char *s2 = s1;
            while (*s2 != ' ')
                s2++;
            *s2 = '\0';
            s2 += 2;
            while (*s2 != ' ')
                s2++;
            s2++;
            tmp[-1] = '\0';
            char *s3 = tmp + 5;
            char *ttmp = (char *)malloc(sizeof(char) * 128);
            if (*s1 == '#')
            {
                sprintf(ttmp, "li %s, %s\n", regs[0], s1 + 1);
                strcat(mm, ttmp);
            }
            else
            {
                sprintf(ttmp, "lw %s, %d($fp)\n", regs[1], find_var_offset_2_fp(s1));
                strcat(mm, ttmp);
            }
            if (*s2 == '#')
            {
                sprintf(ttmp, "li %s, %s\n", regs[0], s2 + 1);
                strcat(mm, ttmp);
            }
            else
            {
                sprintf(ttmp, "lw %s, %d($fp)\n", regs[1], find_var_offset_2_fp(s2));
                strcat(mm, ttmp);
            }
            sprintf(ttmp, "%s %s, %s, %s\n", b_code[label], regs[0], regs[1], s3);
            strcat(mm, ttmp);
        }
        else
        {
            strcat(mm, "To be translate: ");
            strcat(mm, mid_code_array[i]);
        }
        strcat(mm, "\n\n");
        printf(mm);
        strcat(mips_code, mm);
    }
    //printf(mips_code);
}