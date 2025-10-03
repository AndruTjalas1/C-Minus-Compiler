#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringpool.h"

StringPool string_pool = {0};

void init_string_pool() {
    string_pool.pool = malloc(STRING_POOL_SIZE);
    string_pool.pool_used = 0;
    string_pool.unique_strings = 0;
    string_pool.total_requests = 0;
    memset(string_pool.buckets, 0, sizeof(string_pool.buckets));
}

char* intern_string(const char* str) {
    if (!str) return NULL;
    
    string_pool.total_requests++;

    unsigned int hash = 0;
    const char* p = str;
    while(*p) {
        hash = hash * 31 + *p++;
    }
    hash %= STRING_HASH_SIZE;

    // Check if already interned
    StringNode* node = string_pool.buckets[hash];
    while(node) {
        if(strcmp(node->str, str) == 0) {
            return node->str;  // Return existing
        }
        node = node->next;
    }

    // Add new string
    size_t len = strlen(str) + 1;
    if(string_pool.pool_used + len > STRING_POOL_SIZE) {
        // Pool full, fallback to strdup
        return strdup(str);
    }

    char* interned = string_pool.pool + string_pool.pool_used;
    strcpy(interned, str);
    string_pool.pool_used += len;

    // Add to hash table
    StringNode* new_node = malloc(sizeof(StringNode));
    new_node->str = interned;
    new_node->next = string_pool.buckets[hash];
    string_pool.buckets[hash] = new_node;

    string_pool.unique_strings++;
    return interned;
}

void print_string_stats() {
    printf("\n=== String Pool Statistics ===\n");
    printf("Total requests: %d\n", string_pool.total_requests);
    printf("Unique strings: %d\n", string_pool.unique_strings);
    printf("Pool used: %zu / %d bytes (%.1f%%)\n", 
           string_pool.pool_used, STRING_POOL_SIZE,
           (double)string_pool.pool_used / STRING_POOL_SIZE * 100.0);
    int saved = string_pool.total_requests - string_pool.unique_strings;
    if (string_pool.total_requests > 0) {
        printf("Duplicate strings avoided: %d (%.1f%% reduction)\n", 
               saved, (double)saved / string_pool.total_requests * 100.0);
    }
}

void free_string_pool() {
    // Free all nodes in the hash table
    for (int i = 0; i < STRING_HASH_SIZE; i++) {
        StringNode* node = string_pool.buckets[i];
        while (node) {
            StringNode* next = node->next;
            free(node);
            node = next;
        }
    }
    
    // Free the pool
    if (string_pool.pool) {
        free(string_pool.pool);
    }
}
