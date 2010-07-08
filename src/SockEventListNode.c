/* Copyright (c) 2010, Sebastian Ramadan and Andrew Hodges. All rights reserved. */

#include <stdlib.h>

#include "SockEventListNode.h"

SockEventListNode SockEventListNode_Create(SockEventListNode Next, EventHandler Handler) {
    SockEventListNode Node; Node = malloc(sizeof(*Node));
    
    if (Node == NULL) { return NULL; }
    
    Node->Destroy = &free; /* Hehe, this will work for the moment. -- AH (07/08/2010) */
    Node->Next = Next;
    Node->Handler = Handler;
    
    return Node;
}

void SockEventListNode_Raise(SockEventListNode Node, SockEvent Event) {
	if (Node == NULL || Node->Handler == NULL) { return; }
    
    Node->Handler(Event);
    SockEventListNode_Raise(Node->Next, Event);
}
