#include "hashmap.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int _hashmap_hashint(int key, int capacity)
{
    // key = ((key >> 16) ^ key) * 0x45d9f3bu;
    // key = ((key >> 16) ^ key) * 0x45d9f3bu;
    // key = (key >> 16) ^ key;
    return key % capacity;
}

struct HashMap *hashmap_create(size_t initial_capacity)
{
    struct HashMap *hash_map = malloc(sizeof(struct HashMap));
    assert(hash_map != NULL);
    hash_map->table = calloc(initial_capacity, sizeof(struct HashMapNode *));
    assert(hash_map->table != NULL);
    for (size_t i = 0; i < initial_capacity; i++)
    {
        hash_map->table[i] = NULL;
    }
    hash_map->head = NULL;
    hash_map->tail = NULL;
    hash_map->capacity = initial_capacity;
    return hash_map;
}

struct HashMapNode *hashmap_node_create(int key, int value)
{
    struct HashMapNode *node = malloc(sizeof(struct HashMapNode));
    node->next = NULL;
    node->prev = NULL;
    node->key = key;
    node->value = value;
    return node;
}

void hashmap_node_destroy(struct HashMapNode *node)
{
    assert(node != NULL);
    node->next = NULL;
    node->prev = NULL;
    free(node);
}

void hashmap_node_display(struct HashMapNode *node) { printf("Node(%d,%d)", node->key, node->value); }

int hashmap_get(struct HashMap *hash_map, int key)
{
    int hashed_key = _hashmap_hashint(key, hash_map->capacity);
    struct HashMapNode *node = hash_map->table[hashed_key];
    while (node != NULL && node->key != key)
    {
        printf("collision detected! node->key=%d, key=%d\n", node->key, key);
        hashed_key += 1;
        assert(hashed_key <= hash_map->capacity);
        node = hash_map->table[hashed_key];
    }
    if (node == NULL)
    {
        return -1;
    }
    return node->value;
}

void hashmap_display(struct HashMap *hash_map)
{
    struct HashMapNode *current_node = hash_map->head;
    printf("[\n");
    while (current_node != NULL)
    {
        printf("\t");
        hashmap_node_display(current_node);
        printf("\n");
        current_node = current_node->next;
    }
    printf("]\n");
}

void _hashmap_replace_node(struct HashMap *hash_map, struct HashMapNode *existing_node, struct HashMapNode *new_node)
{
    printf("[hashset_put] Found existing node: ");
    hashmap_node_display(existing_node);
    printf("\n");
    printf("[hashset_put] Replacing with new node: ");
    hashmap_node_display(new_node);
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
    if (hash_map->head == existing_node)
    {
        hash_map->head = new_node;
    }
    if (hash_map->tail == existing_node)
    {
        hash_map->tail = new_node;
    }
    printf("[hashset_put] Destroying existing node: ");
    hashmap_node_display(existing_node);
    printf("\n");
    hashmap_node_destroy(existing_node);
}

void hashmap_put(struct HashMap *hash_map, int key, int value)
{
    assert(hash_map != NULL);
    int hashed_key = _hashmap_hashint(key, hash_map->capacity);
    printf("%d, hashed: %d\n", key, hashed_key);

    struct HashMapNode *new_node = hashmap_node_create(key, value);
    assert(new_node != NULL);
    struct HashMapNode *existing_node = hash_map->table[hashed_key];
    while (existing_node != NULL && existing_node->key != new_node->key)
    {
        hashed_key += 1;
        assert(hashed_key != hash_map->capacity);
        existing_node = hash_map->table[hashed_key];
    }

    assert(existing_node == NULL || existing_node->key == new_node->key);
    if (existing_node != NULL)
    {
        _hashmap_replace_node(hash_map, existing_node, new_node);
    }
    else
    {
        if (hash_map->tail != NULL)
        {
            hash_map->tail->next = new_node;
            new_node->prev = hash_map->tail;
            hash_map->tail = new_node;
        }
    }
    if (hash_map->tail == NULL)
    {
        hash_map->tail = new_node;
    }
    if (hash_map->head == NULL)
    {
        hash_map->head = new_node;
    }
    hash_map->table[hashed_key] = new_node;
    assert(hash_map->head->prev == NULL);
    assert(hash_map->tail->next == NULL);
}

void hashmap_destroy(struct HashMap *hash_map)
{
    struct HashMapNode *current_node = hash_map->head;
    while (current_node != NULL)
    {
        struct HashMapNode *node_to_delete = current_node;
        current_node = current_node->next;

        printf("[hashset_destroy] Destroying existing node: ");
        hashmap_node_display(node_to_delete);
        printf("\n");
        free(node_to_delete);
    }
    free(hash_map->table);
    hash_map->capacity = 0;
    hash_map->head = NULL;
    hash_map->tail = NULL;
    free(hash_map);
}
