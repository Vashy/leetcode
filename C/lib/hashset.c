#include "hashset.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int _hashint(int value, int capacity) { return value % capacity; }

struct IntHashSet *inthashset_create(size_t initial_capacity)
{
    struct IntHashSet *hash_set = malloc(sizeof(struct IntHashSet));
    assert(hash_set != NULL);
    hash_set->table = calloc(initial_capacity, sizeof(struct HashSetNode *));
    assert(hash_set->table != NULL);
    for (size_t i = 0; i < initial_capacity; i++)
    {
        hash_set->table[i] = NULL;
    }
    hash_set->head = NULL;
    hash_set->tail = NULL;
    hash_set->capacity = initial_capacity;
    return hash_set;
}

struct HashSetNode *inthashset_node_create(int value)
{
    struct HashSetNode *node = malloc(sizeof(struct HashSetNode));
    node->next = NULL;
    node->prev = NULL;
    node->value = value;
    return node;
}

void inthashset_node_destroy(struct HashSetNode *node)
{
    assert(node != NULL);
    node->next = NULL;
    node->prev = NULL;
    free(node);
}

void inthashset_node_display(struct HashSetNode *node) { printf("%d", node->value); }

bool inthashset_contains(struct IntHashSet *hash_set, int value)
{
    int hashed_key = _hashint(value, hash_set->capacity);
    struct HashSetNode *node = hash_set->table[hashed_key];
    while (node != NULL && node->value != value)
    {
        printf("collision detected! node->value=%d, value=%d\n", node->value, value);
        hashed_key += 1;
        assert(hashed_key <= hash_set->capacity);
        node = hash_set->table[hashed_key];
    }
    if (node == NULL)
    {
        return false;
    }
    return true;
}

void inthashset_display(struct IntHashSet *hash_set)
{
    struct HashSetNode *current_node = hash_set->head;
    printf("[\n");
    while (current_node != NULL)
    {
        printf("\t");
        inthashset_node_display(current_node);
        printf("\n");
        current_node = current_node->next;
    }
    printf("]\n");
}

void _hashset_replace_node(struct IntHashSet *hash_set, struct HashSetNode *existing_node, struct HashSetNode *new_node)
{
    printf("[hashset_put] Found existing node: ");
    inthashset_node_display(existing_node);
    printf("\n");
    printf("[hashset_put] Replacing with new node: ");
    inthashset_node_display(new_node);
    printf("\n");
    if (existing_node->prev != NULL)
    {
        existing_node->prev->next = new_node;
        new_node->prev = existing_node->prev;
    }
    if (existing_node->next != NULL)
    {
        existing_node->next->prev = new_node;
        new_node->next = existing_node->next;
    }
    if (hash_set->head == existing_node)
    {
        hash_set->head = new_node;
    }
    if (hash_set->tail == existing_node)
    {
        hash_set->tail = new_node;
    }
    printf("[hashset_put] Destroying existing node: ");
    inthashset_node_display(existing_node);
    printf("\n");
    inthashset_node_destroy(existing_node);
}

void inthashset_put(struct IntHashSet *hash_set, int value)
{
    assert(hash_set != NULL);
    int hashed_key = _hashint(value, hash_set->capacity);
    printf("%d, hashed: %d\n", value, hashed_key);

    struct HashSetNode *new_node = inthashset_node_create(value);
    assert(new_node != NULL);
    struct HashSetNode *existing_node = hash_set->table[hashed_key];
    while (existing_node != NULL && existing_node->value != new_node->value)
    {
        hashed_key += 1;
        assert(hashed_key != hash_set->capacity);
        existing_node = hash_set->table[hashed_key];
    }

    assert(existing_node == NULL || existing_node->value == new_node->value);
    if (existing_node != NULL)
    {
        _hashset_replace_node(hash_set, existing_node, new_node);
    }
    else
    {
        if (hash_set->tail != NULL)
        {
            hash_set->tail->next = new_node;
            new_node->prev = hash_set->tail;
            hash_set->tail = new_node;
        }
    }
    if (hash_set->tail == NULL)
    {
        hash_set->tail = new_node;
    }
    if (hash_set->head == NULL)
    {
        hash_set->head = new_node;
    }
    hash_set->table[hashed_key] = new_node;
    assert(hash_set->head->prev == NULL);
    assert(hash_set->tail->next == NULL);
}

void inthashset_destroy(struct IntHashSet *hash_set)
{
    struct HashSetNode *current_node = hash_set->head;
    while (current_node != NULL)
    {
        struct HashSetNode *node_to_delete = current_node;
        current_node = current_node->next;

        printf("[hashset_destroy] Destroying existing node: ");
        inthashset_node_display(node_to_delete);
        printf("\n");
        free(node_to_delete);
    }
    free(hash_set->table);
    hash_set->capacity = 0;
    hash_set->head = NULL;
    hash_set->tail = NULL;
    free(hash_set);
}
