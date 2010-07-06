#ifndef __RELATIVETRIENODE_C
#define __RELATIVETRIENODE_C

/* Copyright (c) 2010, Sebastian Ramadan and Andrew Hodges. All rights reserved. */
/** 
 * @file RelativeTrieNode.c
 * @brief Extension of the TrieNode structure for storing Relatives (Parents, siblings, etc).
 *        Functions for initializing/creating/destroying nodes from the collection.
 */

#include "TrieNode.c"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/** \struct RelativeTrieNode
 *  \brief Parent The parent node (or NULL).
 *  \brief This An allocated object that contains a pointer to Node. Used when reorganising the Trie (eg. when an insertion is made).
 *  \extends TrieNode
 */
struct RelativeTrieNode {
	struct TrieNode Node;
	struct RelativeTrieNode **Parent;
	struct RelativeTrieNode **This;
};

struct RelativeTrieNode *RelativeTrie_InitNode(struct RelativeTrieNode *Node, struct RelativeTrieNode **Parent, struct RelativeTrieNode **This);
struct RelativeTrieNode *RelativeTrie_CreateNode(struct RelativeTrieNode **Parent);
void RelativeTrie_DestroyNode(struct RelativeTrieNode *value);

/**
 *  Initializes an RelativeTrieNode.
 *  \param Node The node to be initialized.
 *  \param Parent The RelativeTrieNode to initialize the node to.
 *  \param This An allocated object that contains a pointer to Node.
 *  \returns NULL indicates error. The first argument (\a Node) indicates success.
 */
struct RelativeTrieNode *RelativeTrie_InitNode(struct RelativeTrieNode *Node, struct RelativeTrieNode **Parent, struct RelativeTrieNode **This) {
	if (Node == NULL) { return NULL; }
	
    Node->Parent = Parent;
	Node->This = This;
	
	return *This = Node;
}

/**
 *  Creates a RelativeTrieNode. Passes return value of malloc onto \ref RelativeTrie_InitNode.
 *  \param Parent The RelativeTrieNode to initialize the node to.
 *  \return NULL indicates an error. The return value shall be a pointer to the new RelativeTrieNode.
 */
struct RelativeTrieNode *RelativeTrie_CreateNode(struct RelativeTrieNode **Parent) {
	struct RelativeTrieNode **This = malloc(sizeof (*This));
	
	if (This == NULL) { return NULL; }
	
	return RelativeTrie_InitNode(malloc(sizeof (struct RelativeTrieNode)), Parent, This);
}

void RelativeTrie_DestroyNode(struct RelativeTrieNode *value) {

}
#endif
