#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char num = 0;

#define MAX_STACK_SIZE 101

typedef int element;
typedef struct
{
    element stack[MAX_STACK_SIZE];
    int top;
} StackType;

void init(StackType* s)
{
    memset(s->stack, 0, sizeof(int) * MAX_STACK_SIZE);
    s->top = -1;
}

int is_empty(StackType* s)
{
    return (s->top == -1);
}

int is_full(StackType* s)
{
    return (s->top == (MAX_STACK_SIZE - 1));
}

void push(StackType* s, element item)   // 삽입함수
{
    if (is_full(s))
    {
        fprintf(stderr, "스택 포화 에러\n");
        return;
    }
    else
        s->stack[++(s->top)] = item;
}

char pop(StackType* s)
{
    if (is_empty(s))
    {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else
        return s->stack[(s->top)--];
}

element evalPrefix(FILE* file, StackType* s, char num)
{
    push(s, num);

    if (s->stack[(s->top)] != '+' && s->stack[(s->top)] != '-' && s->stack[(s->top)] != '*' && s->stack[(s->top)] != '/')
    {
        if (s->stack[(s->top) - 1] != '+' && s->stack[(s->top) - 1] != '-' && s->stack[(s->top) - 1] != '*' && s->stack[(s->top) - 1] != '/')
        {
            if (s->stack[(s->top) - 2] == '+' || s->stack[(s->top) - 2] == '-' || s->stack[(s->top) - 2] == '*' || s->stack[(s->top) - 2] == '/')
            {
                int a = pop(s);
                int b = pop(s);
                char c = pop(s);
                int d = b + a;
                int e = b - a;
                int f = b * a;
                int g = b / a;

                switch (c)
                {
                case '+': 
                    push(s, d + '0');
                    break;
                case '-':
                    push(s, e + '0');
                    break;
                case '*': 
                    push(s, f + '0');
                    break;
                case '/': 
                    push(s, g + '0');
                    break;
                }
            }
        }
    }

    printf("after cal top is %c\n", s->stack[s->top]);
}

int main(void)
{
    StackType *s = (StackType*)malloc(sizeof(StackType));
    FILE* fp, * fp2;
    int n = 0;

    fp = fopen("prefix.in", "r");
    fp2 = fopen("prefix.out", "w");

    if (fp == NULL)
    {
        printf("file open fail\n");
        exit(0);
    }

    fscanf(fp, "%d", &n);
    fprintf(fp2, "%d\n", n);
    fgetc(fp);

    for (int i = 0; i < n; i++)
    {
        init(s);
        while (fscanf(fp, "%c", &num) != EOF)
        {
            evalPrefix(fp2, s, num);
            if (fgetc(fp) == '\n')
                break;
        }
        fprintf(fp2, "%c\n", s->stack[s->top]);
    }

    fclose(fp);
    fclose(fp2);

    return 0;
}