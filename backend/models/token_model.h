#ifndef TOKEN_MODEL_H
#define TOKEN_MODEL_H

typedef struct {
    char lexeme[100];
    char token_type[50];
    int line_number;
} Token;

#endif
