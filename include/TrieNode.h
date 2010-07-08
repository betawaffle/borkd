/* Copyright (c) 2010, Sebastian Ramadan and Andrew Hodges. All rights reserved. */

#ifndef INCLUDED_TrieNode_H
#define INCLUDED_TrieNode_H

/**
 * @file TrieNode.h
 * @brief Extension of the TrieNodeBase structure for storing Relatives (Parents, siblings, etc).
 *        Functions for initializing/creating/destroying nodes from the collection.
 */

#include "Common.h"
#include "TrieNodeBase.h"

/**
 * @struct TrieNode
 * @brief Parent The parent node (or NULL).
 * @brief This An allocated object that contains a pointer to Node. Used when reorganising the Trie (eg. when an insertion is made).
 * @extends TrieNode
 */     struct TrieNode;
typedef struct TrieNode *TrieNode;

/**
 * Initializes an TrieNode.
 * @param Node The node to be initialized.
 * @param Parent The TrieNode to initialize the node to.
 * @param This An allocated object that contains a pointer to Node.
 * @returns NULL indicates error. The first argument (\a Node) indicates success.
 */
TrieNode TrieNode_Init(TrieNode Node, TrieNode *Parent, TrieNode *This);

/**
 * Creates a TrieNode. Passes return value of malloc onto \ref Trie_InitNode.
 * @param Parent The TrieNode to initialize the node to.
 * @return NULL indicates an error. The return value shall be a pointer to the new TrieNode.
 */
TrieNode TrieNode_Create(TrieNode *Parent);

unsigned int Trie_AddNode(TrieNode Parent, unsigned char *Prefix, unsigned char *Charmap, TrieNode Node);

/**
 * 
 */
void TrieNode_Destroy(void *Node);

#define TrieNodeDestructor ((Destructor) &TrieNode_Destroy)

/* TODO: Move This -- Andrew Hodges (07/07/2010) */
struct TrieNode {
    struct TrieNodeBase Node; /* This also is still a struct. DO NOT CHANGE! -- Andrew Hodges (07/07/2010) */
    TrieNode *Parent;
    TrieNode *This;
};

#endif
