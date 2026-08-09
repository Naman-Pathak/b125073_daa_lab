#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(){
    int i,n;
    int fairHead=0,fairTail=0;
    int biasedHead=0,biasedTail=0;

    printf("enter number of tosses:");
    scanf("%d",&n);
    srand(time(NULL)); 

    //fair coin
    for(int i=0;i<n;i++){
        if(rand()%2==0)
        fairHead++;
        else
        fairTail++;
    }

    for(int i=0;i<n;i++){
        int r=rand()%100; 
        if(r<70)
        biasedHead++;
        else
        biasedTail++;
    }
    printf("\n \tFair Coin\t\n");
    printf("Heads = %d\n", fairHead);
    printf("Tails = %d\n", fairTail);
    printf("Probability of Head = %.4f\n", (float)fairHead / n);
    printf("Probability of Tail = %.4f\n", (float)fairTail / n);

    printf("\n\t Biased Coin (70%% Head)\t\n");
    printf("Heads = %d\n", biasedHead);
    printf("Tails = %d\n", biasedTail);
    printf("Probability of Head = %.4f\n", (float)biasedHead / n);
    printf("Probability of Tail = %.4f\n", (float)biasedTail / n);

    return 0;
}
