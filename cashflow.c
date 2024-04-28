#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <stdbool.h>
#include <math.h>   

#define MAX_TYPES 10  
#define MAX_SIZE 50
#define INT_MAX 1000
#define INT_MIN -10
struct Set {
    char elements[10][20]; 
    int size;
};

struct bank{
    char name[100] ;
    int netAmount;
    struct Set types;
};

struct Pair {
    int first;
    char second[20]; 
};


struct Pair makePair(int first, const char second[]) {
    struct Pair newPair;
    newPair.first = first;
    strcpy(newPair.second, second);
    return newPair;
}


struct Entry {
    char key[20]; // Assuming a maximum length for the key
    int value;
    bool occupied;
};

struct HashMap {
    struct Entry table[MAX_SIZE];
};


unsigned int hash(const char *key) {
    unsigned int hash = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hash = 31 * hash + key[i];
    }
    return hash % MAX_SIZE;
}


void initializeHashMap(struct HashMap *map) {
    for (int i = 0; i < MAX_SIZE; i++) {
        map->table[i].occupied = false;
    }
}


void insert(struct HashMap *map, const char *key, int value) {
    unsigned int index = hash(key);
    while (map->table[index].occupied) {
        index = (index + 1) % MAX_SIZE; 
    }
    strcpy(map->table[index].key, key);
    map->table[index].value = value;
    map->table[index].occupied = true;
}

// Get the value associated with a key from the hashmap
int get(struct HashMap *map, const char *key) {
    unsigned int index = hash(key);
    while (map->table[index].occupied) {
        if (strcmp(map->table[index].key, key) == 0) {
            return map->table[index].value;
        }
        index = (index + 1) % MAX_SIZE; 
    }
    
    return -1;
}




void initializeSet(struct Set *set) {
    set->size = 0;
}

bool addToSet(struct Set *set, const char *element) {
    if (set->size == MAX_TYPES) {
        printf("Set is full. Cannot add more elements.\n");
        return false;
    }

    for (int i = 0; i < set->size; i++) {
        if (strcmp(set->elements[i], element) == 0) {
            printf("Element already exists in the set.\n");
            return false;
        }
    }

    strcpy(set->elements[set->size], element);
    set->size++;
    return true;
}

bool isInSet(struct Set *set, const char *element) {
    for (int i = 0; i < set->size; i++) {
        if (strcmp(set->elements[i], element) == 0) {
            return true;
        }
    }
    return false;
}

//------------------------------------------------------------------------------------------------------------------
//end of helper functions
//-----------------------------------------------------------------------


struct Pair ***createGraph(int numBanks) {
    struct Pair ***ansGraph = (struct Pair***)malloc(numBanks * sizeof(struct Pair**));
    if (ansGraph == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < numBanks; i++) {
        ansGraph[i] = (struct Pair**)malloc(numBanks * sizeof(struct Pair*));
        if (ansGraph[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }

        for (int j = 0; j < numBanks; j++) {
            ansGraph[i][j] = (struct Pair*)malloc(sizeof(struct Pair));
            if (ansGraph[i][j] == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                exit(1);
            }
            ansGraph[i][j]->first = 0;
            strcpy(ansGraph[i][j]->second, "");
        }
    }

    return ansGraph;
}




int getMinIndex(struct bank listOfNetAmounts[],int numBanks){
    int min = INT_MAX;
    int minIndex = -1;
    for(int i=0;i<numBanks;i++){
    if(listOfNetAmounts[i].netAmount == 0) continue;

    if(listOfNetAmounts[i].netAmount < min){
        minIndex = i;
        min = listOfNetAmounts[i].netAmount;
    }
}
return minIndex;
}

int getsimpleMaxIndex(struct bank listOfNetAmounts[],int numBanks){
    int max = INT_MIN , maxIndex = -1;
    for(int i=0;i<numBanks;i++){
        if(listOfNetAmounts[i].netAmount == 0) continue;

        if(listOfNetAmounts[i].netAmount > max){
            maxIndex = i;
            max = listOfNetAmounts[i].netAmount;
        }
    }
    return maxIndex;
}


void setIntersection(struct Set *set1, struct Set *set2,struct Set *result){

initializeSet(result);
for(int i=0;i<set1->size;i++){
    if(isInSet(set2, set1->elements[i])){
        addToSet(result, set1->elements[i]);
    }
}
}


struct Pair getMaxIndex(struct bank listofNetAmounts[],int numBanks,int minIndex, struct bank input[] ,int maxNumTypes){
    int max = INT_MIN;
    int maxIndex = -1;
    
    char matchingType[100] ;
    

    for(int i=0;i<numBanks;i++)
    {
        if(listofNetAmounts[i].netAmount == 0){
            continue;
        }
        
        if(listofNetAmounts[i].netAmount == 0){
            continue;
        }
        
        char v[50];
        struct Set res;
    
       setIntersection(&listofNetAmounts[minIndex].types,&listofNetAmounts[i].types,&res);

       if(max < listofNetAmounts[i].netAmount){
        max = listofNetAmounts[i].netAmount;
        maxIndex = i;

        strcpy(matchingType,res.elements[0]);

       }
        
    }
struct Pair result ;
result.first = maxIndex;
strcpy(result.second,matchingType);


return result;
}


void printAns(struct Pair ***ansGraph, int numBanks, struct bank input[]) {
    printf("\nThe transactions for minimum cash flow are as follows :\n\n");
    for (int i = 0; i < numBanks; i++) {
        for (int j = 0; j < numBanks; j++) {
            if (i == j) continue;

            if (ansGraph[i][j]->first != 0 && ansGraph[j][i]->first != 0) {
                if (ansGraph[i][j]->first == ansGraph[j][i]->first) {
                    ansGraph[i][j]->first = 0;
                    ansGraph[j][i]->first = 0;
                } else if (ansGraph[i][j]->first > ansGraph[j][i]->first) {
                    ansGraph[i][j]->first -= ansGraph[j][i]->first;
                    ansGraph[j][i]->first = 0;

                    printf("%s pays Rs %d to %s via %s\n", input[i].name, ansGraph[i][j]->first, input[j].name, ansGraph[i][j]->second);
                } else {
                    ansGraph[j][i]->first -= ansGraph[i][j]->first;
                    ansGraph[i][j]->first = 0;

                    printf("%s pays Rs %d to %s via %s\n", input[j].name, ansGraph[j][i]->first, input[i].name, ansGraph[j][i]->second);
                }
            } else if (ansGraph[i][j]->first != 0) {
                printf("%s pays Rs %d to %s via %s\n", input[i].name, ansGraph[i][j]->first, input[j].name, ansGraph[i][j]->second);
            } else if (ansGraph[j][i]->first != 0) {
                printf("%s pays Rs %d to %s via %s\n", input[j].name, ansGraph[j][i]->first, input[i].name, ansGraph[j][i]->second);
            }

            ansGraph[i][j]->first = 0;
            ansGraph[j][i]->first = 0;
        }
    }
    printf("\n");
}


void minimizeCashFlow(int numBanks,struct bank input[],struct HashMap indexOf,int numTrasactions,int **graph,int maxNumTypes){

    struct bank *listofNetAmounts = malloc(numBanks * sizeof(struct bank));

    for(int b=0;b<numBanks;b++){

        strcpy(listofNetAmounts[b].name,input[b].name);
        listofNetAmounts[b].types = input[b].types;

        int amount = 0;

        for(int i=0;i<numBanks;i++){
            amount += (graph[i][b]);
        }

        for(int j=0;j<numBanks;j++){
            amount += ((-1)* graph[b][j]);
        }
         
         listofNetAmounts[b].netAmount = amount;
    }
  
    struct Pair ***ansGraph = createGraph(numBanks);

    int numZeroNetAmounts = 0;

    for(int i=0;i<numBanks;i++){
        if(listofNetAmounts[i].netAmount == 0) {
            numZeroNetAmounts++;
        }
    }

    while(numZeroNetAmounts != numBanks){
       
       int minIndex = getMinIndex(listofNetAmounts,numBanks);
       struct Pair maxAns = getMaxIndex(listofNetAmounts,numBanks,minIndex,input,maxNumTypes);
        
       int maxIndex = maxAns.first;

       if(maxIndex == -1){
        (ansGraph[minIndex][0]->first) += abs(listofNetAmounts[minIndex].netAmount);
        strcpy(ansGraph[minIndex][0]->second,input[minIndex].types.elements[0]);
       
       int simpleMaxIndex = getsimpleMaxIndex(listofNetAmounts,numBanks);

       (ansGraph[0][simpleMaxIndex]->first += abs(listofNetAmounts[minIndex].netAmount));
       strcpy(ansGraph[0][simpleMaxIndex]->second , input[simpleMaxIndex].types.elements[0]);

       listofNetAmounts[simpleMaxIndex].netAmount += listofNetAmounts[minIndex].netAmount;
       listofNetAmounts[minIndex].netAmount = 0;
       
       if(listofNetAmounts[minIndex].netAmount == 0) numZeroNetAmounts++;
       
       if(listofNetAmounts[minIndex].netAmount == 0) numZeroNetAmounts++;
       }else{
        
        int transactionAmount = fmin(abs(listofNetAmounts[minIndex].netAmount),listofNetAmounts[maxIndex].netAmount);

        (ansGraph[minIndex][maxIndex]->first +=(transactionAmount));
        strcpy(ansGraph[minIndex][maxIndex]->second, maxAns.second);

        listofNetAmounts[minIndex].netAmount += transactionAmount;
        listofNetAmounts[maxIndex].netAmount -= transactionAmount;

        if(listofNetAmounts[minIndex].netAmount == 0 ) numZeroNetAmounts++;

        if(listofNetAmounts[maxIndex].netAmount == 0) numZeroNetAmounts++;


       }


    }

    printAns(ansGraph,numBanks,input);

}




int main(){




    printf("\n\t\t\t\t********************* Welcome to CASH FLOW MINIMIZER SYSTEM ***********************\n\n\n");
    printf("This system minimizes the number of transactions among multiple banks in the different corners of the world that use different modes of payment.There is one world bank (with all payment modes) to act as an intermediary between banks that have no common mode of payment. \n\n");
    printf("Enter the number of banks participating in the transactions.\n");
    int numBanks;
    scanf("%d",&numBanks);

    struct bank *input = malloc(numBanks * sizeof(struct bank));
    
    struct HashMap indexOf;
    initializeHashMap(&indexOf);
    
    printf("Enter the details of the banks and transactions as stated:\n");
    printf("Bank name ,number of payment modes it has and the payment modes.\n");
    printf("Bank name and payment modes should not contain spaces\n");

    



    int maxNumTypes;
    for(int i=0;i<numBanks;i++)
    {
        if(i==0){
            printf("world bank : ");
        }else{
            printf("Bank %d :",i);
        }
        

        scanf("%s",&input[i].name);
        insert(&indexOf,input[i].name,i);
        int numTypes;
        scanf("%d",&numTypes);

        if(i == 0 ){
            maxNumTypes = numTypes;
        }

        char type[20];
        while(numTypes--){
            scanf(" %s",type);
            addToSet(&input[i].types,type);
        }
    }
     
     printf("Enter number of transcations.\n");
     int numTransactions;
     scanf("%d",&numTransactions);

    int **graph = (int**)malloc(numBanks * sizeof(int*));

    for(int i=0;i<numBanks;i++){
        graph[i] = (int*)malloc(numBanks * sizeof(int));

    }
    for (int i = 0; i < numBanks; i++) {
        for (int j = 0; j < numBanks; j++) {
            graph[i][j] = 0;
        }
    }

    printf("Enter the details of each transaction as stated:");
    printf("Debtor Bank , creditor Bank and amount\n");
    printf("The transactions can be in any order\n");

    for(int i=0;i<numTransactions;i++){
        printf("%d th transaction :",i);
        char s1[200];    //string s1
        char s2[200];    //string s2
        int amount;
        scanf("%s %s %d",&s1,&s2,&amount);
        
        int temp1 = get(&indexOf,s1);
        int temp2 = get(&indexOf,s2);
        
        graph[temp1][temp2] = amount;
    }

     minimizeCashFlow(numBanks,input,indexOf,numTransactions,graph,maxNumTypes);

    return 0;
}



















