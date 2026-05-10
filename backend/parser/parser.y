%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantic/symboltable.h"
#include "codegen/codegen.h"
#include "models/ast_model.h"

extern int yylex();
extern int line_number;
void yyerror(const char *s);
%}

%union {
    int num;
    char* str;
    struct ASTNode* node;
}

%token START END READ PRINT READSTR IF THEN ELSE ENDIF WHILE DO ENDWHILE FOR TO ENDFOR
%token <str> IDENTIFIER STRING_LITERAL
%token <num> NUMBER
%token PLUS MINUS MUL DIV MOD ASSIGN GT LT GE LE EQ NE

%type <node> program statement_list statement expression condition

%left PLUS MINUS
%left MUL DIV MOD
%nonassoc GT LT GE LE EQ NE

%%

program:
    START statement_list END { 
        printf("INFO: Parsing Completed Successfully.\n"); 
        if (semantic_errors == 0) {
            generate_code($2, "output.c");
        } else {
            printf("ERROR: Compilation stopped due to semantic errors.\n");
        }
    }
    | /* empty */ { printf("ERROR: Empty program.\n"); }
    | error { printf("ERROR: Critical parsing failure.\n"); }
    ;

statement_list:
    statement { $$ = create_node("StmtList", $1, NULL); }
    | statement_list statement { $$ = create_node("StmtList", $1, $2); }
    ;

statement:
    READ IDENTIFIER { 
        declare_variable($2, line_number, "int");
        $$ = create_node("Read", create_leaf_str("ID", $2), NULL);
    }
    | READSTR IDENTIFIER {
        declare_variable($2, line_number, "string");
        $$ = create_node("ReadStr", create_leaf_str("ID", $2), NULL);
    }
    | PRINT IDENTIFIER {
        const char* type = check_variable($2, line_number);
        if (strcmp(type, "string") == 0) {
            $$ = create_node("PrintStr", create_leaf_str("ID", $2), NULL);
        } else {
            $$ = create_node("Print", create_leaf_str("ID", $2), NULL);
        }
    }
    | PRINT STRING_LITERAL {
        $$ = create_node("PrintStrLiteral", create_leaf_str("LITERAL", $2), NULL);
    }
    | PRINT expression {
        $$ = create_node("PrintExpr", $2, NULL);
    }
    | IDENTIFIER ASSIGN expression {
        declare_variable($1, line_number, "int"); // Automatic declaration tracking
        $$ = create_node("Assign", create_leaf_str("ID", $1), $3);
    }
    | IDENTIFIER ASSIGN STRING_LITERAL {
        declare_variable($1, line_number, "string");
        $$ = create_node("AssignStr", create_leaf_str("ID", $1), create_leaf_str("LITERAL", $3));
    }
    | IF condition THEN statement_list ENDIF {
        $$ = create_node("If", $2, $4);
    }
    | IF condition THEN statement_list ELSE statement_list ENDIF {
        struct ASTNode* else_node = create_node("Else", $6, NULL);
        $$ = create_node("IfElse", $2, create_node("Branch", $4, else_node));
    }
    | WHILE condition DO statement_list ENDWHILE {
        $$ = create_node("While", $2, $4);
    }
    | FOR IDENTIFIER { declare_variable($2, line_number, "int"); } ASSIGN NUMBER TO NUMBER statement_list ENDFOR {
        struct ASTNode* init = create_node("Assign", create_leaf_str("ID", $2), create_leaf_num("NUM", $5));
        struct ASTNode* limit = create_leaf_num("NUM", $7);
        $$ = create_node("For", init, create_node("ForBody", limit, $8));
    }
    ;

condition:
    expression GT expression { $$ = create_node(">", $1, $3); }
    | expression LT expression { $$ = create_node("<", $1, $3); }
    | expression GE expression { $$ = create_node(">=", $1, $3); }
    | expression LE expression { $$ = create_node("<=", $1, $3); }
    | expression EQ expression { $$ = create_node("==", $1, $3); }
    | expression NE expression { $$ = create_node("!=", $1, $3); }
    ;

expression:
    expression PLUS expression { $$ = create_node("+", $1, $3); }
    | expression MINUS expression { $$ = create_node("-", $1, $3); }
    | expression MUL expression { $$ = create_node("*", $1, $3); }
    | expression DIV expression { $$ = create_node("/", $1, $3); }
    | expression MOD expression { $$ = create_node("%", $1, $3); }
    | IDENTIFIER { 
        check_variable($1, line_number);
        $$ = create_leaf_str("ID", $1); 
    }
    | NUMBER { $$ = create_leaf_num("NUM", $1); }
    | '(' expression ')' { $$ = $2; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "ERROR: Syntax Error at line %d: %s\n", line_number, s);
}
