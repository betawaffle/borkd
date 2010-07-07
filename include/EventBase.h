/* Copyright (c) 2010, Sebastian Ramadan and Andrew Hodges. All rights reserved. */

#ifndef INCLUDED_EventBase_H
#define INCLUDED_EventBase_H

/**
 * 
 */     struct EventBase;
typedef struct EventBase *EventBase;

/**
 * 
 */
typedef void (*EventHandler)(EventBase Event);

struct EventBase {}; /* This looks crazy, but I think it will work. -- Andrew Hodges (07/07/2010) */

#endif
