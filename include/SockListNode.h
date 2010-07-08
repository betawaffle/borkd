/* Copyright (c) 2010, Sebastian Ramadan and Andrew Hodges. All rights reserved. */

#ifndef INCLUDED_SockListNode_H
#define INCLUDED_SockListNode_H

/**
 * 
 */     struct SockListNode;
typedef struct SockListNode *SockListNode;

typedef void (*SockListNode_Connect)(void);
typedef void (*SockListNode_Send)(void);
typedef void (*SockListNode_Recieve)(void);
typedef void (*SockListNode_Close)(void);
typedef void (*SockListNode_Destroy)(void);

/* TODO: This needs to inherit from ListNode (which doesn't exist yet) -- Andrew Hodges (07/08/2010) */
struct SockListNode {
    /*SockListNodeDestructor Destory;
    
    SockListNode_Connect Connect;
    SockListNode_Send Send;
    SockListNode_Recieve Recieve;
    SockListNode_Close Close;
    SockListNode_Destroy Destroy;*/
    int Socket;
    /*time_t LastConnectAttempt;*/
    SockListNode Next;
};

#endif
