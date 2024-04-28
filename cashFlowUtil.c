
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "cashflow.h"

struct Pair ***createGraph(int numBanks)
{
    struct Pair ***ansGraph = (struct Pair ***)malloc(numBanks * sizeof(struct Pair **));
    if (ansGraph == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < numBanks; i++)
    {
        ansGraph[i] = (struct Pair **)malloc(numBanks * sizeof(struct Pair *));
        if (ansGraph[i] == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }

        for (int j = 0; j < numBanks; j++)
        {
            ansGraph[i][j] = (struct Pair *)malloc(sizeof(struct Pair));
            if (ansGraph[i][j] == NULL)
            {
                fprintf(stderr, "Memory allocation failed\n");
                exit(1);
            }
            ansGraph[i][j]->first = 0;
            strcpy(ansGraph[i][j]->second, "");
        }
    }

    return ansGraph;
}

int getMinIndex(struct bank listOfNetAmounts[], int numBanks)
{
    int min = INT_MAX;
    int minIndex = -1;
    for (int i = 0; i < numBanks; i++)
    {
        if (listOfNetAmounts[i].netAmount == 0)
            continue;

        if (listOfNetAmounts[i].netAmount < min)
        {
            minIndex = i;
            min = listOfNetAmounts[i].netAmount;
        }
    }
    return minIndex;
}

int getsimpleMaxIndex(struct bank listOfNetAmounts[], int numBanks)
{
    int max = INT_MIN, maxIndex = -1;
    for (int i = 0; i < numBanks; i++)
    {
        if (listOfNetAmounts[i].netAmount == 0)
            continue;

        if (listOfNetAmounts[i].netAmount > max)
        {
            maxIndex = i;
            max = listOfNetAmounts[i].netAmount;
        }
    }
    return maxIndex;
}

void setIntersection(struct Set *set1, struct Set *set2, struct Set *result)
{

    initializeSet(result);
    for (int i = 0; i < set1->size; i++)
    {
        if (isInSet(set2, set1->elements[i]))
        {
            addToSet(result, set1->elements[i]);
        }
    }
}

struct Pair getMaxIndex(struct bank listofNetAmounts[], int numBanks, int minIndex, struct bank input[], int maxNumTypes)
{
    int max = INT_MIN;
    int maxIndex = -1;

    char matchingType[100];

    for (int i = 0; i < numBanks; i++)
    {
        if (listofNetAmounts[i].netAmount == 0)
        {
            continue;
        }

        if (listofNetAmounts[i].netAmount == 0)
        {
            continue;
        }

        char v[50];
        struct Set res;

        setIntersection(&listofNetAmounts[minIndex].types, &listofNetAmounts[i].types, &res);

        if (max < listofNetAmounts[i].netAmount)
        {
            max = listofNetAmounts[i].netAmount;
            maxIndex = i;

            strcpy(matchingType, res.elements[0]);
        }
    }
    struct Pair result;
    result.first = maxIndex;
    strcpy(result.second, matchingType);

    return result;
}

void printAns(struct Pair ***ansGraph, int numBanks, struct bank input[])
{
    printf("\nThe transactions for minimum cash flow are as follows :\n\n");
    for (int i = 0; i < numBanks; i++)
    {
        for (int j = 0; j < numBanks; j++)
        {
            if (i == j)
                continue;

            if (ansGraph[i][j]->first != 0 && ansGraph[j][i]->first != 0)
            {
                if (ansGraph[i][j]->first == ansGraph[j][i]->first)
                {
                    ansGraph[i][j]->first = 0;
                    ansGraph[j][i]->first = 0;
                }
                else if (ansGraph[i][j]->first > ansGraph[j][i]->first)
                {
                    ansGraph[i][j]->first -= ansGraph[j][i]->first;
                    ansGraph[j][i]->first = 0;

                    printf("%s pays Rs %d to %s via %s\n", input[i].name, ansGraph[i][j]->first, input[j].name, ansGraph[i][j]->second);
                }
                else
                {
                    ansGraph[j][i]->first -= ansGraph[i][j]->first;
                    ansGraph[i][j]->first = 0;

                    printf("%s pays Rs %d to %s via %s\n", input[j].name, ansGraph[j][i]->first, input[i].name, ansGraph[j][i]->second);
                }
            }
            else if (ansGraph[i][j]->first != 0)
            {
                printf("%s pays Rs %d to %s via %s\n", input[i].name, ansGraph[i][j]->first, input[j].name, ansGraph[i][j]->second);
            }
            else if (ansGraph[j][i]->first != 0)
            {
                printf("%s pays Rs %d to %s via %s\n", input[j].name, ansGraph[j][i]->first, input[i].name, ansGraph[j][i]->second);
            }

            ansGraph[i][j]->first = 0;
            ansGraph[j][i]->first = 0;
        }
    }
    printf("\n");
}

void minimizeCashFlow(int numBanks, struct bank input[], struct HashMap indexOf, int numTrasactions, int **graph, int maxNumTypes)
{

    struct bank *listofNetAmounts = (struct bank*)malloc(numBanks * sizeof(struct bank));
    // struct bank *listofNetAmounts = malloc(numBanks * sizeof(struct bank));

    for (int b = 0; b < numBanks; b++)
    {

        strcpy(listofNetAmounts[b].name, input[b].name);
        listofNetAmounts[b].types = input[b].types;

        int amount = 0;

        for (int i = 0; i < numBanks; i++)
        {
            amount += (graph[i][b]);
        }

        for (int j = 0; j < numBanks; j++)
        {
            amount += ((-1) * graph[b][j]);
        }

        listofNetAmounts[b].netAmount = amount;
    }

    struct Pair ***ansGraph = createGraph(numBanks);

    int numZeroNetAmounts = 0;

    for (int i = 0; i < numBanks; i++)
    {
        if (listofNetAmounts[i].netAmount == 0)
        {
            numZeroNetAmounts++;
        }
    }

    while (numZeroNetAmounts != numBanks)
    {

        int minIndex = getMinIndex(listofNetAmounts, numBanks);
        struct Pair maxAns = getMaxIndex(listofNetAmounts, numBanks, minIndex, input, maxNumTypes);

        int maxIndex = maxAns.first;

        if (maxIndex == -1)
        {
            (ansGraph[minIndex][0]->first) += abs(listofNetAmounts[minIndex].netAmount);
            strcpy(ansGraph[minIndex][0]->second, input[minIndex].types.elements[0]);

            int simpleMaxIndex = getsimpleMaxIndex(listofNetAmounts, numBanks);

            (ansGraph[0][simpleMaxIndex]->first += abs(listofNetAmounts[minIndex].netAmount));
            strcpy(ansGraph[0][simpleMaxIndex]->second, input[simpleMaxIndex].types.elements[0]);

            listofNetAmounts[simpleMaxIndex].netAmount += listofNetAmounts[minIndex].netAmount;
            listofNetAmounts[minIndex].netAmount = 0;

            if (listofNetAmounts[minIndex].netAmount == 0)
                numZeroNetAmounts++;

            if (listofNetAmounts[minIndex].netAmount == 0)
                numZeroNetAmounts++;
        }
        else
        {

            int transactionAmount = fmin(abs(listofNetAmounts[minIndex].netAmount), listofNetAmounts[maxIndex].netAmount);

            (ansGraph[minIndex][maxIndex]->first += (transactionAmount));
            strcpy(ansGraph[minIndex][maxIndex]->second, maxAns.second);

            listofNetAmounts[minIndex].netAmount += transactionAmount;
            listofNetAmounts[maxIndex].netAmount -= transactionAmount;

            if (listofNetAmounts[minIndex].netAmount == 0)
                numZeroNetAmounts++;

            if (listofNetAmounts[maxIndex].netAmount == 0)
                numZeroNetAmounts++;
        }
    }

    printAns(ansGraph, numBanks, input);
}
