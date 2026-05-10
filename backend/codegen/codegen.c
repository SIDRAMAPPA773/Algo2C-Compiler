#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codegen.h"
#include "../semantic/symboltable.h"

extern Symbol* symbol_table[];
#define TABLE_SIZE 100

void generate_declarations(FILE* out) {
    int first_int = 1;
    int first_str = 1;
    char int_decls[1000] = "";
    char str_decls[1000] = "";
    
    for (int i = 0; i < TABLE_SIZE; i++) {
        Symbol* current = symbol_table[i];
        while (current != NULL) {
            if (strcmp(current->type, "int") == 0) {
                if (!first_int) strcat(int_decls, ", ");
                strcat(int_decls, current->name);
                first_int = 0;
            } else if (strcmp(current->type, "string") == 0) {
                if (!first_str) strcat(str_decls, ", ");
                char buf[150];
                sprintf(buf, "%s[100]", current->name);
                strcat(str_decls, buf);
                first_str = 0;
            }
            current = current->next;
        }
    }
    if (!first_int) {
        fprintf(out, "    int %s;\n", int_decls);
    }
    if (!first_str) {
        fprintf(out, "    char %s;\n", str_decls);
    }
    if (!first_int || !first_str) {
        fprintf(out, "\n");
    }
}

void traverse_ast(struct ASTNode* node, FILE* out, int indent) {
    if (node == NULL) return;
    
    char ind_str[100] = "";
    for(int i = 0; i < indent; i++) strcat(ind_str, "    ");
    
    if (strcmp(node->type_name, "StmtList") == 0) {
        traverse_ast(node->left, out, indent);
        traverse_ast(node->right, out, indent);
    }
    else if (strcmp(node->type_name, "Read") == 0) {
        fprintf(out, "%sscanf(\"%%d\", &%s);\n", ind_str, node->left->str_val);
    }
    else if (strcmp(node->type_name, "ReadStr") == 0) {
        fprintf(out, "%sscanf(\"%%99s\", %s);\n", ind_str, node->left->str_val);
    }
    else if (strcmp(node->type_name, "Print") == 0) {
        fprintf(out, "%sprintf(\"%%d\\n\", %s);\n", ind_str, node->left->str_val);
    }
    else if (strcmp(node->type_name, "PrintStr") == 0) {
        fprintf(out, "%sprintf(\"%%s\\n\", %s);\n", ind_str, node->left->str_val);
    }
    else if (strcmp(node->type_name, "PrintStrLiteral") == 0) {
        fprintf(out, "%sprintf(\"%%s\\n\", %s);\n", ind_str, node->left->str_val);
    }
    else if (strcmp(node->type_name, "PrintExpr") == 0) {
        fprintf(out, "%sprintf(\"%%d\\n\", ", ind_str);
        traverse_ast(node->left, out, 0);
        fprintf(out, ");\n");
    }
    else if (strcmp(node->type_name, "Assign") == 0) {
        fprintf(out, "%s%s = ", ind_str, node->left->str_val);
        traverse_ast(node->right, out, 0);
        fprintf(out, ";\n");
    }
    else if (strcmp(node->type_name, "AssignStr") == 0) {
        fprintf(out, "%sstrcpy(%s, %s);\n", ind_str, node->left->str_val, node->right->str_val);
    }
    else if (strcmp(node->type_name, "If") == 0) {
        fprintf(out, "%sif(", ind_str);
        traverse_ast(node->left, out, 0);
        fprintf(out, ") {\n");
        traverse_ast(node->right, out, indent + 1);
        fprintf(out, "%s}\n", ind_str);
    }
    else if (strcmp(node->type_name, "IfElse") == 0) {
        fprintf(out, "%sif(", ind_str);
        traverse_ast(node->left, out, 0);
        fprintf(out, ") {\n");
        traverse_ast(node->right->left, out, indent + 1);
        fprintf(out, "%s}\n%selse {\n", ind_str, ind_str);
        traverse_ast(node->right->right->left, out, indent + 1);
        fprintf(out, "%s}\n", ind_str);
    }
    else if (strcmp(node->type_name, "While") == 0) {
        fprintf(out, "%swhile(", ind_str);
        traverse_ast(node->left, out, 0);
        fprintf(out, ") {\n");
        traverse_ast(node->right, out, indent + 1);
        fprintf(out, "%s}\n", ind_str);
    }
    else if (strcmp(node->type_name, "For") == 0) {
        fprintf(out, "%sfor(", ind_str);
        traverse_ast(node->left->left, out, 0);
        fprintf(out, " = ");
        traverse_ast(node->left->right, out, 0);
        fprintf(out, "; ");
        
        traverse_ast(node->left->left, out, 0);
        fprintf(out, " <= ");
        traverse_ast(node->right->left, out, 0);
        fprintf(out, "; ");
        
        traverse_ast(node->left->left, out, 0);
        fprintf(out, "++) {\n");
        
        traverse_ast(node->right->right, out, indent + 1);
        fprintf(out, "%s}\n", ind_str);
    }
    else if (strcmp(node->type_name, "+") == 0 || strcmp(node->type_name, "-") == 0 ||
             strcmp(node->type_name, "*") == 0 || strcmp(node->type_name, "/") == 0 ||
             strcmp(node->type_name, "%") == 0 || strcmp(node->type_name, ">") == 0 ||
             strcmp(node->type_name, "<") == 0 || strcmp(node->type_name, ">=") == 0 ||
             strcmp(node->type_name, "<=") == 0 || strcmp(node->type_name, "==") == 0 ||
             strcmp(node->type_name, "!=") == 0) {
        traverse_ast(node->left, out, 0);
        fprintf(out, " %s ", node->type_name);
        traverse_ast(node->right, out, 0);
    }
    else if (strcmp(node->type_name, "ID") == 0) {
        fprintf(out, "%s", node->str_val);
    }
    else if (strcmp(node->type_name, "NUM") == 0) {
        fprintf(out, "%d", node->num_val);
    }
    else if (strcmp(node->type_name, "LITERAL") == 0) {
        fprintf(out, "%s", node->str_val);
    }
}

void generate_code(struct ASTNode* root, const char* output_file) {
    FILE* out = fopen(output_file, "w");
    if (!out) {
        fprintf(stderr, "ERROR: Could not open output file %s\n", output_file);
        return;
    }
    
    fprintf(out, "#include <stdio.h>\n");
    fprintf(out, "#include <string.h>\n\n");
    fprintf(out, "int main() {\n\n");
    
    generate_declarations(out);
    
    traverse_ast(root, out, 1);
    
    fprintf(out, "\n    return 0;\n");
    fprintf(out, "}\n");
    
    fclose(out);
    printf("INFO: Successfully generated %s\n", output_file);
}
