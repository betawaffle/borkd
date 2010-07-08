/* Copyright (c) 2010, Sebastian Ramadan and Andrew Hodges. All rights reserved. */

#ifndef INCLUDED_ThreadBase_H
#define INCLUDED_ThreadBase_H

#include "ThreadPool.h"

/**
 * 
 */     struct ThreadBase;
typedef struct ThreadBase *ThreadBase;

struct ThreadBase {
    pthread_t Thread;
    pthread_attr_t Attributes;
    
    void (*Start)(void *);
};

typedef enum {
    ThreadJoinable,
    ThreadDetached
} ThreadDetachState;

struct ThreadStack {
    void  *StackAddr;
    size_t StackSize;
}

#endif
