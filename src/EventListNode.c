/* Copyright (c) 2010, Sebastian Ramadan and Andrew Hodges. All rights reserved. */

#include <stdlib.h>

#include "EventListNode.h"

struct EventListNode {
    EventListNode Next;
    Event Function;
};

EventListNode EventList_CreateNode(EventListNode Next, Event Function) {
    EventListNode Node; Node = malloc(sizeof(*Node));
    
    if (Node == NULL) { return NULL; }
    
    Node->Next = Next;
    Node->Function = Function;
    
    return Node;
}

void EventListNode_Raise(SockListNode SockNode, EventListNode EventNode, unsigned char *Parsed, unsigned char *Unparsed, unsigned char *End) {
    if (EventNode == NULL) { return; }
    if (EventNode->Function == NULL) { return; }
    
    EventNode->Function(SockNode, Parsed, Unparsed, End);
    EventListNode_Raise(SockNode, EventNode->Next, Parsed, Unparsed, End);
}
