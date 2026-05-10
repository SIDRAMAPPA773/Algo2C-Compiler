#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include "../models/symbol_model.h"

void init_symbol_table();
void declare_variable(const char* name, int line, const char* type);
const char* check_variable(const char* name, int line);
void print_symbol_table();

extern int semantic_errors;

#endif
