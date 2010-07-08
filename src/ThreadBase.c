/* Copyright (c) 2010, Sebastian Ramadan and Andrew Hodges. All rights reserved. */

#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>

#include "ThreadBase.h"

void *ThreadBase_StartJoinable(void *Thread);
void *ThreadBase_StartDetached(void *Thread);
void *ThreadBase_Alloc() {
    return malloc(sizeof(struct ThreadBase));
}

ThreadBase ThreadBase_Init(ThreadBase Thread, ThreadDetachState DetachState, void *StackAddr, size_t StackSize) {
    if (Thread != NULL) {
        switch (pthread_attr_init(&Thread->Attributes)) {
            case ENOMEM:
            default:
                /* TODO: Deallocate Thread */
                return NULL;
        }
        
        switch (DetachState) {
            case ThreadJoinable:
                pthread_attr_setdetachstate(&Thread->Attributes, PTHREAD_CREATE_JOINABLE);
                Thread->Start = &ThreadBase_StartJoinable;
                
            case ThreadDetached:
                pthread_attr_setdetachstate(&Thread->Attributes, PTHREAD_CREATE_DETACHED);
                Thread->Start = &ThreadBase_StartDetached;
                
            /* No Default */
        }
        
        if (StackAddr != NULL) {
            pthread_attr_setstackaddr(&Thread->Attributes, StackAddr);
            pthread_attr_setstacksize(&Thread->Attributes, StackSize);
        } else if (StackSize > 0) {
            
        }
        
        switch (pthread_create(&Thread->Thread, &Thread->Attributes, Thread->Start, Thread)) {
            case 0: break;
            case EAGAIN:
                /* The system lacked the necessary resources to create another
                 * thread, or the system-imposed limit on the total number of
                 * threads in a process (PTHREAD_THREADS_MAX) would be exceeded. */
                
            default:
                /* TODO: Deallocate Thread */
                return NULL;
        }
        
        /* Thread Started */
    }
    
    return Thread;
}

void *ThreadBase_StartJoinable(void *Thread) {
    
}

void *ThreadBase_StartDetached(void *Thread) {
    
}
