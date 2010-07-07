#ifndef __EVENTTRIENODE_C
#define __EVENTTRIENODE_C

/* Copyright (c) 2010, Sebastian Ramadan and Andrew Hodges. All rights reserved. */
/** 
 * @file EventTrieNode.c
 * @brief Extension of the TrieNode structure for storing Event handlers in the form of EventList structures (EventTrieNode).
 *        Functions for initializing/creating/adding/destroying nodes from the collection.
 */

#include "EventListNode.c"
#include "RelativeTrieNode.c"

#if 0
/* These should most definitely not be in this file. */
#include "Charmap.c"
#include "SockListNode.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#endif

/** \struct EventTrieNode
 *  \brief Value node for a trie that stores event handlers
 *  \extends TrieNode
 */
struct EventTrieNode {
    struct RelativeTrieNode Node;
    struct EventListNode *EventList;
};

struct EventTrieNode *EventTrie_InitNode(struct EventTrieNode *Node, struct EventListNode *EventList, struct RelativeTrieNode **Parent, struct RelativeTrieNode **This);
struct EventTrieNode *EventTrie_CreateNode(struct EventListNode *EventList, struct RelativeTrieNode **Parent);
unsigned int EventTrie_AddNode(struct TrieNode *Parent, unsigned char *Prefix, unsigned char *Charmap, Event Function);
void EventTrie_DestroyNode(struct EventTrieNode *value);

/**
 *  Initializes an EventTrieNode.
 *  \param Node The node to be initialized.
 *  \param EventList The EventListNode to initialize \a Node to.
 *  \returns NULL indicates error. The first argument (\a Node) indicates success.
 */
struct EventTrieNode *EventTrie_InitNode(struct EventTrieNode *Node, struct EventListNode *EventList, struct RelativeTrieNode **Parent, struct RelativeTrieNode **This) {
    if (Node == NULL) { return NULL; }
    Node->EventList = EventList;
    return (struct EventTrieNode *) RelativeTrie_InitNode((struct RelativeTrieNode *) Node, Parent, This);
}

/**
 *  Creates an EventTrieNode, with \a EventList as it's value. Passes return value of malloc onto \ref EventTrie_InitNode.
 *  \param EventList The EventListNode to initialize the node to.
 *  \return NULL indicates an error. The return value shall be a pointer to the new IRCSockListNode.
 */
struct EventTrieNode *EventTrie_CreateNode(struct EventListNode *EventList, struct RelativeTrieNode **Parent) {
    struct RelativeTrieNode **This = malloc(sizeof (*This));
    if (This == NULL) { return NULL; }
    return EventTrie_InitNode(malloc(sizeof (struct EventTrieNode)), EventList, Parent, This);
}

/**
 *  Adds an Event handler \a Function record to an EventTrieNode collection. This function uses functionality from \ref Trie_FindNearest...
 *  \param Parent The root TrieNode of the EventTrieNode collection.
 *  \param Prefix The prefix that shall be used to store and retrieve the Event handler \a Function.
 *  \param Charmap The map of character translations that shall be used to store and retrieve the Event handler \a Function.
 *  \param Function The Event handler function that shall be added to the EventTrieNode collection.
 *  \return The number of characters parsed before the end of the \a Prefix was reached. 0 indicates that an error.
 *  \warning Thread unsafe.
 */
unsigned int EventTrie_AddNode(struct TrieNode *Parent, unsigned char *Prefix, unsigned char *Charmap, Event Function) {
    struct RelativeTrieNode *Result = NULL;
    unsigned int PrefixIndex = 0, NodeIndex = 0;
    unsigned int success = Trie_FindNearest(Parent, Prefix, Charmap, (struct TrieNode **) &Result, &PrefixIndex, &NodeIndex);
    struct EventTrieNode *e;

    /* The aim of the following group of logic is to create a value node to store our value (the pointer to function, "function").
     * There are 3 possible situations:
     * i. The node already exists, whether it's as a branch node or as a value node.
     * ii. The node doesn't exist, but a branch needs to be split. This handles the following cases:
     * insertion of "foo" into tree that contains "foobar"
     *      foobar turns into:
     *      foo ... bar
     *        `--.--^
     * and insertion of "foohba" into tree that contains "foobar"
     *      foobar turns into:
     *      foo ... bar
     *        `--.--^ ... hba
     *            `-------^
     * iii. The node doesn't exist, but no branch needs to be split. This handles all of the following cases:
     *      foo turns into:
     *      foo ... bar
     *        `-----^
     */
    
    if (success == 1) {
        /* situation i. The node already exists, whether it's as a branch node or as a value node... We need to check! */
        if (Result->Node.Destroy != (Destroy) EventTrie_DestroyNode) {
            /* Branch node (needs to be converted to value node) */
            struct RelativeTrieNode *parent = *Result->Parent;

            assert(parent != NULL);
            assert(parent->Node.Group != NULL);

            e = EventTrie_CreateNode(NULL, Result->Parent);
            if (e == NULL) { return 0; }

            Trie_InitNode((struct TrieNode *) e, Result->Node.Group, Result->Node.GroupCount, Result->Node.Prefix, Result->Node.PrefixLength, (Destroy) EventTrie_DestroyNode);
            parent->Node.Group[Charmap[Prefix[PrefixIndex - Result->Node.PrefixLength]]] = (struct TrieNode *) e;
            free(Result);
        }
    } else {
        /* situation ii & iii. The node doesn't exist...
         * a. the path to the node already partially exists, but a branch might need to be split to add the node. this is situation ii, and we'll deal with it first. */
        unsigned int index = PrefixIndex - NodeIndex;
        unsigned char /* *o, */ *p, *q = Prefix + index;
        struct RelativeTrieNode **parent = Result->Parent, *t;
        struct TrieNode *n;
        
        if (NodeIndex > 0 && NodeIndex < Result->Node.PrefixLength) {
            struct TrieNode **g;

            /* situation ii.
             * The node doesn't exist, and it's path lies between 2 nodes that share a branch for example... in the middle of a branch
             *    inserting foo or foohba to a trie that contains foobar... the foo part needs to be split off
             *    and at the end of this block hopefully what we'll end up with is a situation iii. */
            
            /* The prefix string needs to be split from foobar to foo\0 ... bar\0.
             * ... so allocate some space for foo\0 and copy it over: */
            p = malloc(NodeIndex + 1);
            if (p == NULL) { return 0; }
            memcpy(p, Result->Node.Prefix, NodeIndex);
            p[NodeIndex] = '\0';
            
            g = Trie_CreateGroup();
            if (g == NULL) {
                free(p);
                return 0;
            }

            /* The following branch executes when adding a node causes a branch fork
             *    eg. the collection contains "foobar" and we're adding "foobah". The code below will add a "fooba" item to the root node,
             *    so we need to add a "h" item to the "fooba" item's nodes.
             */
            if (Charmap[Prefix[PrefixIndex]] != '\0') {
                t = RelativeTrie_CreateNode(parent);
                n = Trie_InitNode((struct TrieNode *) t, g, 1, p, NodeIndex, (Destroy) RelativeTrie_DestroyNode);
            }
            /* The following branch executes when adding a node with a prefix that already exists as part of another node's prefix.
             *    eg. the collection contains "foobar" and we're adding "foo".
             */
            else {
                e = EventTrie_CreateNode(NULL, parent);
                t = (struct RelativeTrieNode *) e;
                n = Trie_InitNode((struct TrieNode *) e, g, 1, p, NodeIndex, (Destroy) EventTrie_DestroyNode);
            }

            /* n will be allocated in one of the above branches, so it'll also need to be checked :) */
            if (n == NULL) {
                free(g);
                free(p);
                return 0;
            }
            
            /* The newly created node is to be inserted before "foobar" (eg. "foo"). The old node's prefix and prefix length needs updating. */
            memmove(Result->Node.Prefix, Result->Node.Prefix + NodeIndex, Result->Node.PrefixLength -= NodeIndex);
            Result->Node.Prefix[Result->Node.PrefixLength] = '\0';
            
            /* Insert the new into it's correct (hopefully) position */
            (*parent)->Node.Group[*p] = n;

            /* Add "foobar" as a node within the new node and update it's Parent value to reflect the change */
            (n->Group = g)[Result->Node.Prefix[0]] = (struct TrieNode *) Result;
            Result->Parent = t->This;
            NodeIndex = 0;
            Result = (struct RelativeTrieNode *) n;
        }
        
        /* The following branch executes when:
         * i. adding a node causes a branch fork
         *    eg. the collection contains "foobar" and we're adding "foobah". The code above has added a "fooba" item to the root node,
         *    so we need to add a "h" item to the "fooba" item's nodes.
         * ii. adding a node is a simple case of just appending the node onto the end of an existing prefix (this actually also covers point i.)
         *    eg. the collection contains a "foo" item and we're adding "foobar" (eg. adding "bar" to the "foo" item's nodes)
         *           ---------
         * ... It will *not* execute when adding a node with a prefix that already exists as part of another node's prefix.
         *    eg. the collection contains "foobar" and we're adding "foo".
         */
        if (Charmap[Prefix[PrefixIndex]] != '\0') {
            unsigned int len;
            unsigned char *o;

            /* Calculate the length of the new nodes prefix. */
            for (q = Prefix + PrefixIndex; Charmap[*q]; q++);
            len = q - Prefix;
            
            /* Allocate and set the new nodes prefix. */
            p = malloc(len + 1);
            if (p == NULL) { return 0; }
            for (o = p, q = Prefix + PrefixIndex; *o = Charmap[*q]; o++, q++);
            
            /* Create the node that will store the event handler */
            e = EventTrie_CreateNode(NULL, Result->Parent);
            if (e == NULL) {
                free(p);
                return 0;
            }

            /* Initialize the node that will store the event handler */
            Trie_InitNode((struct TrieNode *) e, Trie_CreateGroup(), 0, p, len, (Destroy) EventTrie_DestroyNode);

            Result->Node.Group[*p] = (struct TrieNode *) e;
            e->Node.Parent = Result->This;
            PrefixIndex += len;
        }

    }
    
    // a value node! hoorah
    e->EventList = EventList_CreateNode(e->EventList, Function);
    
    return PrefixIndex;
}

void EventTrie_DestroyNode(struct EventTrieNode *value) {

}
#endif
