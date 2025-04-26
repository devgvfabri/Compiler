#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"global.h"
#include"util.h"

char* generateCode(TreeNode *t) {
    if (t == NULL) return NULL;

    // Pós-ordem nos filhos
    char *left = generateCode(t->child[0]);
    char *right = generateCode(t->child[1]);
    char *extra = generateCode(t->child[2]);

    char *result = NULL;

    switch (t->kind) {
        case ConstK: {
            
            break;
        }
        case IdK: {
            break;
        }
        case OpK: {
            
            break;
        }
        case AtrK: {
           
            break;
        }
        case CallK: {
            
            break;
        }
        case IfK: {
            
            break;
        }
        default:
            break;
    }

    generateCode(t->sibling); // percorre irmãos
    return result;
}
