#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bison.h"
#include "errortype.h"

static const char *read_mips = "read:\nli $v0, 4\nla $a0, _prompt\nsyscall\nli $v0, 5\nsyscall\njr $ra\n";
static const char *write_mips = "write:\nli $v0, 1\nsyscall\nli $v0, 4\nla $a0, _ret\nsyscall\nmove $v0, $0\njr $ra\n";

extern char *mid_code;
static char *mid_code_array[10000];

static void mid_code_2_array()
{
    int cc = 0;
    mid_code_array[cc++] = mid_code;
    int len = strlen(mid_code);
    for (int i = 0; i < len; i++)
    {
        if (mid_code[i] == '\n')
        {
            mid_code[i] = '\0';
            mid_code_array[cc++] = mid_code[i + 1];
        }
    }
}

void gen_target_code()
{
    mid_code_2_array();
}