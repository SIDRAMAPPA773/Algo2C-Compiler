#include <stdio.h>
#include <stdlib.h>
#include "semantic/symboltable.h"

extern int yyparse();
extern FILE* yyin;

int main(int argc, char** argv) {
    if (argc > 1) {
        FILE* file = fopen(argv[1], "r");
        if (!file) {
            fprintf(stderr, "ERROR: Could not open %s\n", argv[1]);
            return 1;
        }
        yyin = file;
    }
    
    // Remove old output file
    remove("output.c");

    init_symbol_table();
    
    printf("INFO: Compiler Started...\n");
    yyparse();
    
    print_symbol_table();
    
    return 0;
}
