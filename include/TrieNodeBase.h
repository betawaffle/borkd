/* Copyright (c) 2010, Sebastian Ramadan and Andrew Hodges. All rights reserved. */

#ifndef INCLUDED_TrieNodeBase_H
#define INCLUDED_TrieNodeBase_H

/** 
 * @file TrieNodeBase.h
 * @brief Generic prefix TrieNodeBase structures and functions for initializing/creating/finding/destroying generic prefix TrieNodeBase instances.
 */

#include "Common.h"

/**
 * 
 */     struct TrieNodeBase;
typedef struct TrieNodeBase  *TrieNodeBase;
typedef struct TrieNodeBase **TrieNodeBaseGroup;

/**
 * 
 */
TrieNodeBaseGroup TrieNodeBaseGroup_Create();

/**
 * 
 */
TrieNodeBase TrieNodeBase_Init(TrieNodeBase Node, TrieNodeBaseGroup Group, unsigned int GroupCount, unsigned char *Prefix, unsigned int PrefixLength, Destructor Destroy);

/**
 * 
 */
TrieNodeBase TrieNodeBase_Create(TrieNodeBaseGroup Group, unsigned int GroupCount, unsigned char *Prefix, unsigned int PrefixLength, Destructor Destroy);

/**
 * Finds the node identified by the Charmap translation of Prefix, and stores it in Result. If the node can't be found, stores the closest potential parent node in Result instead.
 * @param Root The root TrieNodeBase to search.
 * @param Prefix The path of the node to search for.
 * @param Charmap The translation table used to convert Prefix ie. from lowercase to uppercase.
 * @param Result A location that will store a pointer to the resulting node.
 * @param InputPrefixIndex A location that will store the number of bytes parsed from Prefix.
 * @param NodePrefixIndex A location that will store the number of bytes parsed from Result->Prefix.
 * @return 1 if the item was successfully located. 0 otherwise.
 */
unsigned int Trie_FindNearest(TrieNodeBase Root, unsigned char *Prefix, unsigned char *Charmap, TrieNodeBase *Result, unsigned int *InputPrefixIndex, unsigned int *NodePrefixIndex);

/**
 * 
 */
void TrieNodeBase_Destroy(void *Node);

#define TrieNodeBaseDestructor ((Destructor) &TrieNodeBase_Destroy)

/* TODO: Move This -- Andrew Hodges (07/07/2010) */
struct TrieNodeBase {
    Destructor Destroy;
    
    TrieNodeBaseGroup Group;
    unsigned int GroupCount;
    
    unsigned char *Prefix;
    unsigned int PrefixLength;
};

#endif
