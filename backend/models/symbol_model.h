#ifndef SYMBOL_MODEL_H
#define SYMBOL_MODEL_H

typedef struct Symbol {
    char name[100];
    char type[50];
    int line_declared;
    struct Symbol* next;
} Symbol;

#endif
