/* Copyright (c) 2010, Sebastian Ramadan and Andrew Hodges. All rights reserved. */

#ifndef INCLUDED_ListNode_H
#define INCLUDED_ListNode_H

#include "Common.h"

/**
 * 
 */     struct ListNode;
typedef struct ListNode *ListNode;
        struct ListNode {
    Destructor Destroy; 
    EventListNode Next;
};

#endif
