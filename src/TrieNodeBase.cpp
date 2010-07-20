/* Copyright (c) 2010, Sebastian Ramadan and Andrew Hodges. All rights reserved. */

#include <stdlib.h>
#include <string.h>

#include "Common.h"
#include "TrieNodeBase.h"

namespace TrieNode {
	TrieNodeBase **TrieNodeBaseGroup_Create(int Capacity) {
		TrieNodeBase **g;
		int x;

		g = new TrieNodeBase *[Capacity];
		if (g == NULL) { return NULL; }

		for (x = 0; x < Capacity; x++) { g[x] = NULL; }
	 
		return g;
	}

	TrieNodeBase::TrieNodeBase(void) {
		this->Type = TrieNodeBaseID;
	}

	TrieNodeBase::TrieNodeBase(TrieNodeBase **Group, unsigned int GroupCount, unsigned char *Prefix, unsigned int PrefixLength) {
		this->Init(Group, GroupCount, Prefix, PrefixLength);
		this->Type = TrieNodeBaseID;
	}

	void TrieNodeBase::Init(TrieNodeBase **Group, unsigned int GroupCount, unsigned char *Prefix, unsigned int PrefixLength) {
		this->Group = Group;
		this->GroupCount = GroupCount;
		this->Prefix = Prefix;
		this->PrefixLength = PrefixLength;
	}

	/**
	 * Finds the node identified by the Charmap translation of Prefix, and stores it in Result. If the node can't be found, stores the closest potential parent node in Result instead.
	 * @param Root The root TrieNodeBase to search.
	 * @param Prefix The path of the node to search for.
	 * @param Charmap The translation table used to convert Prefix ie. from lowercase to uppercase.
	 * @param Result A location that will store a pointer to the resulting node.
	 * @param InputPrefixIndex A location that will store the number of bytes parsed from Prefix.
	 * @param NodePrefixIndex A location that will store the number of bytes parsed from Result->Prefix.
	 * @return 1 if the item was successfully located. 0 otherwise.
	 */
	unsigned int TrieNodeBase::FindNearest(unsigned char *Prefix, int *Charmap, TrieNodeBase **Result, unsigned int *InputPrefixIndex, unsigned int *NodePrefixIndex) {
		TrieNodeBase *n = this, **g;
		int c;
		unsigned char *s, *u;
	    
		if (Prefix == NULL || Charmap == NULL || Result == NULL || InputPrefixIndex == NULL || NodePrefixIndex == NULL) { return 0; }
	    
		s = Prefix;
	    
		while (c = Charmap[*s], c != -1) {
			if (g = n->Group, g == NULL) {
				*Result = n;
				*InputPrefixIndex = s - Prefix;
				*NodePrefixIndex = 0;
	            
				return 0;
			}
	        
			if (g[c] == NULL) {
				*Result = n;
				*InputPrefixIndex = s - Prefix;
				*NodePrefixIndex = 0;
	            
				return 0;
			}
	        
			for (n = g[c], u = n->Prefix; c = Charmap[*s], (u - n->Prefix) < n->PrefixLength && c == *u; u++, s++);
	        
			if ((u - n->Prefix) < n->PrefixLength && c != *u) {
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

	TrieNodeBase::~TrieNodeBase() {

	}
};