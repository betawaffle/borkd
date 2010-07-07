/* Copyright (c) 2010, Sebastian Ramadan and Andrew Hodges. All rights reserved. */

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "EventTrieNode.h"

EventTrieNode EventTrie_InitNode(EventTrieNode Node, EventListNode EventList, RelativeTrieNode *Parent, RelativeTrieNode *This) {
    if (Node == NULL) { return NULL; }
    
    Node->EventList = EventList;
    
    return (EventTrieNode) RelativeTrie_InitNode((RelativeTrieNode) Node, Parent, This);
}

EventTrieNode EventTrie_CreateNode(EventListNode EventList, RelativeTrieNode *Parent) {
    RelativeTrieNode *This = malloc(sizeof (*This));
    
    if (This == NULL) { return NULL; }
    
    return EventTrie_InitNode(malloc(sizeof(struct EventTrieNode)), EventList, Parent, This);
}

unsigned int EventTrie_AddNode(TrieNode Parent, unsigned char *Prefix, unsigned char *Charmap, Event Function) {
    RelativeTrieNode Result = NULL;
    unsigned int PrefixIndex = 0, NodeIndex = 0;
    unsigned int success = Trie_FindNearest(Parent, Prefix, Charmap, (TrieNode *) &Result, &PrefixIndex, &NodeIndex);
    EventTrieNode e = (EventTrieNode) Result; 
    
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
        if (Result->Node.Destroy != EventTrieDestructorDefault) {
            /* Branch node (needs to be converted to value node) */
            RelativeTrieNode parent = *Result->Parent;
            
            assert(parent != NULL);
            assert(parent->Node.Group != NULL);
            
            if (e = EventTrie_CreateNode(NULL, Result->Parent), e == NULL) { return 0; }
            
            Trie_InitNode((TrieNode) e, Result->Node.Group, Result->Node.GroupCount, Result->Node.Prefix, Result->Node.PrefixLength, EventTrieDestructorDefault);
            parent->Node.Group[Charmap[Prefix[PrefixIndex - Result->Node.PrefixLength]]] = (TrieNode) e;
            free(Result);
        } /* FIXME: e is not set! -- Andrew Hodges (07/07/2010) */
    } else {
        /* situation ii & iii. The node doesn't exist...
         * a. the path to the node already partially exists, but a branch might need to be split to add the node. this is situation ii, and we'll deal with it first. */
        //unsigned int index = PrefixIndex - NodeIndex;
        unsigned char *p, *q /* = Prefix + index; <--- This value wasn't used -- Andrew Hodges (07/07/2010) */;
        RelativeTrieNode *parent = Result->Parent, t;
        TrieNode n;
        
        if (NodeIndex > 0 && NodeIndex < Result->Node.PrefixLength) {
            TrieNode *g;

            /* situation ii.
             * The node doesn't exist, and it's path lies between 2 nodes that share a branch for example... in the middle of a branch
             *    inserting foo or foohba to a trie that contains foobar... the foo part needs to be split off
             *    and at the end of this block hopefully what we'll end up with is a situation iii. */
            
            /* The prefix string needs to be split from foobar to foo\0 ... bar\0.
             * ... so allocate some space for foo\0 and copy it over: */
            if (p = malloc(NodeIndex + 1), p == NULL) { return 0; }
            
            memcpy(p, Result->Node.Prefix, NodeIndex), p[NodeIndex] = '\0';
            
            if (g = Trie_CreateGroup(), g == NULL) {
                free(p);
                return 0;
            }

            /* The following branch executes when adding a node causes a branch fork
             *    eg. the collection contains "foobar" and we're adding "foobah". The code below will add a "fooba" item to the root node,
             *    so we need to add a "h" item to the "fooba" item's nodes. */
            if (Charmap[Prefix[PrefixIndex]] != '\0') {
                t = RelativeTrie_CreateNode(parent);
                n = Trie_InitNode((TrieNode) t, g, 1, p, NodeIndex, RelativeTrieDestructorDefault);
            }
            
            /* The following branch executes when adding a node with a prefix that already exists as part of another node's prefix.
             *    eg. the collection contains "foobar" and we're adding "foo". */
            else {
                e = EventTrie_CreateNode(NULL, parent);
                t = (RelativeTrieNode) e;
                n = Trie_InitNode((TrieNode) e, g, 1, p, NodeIndex, EventTrieDestructorDefault);
            }

            /* n will be allocated in one of the above branches, so it'll also need to be checked :) */
            if (n == NULL) {
                free(g);
                free(p);
                return 0;
            }
            
            /* The newly created node is to be inserted before "foobar" (eg. "foo"). The old node's prefix and prefix length needs updating. */
            memmove(Result->Node.Prefix, Result->Node.Prefix + NodeIndex, Result->Node.PrefixLength -= NodeIndex), Result->Node.Prefix[Result->Node.PrefixLength] = '\0';
            
            /* Insert the new into it's correct (hopefully) position */
            (*parent)->Node.Group[*p] = n;

            /* Add "foobar" as a node within the new node and update it's Parent value to reflect the change */
            (n->Group = g)[Result->Node.Prefix[0]] = (TrieNode) Result;
            Result->Parent = t->This;
            NodeIndex = 0;
            Result = (RelativeTrieNode) n;
        }
        
        /* The following branch executes when:
         *
         * i.  adding a node causes a branch fork
         *      eg. the collection contains "foobar" and we're adding "foobah". The code above has added a "fooba" item to the root node,
         *          so we need to add a "h" item to the "fooba" item's nodes.
         * ii. adding a node is a simple case of just appending the node onto the end of an existing prefix (this actually also covers point i.)
         *      eg. the collection contains a "foo" item and we're adding "foobar" (eg. adding "bar" to the "foo" item's nodes)
         *          ---------
         * ... It will *not* execute when adding a node with a prefix that already exists as part of another node's prefix.
         *      eg. the collection contains "foobar" and we're adding "foo".
         */
        if (Charmap[Prefix[PrefixIndex]] != '\0') {
            unsigned int len;
            unsigned char *o;

            /* Calculate the length of the new node's prefix. */
            for (q = Prefix + PrefixIndex; Charmap[*q]; q++); len = q - Prefix;
            
            /* Allocate the new node's prefix. */
            if (p = malloc(len + 1), p == NULL) { return 0; }
            
            /* Set the new node's prefix. */
            for (o = p, q = Prefix + PrefixIndex; *o = Charmap[*q]; o++, q++);
            
            /* Create the node that will store the event handler */
            if (e = EventTrie_CreateNode(NULL, Result->Parent), e == NULL) {
                free(p);
                return 0;
            }

            /* Initialize the node that will store the event handler */
            Trie_InitNode((TrieNode) e, Trie_CreateGroup(), 0, p, len, EventTrieDestructorDefault);

            Result->Node.Group[*p] = (TrieNode) e;
            e->Node.Parent = Result->This;
            PrefixIndex += len;
        }

    }
    
    /* A value node! Hoorah! */
    e->EventList = EventList_CreateNode(e->EventList, Function); /* FIXME: I get a static analysis bug here (Dereference of null pointer).
                                                                  *        See line 64ish. -- Andrew Hodges (07/07/2010) */
    return PrefixIndex;
}

void EventTrie_DestroyNode(EventTrieNode Node) {

}
