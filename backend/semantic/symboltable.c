#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symboltable.h"

#define TABLE_SIZE 100

Symbol* symbol_table[TABLE_SIZE];
int semantic_errors = 0;

unsigned int hash(const char* name) {
    unsigned int hash_val = 0;
    for (; *name != '\0'; name++) hash_val = *name + (hash_val << 5) - hash_val;
    return hash_val % TABLE_SIZE;
}

void init_symbol_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        symbol_table[i] = NULL;
    }
}

void declare_variable(const char* name, int line, const char* type) {
    unsigned int index = hash(name);
    Symbol* current = symbol_table[index];
    
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return; // Already declared, automatic declaration tracking allows this
        }
        current = current->next;
    }
    
    Symbol* new_sym = (Symbol*)malloc(sizeof(Symbol));
    strcpy(new_sym->name, name);
    strcpy(new_sym->type, type);
    new_sym->line_declared = line;
    new_sym->next = symbol_table[index];
    symbol_table[index] = new_sym;
    
    printf("SYMBOL: Declared %s of type %s at line %d\n", name, type, line);
}

const char* check_variable(const char* name, int line) {
    unsigned int index = hash(name);
    Symbol* current = symbol_table[index];
    
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current->type; // Found
        }
        current = current->next;
    }
    
    fprintf(stderr, "ERROR: Semantic Error at line %d: Undeclared variable '%s'\n", line, name);
    semantic_errors++;
    return "int";
}

void print_symbol_table() {
    printf("\n--- Symbol Table ---\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        Symbol* current = symbol_table[i];
        while (current != NULL) {
            printf("Name: %s | Type: %s | Line: %d\n", current->name, current->type, current->line_declared);
            current = current->next;
        }
    }
    printf("--------------------\n");
}
