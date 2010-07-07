/* Copyright (c) 2010, Sebastian Ramadan and Andrew Hodges. All rights reserved. */

#ifndef INCLUDED_EventListNode_H
#define INCLUDED_EventListNode_H

/**
 * @file EventListNode.c
 * @brief Function prototype definition (Event), and linked list structure (EventListNode) for defining/storing Event handler functions.
 *        Function for creating/initializing EventListNode instances.
 */

#include "SockListNode.h"

/**
 * 
 */     struct EventListNode;
typedef struct EventListNode *EventListNode;

/**
 * 
 */
typedef void (*Event)(SockListNode Node, unsigned char *Parsed, unsigned char *Unparsed, unsigned char *End);

/**
 * 
 */
EventListNode EventList_CreateNode(EventListNode Next, Event Function);

/**
 * 
 */
void EventListNode_Raise(SockListNode SockNode, EventListNode EventNode, unsigned char *Parsed, unsigned char *Unparsed, unsigned char *End);

#endif