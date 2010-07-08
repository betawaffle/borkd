/* Copyright (c) 2010, Sebastian Ramadan and Andrew Hodges. All rights reserved. */

#include <stdlib.h>

#include "SockEvent.h"

DefineInit(SockEvent, SockListNode SockNode, unsigned char *Parsed, unsigned char *Unparsed, unsigned char *End) {
    if (self != NULL) {
        /*self->Destroy = &free;*/
        self->SockNode = SockNode;
        self->Parsed = Parsed;
        self->Unparsed = Unparsed;
        self->End = End;
    }
    
    return self;
}
