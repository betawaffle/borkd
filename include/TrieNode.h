/* Copyright (c) 2010, Sebastian Ramadan and Andrew Hodges. All rights reserved. */

#ifndef INCLUDED_TrieNode_H
#define INCLUDED_TrieNode_H

/** 
 * @file TrieNode.h
 * @brief Generic prefix TrieNode structures and functions for initializing/creating/finding/destroying generic prefix TrieNode instances.
 */

/**
 * 
 */     //struct TrieNode;
typedef struct TrieNode *TrieNode;

/**
 * 
 */
typedef void (*TrieNodeDestructor)(struct TrieNode *Node);

/**
 * 
 */
TrieNode *Trie_CreateGroup();

/**
 * 
 */
TrieNode Trie_InitNode(TrieNode Node, TrieNode *Group, unsigned int GroupCount, unsigned char *Prefix, unsigned int PrefixLength, TrieNodeDestructor Destroy);

/**
 * 
 */
TrieNode Trie_CreateNode(TrieNode *Group, unsigned int GroupCount, unsigned char *Prefix, unsigned int PrefixLength, TrieNodeDestructor Destroy);

/**
 * Finds the node identified by the Charmap translation of Prefix, and stores it in Result. If the node can't be found, stores the closest potential parent node in Result instead.
 * @param Root The root TrieNode to search.
 * @param Prefix The path of the node to search for.
 * @param Charmap The translation table used to convert Prefix ie. from lowercase to uppercase.
 * @param Result A location that will store a pointer to the resulting node.
 * @param InputPrefixIndex A location that will store the number of bytes parsed from Prefix.
 * @param NodePrefixIndex A location that will store the number of bytes parsed from Result->Prefix.
 * @return 1 if the item was successfully located. 0 otherwise.
 */
unsigned int Trie_FindNearest(TrieNode Root, unsigned char *Prefix, unsigned char *Charmap, TrieNode *Result, unsigned int *InputPrefixIndex, unsigned int *NodePrefixIndex);

/**
 * 
 */
void Trie_DestroyNode(TrieNode Node);

#define TrieNodeDestructorDefault ((TrieNodeDestructor) &Trie_DestroyNode)

/* TODO: Move This -- Andrew Hodges (07/07/2010) */
struct TrieNode {
    TrieNodeDestructor Destroy;
    
    TrieNode *Group;
    unsigned int GroupCount;
    
    unsigned char *Prefix;
    unsigned int PrefixLength;
};

#endif
