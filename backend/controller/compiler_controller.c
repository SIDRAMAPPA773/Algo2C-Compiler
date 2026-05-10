#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../models/ast_model.h"

struct ASTNode* create_node(const char* type_name, struct ASTNode* left, struct ASTNode* right) {
    struct ASTNode* node = (struct ASTNode*)malloc(sizeof(struct ASTNode));
    strcpy(node->type_name, type_name);
    node->node_type = NODE_INTERNAL;
    node->left = left;
    node->right = right;
    return node;
}

struct ASTNode* create_leaf_str(const char* type_name, const char* val) {
    struct ASTNode* node = (struct ASTNode*)malloc(sizeof(struct ASTNode));
    strcpy(node->type_name, type_name);
    node->node_type = NODE_LEAF_STR;
    strcpy(node->str_val, val);
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct ASTNode* create_leaf_num(const char* type_name, int val) {
    struct ASTNode* node = (struct ASTNode*)malloc(sizeof(struct ASTNode));
    strcpy(node->type_name, type_name);
    node->node_type = NODE_LEAF_NUM;
    node->num_val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}
