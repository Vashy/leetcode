#ifndef LEETCODE_INTHASHSET
#define LEETCODE_INTHASHSET

#include <stdbool.h>
#include <stddef.h>

struct HashSetNode
{
    int value;
    struct HashSetNode *next;
    struct HashSetNode *prev;
};

/*!
 * Simple Linked Hash Set implementation using linear probing for collision management
 */
struct IntHashSet
{
    struct HashSetNode **table;
    struct HashSetNode *head;
    struct HashSetNode *tail;
    size_t capacity;
};

struct HashSetNode *inthashset_node_create(int value);
void inthashset_node_destroy(struct HashSetNode *node);
void inthashset_node_display(struct HashSetNode *node);

struct IntHashSet *inthashset_create(size_t initial_capacity);
void inthashset_put(struct IntHashSet *hash_set, int value);
bool inthashset_contains(struct IntHashSet *hash_set, int value);
void inthashset_destroy(struct IntHashSet *hash_set);
void inthashset_display(struct IntHashSet *hash_set);

#endif // !LEETCODE_INTHASHSET
