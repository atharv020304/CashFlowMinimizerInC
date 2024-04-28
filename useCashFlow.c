#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "cashflow.h"

int main()
{

    printf("\n\t\t\t\t********************* Welcome to CASH FLOW MINIMIZER SYSTEM ***********************\n\n\n");
    printf("This system minimizes the number of transactions among multiple banks in the different corners of the world that use different modes of payment.There is one world bank (with all payment modes) to act as an intermediary between banks that have no common mode of payment. \n\n");
    printf("Enter the number of banks participating in the transactions.\n");
    int numBanks;
    scanf("%d", &numBanks);

    struct bank *input = (struct bank*)malloc(numBanks * sizeof(struct bank));
    // struct bank *input = malloc(numBanks * sizeof(struct bank));

    struct HashMap indexOf;
    initializeHashMap(&indexOf);

    printf("Enter the details of the banks and transactions as stated:\n");
    printf("Bank name ,number of payment modes it has and the payment modes.\n");
    printf("Bank name and payment modes should not contain spaces\n");

    int maxNumTypes;
    for (int i = 0; i < numBanks; i++)
    {
        if (i == 0)
        {
            printf("world bank : ");
        }
        else
        {
            printf("Bank %d :", i);
        }

        scanf("%s", &input[i].name);
        insert(&indexOf, input[i].name, i);
        int numTypes;
        scanf("%d", &numTypes);

        if (i == 0)
        {
            maxNumTypes = numTypes;
        }

        char type[20];
        while (numTypes--)
        {
            scanf(" %s", type);
            addToSet(&input[i].types, type);
        }
    }

    printf("Enter number of transcations.\n");
    int numTransactions;
    scanf("%d", &numTransactions);

    int **graph = (int **)malloc(numBanks * sizeof(int *));

    for (int i = 0; i < numBanks; i++)
    {
        graph[i] = (int *)malloc(numBanks * sizeof(int));
    }
    for (int i = 0; i < numBanks; i++)
    {
        for (int j = 0; j < numBanks; j++)
        {
            graph[i][j] = 0;
        }
    }

    printf("Enter the details of each transaction as stated:");
    printf("Debtor Bank , creditor Bank and amount\n");
    printf("The transactions can be in any order\n");

    for (int i = 0; i < numTransactions; i++)
    {
        printf("%d th transaction :", i);
        char s1[200]; // string s1
        char s2[200]; // string s2
        int amount;
        scanf("%s %s %d", &s1, &s2, &amount);

        int temp1 = get(&indexOf, s1);
        int temp2 = get(&indexOf, s2);

        graph[temp1][temp2] = amount;
    }

    minimizeCashFlow(numBanks, input, indexOf, numTransactions, graph, maxNumTypes);

    return 0;
}
