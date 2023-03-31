/* ROTARU RĂZVAN-ANDREI - 315CBa*/
#include "datatypes.h"

char *strdup_sda(char *src) {
    size_t len = strlen(src);
    char *out = (char *) malloc(len + 1);
    strcpy(out, src);
    out[len] = '\0';
    return out;
}  // strdup home made

TLL_LIST_CHAR *alloc_TLL_LIST_CHAR(char *str) {
    TLL_LIST_CHAR *new = (TLL_LIST_CHAR *)malloc(sizeof(TLL_LIST_CHAR));
    if (new == NULL) {
        printf()"Eroare alocare\n");
        exit(1);
    }
    new->info = strdup_sda(str);
    new->next = NULL;
    return new;
}
TLL_LIST_DLL *alloc_TLL_LIST_DLL(TDLL_LIST *deget) {
    TLL_LIST_DLL *new = (TLL_LIST_DLL *)malloc(sizeof(TLL_LIST_DLL));
    if (new == NULL) {
        printf("Eroare alocare\n");
        exit(1);
    }
    new->info = deget;
    new->next = NULL;
    return new;
}

TQUEUE* TQUEUE_INIT() {
    TQUEUE *q = malloc(sizeof(TQUEUE));
    q->front = q->back = NULL;
    return q;
}
void TQUEUE_PUSH(TQUEUE *q, char *info) {
    if (!q->front) {
        TLL_LIST_CHAR *new = alloc_TLL_LIST_CHAR(info);
        q->front = q->back = new;
        return;
    }
    TLL_LIST_CHAR *new = alloc_TLL_LIST_CHAR(info);
    q->back->next = new;
    q->back = new;
}
char *TQUEUE_POP(TQUEUE *q) {
    if (!q->front) {
        return NULL;
    }
    TLL_LIST_CHAR *out = q->front;
    q->front = q->front->next;
    out->next = NULL;
    if (!q->front) {
        q->back = q->front;
    }
    char *p = out->info;
    free(out);
    return p;
}
void TQUEUE_DELETE(TQUEUE **q) {
    while ((*q)->front) {
        TLL_LIST_CHAR *aux = (*q)->front;
        (*q)->front = (*q)->front->next;
        free(aux->info);
        free(aux);
    }
    free(*q);
    *q = NULL;
}

TSTACK* TSTACK_INIT() {
    TSTACK *s = malloc(sizeof(TSTACK));
    s->top = NULL;
    return s;
}
void TSTACK_PUSH(TSTACK *s, TDLL_LIST *deget) {
    TLL_LIST_DLL *new = alloc_TLL_LIST_DLL(deget);
    new->next = s->top;
    s->top = new;
}
TDLL_LIST *TSTACK_POP(TSTACK *s) {
    if (!s->top) {
        return NULL;
    }
    TLL_LIST_DLL *aux = s->top;
    s->top = s->top->next;
    aux->next = NULL;
    TDLL_LIST *p = aux->info;
    free(aux);
    return p;
}
void TSTACK_DELETE(TSTACK **s) {
    while ((*s)->top) {
        TLL_LIST_DLL *aux = (*s)->top;
        (*s)->top = (*s)->top->next;
        free(aux);
    }
    free(*s);
    *s = NULL;
}

TDLL_LIST *alloc_TDLL_LIST(char info) {
    TDLL_LIST *dll = malloc(sizeof(TDLL_LIST));
    dll->info = info;
    dll->next = dll->prev = NULL;
    return dll;
}
TDLL_LIST *TDLL_LIST_INIT() {
    TDLL_LIST *santinela = alloc_TDLL_LIST('\0');
    return santinela;
}
TDLL_LIST *LINK_RIGHT(TDLL_LIST *list, char info) {
    TDLL_LIST *next = alloc_TDLL_LIST(info);
    list->next = next;
    next->prev = list;
    return next;
}

TMAGIC_BAND *TMAGIC_BAND_INIT() {
    TMAGIC_BAND * magic = malloc(sizeof(TMAGIC_BAND));
    magic->santinela = TDLL_LIST_INIT();
    magic->deget = LINK_RIGHT(magic->santinela, '#');
    return magic;
}
void TMAGIC_BAND_DELETE(TMAGIC_BAND **banda) {
    TDLL_LIST *aux;
    while ((*banda)->santinela) {
        aux = (*banda)->santinela;
        (*banda)->santinela = (*banda)->santinela->next;
        free(aux);
    }
    free(*banda);
    *banda = NULL;
}
void MOVE_RIGHT(TMAGIC_BAND *banda) {
    if (banda->deget->next == NULL) {
        TDLL_LIST *new = alloc_TDLL_LIST('#');
        new->prev = banda->deget;
        banda->deget->next = new;
        banda->deget = new;
    } else {
        banda->deget = banda->deget->next;
    }
}
int MOVE_LEFT(TMAGIC_BAND *banda) {
    if (banda->deget->prev != banda->santinela) {
        banda->deget = banda->deget->prev;
        return 1;
    }
    return 0;
}
int MOVE_RIGHT_CHAR(TMAGIC_BAND *banda, char ref) {
    TDLL_LIST *it = banda->deget;
    if (it->info == ref) {
        return 1;
    }
    while (it->next) {
        if (it->next->info == ref) {
            banda->deget = it->next;
            return 1;
        }
        it = it->next;
    }
    TDLL_LIST *new = alloc_TDLL_LIST('#');
    it->next = new;
    new->prev = it;
    banda->deget = new;
    return 0;
}
int MOVE_LEFT_CHAR(TMAGIC_BAND *banda, char ref) {
    TDLL_LIST *it = banda->deget;
    while (it != banda->santinela) {
        if (it->info == ref) {
            banda->deget = it;
            return 1;
        }
        it = it->prev;
    }
    return 0;
}
void WRITE(TMAGIC_BAND *banda, char src) {
    banda->deget->info = src;
}
int INSERT_LEFT(TMAGIC_BAND *banda, char src) {
    if (banda->deget->prev == banda->santinela) {
        return 0;
    }
    TDLL_LIST *new = alloc_TDLL_LIST(src);
    new->next = banda->deget;
    new->prev = banda->deget->prev;
    banda->deget->prev->next = new;
    banda->deget->prev = new;
    banda->deget = new;
    return 1;
}
int INSERT_RIGHT(TMAGIC_BAND *banda, char src) {
    TDLL_LIST *new = alloc_TDLL_LIST(src);
    new->next = banda->deget->next;
    new->prev = banda->deget;
    if (banda->deget->next)
        banda->deget->next->prev = new;
    banda->deget->next = new;
    banda->deget = new;
    return 1;
}
void SHOW_CURRENT(TMAGIC_BAND *banda) {
    printf("%c\n", banda->deget->info);
}
void SHOW(TMAGIC_BAND *banda) {
    TDLL_LIST *it = banda->santinela->next;
    while (it) {
        if (it == banda->deget) {
            printf("|%c|", it->info);
        } else {
            printf("%c", it->info);
        }
        it = it->next;
    }
    printf("\n");
}
void UNDO(TMAGIC_BAND *banda, TSTACK *undo_stack, TSTACK *redo_stack) {
    TSTACK_PUSH(redo_stack, banda->deget);
    // SHOW(banda);
    banda->deget = TSTACK_POP(undo_stack);
}
void REDO(TMAGIC_BAND *banda, TSTACK *undo_stack, TSTACK *redo_stack) {
    TSTACK_PUSH(undo_stack, banda->deget);
    banda->deget = TSTACK_POP(redo_stack);
}
void EXECUTE(TMAGIC_BAND *banda, TQUEUE *queue,
            TSTACK *undo_stack, TSTACK *redo_stack) {
    char *cmd = TQUEUE_POP(queue);
    char *p = strtok(cmd, " ");  //  Luam comanda
    char *p2 = strtok(NULL, " ");  //  Argumentul comenzii
    if (strcmp(p, "MOVE_LEFT") == 0) {
        TDLL_LIST *deget_tmp = banda->deget;
        //  In caz ca esueaza sa nu mai adaugam in stiva
        if (MOVE_LEFT(banda)) {
            TSTACK_PUSH(undo_stack, deget_tmp);
        }
    } else if (strcmp(p, "MOVE_RIGHT") == 0) {
        TSTACK_PUSH(undo_stack, banda->deget);
        MOVE_RIGHT(banda);
    } else if (strcmp(p, "MOVE_LEFT_CHAR") == 0) {
        TDLL_LIST *tmp_deget = banda->deget;
        if (MOVE_LEFT_CHAR(banda, *p2)) {
            TSTACK_PUSH(undo_stack, tmp_deget);
        } else {
            printf("ERROR\n");
        }
    } else if (strcmp(p, "MOVE_RIGHT_CHAR") == 0) {
        TSTACK_PUSH(undo_stack, banda->deget);
        MOVE_RIGHT_CHAR(banda, *p2);
    } else if (strcmp(p, "WRITE") == 0) {
        WRITE(banda, *p2);
    } else if (strcmp(p, "INSERT_LEFT") == 0) {
        if (!INSERT_LEFT(banda, *p2)) {
            printf("ERROR\n");
        }
    } else if (strcmp(p, "INSERT_RIGHT") == 0) {
        INSERT_RIGHT(banda, *p2);
    }
    free(cmd);
}
void RUN() {
    TMAGIC_BAND *banda = TMAGIC_BAND_INIT();
    TQUEUE *queue = TQUEUE_INIT();
    TSTACK *undo_stack = TSTACK_INIT(), *redo_stack = TSTACK_INIT();

    freopen("tema1.in", "r", stdin);
    freopen("tema1.out", "w", stdout);

    int n, i;
    char buf[256];

    scanf("%d", &n);
    getchar();

    for (i = 0; i < n; i++) {
        fgets(buf, 256, stdin);

        if (buf[strlen(buf)-1] == '\n')
            buf[strlen(buf)-1] = '\0';   //  Scoatem \n

        if (strstr(buf, "MOVE_")) {
            TQUEUE_PUSH(queue, buf);
        } else if (strstr(buf, "WRITE")) {
            TQUEUE_PUSH(queue, buf);
        } else if (strstr(buf, "INSERT_")) {
            TQUEUE_PUSH(queue, buf);
        } else if (strcmp(buf, "SHOW") == 0) {
            SHOW(banda);
        } else if (strcmp(buf, "SHOW_CURRENT") == 0) {
            SHOW_CURRENT(banda);
        } else if (strcmp(buf, "UNDO") == 0) {
            UNDO(banda, undo_stack, redo_stack);
        } else if (strcmp(buf, "REDO") == 0) {
            REDO(banda, undo_stack, redo_stack);
        } else if (strcmp(buf, "EXECUTE") == 0) {
            EXECUTE(banda, queue, undo_stack, redo_stack);
        }
    }
    //  Dezalocari
    TMAGIC_BAND_DELETE(&banda);
    TQUEUE_DELETE(&queue);
    TSTACK_DELETE(&undo_stack);
    TSTACK_DELETE(&redo_stack);
}

