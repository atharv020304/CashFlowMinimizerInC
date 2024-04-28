#ifndef _CAHSFLOW_HPP
#define _CAHSFLOW_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define MAX_TYPES 10
#define MAX_SIZE 50
#define INT_MAX 1000
#define INT_MIN -10
struct Set
{
    char elements[10][20];
    int size;
};

struct bank
{
    char name[100];
    int netAmount;
    struct Set types;
};

struct Pair
{
    int first;
    char second[20];
};

struct Entry
{
    char key[20];
    int value;
    bool occupied;
};

struct HashMap
{
    struct Entry table[MAX_SIZE];
};





struct Pair makePair(int first, const char second[]);
unsigned int hash(const char *key);
void initializeHashMap(struct HashMap *map);
void insert(struct HashMap *map, const char *key, int value);
int get(struct HashMap *map, const char *key);
void initializeSet(struct Set *set);
bool addToSet(struct Set *set, const char *element);
bool isInSet(struct Set *set, const char *element);



struct Pair ***createGraph(int numBanks);
int getMinIndex(struct bank listOfNetAmounts[], int numBanks);
int getsimpleMaxIndex(struct bank listOfNetAmounts[], int numBanks);
void setIntersection(struct Set *set1, struct Set *set2, struct Set *result);
struct Pair getMaxIndex(struct bank listofNetAmounts[], int numBanks, int minIndex, struct bank input[], int maxNumTypes);
void printAns(struct Pair ***ansGraph, int numBanks, struct bank input[]);
void minimizeCashFlow(int numBanks, struct bank input[], struct HashMap indexOf, int numTrasactions, int **graph, int maxNumTypes);


#endif /* _CAHSFLOW_HPP */
