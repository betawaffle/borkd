/* Copyright (c) 2010, Sebastian Ramadan and Andrew Hodges. All rights reserved. */

#ifndef INCLUDED_SockEventListNode_H
#define INCLUDED_SockEventListNode_H

#include "Common.h"
#include "SockEvent.h"

/**
 * 
 */     struct SockEventListNode;
typedef struct SockEventListNode *SockEventListNode;
        struct SockEventListNode {
    Destructor          Destroy; 
    SockEventListNode   Next;
    EventHandler        Handler;
};


/**
 * 
 */
SockEventListNode SockEventListNode_Create(SockEventListNode Next, EventHandler Handler);

/**
 * 
 */
void SockEventListNode_Raise(SockEventListNode Node, SockEvent Event); /* Use SockEvent_Create() to create Event. -- AH (07/08/2010) */

#endif