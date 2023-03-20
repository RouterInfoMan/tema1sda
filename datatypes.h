#pragma once

struct dll_list {
    char info;
    struct dll_list *prev, *next;
};
typedef struct dll_list TDLL_LIST;

struct ll_list {
    char *info;
    struct ll_list *next;
};
typedef struct ll_list TLL_LIST;

struct QUEUE{
    TLL_LIST *front, *back;
};
typedef struct QUEUE TQUEUE;

struct STACK{
    TLL_LIST *TOP;
}
typedef struct STACK TSTACK;