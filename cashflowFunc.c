
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "cashflow.h"

struct Pair makePair(int first, const char second[])
{
    struct Pair newPair;
    newPair.first = first;
    strcpy(newPair.second, second);
    return newPair;
}

unsigned int hash(const char *key)
{
    unsigned int hash = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        hash = 31 * hash + key[i];
    }
    return hash % MAX_SIZE;
}

void initializeHashMap(struct HashMap *map)
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        map->table[i].occupied = false;
    }
}

void insert(struct HashMap *map, const char *key, int value)
{
    unsigned int index = hash(key);
    while (map->table[index].occupied)
    {
        index = (index + 1) % MAX_SIZE;
    }
    strcpy(map->table[index].key, key);
    map->table[index].value = value;
    map->table[index].occupied = true;
}

int get(struct HashMap *map, const char *key)
{
    unsigned int index = hash(key);
    while (map->table[index].occupied)
    {
        if (strcmp(map->table[index].key, key) == 0)
        {
            return map->table[index].value;
        }
        index = (index + 1) % MAX_SIZE;
    }

    return -1;
}

void initializeSet(struct Set *set)
{
    set->size = 0;
}

bool addToSet(struct Set *set, const char *element)
{
    if (set->size == MAX_TYPES)
    {
        printf("Set is full. Cannot add more elements.\n");
        return false;
    }

    for (int i = 0; i < set->size; i++)
    {
        if (strcmp(set->elements[i], element) == 0)
        {
            printf("Element already exists in the set.\n");
            return false;
        }
    }

    strcpy(set->elements[set->size], element);
    set->size++;
    return true;
}

bool isInSet(struct Set *set, const char *element)
{
    for (int i = 0; i < set->size; i++)
    {
        if (strcmp(set->elements[i], element) == 0)
        {
            return true;
        }
    }
    return false;
}
