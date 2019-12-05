#ifndef HASHMAP_H
#define HASHMAP_H

#include "stdint.h"

const static int DEFAULT_SIZE = 1 << 4;
const static double LOAD_FACTOR = .75;

typedef struct hashmap_entry *hashmap_entry_t;

struct hashmap_entry {
    hashmap_entry_t *next_entry;
    void *key;
    void *value;
};

typedef struct {
    hashmap_entry_t *entries;
    size_t size;
    size_t count;
} hashmap_t;

hashmap_t *hashmap_alloc(size_t size);

hashmap_t *hashmap_alloc_default(size_t size);

void* hashmap_get(hashmap_t*, void *);

void hashmap_put(hashmap_t *hashmap, void *key, void *value);

void hashmap_update(hashmap_t *hashmap, void *key, void *new_value);

void hashmap_remove(hashmap_t *hashmap, void *key);

void hashmap_clear(hashmap_t*);

void hashmap_dealloc(hashmap_t*);

#endif