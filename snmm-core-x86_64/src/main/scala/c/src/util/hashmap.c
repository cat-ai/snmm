#include "stdlib.h"
#include "hashmap.h"

static int hash(void *ptr, int size) {
    return (int)(long)ptr % size;
}

static hashmap_entry_t *hashmap_entries_alloc(size_t size) {
    return calloc(size, sizeof(hashmap_entry_t));
}

static hashmap_entry_t hashmap_entry_alloc(void *key, void *value) {
    hashmap_entry_t item = (hashmap_entry_t) malloc(sizeof(struct hashmap_entry));
    item->key = key;
    item->value = value;
    return item;
}

static void hashmap_recalc_hash_of_entries(hashmap_t *hashmap) {
    size_t size = hashmap->size << 1;

    hashmap_entry_t *entries = hashmap->entries;
    hashmap_entry_t *alloc_entries = calloc(size, sizeof(hashmap_entry_t));

    for (int i = 0; i < hashmap->size; i++) {
        hashmap_entry_t entry = entries[i];
        while (entry != NULL) {
            int entries_key_hash = hash(entry->key, size);
            hashmap_entry_t *next_entry = entry->next_entry;
            entry->next_entry = (hashmap_entry_t *) alloc_entries[entries_key_hash];
            alloc_entries[entries_key_hash] = entry;
            entry = next_entry;
        }
    }

    hashmap_clear(hashmap);
    hashmap->entries = alloc_entries;
    hashmap->size = size;
}

hashmap_t *hashmap_alloc(size_t size) {
    hashmap_t *hashmap = (hashmap_t*) malloc(sizeof(hashmap_t));
    hashmap->entries = hashmap_entries_alloc(size);
    hashmap->size = size;
    hashmap->count = 0;
    return hashmap;
}

hashmap_t *hashmap_alloc_default() {
    return hashmap_alloc(DEFAULT_SIZE);
}

void *hashmap_get(hashmap_t *hashmap, void *key) {
    int key_hash = hash(key, hashmap->size);
    hashmap_entry_t entry = hashmap->entries[key_hash];

    while (entry != NULL) {
        if (entry->key == key) {
            return entry->value;
        }

        entry = *entry->next_entry;
    }
    return NULL;
}

static void hashmap_put_entry(hashmap_t *hashmap, hashmap_entry_t *entry_ptr, void *key, void *value) {
    hashmap_entry_t temp = *entry_ptr;
    *entry_ptr = hashmap_entry_alloc(key, value);

    hashmap_entry_t entry = *entry_ptr;
    entry->next_entry = temp;

    if ((++hashmap->count) >= hashmap->size * LOAD_FACTOR) {
        hashmap_recalc_hash_of_entries(hashmap);
    }
}

void hashmap_put(hashmap_t *hashmap, void *key, void *value) {
    int key_hash = hash(key, hashmap->size);

    hashmap_entry_t *entry_at_hash = &hashmap->entries[key_hash];
    hashmap_put_entry(hashmap, entry_at_hash, key, value);
}

void hashmap_update(hashmap_t *hashmap, void *key, void *new_value) {
    int key_hash = hash(key, hashmap->size);

    hashmap_entry_t *ptr_to_entry = &hashmap->entries[key_hash];
    hashmap_entry_t entry = *ptr_to_entry;

    while (entry != NULL) {
        if (entry->key == key) {
            entry->value = new_value;
            return;
        }
        entry = *entry->next_entry;
    }
}

void hashmap_remove(hashmap_t *hashmap, void *key) {
    int key_hash = hash(key, hashmap->size);
    hashmap_entry_t entry = hashmap->entries[key_hash];

    if (entry == NULL) {
        return;
    } else if (entry->next_entry == NULL) {
        free(entry);
        hashmap->entries[key_hash] = NULL;
        hashmap->count--;
        return;
    } else {
        hashmap_entry_t next_entry;

        while (entry != NULL) {
            next_entry = entry->next_entry;
            if (next_entry != NULL && next_entry->key == key) {
                entry->next_entry = next_entry->next_entry;
                hashmap->count--;
                free(next_entry);
                return;
            }
            entry = next_entry;
        }
    }
}

void hashmap_clear(hashmap_t *hashmap) {
    free(hashmap->entries);
}

void hashmap_dealloc(hashmap_t *hashmap) {
    hashmap_entry_t entry;

    for (int i = 0; i < hashmap->size; i++) {
        entry = hashmap->entries[i];
        while (entry != NULL) {
            hashmap_entry_t next_entry = *entry->next_entry;
            free(entry);
            entry = next_entry;
        }
    }
    hashmap_clear(hashmap);
    free(hashmap);
}