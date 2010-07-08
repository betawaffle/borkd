/* Copyright (c) 2010, Sebastian Ramadan and Andrew Hodges. All rights reserved. */

#ifndef INCLUDED_Common_H
#define INCLUDED_Common_H

typedef void (*Destructor)(void *);

#define Inline __inline__ __attribute__(( always_inline ))

#define Alloc(type, extra_sz) malloc(sizeof(struct type) + extra_sz)
#define Create(type, extra_sz, ...) type##_Init(Alloc(type, extra_sz), ##__VA_ARGS__)

#define DefineInit(type, ...) type type##_Init(type self, ##__VA_ARGS__)

#endif