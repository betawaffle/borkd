/* Copyright (c) 2010, Sebastian Ramadan and Andrew Hodges. All rights reserved. */

#include <stdlib.h>

#include "TrieNode.h"

TrieNode TrieNode_Init(TrieNode Node, TrieNode *Parent, TrieNode *This) {
    if (Node == NULL) { return NULL; }
    
    Node->Parent = Parent;
    Node->This = This;
    
    return *This = Node;
}

TrieNode TrieNode_Create(TrieNode *Parent) {
    TrieNode *This = malloc(sizeof(*This));
    
    if (This == NULL) { return NULL; }
    
    return TrieNode_Init(malloc(sizeof(struct TrieNode)), Parent, This);
}

void TrieNode_Destroy(TrieNode Node) {
    
}
