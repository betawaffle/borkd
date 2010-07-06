#ifndef __EVENTLISTNODE_C
#define __EVENTLISTNODE_C

// Copyright (c) 2009, Sebastian Ramadan. All rights reserved.
/** \file EventListNode.c
 *  \brief Function prototype definition (Event), and linked list structure (EventListNode) for defining/storing Event handler functions. Function for creating/initializing EventListNode instances.
 */

typedef int (* Event)(struct SockListNode *Node, unsigned char *Parsed, unsigned char *Unparsed, unsigned char *End);

struct EventListNode {
	struct EventListNode *Next;
	Event Function;
};

struct EventListNode *EventList_CreateNode(struct EventListNode *Next, Event Function) {
	struct EventListNode *Node;

	if ((Node = malloc(sizeof(*Node))) == NULL) { return NULL; }
	
	Node->Next = Next;
	Node->Function = Function;

	return Node;
}

void EventListNode_Raise(struct SockListNode *SockNode, struct EventListNode *EventNode, unsigned char *Parsed, unsigned char *Unparsed, unsigned char *End) {
	if (EventNode == NULL) { return; }
	if (EventNode->Function == NULL) { return; }
	
	EventNode->Function(SockNode, Parsed, Unparsed, End);
	EventListNode_Raise(SockNode, EventNode->Next, Parsed, Unparsed, End);
}
#endif
