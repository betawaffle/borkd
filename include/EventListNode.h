/* Copyright (c) 2010, Sebastian Ramadan and Andrew Hodges. All rights reserved. */

#ifndef INCLUDED_EventListNode_H
#define INCLUDED_EventListNode_H

/* TODO: This @brief is out of date. -- AH (07/08/2010) */
/**
 * @file EventListNode.h
 * @brief Linked list structure (EventListNode) for defining/storing Event handler functions.
 *        Function for creating/initializing EventListNode instances.
 */

#include "EventBase.h"
#include "ListNode.h"

/**
 * @struct EventListNode
 * @extends ListNode
 */
class EventListNode {
    EventListNode   *Next;
    EventHandler    Handler;
};

/**
 * 
 */
EventListNode EventListNode_Create(EventListNode Next, EventHandler Handler);

/**
 * 
 */
void EventListNode_Raise(EventListNode Node, EventBase Event);

#endif
