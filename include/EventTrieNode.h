/* Copyright (c) 2010, Sebastian Ramadan and Andrew Hodges. All rights reserved. */

#ifndef INCLUDED_EventTrieNode_H
#define INCLUDED_EventTrieNode_H

/**
 * @file EventTrieNode.h
 * @brief Extension of the TrieNode structure for storing Event handlers in the form of EventList structures (EventTrieNode).
 *        Functions for initializing/creating/adding/destroying nodes from the collection.
 */

#include "Common.h"
#include "EventListNode.h"
#include "TrieNode.h"

/**
 * @struct EventTrieNode
 * @brief Value node for a trie that stores event handlers
 * @extends TrieNode
 */     struct EventTrieNode;
typedef struct EventTrieNode *EventTrieNode;

/**
 * Initializes an EventTrieNode.
 * @param Node The node to be initialized.
 * @param EventList The EventListNode to initialize \a Node to.
 * @returns NULL indicates error. The first argument (\a Node) indicates success.
 */
EventTrieNode EventTrieNode_Init(EventTrieNode Node, EventListNode EventList, TrieNode *Parent, TrieNode *This);

/**
 * Creates an EventTrieNode, with \a EventList as it's value. Passes return value of malloc onto \ref EventTrie_InitNode.
 * @param EventList The EventListNode to initialize the node to.
 * @return NULL indicates an error. The return value shall be a pointer to the new IRCSockListNode.
 */
EventTrieNode EventTrieNode_Create(EventListNode EventList, TrieNode *Parent);

/**
 * Adds an Event handler \a Function record to an EventTrieNode collection. This function uses functionality from \ref Trie_FindNearest...
 * @param Parent The root TrieNode of the EventTrieNode collection.
 * @param Prefix The prefix that shall be used to store and retrieve the Event handler \a Function.
 * @param Charmap The map of character translations that shall be used to store and retrieve the Event handler \a Function.
 * @param Function The Event handler function that shall be added to the EventTrieNode collection.
 * @return The number of characters parsed before the end of the \a Prefix was reached. 0 indicates that an error.
 * @warning Thread unsafe.
 */

/* TODO: Not sure if Parent should actually be a TrieNodeBase here. I must refactor the rest before changing it. - Seb */
unsigned int EventTrie_AddNode(TrieNode Parent, unsigned char *Prefix, unsigned char *Charmap, EventHandler Handler);

/**
 * 
 */
void EventTrieNode_Destroy(void *Node);

#define EventTrieNodeDestructor ((Destructor) &EventTrieNode_Destroy)

/* TODO: Move This -- Andrew Hodges (07/07/2010) */
struct EventTrieNode {
    struct TrieNode Node; /* This is still a struct because it's not a pointer. DO NOT CHANGE! -- Andrew Hodges (07/07/2010) */
    EventListNode EventList;
};

#endif
