%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"

int line_number = 1;
void log_token(const char* lexeme, const char* token_type) {
    printf("TOKEN: {\"lexeme\":\"%s\", \"type\":\"%s\", \"line\":%d}\n", lexeme, token_type, line_number);
}
%}

%option noyywrap

%%

"START"         { log_token(yytext, "KEYWORD"); return START; }
"END"           { log_token(yytext, "KEYWORD"); return END; }
"READ"          { log_token(yytext, "KEYWORD"); return READ; }
"READSTR"       { log_token(yytext, "KEYWORD"); return READSTR; }
"PRINT"         { log_token(yytext, "KEYWORD"); return PRINT; }
"IF"            { log_token(yytext, "KEYWORD"); return IF; }
"THEN"          { log_token(yytext, "KEYWORD"); return THEN; }
"ELSE"          { log_token(yytext, "KEYWORD"); return ELSE; }
"ENDIF"         { log_token(yytext, "KEYWORD"); return ENDIF; }
"WHILE"         { log_token(yytext, "KEYWORD"); return WHILE; }
"DO"            { log_token(yytext, "KEYWORD"); return DO; }
"ENDWHILE"      { log_token(yytext, "KEYWORD"); return ENDWHILE; }
"FOR"           { log_token(yytext, "KEYWORD"); return FOR; }
"TO"            { log_token(yytext, "KEYWORD"); return TO; }
"ENDFOR"        { log_token(yytext, "KEYWORD"); return ENDFOR; }

[0-9]+          { yylval.num = atoi(yytext); log_token(yytext, "NUMBER"); return NUMBER; }
\"[^\"]*\"      { yylval.str = strdup(yytext); log_token(yytext, "STRING_LITERAL"); return STRING_LITERAL; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.str = strdup(yytext); log_token(yytext, "IDENTIFIER"); return IDENTIFIER; }

"+"             { log_token(yytext, "OPERATOR"); return PLUS; }
"-"             { log_token(yytext, "OPERATOR"); return MINUS; }
"*"             { log_token(yytext, "OPERATOR"); return MUL; }
"/"             { log_token(yytext, "OPERATOR"); return DIV; }
"%"             { log_token(yytext, "OPERATOR"); return MOD; }
"="             { log_token(yytext, "OPERATOR"); return ASSIGN; }

">"             { log_token(yytext, "OPERATOR"); return GT; }
"<"             { log_token(yytext, "OPERATOR"); return LT; }
">="            { log_token(yytext, "OPERATOR"); return GE; }
"<="            { log_token(yytext, "OPERATOR"); return LE; }
"=="            { log_token(yytext, "OPERATOR"); return EQ; }
"!="            { log_token(yytext, "OPERATOR"); return NE; }

[ \t\r]+        { /* Ignore whitespace */ }
\n              { line_number++; }
.               { printf("ERROR: Lexical Error at line %d: Unknown character %s\n", line_number, yytext); }

%%
