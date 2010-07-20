/* Copyright (c) 2010, Sebastian Ramadan and Andrew Hodges. All rights reserved. */

#ifndef INCLUDED_TrieNodeBase_H
#define INCLUDED_TrieNodeBase_H

/** 
 * @file TrieNodeBase.h
 * @brief Generic prefix TrieNodeBase class.
 */

namespace TrieNode {
	typedef int TrieNodeTypeID;
	static const TrieNodeTypeID TrieNodeBaseID = 0;

	class TrieNodeBase;
	TrieNodeBase **TrieNodeBaseGroup_Create(int Capacity);

	class TrieNodeBase {
	protected:
	    
	public:
		TrieNodeTypeID Type;

		TrieNodeBase **Group;
		unsigned int GroupCount;

		unsigned char *Prefix;
		unsigned int PrefixLength;

		TrieNodeBase(void);
		TrieNodeBase(TrieNodeBase **Group, unsigned int GroupCount, unsigned char *Prefix, unsigned int PrefixLength);
		void Init(TrieNodeBase **Group, unsigned int GroupCount, unsigned char *Prefix, unsigned int PrefixLength);
		unsigned int FindNearest(unsigned char *Prefix, int *Charmap, TrieNodeBase **Result, unsigned int *InputPrefixIndex, unsigned int *NodePrefixIndex);
		~TrieNodeBase();
	};
};

#endif
