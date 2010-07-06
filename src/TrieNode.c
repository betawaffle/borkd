#ifndef __TRIENODE_C
#define __TRIENODE_C

// Copyright Seb Ramadan, 2009.
/** \file TrieNode.c
 *  \brief Generic prefix TrieNode structures and functions for initializing/creating/finding/destroying generic prefix TrieNode instances.
 */

typedef void (* Destroy)(struct TrieNode *value);
typedef void (* Create)(struct TrieNode **Group, unsigned int GroupCount, unsigned char *Prefix, unsigned int PrefixLength, Destroy *Destroy);

struct TrieNode *Trie_InitNode(struct TrieNode *Node, struct TrieNode **Group, unsigned int GroupCount, unsigned char *Prefix, unsigned int PrefixLength, Destroy Destroy);
struct TrieNode *Trie_CreateNode(struct TrieNode **Group, unsigned int GroupCount, unsigned char *Prefix, unsigned int PrefixLength, Destroy Destroy);
unsigned int Trie_FindNearest(struct TrieNode *Root, unsigned char *Prefix, unsigned char *Charmap, struct TrieNode **Result, unsigned int *InputPrefixIndex, unsigned int *NodePrefixIndex);
void Trie_DestroyNode(struct TrieNode *Node);

struct TrieNode {
    Destroy Destroy;

    struct TrieNode **Group;
    unsigned int GroupCount;
 
    unsigned char *Prefix;
    unsigned int PrefixLength;
};
 
struct TrieNode **Trie_CreateGroup() {
    struct TrieNode **g; g = malloc(256 * sizeof (*g));
    
    if (g == NULL) { return NULL; }
 
    return memset(g, 0, 256 * sizeof (*g));
}

struct TrieNode *Trie_InitNode(struct TrieNode *Node, struct TrieNode **Group, unsigned int GroupCount, unsigned char *Prefix, unsigned int PrefixLength, Destroy Destroy) {
    if (Node == NULL) { return NULL; }
    
    Node->Group = Group;
    Node->GroupCount = GroupCount;
    Node->Prefix = Prefix;
    Node->PrefixLength = PrefixLength;
    Node->Destroy = Destroy;
    
    return Node;
}
 
struct TrieNode *Trie_CreateNode(struct TrieNode **Group, unsigned int GroupCount, unsigned char *Prefix, unsigned int PrefixLength, Destroy Destroy) {
    return Trie_InitNode(malloc(sizeof (struct TrieNode)), Group, GroupCount, Prefix, PrefixLength, Destroy);
}

/**
 *  Finds the node identified by the Charmap translation of Prefix, and stores it in Result. If the node can't be found, stores the closest potential parent node in Result instead.
 *  \param Root The root TrieNode to search.
 *  \param Prefix The path of the node to search for.
 *  \param Charmap The translation table used to convert Prefix ie. from lowercase to uppercase.
 *  \param Result A location that will store a pointer to the resulting node.
 *  \param InputPrefixIndex A location that will store the number of bytes parsed from Prefix.
 *  \param NodePrefixIndex A location that will store the number of bytes parsed from Result->Prefix.
 *  \return 1 if the item was successfully located. 0 otherwise.
 */
unsigned int Trie_FindNearest(struct TrieNode *Root, unsigned char *Prefix, unsigned char *Charmap, struct TrieNode **Result, unsigned int *InputPrefixIndex, unsigned int *NodePrefixIndex) {
	struct TrieNode *n = Root, **g;
	unsigned char c, *s, /* *t, */ *u;

	if (Root == NULL || Prefix == NULL || Charmap == NULL || Result == NULL || InputPrefixIndex == NULL || NodePrefixIndex == NULL) { return 0; }

	s = Prefix;
	
	while (c = Charmap[*s]) {
		g = n->Group;
		if (g == NULL) {
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

		n = g[c];
		for (u = n->Prefix; (c = Charmap[*s]) == *u && c; u++, s++);

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

void Trie_DestroyNode(struct TrieNode *Node) {

}
#endif
