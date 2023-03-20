#include "datatypes.h"

char *strdup(char *src) {
    size_t len = strlen(src);
    char *out = (char *) malloc(len + 1);
    strcpy(out, src);
    out[len] = '\0';
    return out;
}

void TQUEUE_INIT(TQUEUE *q) {
    if (!q) {
        return;
    }
    q->front = q->back = NULL;
}
void TQUEUE_PUSH(TQUEUE *q, char *info) {
    if (!q->front) {
        TLL_LIST *new = (TLL_LIST *)malloc(sizeof(TLL_LIST));
        //free 
        new->info = strdup(info);
        new->next = NULL;
        q->front = q->back = new;
        return;
    }
    TLL_LIST *new = (TLL_LIST *) malloc(sizeof(TLL_LIST));
    new->info = strdup(info);
    new->next = NULL;
    q->back->next = new;
    q->back = new;
}
char* TQUEUE_POP(TQUEUE *q) {
    TLL_LIST *out = q->front;
    q->front = q->front->next;
    out->next = NULL;
    if (!q->front) {
        q->back = q->front;
    }
    char *p = out->info;
    free(out);
    return p;
}
void TQUEUE_DELETE(TQUEUE *q) {
    while (q->front) {
        TLL_LIST *aux = q->front;
        q->front = q->front->next;
        free(aux->info);
        free(aux);
    }
    free(q);
}
void TSTACK_INIT(TSTACK *s) {
    if (!s) return;
    s->top = NULL;
}
void TSTACK_PUSH(TSTACK *s, char *info) {
    TLL_LIST *new = (TLL_LIST *) malloc(sizeof(TLL_LIST));
    new->info = strdup(info);
    new->next = s->top;
    s->top = new;
}
char *TSTACK_POP(TSTACK *s) {
    TLL_LIST *aux = s->top;
    s->top = s->top->next;
    aux->next = NULL;
    char *p = aux->info;
    free(aux);
    return p;
}