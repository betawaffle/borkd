/* Copyright (c) 2010, Sebastian Ramadan and Andrew Hodges. All rights reserved. */

#include <stdlib.h>
#include <string.h>

#include "TrieNode.h"

TrieNode *Trie_CreateGroup() {
    TrieNode *g; g = malloc(256 * sizeof(*g));
    
    if (g == NULL) { return NULL; }
 
    return memset(g, 0, 256 * sizeof(*g));
}

TrieNode Trie_InitNode(TrieNode Node, TrieNode *Group, unsigned int GroupCount, unsigned char *Prefix, unsigned int PrefixLength, TrieNodeDestructor Destroy) {
    if (Node == NULL) { return NULL; }
    
    Node->Group = Group;
    Node->GroupCount = GroupCount;
    Node->Prefix = Prefix;
    Node->PrefixLength = PrefixLength;
    Node->Destroy = Destroy;
    
    return Node;
}
 
TrieNode Trie_CreateNode(TrieNode *Group, unsigned int GroupCount, unsigned char *Prefix, unsigned int PrefixLength, TrieNodeDestructor Destroy) {
    return Trie_InitNode(malloc(sizeof(struct TrieNode)), Group, GroupCount, Prefix, PrefixLength, Destroy);
}


unsigned int Trie_FindNearest(TrieNode Root, unsigned char *Prefix, unsigned char *Charmap, TrieNode *Result, unsigned int *InputPrefixIndex, unsigned int *NodePrefixIndex) {
    TrieNode n = Root, *g;
    unsigned char c, *s, *u;
    
    if (Root == NULL || Prefix == NULL || Charmap == NULL || Result == NULL || InputPrefixIndex == NULL || NodePrefixIndex == NULL) { return 0; }
    
    s = Prefix;
    
    while (c = Charmap[*s]) {
        if (g = n->Group, g == NULL) {
            *Result = n;
            *InputPrefixIndex = s - Prefix;
            *NodePrefixIndex = 0 /* n->PrefixLength */;
            
            return 0;
        }
        
        if (g[c] == NULL) {
            *Result = n;
            *InputPrefixIndex = s - Prefix;
            *NodePrefixIndex = 0 /* n->PrefixLength */;
            
            return 0;
        }
        
        for (n = g[c], u = n->Prefix; c = Charmap[*s], c == *u && c; u++, s++);
        
        if (*u && c != *u) {
            *Result = n;
            *InputPrefixIndex = s - Prefix;
            *NodePrefixIndex = u - n->Prefix;
            
            return 0;
        }
    }
    
    *Result = n;
    *InputPrefixIndex = s - Prefix;
    *NodePrefixIndex = 0;
    
    return 1;
}

void Trie_DestroyNode(TrieNode Node) {

}
