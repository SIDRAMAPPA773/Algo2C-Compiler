#ifndef AST_MODEL_H
#define AST_MODEL_H

typedef enum {
    NODE_INTERNAL,
    NODE_LEAF_STR,
    NODE_LEAF_NUM
} NodeType;

struct ASTNode {
    char type_name[50];
    NodeType node_type;
    struct ASTNode* left;
    struct ASTNode* right;
    char str_val[100];
    int num_val;
};

struct ASTNode* create_node(const char* type_name, struct ASTNode* left, struct ASTNode* right);
struct ASTNode* create_leaf_str(const char* type_name, const char* val);
struct ASTNode* create_leaf_num(const char* type_name, int val);

#endif
