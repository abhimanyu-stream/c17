#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 20000

typedef struct entry_t
{
    char *key;
    char *value;
    struct entry_t *next;
} entry_t;

typedef struct
{
    entry_t **entries;
} ht_t;

unsigned int hash(const char *key)
{
    unsigned long int value = 0;
    unsigned int i = 0;
    unsigned int key_len = strlen(key);

    // do several rounds of multiplication
    for (; i < key_len; ++i)
    {
        value = value * 37 + key[i];
    }

    // make sure value is 0 <= value < TABLE_SIZE
    value = value % TABLE_SIZE;

    return value;
}

entry_t *ht_pair(const char *key, const char *value)
{
    // allocate the entry
    entry_t *entry = malloc(sizeof(entry_t) * 1);
    entry->key = malloc(strlen(key) + 1);
    entry->value = malloc(strlen(value) + 1);

    // copy the key and value in place
    strcpy(entry->key, key);
    strcpy(entry->value, value);

    // next starts out null but may be set later on
    entry->next = NULL;

    return entry;
}

ht_t *ht_create(void)
{
    // allocate table
    ht_t *hashtable = malloc(sizeof(ht_t) * 1);

    // allocate table entries
    hashtable->entries = malloc(sizeof(entry_t *) * TABLE_SIZE);

    // set each to null (needed for proper operation)
    int i = 0;
    for (; i < TABLE_SIZE; ++i)
    {
        hashtable->entries[i] = NULL;
    }

    return hashtable;
}

void ht_set(ht_t *hashtable, const char *key, const char *value)
{
    unsigned int slot = hash(key);

    // try to look up an entry set
    entry_t *entry = hashtable->entries[slot];

    // no entry means slot empty, insert immediately
    if (entry == NULL)
    {
        hashtable->entries[slot] = ht_pair(key, value);
        return;
    }

    entry_t *prev;

    // walk through each entry until either the end is
    // reached or a matching key is found
    while (entry != NULL)
    {
        // check key
        if (strcmp(entry->key, key) == 0)
        {
            // match found, replace value
            free(entry->value);
            entry->value = malloc(strlen(value) + 1);
            strcpy(entry->value, value);
            return;
        }

        // walk to next
        prev = entry;
        entry = prev->next;
    }

    // end of chain reached without a match, add new
    prev->next = ht_pair(key, value);
}

char *ht_get(ht_t *hashtable, const char *key)
{
    unsigned int slot = hash(key);

    // try to find a valid slot
    entry_t *entry = hashtable->entries[slot];

    // no slot means no entry
    if (entry == NULL)
    {
        return NULL;
    }

    // walk through each entry in the slot, which could just be a single thing
    while (entry != NULL)
    {
        // return value if found
        if (strcmp(entry->key, key) == 0)
        {
            return entry->value;
        }

        // proceed to next key if available
        entry = entry->next;
    }

    // reaching here means there were >= 1 entries but no key match
    return NULL;
}

void ht_del(ht_t *hashtable, const char *key)
{
    unsigned int bucket = hash(key);

    // try to find a valid bucket
    entry_t *entry = hashtable->entries[bucket];

    // no bucket means no entry
    if (entry == NULL)
    {
        return;
    }

    entry_t *prev;
    int idx = 0;

    // walk through each entry until either the end is reached or a matching key is found
    while (entry != NULL)
    {
        // check key
        if (strcmp(entry->key, key) == 0)
        {
            // first item and no next entry
            if (entry->next == NULL && idx == 0)
            {
                hashtable->entries[bucket] = NULL;
            }

            // first item with a next entry
            if (entry->next != NULL && idx == 0)
            {
                hashtable->entries[bucket] = entry->next;
            }

            // last item
            if (entry->next == NULL && idx != 0)
            {
                prev->next = NULL;
            }

            // middle item
            if (entry->next != NULL && idx != 0)
            {
                prev->next = entry->next;
            }

            // free the deleted entry
            free(entry->key);
            free(entry->value);
            free(entry);

            return;
        }

        // walk to next
        prev = entry;
        entry = prev->next;

        ++idx;
    }
}

void ht_dump(ht_t *hashtable)
{
    for (int i = 0; i < TABLE_SIZE; ++i)
    {
        entry_t *entry = hashtable->entries[i];

        if (entry == NULL)
        {
            continue;
        }

        printf("slot[%4d]: ", i);

        for (;;)
        {
            printf("%s=%s ", entry->key, entry->value);

            if (entry->next == NULL)
            {
                break;
            }

            entry = entry->next;
        }

        printf("\n");
    }
}

int main(int argc, char **argv)
{
    ht_t *ht = ht_create();

    ht_set(ht, "name1", "em");
    ht_set(ht, "name2", "russian");
    ht_set(ht, "name3", "pizza");
    ht_set(ht, "name4", "doge");
    ht_set(ht, "name5", "pyro");
    ht_set(ht, "name6", "joost");
    ht_set(ht, "name7", "kalix");

    ht_dump(ht);

    return 0;
}
/***


This C program implements a basic hash table (a data structure that maps keys to values) with functionality for adding, retrieving, deleting, and displaying key-value pairs. Below is a detailed explanation of each term and concept:

Headers and Macros
#include <limits.h>: Includes macros defining limits of integral types (e.g., INT_MAX).
#include <stdio.h>: Provides functionality for input and output operations (e.g., printf).
#include <stdlib.h>: Provides memory allocation functions like malloc, free, and more.
#include <string.h>: Provides functions for string manipulation (e.g., strlen, strcpy, strcmp).
#define TABLE_SIZE 20000: Defines the size of the hash table as a compile-time constant.
Data Structures
entry_t: Represents a single key-value pair in the hash table.

key: A string representing the key.
value: A string representing the associated value.
next: Pointer to the next entry in case of a hash collision (chaining mechanism).
ht_t: Represents the hash table.

entries: An array of pointers to entry_t objects.
Hash Function
c
Copy code
unsigned int hash(const char *key)
Computes a hash value for a given string key using a simple algorithm:
Multiplies the current value by 37 and adds the ASCII value of the character.
Uses modulo operation to ensure the hash fits within the table size.
Utility Functions
entry_t *ht_pair(const char *key, const char *value)

Creates a new key-value pair (entry_t).
Allocates memory for the structure and the strings.
Initializes the key, value, and sets next to NULL.
ht_t *ht_create(void)

Creates and initializes a hash table (ht_t).
Allocates memory for the hash table and its entries.
Sets all entries to NULL.
Core Operations
void ht_set(ht_t *hashtable, const char *key, const char *value)

Inserts or updates a key-value pair in the hash table.
Handles collisions using chaining:
If a slot is empty, inserts directly.
If a slot has existing entries, traverses the chain:
Updates value if the key matches.
Appends a new entry if no match is found.
char *ht_get(ht_t *hashtable, const char *key)

Retrieves the value for a given key.
Searches through the chain in the corresponding slot.
Returns the value if found, or NULL if not.
void ht_del(ht_t *hashtable, const char *key)

Deletes a key-value pair.
Handles cases based on the position in the chain:
First, last, or middle entry in the chain.
Frees allocated memory for the deleted entry.
void ht_dump(ht_t *hashtable)

Prints all key-value pairs in the hash table.
Iterates through each slot and traverses chains, printing all entries.
main Function
Creates a hash table with ht_create.
Inserts several key-value pairs using ht_set.
Dumps the contents of the hash table using ht_dump.
Key Features
Hashing: Maps string keys to integer indices for fast access.
Collision Handling: Uses separate chaining with linked lists to manage collisions.
Dynamic Memory Management: Allocates and frees memory dynamically for entries and strings.
Basic Operations: Implements insert, retrieve, delete, and display functionalities.
*/