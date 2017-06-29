#ifndef VECTOR_H
#define VECTOR_H

#define VECTOR_INIT_CAPACITY 4

typedef struct Vector {
    void **items;
    int capacity;
    int total;
} Vector;

void vector_init(Vector *);
int vector_total(Vector *);
static void vector_resize(Vector *, int);
void vector_add(Vector *, void *);
void vector_set(Vector *, int, void *);
void *vector_get(Vector *, int);
void vector_delete(Vector *, int);
void vector_free(Vector *);

#endif