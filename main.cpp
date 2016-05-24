#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
int main() {
    Card card[54];
    int i = 0;
    for(; i<52; i++){
        card[i].value = i/4 + 1;
        card[i].suit = static_cast<Suit>(i % 4);
    }

    card[52].value = 14;
    card[52].suit = (Suit)4;
    card[53].value = 15;
    card[53].suit = (Suit)5;
    for(i=0; i<54; i++){
        char* ret = (char *)malloc(16);
        getCardName(&card[i], ret);
        printf("%s\n", ret);
        free(ret);
    }
    return 0;
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

}