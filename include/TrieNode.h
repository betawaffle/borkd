/* Copyright (c) 2010, Sebastian Ramadan and Andrew Hodges. All rights reserved. */

#ifndef INCLUDED_TrieNode_H
#define INCLUDED_TrieNode_H

/**
 * @file TrieNode.h
 * @brief Extension of the TrieNodeBase class for storing Relatives (Parents, siblings, etc).
 */

#include "TrieNodeBase.h"

namespace TrieNode {
	static const TrieNodeTypeID TrieNodeID = 1;
	static const TrieNodeTypeID ValueTrieNodeID = 2;

	class TrieNode;
	class TrieNode: public TrieNodeBase {
	protected:

	public:
		TrieNode **Parent;
		TrieNode **This;

		TrieNode(void);
		TrieNode(TrieNode **Parent);
		TrieNode(TrieNode **Parent, TrieNode **This);
		TrieNode(TrieNodeBase **Group, unsigned int GroupCount, unsigned char *Prefix, unsigned int PrefixLength);
		TrieNode(TrieNode **Parent, TrieNodeBase **Group, unsigned int GroupCount, unsigned char *Prefix, unsigned int PrefixLength);
		TrieNode(TrieNode **Parent, TrieNode **This, TrieNodeBase **Group, unsigned int GroupCount, unsigned char *Prefix, unsigned int PrefixLength);
		void Init(TrieNode **Parent, TrieNode **This);
		void Init(TrieNodeBase **Group, unsigned int GroupCount, unsigned char *Prefix, unsigned int PrefixLength);
		void Init(TrieNode **Parent, TrieNodeBase **Group, unsigned int GroupCount, unsigned char *Prefix, unsigned int PrefixLength);
		unsigned int AddNode(unsigned char *Prefix, int *Charmap, int GroupSize, TrieNode *Node);
		unsigned int RenameNode(unsigned char *SourcePrefix, unsigned char *DestPrefix, int *Charmap, int GroupSize);
		~TrieNode();
	};

	template<class foo> class ValueTrieNode: public TrieNode {
	public:
		foo Value;
		ValueTrieNode(void);
	};
};

/* TODO REWORD/RELOCATE THIS: */
/**
 * @struct TrieNode
 * @brief Parent The parent node (or NULL).
 * @brief This An allocated object that contains a pointer to Node. Used when reorganising the Trie (eg. when an insertion is made).
 * @extends TrieNode
 */
/**
 * Creates a TrieNode. Passes return value of malloc onto \ref Trie_InitNode.
 * @param Parent The TrieNode to initialize the node to.
 * @return NULL indicates an error. The return value shall be a pointer to the new TrieNode.
 */
/**
 * Initializes an TrieNode.
 * @param Node The node to be initialized.
 * @param Parent The TrieNode to initialize the node to.
 * @param This An allocated object that contains a pointer to Node.
 * @returns NULL indicates error. The first argument (\a Node) indicates success.
 */

#endif
