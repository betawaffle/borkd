/* Copyright (c) 2010, Sebastian Ramadan and Andrew Hodges. All rights reserved. */

#ifndef INCLUDED_EventTrieNode_H
#define INCLUDED_EventTrieNode_H

/**
 * @file EventTrieNode.h
 * @brief Extension of the TrieNode structure for storing Event handlers in the form of EventList structures (EventTrieNode)..
 */

//#include "EventListNode.h"
#include "TrieNode.h"

namespace TrieNode {
	/**
	 * @struct EventTrieNode
	 * @brief Value node for a trie that stores event handlers
	 * @extends TrieNode
	 */
	typedef void *EventHandler;
	class EventTrieNode : public ValueTrieNode<EventHandler> {
	public:
		EventTrieNode();
	};
};

#endif
