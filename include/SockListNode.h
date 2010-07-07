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

#endif
