#ifndef CODEGEN_H
#define CODEGEN_H

#include "../models/ast_model.h"

void generate_code(struct ASTNode* root, const char* output_file);

#endif
