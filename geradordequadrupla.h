#ifndef GERADORDEQUADRUPLA_H
#define GERADORDEQUADRUPLA_H

#include<stdio.h>
#include"global.h"


void genStmt(TreeNode *tree);

void genExp(TreeNode *tree);

void cGen(TreeNode *t);

void generateCode(TreeNode *t);

void cGen_noSibling(TreeNode *t);

void imprimirQuadruplas();

#endif

