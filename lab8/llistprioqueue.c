#include "ADTs/llistprioqueue.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct pqnode {
    struct pqnode *next;
    void *priority;
    void *value;
} PQNode;

typedef struct pq_data {
    int (*cmp)(void *p1, void *p2);
    long size;
    PQNode *head;
    PQNode *tail;
    void (*freePrio)(void *p);
    void (*freeValue)(void *v);
} PqData;

/*
 * traverses the list, calling freeP on each priority and freeV on each entry
 */
static void purge(PqData *pqd, void (*freeP)(void *p), void (*freeV)(void *e)) {
    if (freeP != NULL) {
        PQNode *p;

        for (p = pqd->head; p != NULL; p = p->next)
            (*freeP)(p->priority);
    }
    if (freeV != NULL) {
        PQNode *p;

        for (p = pqd->head; p != NULL; p = p->next)
            (*freeV)(p->value);
    }
}

/*
 * traverses the list, freeing nodes in the list
 */
static void freeList(PqData *pqd) {
    PQNode *p, *q = NULL;

    for (p = pqd->head; p != NULL; p = q) {
        q = p->next;
        free(p);
    }
}

static void pq_destroy(const PrioQueue *pq) {
    PqData *pqd = (PqData *)pq->self;
    purge(pqd, pqd->freePrio, pqd->freeValue);
    freeList(pqd);
    free(pqd);
    free((void *)pq);
}

//we did this 1st
static void pq_clear(const PrioQueue *pq) {
    PqData *pqd = (PqData *)pq->self;
    purge(pqd, pqd->freePrio, pqd->freeValue);
    freeList(pqd);
    pqd->head = pqd->tail = NULL;
    pqd->size = 0L;
}

//Did this 7th
static bool pq_insert(const PrioQueue *pq, void *priority, void *value) {
    PqData *pqd = (PqData *)pq->self;
    printf("insert called.\n");
    PQNode *new = (PQNode *)malloc(sizeof(PQNode));
    bool status = (new != NULL);
    if (status) {
        PQNode *prev, *next = NULL;
        new->next = NULL;
        new->priority = priority;
        new->value = value;

        for (next = pqd->head; next != NULL; prev = next, next = next->next) {
            if (pqd->cmp(priority, next->priority) < 0)
                break;
            if (prev == NULL) {
                if (next == NULL) {
                    pqd->head = new;
                    pqd->tail = new;
                } else {
                    new->next = pqd->head;
                    pqd->head = new;
                }
            } else {
                if (next == NULL) {
                    prev->next = new;
                    pqd->tail = new;
                } else {
                    new->next = next;
                    prev->next = new;
                }
            }
            pqd->size++;
        }
    }
    return status;
}

//we did this 2nd
static bool pq_min(const PrioQueue *pq, void **value) {
    PqData *pqd = (PqData *)pq->self;
    printf("min called.\n");
    bool status = (pqd->size > 0L);
    if (status) {
        *value = pqd->head->value;
    }
    return status;
}

//we did this 3rd
static bool pq_removeMin(const PrioQueue *pq, void **priority, void **value) {
    PqData *pqd = (PqData *)pq->self;
    bool status = (pqd->size > 0L);
    printf("removeMin called.\n");
    if (status) {
        PQNode *p = pqd->head->value;
        if ((pqd->head = p->next) == NULL) {
            pqd->tail = NULL;
        }
        *priority = p->priority;
        *value = p->value;
        pqd->size--;
        free(p);
    }
    return status;
}

static long pq_size(const PrioQueue *pq) {
    PqData *pqd = (PqData *)pq->self;
    return pqd->size;
}

static bool pq_isEmpty(const PrioQueue *pq) {
    PqData *pqd = (PqData *)pq->self;
    return (pqd->size == 0L);
}

/*
 * helper function to generate array of void *'s for toArray and itCreate
 */
//did this 4th
static void **genArray(PqData *pqd) {
    void **arr = NULL;
    if (pqd->size > 0L) {
        arr = (void**)malloc(pqd->size*sizeof(void*));
        if (arr != NULL) {
            long i = 0L;
            PQNode *p;
            for (p = pqd->head; p != NULL; p = p->next) {
                arr[i++] = p->value;
            }
        }
    }
    return arr;
}

//Did this 5th
static void **pq_toArray(const PrioQueue *pq, long *len) {
    PqData *pqd = (PqData *)pq->self;
    void **tmp = genArray(pqd);
    if (tmp != NULL) {
        *len = pqd->size;
    }
    return tmp;
}

//Did this 6th
static const Iterator *pq_itCreate(const PrioQueue *pq) {
    PqData *pqd = (PqData *)pq->self;
    const Iterator *it = NULL;
    void **tmp = genArray(pqd);
    if (tmp != NULL) {
        it = Iterator_create(pqd->size, tmp);
        if (it == NULL) {
            free(tmp);
        }
    }
    return it;
}

#define UNUSED __attribute__((unused))
extern void doNothing(UNUSED void *x) {
}

static const PrioQueue *pq_create(const PrioQueue *pq);

static PrioQueue template = {
    NULL, pq_create, pq_destroy, pq_clear, pq_insert, pq_min, pq_removeMin,
    pq_size, pq_isEmpty, pq_toArray, pq_itCreate
};

/*
 * helper function to create a new Priority Queue dispatch table
 */
static const PrioQueue *newPrioQueue(int (*cmp)(void*,void*),
                                     void (*freeP)(void*),
                                     void (*freeV)(void*)) {
    PrioQueue *pq = (PrioQueue *)malloc(sizeof(PrioQueue));

    if (pq != NULL) {
        PqData *pqd = (PqData *)malloc(sizeof(PqData));

        if (pqd != NULL) {
            pqd->cmp = cmp;
            pqd->size = 0L;
            pqd->head = NULL;
            pqd->tail = NULL;
            pqd->freePrio = freeP;
            pqd->freeValue = freeV;
            *pq = template;
            pq->self = pqd;
        } else {
            free(pq);
            pq = NULL;
        }
    }
    return pq;
}

static const PrioQueue *pq_create(const PrioQueue *pq) {
    PqData *pqd = (PqData *)pq->self;

    return newPrioQueue(pqd->cmp, pqd->freePrio, pqd->freeValue);
}

const PrioQueue *LListPrioQueue(int (*cmp)(void *p1, void *p2),
                                void (*freePrio)(void *prio),
                                void (*freeValue)(void *value)) {
    return newPrioQueue(cmp, freePrio, freeValue);
}

const PrioQueue *PrioQueue_create(int (*cmp)(void *p1, void *p2),
                                  void (*freePrio)(void *prio),
                                  void (*freeValue)(void *value)) {
    return newPrioQueue(cmp, freePrio, freeValue);
}
