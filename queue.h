#ifndef QUEUE_H
#define QUEUE_H

#include "task.h"

typedef struct QueueNode {
    Task task;
    struct QueueNode *next;
} QueueNode;


typedef struct {
    QueueNode *front;
    QueueNode *rear;
    int size;
} TaskQueue;

typedef struct StackNode {
    Task task;
    struct StackNode *next;
} StackNode;


typedef struct {
    StackNode *top;
    int size;
} UndoStack;

extern TaskQueue assemblyQueue;
extern UndoStack undoStack;

void enqueue(Task task);
Task dequeue(void);
void displayQueue(void);
void freeQueue(TaskQueue *queue);

void pushUndo(Task task);
Task popUndo(void);
void freeStack(UndoStack *stack);

#endif

