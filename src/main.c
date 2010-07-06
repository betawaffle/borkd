#define SOCKET int

struct SockListNode {
	int fd;
};

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "EventListNode.c"
#include "EventTrieNode.c"

void IterateNodes(struct TrieNode *root, void (* pre)(struct TrieNode *, int), void (* post)(struct TrieNode *, int), int level) {
	int x;

	if (pre != NULL) {
		pre(root, level);
	}

	for (x = 0; x < 256; x++) {
		if (root->Group[x] != NULL) {
            struct RelativeTrieNode *n = (void *) root->Group[x];
            
            if (*n->Parent != root) { printf("SHIT! PARENT MISMATCH!\n"); }
            
			IterateNodes(root->Group[x], pre, post, level + 1);
		}
	}

	if (post != NULL) {
		post(root, level);
	}
}

void PrintNode(struct TrieNode *node, int level) {
	char buf[1024];
	int x;

	for (x = 0; x < level; x++) buf[x] = ' ';
	buf[x] = '\0';

	printf("%sPrefix: %s\n", buf, node->Prefix);
}

void FreeNode(struct TrieNode *node, int level) {
	/* FIXME: Memory leak here! */
	free(node);
}

unsigned char LowercaseCharmap[] = {
	'\x00',	'\x01',	'\x02',	'\x03',	'\x04',	'\x05',	'\x06',	'\x07',	'\x08',	'\x09',	'\x0A',	'\x0B',	'\x0C',	'\x0D',	'\x0E',	'\x0F',
	'\x10',	'\x11',	'\x12',	'\x13',	'\x14',	'\x15',	'\x16',	'\x17',	'\x18',	'\x19',	'\x1A',	'\x1B',	'\x1C',	'\x1D',	'\x1E',	'\x1F',
	'\x20',	'\x21',	'\x22',	'\x23',	'\x24',	'\x25',	'\x26',	'\x27',	'\x28',	'\x29',	'\x2A',	'\x2B',	'\x2C',	'\x2D',	'\x2E',	'\x2F',
	'\x30',	'\x31',	'\x32',	'\x33',	'\x34',	'\x35',	'\x36',	'\x37',	'\x38',	'\x39',	'\x3A',	'\x3B',	'\x3C',	'\x3D',	'\x3E',	'\x3F',
	'\x40',	'\x61',	'\x62',	'\x63',	'\x64',	'\x65',	'\x66',	'\x67',	'\x68',	'\x69',	'\x6A',	'\x6B',	'\x6C',	'\x6D',	'\x6E',	'\x6F',
	'\x70',	'\x71',	'\x72',	'\x73',	'\x74',	'\x75',	'\x76',	'\x77',	'\x78',	'\x79',	'\x7A',	'\x5B',	'\x5C',	'\x5D',	'\x5E',	'\x5F',
	'\x60',	'\x61',	'\x62',	'\x63',	'\x64',	'\x65',	'\x66',	'\x67',	'\x68',	'\x69',	'\x6A',	'\x6B',	'\x6C',	'\x6D',	'\x6E',	'\x6F',
	'\x70',	'\x71',	'\x72',	'\x73',	'\x74',	'\x75',	'\x76',	'\x77',	'\x78',	'\x79',	'\x7A',	'\x7B',	'\x7C',	'\x7D',	'\x7E',	'\x7F',
	'\x80',	'\x81',	'\x82',	'\x83',	'\x84',	'\x85',	'\x86',	'\x87',	'\x88',	'\x89',	'\x8A',	'\x8B',	'\x8C',	'\x8D',	'\x8E',	'\x8F',
	'\x90',	'\x91',	'\x92',	'\x93',	'\x94',	'\x95',	'\x96',	'\x97',	'\x98',	'\x99',	'\x9A',	'\x9B',	'\x9C',	'\x9D',	'\x9E',	'\x9F',
	'\xA0',	'\xA1',	'\xA2',	'\xA3',	'\xA4',	'\xA5',	'\xA6',	'\xA7',	'\xA8',	'\xA9',	'\xAA',	'\xAB',	'\xAC',	'\xAD',	'\xAE',	'\xAF',
	'\xB0',	'\xB1',	'\xB2',	'\xB3',	'\xB4',	'\xB5',	'\xB6',	'\xB7',	'\xB8',	'\xB9',	'\xBA',	'\xBB',	'\xBC',	'\xBD',	'\xBE',	'\xBF',
	'\xC0',	'\xC1',	'\xC2',	'\xC3',	'\xC4',	'\xC5',	'\xC6',	'\xC7',	'\xC8',	'\xC9',	'\xCA',	'\xCB',	'\xCC',	'\xCD',	'\xCE',	'\xCF',
	'\xD0',	'\xD1',	'\xD2',	'\xD3',	'\xD4',	'\xD5',	'\xD6',	'\xD7',	'\xD8',	'\xD9',	'\xDA',	'\xDB',	'\xDC',	'\xDD',	'\xDE',	'\xDF',
	'\xE0',	'\xE1',	'\xE2',	'\xE3',	'\xE4',	'\xE5',	'\xE6',	'\xE7',	'\xE8',	'\xE9',	'\xEA',	'\xEB',	'\xEC',	'\xED',	'\xEE',	'\xEF',
	'\xF0',	'\xF1',	'\xF2',	'\xF3',	'\xF4',	'\xF5',	'\xF6',	'\xF7',	'\xF8',	'\xF9',	'\xFA',	'\xFB',	'\xFC',	'\xFD',	'\xFE',	'\xFF'
};

void foo(struct SockListNode *Node, unsigned char *Parsed, unsigned char *Unparsed, unsigned char *End) {
	printf("foo called\n");
}

void bar(struct SockListNode *Node, unsigned char *Parsed, unsigned char *Unparsed, unsigned char *End) {
	printf("bar called\n");
}

void foobar(struct SockListNode *Node, unsigned char *Parsed, unsigned char *Unparsed, unsigned char *End) {
	printf("foobar called\n");
}

void foobard(struct SockListNode *Node, unsigned char *Parsed, unsigned char *Unparsed, unsigned char *End) {
	printf("foobar'd called\n");
}

int main(const int argc, const char **argv) {
    struct EventTrieNode *TrieRoot/* = Trie_InitNode((struct TrieNode *) RelativeTrie_CreateNode(NULL), Trie_CreateGroup(), 0, NULL, 0, (Destroy) &RelativeTrie_DestroyNode)*/;
    /*
    struct EventTrieNode *item;
	unsigned int success = 0, inputindex = 0, nodeindex = 0;
    struct TrieNode *t;
    struct TrieNode **n;
    int x;
    */
    char *str;
    /*
    unsigned char charmap[] = {
        0x00,    0x01,    0x02,    0x03,    0x04,    0x05,    0x06,    0x07,    0x08,    0x09,    0x0a,    0x0b,    0x0c,    0x0d,    0x0e,    0x0f,
        0x10,    0x11,    0x12,    0x13,    0x14,    0x15,    0x16,    0x17,    0x18,    0x19,    0x1a,    0x1b,    0x1c,    0x1d,    0x1e,    0x1f,
        0x20,    0x21,    0x22,    0x23,    0x24,    0x25,    0x26,    0x27,    0x28,    0x29,    0x2a,    0x2b,    0x2c,    0x2d,    0x2e,    0x2f,
        0x30,    0x31,    0x32,    0x33,    0x34,    0x35,    0x36,    0x37,    0x38,    0x39,    0x3a,    0x3b,    0x3c,    0x3d,    0x3e,    0x3f,
        0x40,    0x41,    0x42,    0x43,    0x44,    0x45,    0x46,    0x47,    0x48,    0x49,    0x4a,    0x4b,    0x4c,    0x4d,    0x4e,    0x4f,
        0x50,    0x51,    0x52,    0x53,    0x54,    0x55,    0x56,    0x57,    0x58,    0x59,    0x5a,    0x5b,    0x5c,    0x5d,    0x5e,    0x5f,
        0x60,    0x61,    0x62,    0x63,    0x64,    0x65,    0x66,    0x67,    0x68,    0x69,    0x6a,    0x6b,    0x6c,    0x6d,    0x6e,    0x6f,
        0x70,    0x71,    0x72,    0x73,    0x74,    0x75,    0x76,    0x77,    0x78,    0x79,    0x7a,    0x7b,    0x7c,    0x7d,    0x7e,    0x7f,
        0x80,    0x81,    0x82,    0x83,    0x84,    0x85,    0x86,    0x87,    0x88,    0x89,    0x8a,    0x8b,    0x8c,    0x8d,    0x8e,    0x8f,
        0x90,    0x91,    0x92,    0x93,    0x94,    0x95,    0x96,    0x97,    0x98,    0x99,    0x9a,    0x9b,    0x9c,    0x9d,    0x9e,    0x9f,
        0xa0,    0xa1,    0xa2,    0xa3,    0xa4,    0xa5,    0xa6,    0xa7,    0xa8,    0xa9,    0xaa,    0xab,    0xac,    0xad,    0xae,    0xaf,
        0xb0,    0xb1,    0xb2,    0xb3,    0xb4,    0xb5,    0xb6,    0xb7,    0xb8,    0xb9,    0xba,    0xbb,    0xbc,    0xbd,    0xbe,    0xbf,
        0xc0,    0xc1,    0xc2,    0xc3,    0xc4,    0xc5,    0xc6,    0xc7,    0xc8,    0xc9,    0xca,    0xcb,    0xcc,    0xcd,    0xce,    0xcf,
        0xd0,    0xd1,    0xd2,    0xd3,    0xd4,    0xd5,    0xd6,    0xd7,    0xd8,    0xd9,    0xda,    0xdb,    0xdc,    0xdd,    0xde,    0xdf,
        0xe0,    0xe1,    0xe2,    0xe3,    0xe4,    0xe5,    0xe6,    0xe7,    0xe8,    0xe9,    0xea,    0xeb,    0xec,    0xed,    0xee,    0xef,
        0xf0,    0xf1,    0xf2,    0xf3,    0xf4,    0xf5,    0xf6,    0xf7,    0xf8,    0xf9,    0xfa,    0xfb,    0xfc,    0xfd,    0xfe,    0xff
    };
    */
    
#define TEST_START(i, name) printf("*** Test %d *** : %s\n\n", i, name);\
    TrieRoot = (struct EventTrieNode *) Trie_InitNode((struct TrieNode *) RelativeTrie_CreateNode(NULL), Trie_CreateGroup(), 0, NULL, 0, (Destroy) &RelativeTrie_DestroyNode)
#define TEST(s) str = s; printf("Trie_AddNode(\"%s\"): %u\n", str, EventTrie_AddNode((struct TrieNode *) TrieRoot, (unsigned char *) str, LowercaseCharmap, (void *) str))
#define TEST_END() IterateNodes((struct TrieNode *) TrieRoot, PrintNode, NULL, 0);\
    IterateNodes((struct TrieNode *) TrieRoot, NULL, FreeNode, 0);\
    printf("-----\n\n")
    
    TEST_START(1, "Append");
    TEST("foo");
    TEST("foobar");
	TEST_END();
    
    TEST_START(2, "Truncate & Append");
	TEST("foobar");
    TEST("foo");
	TEST_END();
    
    TEST_START(3, "Fork");
	TEST("foo");
    TEST("f00");
	TEST_END();
    
    TEST_START(4, "Append, Append");
	TEST("foo");
    TEST("foobar");
    TEST("foobar'd");
	TEST_END();
    
    TEST_START(5, "Append, Truncate & Append");
	TEST("foo");
    TEST("foobar'd");
    TEST("foobar");
	TEST_END();
    
    TEST_START(6, "Append, Fork");
    TEST("foo");
    TEST("foobar");
    TEST("foob4r");
	TEST_END();
    
    TEST_START(7, "Truncate & Append, Append");
    TEST("foobar");
    TEST("foo");
    TEST("foobar'd");
	TEST_END();
    
    TEST_START(8, "Truncate & Append, Truncate & Append");
    TEST("foobar'd");
    TEST("foobar");
    TEST("foo");
	TEST_END();
    
    TEST_START(9, "Truncate & Append, Fork");
    TEST("foobar");
    TEST("foo");
    TEST("foob4r");
	TEST_END();
    
    TEST_START(10, "Fork, Append");
    TEST("foobar");
    TEST("foob4r");
    TEST("foobar'd");
	TEST_END();
    
    TEST_START(11, "Fork, Truncate & Append");
    TEST("foobar");
    TEST("foob4r");
    TEST("foo");
	TEST_END();
    
    TEST_START(12, "Fork, Fork");
    TEST("foobar");
    TEST("foobah");
    TEST("foob4r");
	TEST_END();
    
#undef TEST_START()
#undef TEST()
#undef TEST_END()
    
	/*
	EventTrie_AddNode(TrieRoot, "BAR", LowercaseCharmap, bar);
	EventTrie_AddNode(TrieRoot, "FUBAR", LowercaseCharmap, fubar);
	EventTrie_AddNode(TrieRoot, "FOO", LowercaseCharmap, foo);
	EventTrie_AddNode(TrieRoot, "FOOBAR", LowercaseCharmap, foobar);

	// fetching this item, yeh? ---------------------------------.
	//                                                           v
	success = Trie_FindNearest((struct TrieNode *) TrieRoot, "FOOBAR", LowercaseCharmap, &item, &inputindex, &nodeindex);
	if (success == 0) {
		printf("item was not found\n");
	}
	else if (item->Node.Node.Destroy != EventTrie_DestroyNode) {
		printf("item does not contain events.");
	}
	else {
		// call the list of handlers that it contains
		EventListNode_Raise(NULL, item->EventList, NULL, NULL, NULL);
	}
	*/

	//getchar();
	return 0;
}