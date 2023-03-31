#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct dll_list {
    char info;
    struct dll_list *prev, *next;
} TDLL_LIST;

typedef struct ll_list_char {
    char *info;
    struct ll_list_char *next;
} TLL_LIST_CHAR;
typedef struct ll_list_dll {
    TDLL_LIST *info;
    struct ll_list_dll *next;
} TLL_LIST_DLL;

typedef struct QUEUE {
    TLL_LIST_CHAR *front, *back;
} TQUEUE;

typedef struct STACK {
    TLL_LIST_DLL *top;
} TSTACK;

typedef struct MAGIC_BAND {
    TDLL_LIST *santinela, *deget;
} TMAGIC_BAND;

void RUN();
