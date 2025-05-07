#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include "task.h"

TaskQueue assemblyQueue = {NULL, NULL, 0};
UndoStack undoStack = {NULL, 0};

void enqueue(Task task) {
    QueueNode *newNode = malloc(sizeof(QueueNode));
    if (!newNode) {
        fprintf(stderr, "Error: Memory allocation failed in enqueue()!\n");
        return;
    }
    newNode->task = task;
    newNode->next = NULL;
    if (!assemblyQueue.rear) {
        assemblyQueue.front = assemblyQueue.rear = newNode;
    } else {
        assemblyQueue.rear->next = newNode;
        assemblyQueue.rear = newNode;
    }
    assemblyQueue.size++;
    printf("Task %d queued successfully!\n", task.id);
}

Task dequeue(void) {
    Task emptyTask = {.id = -1};
    if (!assemblyQueue.front) {
        printf("Queue is empty!\n");
        return emptyTask;
    }
    QueueNode *temp = assemblyQueue.front;
    Task t = temp->task;
    assemblyQueue.front = temp->next;
    if (!assemblyQueue.front) assemblyQueue.rear = NULL;
    free(temp);
    assemblyQueue.size--;
    pushUndo(t);
    return t;
}

void displayQueue(void) {
    if (!assemblyQueue.front) {
        printf("Task Queue is empty!\n");
        return;
    }
    printf("\n=== Task Queue (%d tasks) ===\n", assemblyQueue.size);
    int pos = 1;
    for (QueueNode *cur = assemblyQueue.front; cur; cur = cur->next) {
        printf("\nPosition %d:\n", pos++);
    
    }
    printf("==============================\n");
}

void freeQueue(TaskQueue *queue) {
    QueueNode *cur = queue->front;
    while (cur) {
        QueueNode *next = cur->next;
        free(cur);
        cur = next;
    }
    queue->front = queue->rear = NULL;
    queue->size = 0;
    printf("Queue memory freed!\n");
}

void pushUndo(Task task) {
    StackNode *newNode = malloc(sizeof(StackNode));
    if (!newNode) {
        fprintf(stderr, "Error: Memory allocation failed in pushUndo()!\n");
        return;
    }
    newNode->task = task;
    newNode->next = undoStack.top;
    undoStack.top = newNode;
    undoStack.size++;
}

Task popUndo(void) {
    Task emptyTask = {.id = -1};
    if (!undoStack.top) {
        printf("Undo stack is empty!\n");
        return emptyTask;
    }
    StackNode *temp = undoStack.top;
    Task t = temp->task;
    undoStack.top = temp->next;
    free(temp);
    undoStack.size--;
    return t;
}

void freeStack(UndoStack *stack) {
    StackNode *cur = stack->top;
    while (cur) {
        StackNode *next = cur->next;
        free(cur);
        cur = next;
    }
    stack->top = NULL;
    stack->size = 0;
    printf("Undo stack memory freed!\n");
}
