/* Copyright (c) 2010, Sebastian Ramadan and Andrew Hodges. All rights reserved. */
/* TODO: Rename to SockEventListNode -- Andrew Hodges (07/08/2010) */

#ifndef INCLUDED_EventListNode_H
#define INCLUDED_EventListNode_H

/* TODO: This @brief is out of date. -- AH (07/08/2010) */
/**
 * @file EventListNode.h
 * @brief Function prototype definition (Event), and linked list structure (EventListNode) for defining/storing Event handler functions.
 *        Function for creating/initializing EventListNode instances.
 */

#include "SockEvent.h"
#include "SockListNode.h"

/**
 * 
 */     struct EventListNode;
typedef struct EventListNode *EventListNode;

/* Old Functions -- Andrew Hodges (07/08/2010) */
typedef void (*Event)(SockListNode Node, unsigned char *Parsed, unsigned char *Unparsed, unsigned char *End);
EventListNode EventList_CreateNode(EventListNode Next, Event Function);
void EventListNode_Raise(SockListNode SockNode, EventListNode EventNode, unsigned char *Parsed, unsigned char *Unparsed, unsigned char *End);

#if 0
struct ListNode {
 /* struct Collection Base; *//* In theory, Trie would inherit from this too -- AH (07/08/2010) */
    Destructor Destroy;
    ListNode Next;
}

struct EventListNode {
 /* struct ListNode Base; *//* What we may want to do instead is just insert the same members as ListNode (as below) -- AH (07/08/2010) */
    Destructor Destroy; 
    EventListNode Next;
    EventHandler Handler;
}

struct SockEventListNode {
 /* struct EventListNode Base; *//* Will contain Base.Next and Handler -- AH (07/08/2010) */
    Destructor Destroy; 
    SockEventListNode Next;
    EventHandler Handler;
};

/* New Functions -- Andrew Hodges (07/08/2010) */
SockEventListNode SockEventListNode_Create(SockEventListNode Next, EventHandler Handler);
void SockEventListNode_Raise(SockEventListNode Node, SockEvent Event); /* Use SockEvent_Create() to create Event. -- AH (07/08/2010) */

/* BTW, for now, we can skip creating ListNode and EventListNode -- AH (07/08/2010) */
#endif

#endif
