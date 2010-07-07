/* Copyright (c) 2010, Sebastian Ramadan and Andrew Hodges. All rights reserved. */

#include <stdlib.h>

#include "RelativeTrieNode.h"

RelativeTrieNode RelativeTrie_InitNode(RelativeTrieNode Node, RelativeTrieNode *Parent, RelativeTrieNode *This) {
    if (Node == NULL) { return NULL; }
    
    Node->Parent = Parent;
    Node->This = This;
    
    return *This = Node;
}

RelativeTrieNode RelativeTrie_CreateNode(RelativeTrieNode *Parent) {
    RelativeTrieNode *This = malloc(sizeof(*This));
    
    if (This == NULL) { return NULL; }
    
    return RelativeTrie_InitNode(malloc(sizeof(struct RelativeTrieNode)), Parent, This);
}

void RelativeTrie_DestroyNode(RelativeTrieNode Node) {
    
}
