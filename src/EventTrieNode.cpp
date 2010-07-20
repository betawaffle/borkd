/* Copyright (c) 2010, Sebastian Ramadan and Andrew Hodges. All rights reserved. */

#include <stdlib.h>
#include <string.h>

#include "Common.h"
#include "EventTrieNode.h"

#if 0
struct EventTrieNode *EventTrieNode_Init(struct EventTrieNode *Node, EventListNode EventList, struct TrieNode **Parent, struct TrieNode **This) {
    if (Node == NULL) { return NULL; }
    
    Node->EventList = EventList;
    
    return (struct EventTrieNode *) TrieNode_Init((struct TrieNode *) Node, Parent, This);
}

struct EventTrieNode *EventTrieNode_Create(EventListNode EventList, struct TrieNode **Parent) {
    struct TrieNode **This = malloc(sizeof (*This));
    
    if (This == NULL) { return NULL; }
    
    return EventTrieNode_Init(malloc(sizeof(struct EventTrieNode)), EventList, Parent, This);
}

unsigned int EventTrie_AddNode(struct TrieNode *Parent, unsigned char *Prefix, unsigned char *Charmap, EventHandler Handler) {
	struct EventTrieNode *e;
	struct TrieNode *Result = NULL;
    unsigned int PrefixIndex = 0, NodeIndex = 0;
	unsigned int success = Trie_FindNearest((struct TrieNodeBase *) Parent, Prefix, Charmap, (struct TrieNodeBase **) &Result, &PrefixIndex, &NodeIndex);

	/* The following will execute if the node could not be found, or if the node is not an EventTrieNode */
	if (success == 0 || (success == 1 && Result->Node.Destroy != EventTrieNodeDestructor)) {
		if (e = EventTrieNode_Create(NULL, NULL), e == NULL) { return 0; }
	}
	else {
		e = (struct EventTrieNode *) Result;
	}

	/* The Trie_AddNode call below is slightly inefficient, in that it'll have to iterate part of the Prefix string a second time */
	e->Node.Node.Destroy = EventTrieNodeDestructor;
	e->EventList = EventListNode_Create(e->EventList, Handler);
	if (NodeIndex > 0 && Result->Parent != NULL) {
		return Trie_AddNode(*Result->Parent, Prefix + (PrefixIndex - NodeIndex), Charmap, (struct TrieNode *) e);
	}
	return Trie_AddNode(Result, Prefix + (PrefixIndex - NodeIndex), Charmap, (struct TrieNode *) e);
}

void EventTrieNode_Destroy(void *Node) {

}
#endif