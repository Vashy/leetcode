#ifndef LEETCODE_HASHMAP
#define LEETCODE_HASHMAP

#include <stddef.h>

struct HashMapNode
{
    int key;
    int value;
    struct HashMapNode *next;
    struct HashMapNode *prev;
};

/*!
 * Simple Linked Hash Map implementation using linear probing for collision management
 */
struct HashMap
{
    struct HashMapNode **table;
    struct HashMapNode *head;
    struct HashMapNode *tail;
    size_t capacity;
};

struct HashMapNode *hashmap_node_create(int key, int value);
void hashmap_node_destroy(struct HashMapNode *node);
void hashmap_node_display(struct HashMapNode *node);

struct HashMap *hashmap_create(size_t initial_capacity);
void hashmap_put(struct HashMap *hash_map, int key, int value);
int hashmap_get(struct HashMap *hash_map, int key);
void hashmap_destroy(struct HashMap *hash_map);
void hashmap_display(struct HashMap *hash_map);

#endif // !LEETCODE_HASHMAP
