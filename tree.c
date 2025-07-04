#include "tree.h"
#include "robot.h"
#include "task.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

TreeNode* createFactoryTree(void) {
    TreeNode* root = createNode("Factory");

    TreeNode* taskZone = createNode("Task Zone");
    TreeNode* robotZone = createNode("Robot Zone");
    TreeNode* statusCheck = createNode("Status Check");
    TreeNode* completedZone = createNode("Completed Zone");

    TreeNode* robot1 = createNode("Robot 1");
    TreeNode* robot2 = createNode("Robot 2");

    addChild(robotZone, robot1);
    addChild(robotZone, robot2);

    addChild(root, taskZone);
    addChild(root, robotZone);
    addChild(root, statusCheck);
    addChild(root, completedZone);

    return root;
}


TreeNode* createNode(const char* name) {
    TreeNode* node = malloc(sizeof(TreeNode));
    if (!node) return NULL;
    strncpy(node->zoneName, name, sizeof(node->zoneName)-1);
    node->zoneName[sizeof(node->zoneName)-1] = '\0';
    node->children = NULL;
    node->childCount = 0;
    return node;
}

void addChild(TreeNode* parent, TreeNode* child) {
    if (!parent || !child) return;
    TreeNode** temp = realloc(parent->children,
                               (parent->childCount + 1) * sizeof(TreeNode*));
    if (!temp) return;
    parent->children = temp;
    parent->children[parent->childCount++] = child;
}

void displayFactoryTree(const TreeNode* node, int depth) {
    if (!node) return;
    for (int i = 0; i < depth; i++) printf("  ");
    printf("- %s\n", node->zoneName);
    for (int i = 0; i < node->childCount; i++) {
        displayFactoryTree(node->children[i], depth + 1);
    }
}

void freeFactoryTree(TreeNode* node) {
    if (!node) return;
    for (int i = 0; i < node->childCount; i++) {
        freeFactoryTree(node->children[i]);
    }
    free(node->children);
    free(node);
}

BSTNode* insertRobotBST(BSTNode* root, Robot robot) {
    if (!root) {
        BSTNode* newNode = malloc(sizeof(BSTNode));
        if (!newNode) return NULL;
        newNode->robot = robot;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    if (robot.id < root->robot.id) {
        root->left = insertRobotBST(root->left, robot);
    } else if (robot.id > root->robot.id) {
        root->right = insertRobotBST(root->right, robot);
    }
    return root;
}

BSTNode* searchRobotBST(BSTNode* root, int id) {
    if (!root) return NULL;
    if (id == root->robot.id) return root;
    if (id < root->robot.id)
        return searchRobotBST(root->left, id);
    return searchRobotBST(root->right, id);
}

void inorderTraversalBST(const BSTNode* root) {
    if (!root) return;
    inorderTraversalBST(root->left);
    printRobotDetails(&root->robot);
    inorderTraversalBST(root->right);
}

void freeRobotBST(BSTNode* root) {
    if (!root) return;
    freeRobotBST(root->left);
    freeRobotBST(root->right);
    free(root);
}
