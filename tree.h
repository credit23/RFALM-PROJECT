#ifndef TREE_H
#define TREE_H

#include <stdlib.h>
#include "robot.h"

typedef struct TreeNode {
    char zoneName[50];
    struct TreeNode **children;
    int childCount;
} TreeNode;

typedef struct BSTNode {
    Robot robot;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

TreeNode *createFactoryTree(void);

TreeNode *createNode(const char *name);

void addChild(TreeNode *parent, TreeNode *child);

void displayFactoryTree(const TreeNode *node, int depth);

void freeFactoryTree(TreeNode *node);

BSTNode *insertRobotBST(BSTNode *root, Robot robot);

BSTNode *searchRobotBST(BSTNode *root, int id);

void inorderTraversalBST(const BSTNode *root);

void freeRobotBST(BSTNode *root);

#endif 