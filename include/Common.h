/* Copyright (c) 2010, Sebastian Ramadan and Andrew Hodges. All rights reserved. */

#ifndef INCLUDED_Common_H
#define INCLUDED_Common_H

typedef void (*Destructor)(void *);

#define Inline __inline__ __attribute__(( always_inline ))
#define Create(type, extra_sz, ...) type##_Init(##type##_Alloc(extra_sz), ##__VA_ARGS__)

#endif