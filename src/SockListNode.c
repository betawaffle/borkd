/* Copyright (c) 2010, Sebastian Ramadan and Andrew Hodges. All rights reserved. */

#include <time.h>

#include "SockListNode.h"

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
