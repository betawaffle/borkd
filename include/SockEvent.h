/* Copyright (c) 2010, Sebastian Ramadan and Andrew Hodges. All rights reserved. */

#ifndef INCLUDED_SockEvent_H
#define INCLUDED_SockEvent_H

#include "Common.h"
#include "EventBase.h"
#include "SockListNode.h" /* This is here (while we're still using SockListNode) -- Andrew Hodges (07/08/2010) */

/**
 * 
 */     struct SockEvent;
typedef struct SockEvent *SockEvent;
        struct SockEvent {
    struct EventBase    Base;
    SockListNode        SockNode;
    unsigned char      *Parsed;
    unsigned char      *Unparsed;
    unsigned char      *End;
};

/**
 * 
 */
DefineInit(SockEvent, SockListNode SockNode, unsigned char *Parsed, unsigned char *Unparsed, unsigned char *End);

/**
 * 
 */
SockEvent SockEvent_Create(SockListNode SockNode, unsigned char *Parsed, unsigned char *Unparsed, unsigned char *End);

/**
 * 
 */
void SockEvent_Destroy(void *Event);

#define SockEventDestructor ((Destructor) &SockEvent_Destroy)

#endif
