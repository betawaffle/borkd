/* Copyright (c) 2010, Sebastian Ramadan and Andrew Hodges. All rights reserved. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "EventTrieNode.h"

void IterateNodes(TrieNodeBase root, void (*pre)(TrieNodeBase, int), void (*post)(TrieNodeBase, int), int depth) {
    int  x; /* please leave variables at the top of their blocks, because some people use stupid-C89 compilers :P - Seb */
    if (pre != NULL) {
        pre(root, depth);
    }
    
    for (x = 0; x < 256; x++) {
        if (root->Group[x] != NULL) {
            TrieNode n = (void *) root->Group[x];
            
			assert(*n->This == n);
            assert(*n->Parent == (TrieNode) root);
            assert(depth < 1024);

            IterateNodes((TrieNodeBase) n, pre, post, depth + 1);
        }
    }
    
    if (post != NULL) {
        post(root, depth);
    }
}

void PrintNode(TrieNodeBase node, int depth) {
    int  x;
    for (x = 0; x < depth; x++) putchar(' ');
    
    printf("Prefix: %s\n", node->Prefix);
}

void FreeNode(TrieNodeBase node, int depth) {
    /* FIXME: Memory leak here! */
    
    free(node);
}

unsigned char DefaultCharmap[] = {
    '\x00', '\x01', '\x02', '\x03', '\x04', '\x05', '\x06', '\x07', '\x08', '\x09', '\x0A', '\x0B', '\x0C', '\x0D', '\x0E', '\x0F',
    '\x10', '\x11', '\x12', '\x13', '\x14', '\x15', '\x16', '\x17', '\x18', '\x19', '\x1A', '\x1B', '\x1C', '\x1D', '\x1E', '\x1F',
    '\x20', '\x21', '\x22', '\x23', '\x24', '\x25', '\x26', '\x27', '\x28', '\x29', '\x2A', '\x2B', '\x2C', '\x2D', '\x2E', '\x2F',
    '\x30', '\x31', '\x32', '\x33', '\x34', '\x35', '\x36', '\x37', '\x38', '\x39', '\x3A', '\x3B', '\x3C', '\x3D', '\x3E', '\x3F',
    '\x40', '\x61', '\x62', '\x63', '\x64', '\x65', '\x66', '\x67', '\x68', '\x69', '\x6A', '\x6B', '\x6C', '\x6D', '\x6E', '\x6F',
    '\x70', '\x71', '\x72', '\x73', '\x74', '\x75', '\x76', '\x77', '\x78', '\x79', '\x7A', '\x5B', '\x5C', '\x5D', '\x5E', '\x5F',
    '\x60', '\x61', '\x62', '\x63', '\x64', '\x65', '\x66', '\x67', '\x68', '\x69', '\x6A', '\x6B', '\x6C', '\x6D', '\x6E', '\x6F',
    '\x70', '\x71', '\x72', '\x73', '\x74', '\x75', '\x76', '\x77', '\x78', '\x79', '\x7A', '\x7B', '\x7C', '\x7D', '\x7E', '\x7F',
    '\x80', '\x81', '\x82', '\x83', '\x84', '\x85', '\x86', '\x87', '\x88', '\x89', '\x8A', '\x8B', '\x8C', '\x8D', '\x8E', '\x8F',
    '\x90', '\x91', '\x92', '\x93', '\x94', '\x95', '\x96', '\x97', '\x98', '\x99', '\x9A', '\x9B', '\x9C', '\x9D', '\x9E', '\x9F',
    '\xA0', '\xA1', '\xA2', '\xA3', '\xA4', '\xA5', '\xA6', '\xA7', '\xA8', '\xA9', '\xAA', '\xAB', '\xAC', '\xAD', '\xAE', '\xAF',
    '\xB0', '\xB1', '\xB2', '\xB3', '\xB4', '\xB5', '\xB6', '\xB7', '\xB8', '\xB9', '\xBA', '\xBB', '\xBC', '\xBD', '\xBE', '\xBF',
    '\xC0', '\xC1', '\xC2', '\xC3', '\xC4', '\xC5', '\xC6', '\xC7', '\xC8', '\xC9', '\xCA', '\xCB', '\xCC', '\xCD', '\xCE', '\xCF',
    '\xD0', '\xD1', '\xD2', '\xD3', '\xD4', '\xD5', '\xD6', '\xD7', '\xD8', '\xD9', '\xDA', '\xDB', '\xDC', '\xDD', '\xDE', '\xDF',
    '\xE0', '\xE1', '\xE2', '\xE3', '\xE4', '\xE5', '\xE6', '\xE7', '\xE8', '\xE9', '\xEA', '\xEB', '\xEC', '\xED', '\xEE', '\xEF',
    '\xF0', '\xF1', '\xF2', '\xF3', '\xF4', '\xF5', '\xF6', '\xF7', '\xF8', '\xF9', '\xFA', '\xFB', '\xFC', '\xFD', '\xFE', '\xFF'
};

/*
void foo(SockListNode Node, unsigned char *Parsed, unsigned char *Unparsed, unsigned char *End) {
    printf("foo called\n");
}

void bar(SockListNode Node, unsigned char *Parsed, unsigned char *Unparsed, unsigned char *End) {
    printf("bar called\n");
}

void foobar(SockListNode Node, unsigned char *Parsed, unsigned char *Unparsed, unsigned char *End) {
    printf("foobar called\n");
}

void foobard(SockListNode Node, unsigned char *Parsed, unsigned char *Unparsed, unsigned char *End) {
    printf("foobar'd called\n");
}
*/

int main(const int argc, const char *argv[]) {
    TrieNode TrieRoot;
    char *str;
    
#define TEST_START(i, name) printf("*** Test %d *** : %s\n\n", i, name);\
    TrieRoot = (TrieNode) TrieNodeBase_Init((TrieNodeBase) TrieNode_Create(NULL), TrieNodeBaseGroup_Create(), 0, NULL, 0, TrieNodeBaseDestructor)
#define TEST(s) str = s; printf("Trie_AddNode(\"%s\"): %u\n", str, EventTrie_AddNode((TrieNode) TrieRoot, (unsigned char *) str, DefaultCharmap, (void *) str))
#define TEST_END() IterateNodes((TrieNodeBase) TrieRoot, PrintNode, NULL, 0);\
    IterateNodes((TrieNodeBase) TrieRoot, NULL, FreeNode, 0);\
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
    
#undef TEST_END()
#undef TEST()
#undef TEST_START()
    
#if 0 /* How To Use. -- Andrew Hodges (07/06/2010) */
    EventTrieNode item;
    unsigned int inputindex = 0, nodeindex = 0;
    
    TrieNode_Add(TrieRoot, "BAR", DefaultCharmap, bar);
    TrieNode_Add(TrieRoot, "FUBAR", DefaultCharmap, fubar);
    TrieNode_Add(TrieRoot, "FOO", DefaultCharmap, foo);
    TrieNode_Add(TrieRoot, "FOOBAR", DefaultCharmap, foobar);

    /* Fetching this item, yeh? ----------------------------------------.
     *                                                                vvvvvv */
    int success; success = Trie_FindNearest((TrieNodeBase) TrieRoot, "FOOBAR", DefaultCharmap, (TrieNodeBase) &item, &inputindex, &nodeindex);
    if (success == 0) {
        printf("item was not found\n");
    } else if (item->Node.Node.Destroy != EventTrieNode_Destroy) {
        printf("item does not contain events.");
    } else { /* Call the list of handlers that it contains. */
        EventListNode_Raise(NULL, item->EventList, NULL, NULL, NULL);
    }
#endif
    
    return 0;
}