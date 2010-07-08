/* Copyright (c) 2010, Sebastian Ramadan and Andrew Hodges. All rights reserved. */

#include <stdlib.h>

#include "EventListNode.h"

EventListNode EventListNode_Create(EventListNode Next, EventHandler Handler) {
    EventListNode Node; Node = malloc(sizeof(*Node));
    
    if (Node == NULL) { return NULL; }
    
    Node->Destroy = &free;
    Node->Next = Next;
    Node->Handler = Handler;
    
    return Node;
}

void EventListNode_Raise(EventListNode Node, EventBase Event) {
    switch (NULL) {
        case Node:
        case Node->Handler:
        return;
    }
    
    Node->Handler(Event);
    EventListNode_Raise(Node->Next, Event);
}
