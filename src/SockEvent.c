/* Copyright (c) 2010, Sebastian Ramadan and Andrew Hodges. All rights reserved. */

#include "SockEvent.h"
#include <stdlib.h>

SockEvent SockEvent_Create(SockListNode SockNode, unsigned char *Parsed, unsigned char *Unparsed, unsigned char *End) {
    SockEvent Event; Event = malloc(sizeof(*Event));
    
    if (Event == NULL) { return NULL; }
    
    Event->SockNode = SockNode;
    Event->Parsed = Parsed;
    Event->Unparsed = Unparsed;
    Event->End = End;
    
    return Event;
}

void SockEvent_Destroy(void *Event) {
    free(Event);
}
