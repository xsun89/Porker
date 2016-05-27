#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define CARD_COUNT 54
#define PLAYER_COUNT 3

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

typedef struct Player{
    char name[30];
    Card** myCard;
    int cardCount;
}Player;
typedef int (*COMPARE)(Card*, Card*);
void getCardName(const Card* card, char* ret);
void shaffle(const Card* card, Card** shaffledCard);
void printCard(const Card* card);
void printPCard(const Card** pcard);
void dispatchCard(Player* players, Card** pCard);
int comp1(Card*, Card*);
void sort(Card** poker, int count, COMPARE);
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
    //printPCard((const Card**)shaffled);
    Player player[PLAYER_COUNT];
    for(i=0; i<PLAYER_COUNT;i++) {
        player[i].cardCount = 0;
        player[i].myCard = (Card**)malloc(CARD_COUNT/PLAYER_COUNT*sizeof(Card*));
        memset(player[i].name, '\0', sizeof(player[i].name));
        sprintf(player[i].name, "PLAYER%d", i);
    }
    dispatchCard(player, shaffled);
    for(i=0; i<PLAYER_COUNT; i++){
        sort(player[i].myCard, player[i].cardCount, comp1);
    }
    for(i=0; i<PLAYER_COUNT;i++){
        printf("Player: %s\n", player[i].name);
        int j;
        for(j=0; j<player[i].cardCount; j++){
            char* ret = (char *)malloc(16);
            getCardName(player[i].myCard[j], ret);
            printf("%s\n", ret);
            free(ret);
        }
        printf("\n");
    }
    for(i=0; i<PLAYER_COUNT;i++) {
        player[i].cardCount = 0;
        free(player[i].myCard);
    }
    free(shaffled);

    return 0;
}
int comp1(Card* c1, Card* c2){
    int ret = -1;
    if(c1->value > c2->value){
        ret = 1;
    }else if(c1->value == c2->value){
        if(c1->suit >c2->suit){
            ret = 1;
        }else if(c1->suit== c2->suit){
            ret = 0;
        }
    }
    return ret;
}
void sort(Card** poker, int count, COMPARE compare){
    int i, j;
    for(i=0; i<count-1; i++){
        for(j=i+1; j<count; j++){
            if(compare(poker[i], poker[j]) < 0){
                Card* tmp = poker[i];
                poker[i] = poker[j];
                poker[j] = tmp;
            }
        }
    }
}
void dispatchCard(Player* players, Card** pCard){
    int i;
    for (int i = 0; i < CARD_COUNT; ++i) {
        players[i%PLAYER_COUNT].myCard[players[i%PLAYER_COUNT].cardCount] = pCard[i];
        players[i%PLAYER_COUNT].cardCount++;
    }

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