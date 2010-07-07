/* Copyright (c) 2010, Sebastian Ramadan and Andrew Hodges. All rights reserved. */

#ifndef INCLUDED_RelativeTrieNode_H
#define INCLUDED_RelativeTrieNode_H

/**
 * @file RelativeTrieNode.h
 * @brief Extension of the TrieNode structure for storing Relatives (Parents, siblings, etc).
 *        Functions for initializing/creating/destroying nodes from the collection.
 */

#include "TrieNode.h"

/**
 * @struct RelativeTrieNode
 * @brief Parent The parent node (or NULL).
 * @brief This An allocated object that contains a pointer to Node. Used when reorganising the Trie (eg. when an insertion is made).
 * @extends TrieNode
 */     struct RelativeTrieNode;
typedef struct RelativeTrieNode *RelativeTrieNode;

/**
 * Initializes an RelativeTrieNode.
 * @param Node The node to be initialized.
 * @param Parent The RelativeTrieNode to initialize the node to.
 * @param This An allocated object that contains a pointer to Node.
 * @returns NULL indicates error. The first argument (\a Node) indicates success.
 */
RelativeTrieNode RelativeTrie_InitNode(RelativeTrieNode Node, RelativeTrieNode *Parent, RelativeTrieNode *This);

/**
 * Creates a RelativeTrieNode. Passes return value of malloc onto \ref RelativeTrie_InitNode.
 * @param Parent The RelativeTrieNode to initialize the node to.
 * @return NULL indicates an error. The return value shall be a pointer to the new RelativeTrieNode.
 */
RelativeTrieNode RelativeTrie_CreateNode(RelativeTrieNode *Parent);

/**
 * 
 */
void RelativeTrie_DestroyNode(RelativeTrieNode Node);

#define RelativeTrieDestructorDefault ((TrieNodeDestructor) &RelativeTrie_DestroyNode)

/* TODO: Move This -- Andrew Hodges (07/07/2010) */
struct RelativeTrieNode {
    struct TrieNode Node; /* This also is still a struct. DO NOT CHANGE! -- Andrew Hodges (07/07/2010) */
    RelativeTrieNode *Parent;
    RelativeTrieNode *This;
};

#endif
