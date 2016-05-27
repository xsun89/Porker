#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define CARD_COUNT 54

typedef enum Suit{
    heart,
    spade,
    diamond,
    club,
    porker1,
    porker2
}Suit;

typedef struct Card{
    int value;
    Suit suit;
}Card;

void getCardName(const Card* card, char* ret);
void shaffle(const Card* card, Card** shaffledCard);
void printCard(const Card* card);
void printPCard(const Card** pcard);
int main() {
    Card card[CARD_COUNT];
    int i = 0;
    for(; i<CARD_COUNT- 2; i++){
        card[i].value = i/4 + 1;
        card[i].suit = static_cast<Suit>(i % 4);
    }

    card[CARD_COUNT-2].value = 14;
    card[CARD_COUNT-2].suit = (Suit)4;
    card[CARD_COUNT-1].value = 15;
    card[CARD_COUNT-1].suit = (Suit)5;

    //printCard(card);

    Card** shaffled = (Card**)malloc(CARD_COUNT*sizeof(Card*));
    shaffle(card, shaffled);
    printPCard((const Card**)shaffled);

    return 0;
}

void printCard(const Card* card){
    int i;
    for(i=0; i<CARD_COUNT; i++){
        char* ret = (char *)malloc(16);
        getCardName(&card[i], ret);
        printf("%s\n", ret);
        free(ret);
    }
}

void printPCard(const Card** pCard){
    int i;
    for(i=0; i<CARD_COUNT; i++){
        char* ret = (char *)malloc(16);
        getCardName(pCard[i], ret);
        printf("%s\n", ret);
        free(ret);
    }
}

void getCardName(const Card* card, char* ret){
    char valueTemp[16];
    memset(valueTemp, '\0', sizeof(valueTemp));
    switch ((int)card->suit) {
        case 0:
            strcpy(valueTemp, "heart");
            break;
        case 1:
            strcpy(valueTemp, "spade");
            break;
        case 2:
            strcpy(valueTemp, "diamond");
            break;
        case 3:
            strcpy(valueTemp, "club");
            break;
        case 4:
            strcpy(valueTemp, "porker1");
            break;
        case 5:
            strcpy(valueTemp, "porker2");
            break;
    }
    char suitTemp[16];
    memset(suitTemp, '\0', sizeof(suitTemp));
    if(card->value == 1) {
        strcpy(suitTemp, "A");
    }else if(card->value == 11) {
        strcpy(suitTemp, "J");
    }else if(card->value == 12) {
        strcpy(suitTemp, "Q");
    }else if(card->value == 13) {
        strcpy(suitTemp, "K");
    }else if(card->value == 14) {
        strcpy(suitTemp, "");
    }else if(card->value == 15){
        strcpy(suitTemp, "");
    }else{
        sprintf(suitTemp, "%d", card->value);
    }


    sprintf(ret, "%s %s\n", valueTemp, suitTemp);

}

void shaffle(const Card* card, Card** shaffledCard){

    Card** copiedCard = (Card**)malloc(CARD_COUNT*sizeof(Card*));

    int i = 0;
    for (int i = 0; i < CARD_COUNT; ++i) {
        copiedCard[i] = (Card *) &(card[i]);
    }

    srand(time(NULL));
    for(i=0; i<CARD_COUNT;i++){
        int index = rand()%CARD_COUNT;
        if(copiedCard[index] != NULL) {
            shaffledCard[i] = copiedCard[index];
            copiedCard[index] = NULL;
        }else{
            i--;
        }
    }
    free(copiedCard);
}