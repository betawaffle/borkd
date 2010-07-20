/* Copyright (c) 2010, Sebastian Ramadan and Andrew Hodges. All rights reserved. */

#include <stdlib.h>
#include <string.h>

#include "Common.h"
#include "TrieNode.h"
#include "TrieNodeBase.cpp"

namespace TrieNode {
	void TrieNode::Init(TrieNode **Parent, TrieNode **This) {
		this->Parent = Parent;
		this->This = This;
		*This = this;
	}

	void TrieNode::Init(TrieNodeBase **Group, unsigned int GroupCount, unsigned char *Prefix, unsigned int PrefixLength) {
		TrieNodeBase *This = (TrieNodeBase *) this;
		This->Init(Group, GroupCount, Prefix, PrefixLength);
	}

	void TrieNode::Init(TrieNode **Parent, TrieNodeBase **Group, unsigned int GroupCount, unsigned char *Prefix, unsigned int PrefixLength) {
		TrieNodeBase *This = (TrieNodeBase *) this;
		this->Parent = Parent;
		This->Init(Group, GroupCount, Prefix, PrefixLength);
	}

	TrieNode::TrieNode(void) {
		this->Type = TrieNodeID;
	}

	TrieNode::TrieNode(TrieNode **Parent) {
		TrieNode **This = new TrieNode *();
		if (This == NULL) { assert(0); }
	    
		this->Init(Parent, This);
		this->Type = TrieNodeID;
	}

	TrieNode::TrieNode(TrieNode **Parent, TrieNode **This) {
		this->Init(Parent, This);
		this->Type = TrieNodeID;
	}

	TrieNode::TrieNode(TrieNodeBase **Group, unsigned int GroupCount, unsigned char *Prefix, unsigned int PrefixLength) {
		TrieNode **This = new TrieNode *();
		if (This == NULL) { assert(0); }

		this->Init(NULL, This);
		this->Init(Group, GroupCount, Prefix, PrefixLength);
		this->Type = TrieNodeID;
	}
	
	TrieNode::TrieNode(TrieNode **Parent, TrieNodeBase **Group, unsigned int GroupCount, unsigned char *Prefix, unsigned int PrefixLength) {
		TrieNode **This = new TrieNode *();
		if (This == NULL) { assert(0); }

		this->Init(Parent, This);
		this->Init(Group, GroupCount, Prefix, PrefixLength);
		this->Type = TrieNodeID;
	}

	TrieNode::TrieNode(TrieNode **Parent, TrieNode **This, TrieNodeBase **Group, unsigned int GroupCount, unsigned char *Prefix, unsigned int PrefixLength) {
		this->Init(Parent, This);
		this->Init(Group, GroupCount, Prefix, PrefixLength);
		this->Type = TrieNodeID;
	}

	template<class foo> ValueTrieNode<foo>::ValueTrieNode(void) {
		this->Type = ValueTrieNodeID;
	}

	unsigned int TrieNode::AddNode(unsigned char *Prefix, int *Charmap, int GroupSize, TrieNode *Node) {
		TrieNode *Result = this;
		unsigned int PrefixIndex = 0, NodeIndex = 0;
		unsigned int success = this->FindNearest(Prefix, Charmap, (TrieNodeBase **) &Result, &PrefixIndex, &NodeIndex);
		unsigned char *p;
		TrieNode *node;

		assert(*Result->This == Result && *Node->This == Node); /* If you get a break here, something has stolen the This value and forgotten to set up a new one.
																 * Don't blame this function. */
	    
		/* The aim of the following group of logic is to create a value node to store our value (the pointer to function, "function").
		 * There are 3 possible situations:
		 * i. The node already exists, whether it's as a branch node or as a value node.
		 * ii. The node doesn't exist, but a branch needs to be split. This handles the following cases:
		 * insertion of "foo" into tree that contains "foobar"
		 *      foobar turns into:
		 *      foo ... bar
		 *        `--.--^
		 * and insertion of "foohba" into tree that contains "foobar"
		 *      foobar turns into:
		 *      foo ... bar
		 *        `--.--^ ... hba
		 *            `-------^
		 * iii. The node doesn't exist, but no branch needs to be split. This handles all of the following cases:
		 *      foo turns into:
		 *      foo ... bar
		 *        `-----^
		 */
	    
		if (success == 1) {
			TrieNode *parent;
			/* situation i. The node already exists. It may or may not have any value members.
			 * If it has no value members, we can safely replace it. This is the purpose of the following block of code. */
			if (Result->Type != TrieNodeID || Result->Parent == NULL) { return 0; }
			parent = *Result->Parent;

			assert(parent != NULL);
			assert(parent->Group != NULL);

			Node->Init(Result->Group, Result->GroupCount, Result->Prefix, Result->PrefixLength);
			Node->Init(Result->Parent, Result->This);
			parent->Group[Charmap[Prefix[PrefixIndex - Result->PrefixLength]]] = (TrieNodeBase *) Node;
			delete Result;
			return PrefixIndex;
			/* return 0; */
		}

		/* situation ii & iii. The node doesn't exist...
		 * a. The path to the node already partially exists, but a branch might need to be split to add the node.
		 *    This is situation ii, and we'll deal with it first. */
        
		/* The following branch executes when a node needs to be inserted between two other existing nodes,
		 * whether due to branching or because that's where the value node lies */
		if (NodeIndex > 0 && NodeIndex < Result->PrefixLength) {
			TrieNodeBase **g;
			TrieNode *parent = *Result->Parent;
	            
			assert(Result->Parent != NULL); /* Well, it helps to know if we're derefing NULL
											 * This might happen if a ->This value fails to allocate.
											 * We should get a different assertion fail before we get here */
			assert(parent != NULL);
			assert(parent->Group != NULL);

			/* situation ii.
			 * The node doesn't exist, and it's path lies between 2 nodes that share a branch for example... in the middle of a branch
			 *    inserting foo or foohba to a trie that contains foobar... the foo part needs to be split off
			 *    and at the end of this block hopefully what we'll end up with is a situation iii. */
            
			/* The prefix string needs to be split from foobar to foo\0 ... bar\0.
			 * ... so allocate some space for foo\0 and copy it over: */
			if (p = new unsigned char[NodeIndex + 1], p == NULL) { return 0; }
            
			memcpy(p, Result->Prefix, NodeIndex), p[NodeIndex] = '\0';
            
			if (g = TrieNodeBaseGroup_Create(GroupSize), g == NULL) {
				delete p;
				return 0;
			}

			/* The following branch executes when adding a node causes a branch fork
			 *    eg. the collection contains "foobar" and we're adding "foobah". The code below will add a "fooba" item to the root node */
			if (Charmap[Prefix[PrefixIndex]] != -1) {
				node = new TrieNode(Result->Parent, g, 1, p, NodeIndex);
			}
            
			/* The following branch executes when adding a node with a prefix that already exists as part of another node's prefix.
			 *    eg. the collection contains "foobar" and we're adding "foo". */
			else {
				node = Node;
				node->Init(g, 1, p, NodeIndex);
				node->Parent = Result->Parent;
			}

			/* node will be allocated in one of the above branches, so it'll also need to be checked :) */
			if (node == NULL) {
				delete g;
				delete p;
				return 0;
			}
            
			/* The newly created node is to be inserted before "foobar" (eg. "foo"). The old node's prefix and prefix length needs updating. */
			memmove(Result->Prefix, Result->Prefix + NodeIndex, Result->PrefixLength -= NodeIndex), Result->Prefix[Result->PrefixLength] = '\0';
            
			/* Insert the new into it's correct (hopefully) position */
			parent->Group[*p] = node;

			/* Add "foobar" as a node within the new node and update it's Parent value to reflect the change */
			node->Group[Result->Prefix[0]] = (TrieNodeBase *) Result;
			Result->Parent = node->This;
			NodeIndex = 0;
			Result = node;
		}
        
		/* The following branch executes when:
		 *
		 * i.  adding a node causes a branch fork
		 *      eg. the collection contains "foobar" and we're adding "foobah". The code above has added a "fooba" item to the root node,
		 *          so we need to add a "h" item to the "fooba" item's nodes.
		 * ii. adding a node is a simple case of just appending the node onto the end of an existing prefix (this actually also covers point i.)
		 *      eg. the collection contains a "foo" item and we're adding "foobar" (eg. adding "bar" to the "foo" item's nodes)
		 *          ---------
		 * ... It will *not* execute when adding a node with a prefix that already exists as part of another node's prefix.
		 *      eg. the collection contains "foobar" and we're adding "foo".
		 */
		if (Charmap[Prefix[PrefixIndex]] != -1) {
			unsigned int len;
			unsigned char *o, *q;
			int x;

			/* Calculate the length of the new node's prefix. */
			/* Fixed a calculation bug here. - Seb */
			for (q = Prefix + PrefixIndex; Charmap[*q] != -1; q++); len = q - (Prefix + PrefixIndex);
            
			/* Allocate the new node's prefix. */
			if (p = new unsigned char[len + 1], p == NULL) { return 0; }
            
			/* Set the new node's prefix. */
			for (o = p, q = Prefix + PrefixIndex; x = Charmap[*q], x != -1; *o++ = (unsigned char) x, q++);
			*o = '\0';
			//for (o = p, q = Prefix + PrefixIndex; *o = Charmap[*q], *o != -1; o++, q++);
            
			/* Initialize the node that will store the event handler */
			Node->Init(Result->This, TrieNodeBaseGroup_Create(GroupSize), 0, p, len);

			Result->Group[*p] = (TrieNodeBase *) Node;
			Result->GroupCount++;
			PrefixIndex += len;
		}
	    
		return PrefixIndex;
	}

	unsigned int TrieNode::RenameNode(unsigned char *SourcePrefix, unsigned char *DestPrefix, int *Charmap, int GroupSize) {
		return 0;
	}

	TrieNode::~TrieNode() {

	}
};
