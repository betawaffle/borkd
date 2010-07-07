/* Copyright (c) 2010, Sebastian Ramadan and Andrew Hodges. All rights reserved. */

#ifndef INCLUDED_SockEvent_H
#define INCLUDED_SockEvent_H

/**
 * 
 */     struct SockEvent;
typedef struct SockEvent *SockEvent;

SockEvent SockEvent_Create(SockListNode SockNode, unsigned char *Parsed, unsigned char *Unparsed, unsigned char *End);

/**
 * 
 */
void SockEvent_Destroy(void *Event);

#define SockEventDestructor ((Destructor) &SockEvent_Destroy)

struct SockEvent {
    struct EventBase Base;
    SockListNode SockNode;
    unsigned char *Parsed;
    unsigned char *Unparsed;
    unsigned char *End;
};

#endif
