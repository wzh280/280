
#include <cassert>
#include <iostream>
#include <string>
#include <array>
#include "Pack.h"
#include "Card.h"

Pack::Pack(){
    next = 0;
    int index = 0;
    for(int i=7; i<NUM_RANKS; i++){
        for(int j=0; j<NUM_SUITS; j++){
            cards[index] = Card(RANK_NAMES_BY_WEIGHT[i], SUIT_NAMES_BY_WEIGHT[j]);
            index = index + 1;
        }
    }

}

Pack::Pack(std::istream& pack_input){
    std::string word;
    next = 0;
    int i = 0;
    int index = 0;
    std::string rank,suit;
    while(pack_input>>word){
        if(i%3==0){
            rank = word;
        }
        else if(i%3==2){
            suit = word;
            cards[index] = Card(rank, suit);
            //std::cout<<"pack:"<<rank<< "of"<<suit<<std::endl;
            index = index +1;
        }
        i = i+1;
    }
}

Card Pack::deal_one(){
    next = next + 1;
    //std::cout<<next-1<<std::endl;
    return cards[next - 1];
}

void Pack::reset(){
    next = 0;
}

void Pack::shuffle(){ ////24 cards
    std::array<Card, PACK_SIZE/2> card_1;
    std::array<Card, PACK_SIZE/2> card_2;
    
    for(int i=0; i<7; i++){
        for(int k=0; k<PACK_SIZE/2; k++){
        card_1[k] = cards[k];
        card_2[k] = cards[k+12];
        }
    
        for(int j=0; j<PACK_SIZE/2; j++){
            cards[2*j] = card_2[j];
            cards[2*j+1] = card_1[j];
        }
    }
    reset();

    // std::array<Card, 6/2> card_1;
    // std::array<Card, 6/2> card_2;
    // reset();
    // for(int i=0; i<3; i++){
    //     for(int k=0; k<6/2; k++){
    //     card_1[k] = cards[k];
    //     card_2[k] = cards[k+3];
    //     }
    
    //     for(int j=0; j<6/2; j++){
    //         cards[2*j] = card_2[j];
    //         cards[2*j+1] = card_1[j];
    //     }
    // }
}

// void Pack::shuffle() {
//     Card temp[PACK_SIZE];
//     for (int i = 0; i < 7; ++i) {
//         for (int j = 0; j < PACK_SIZE; ++j) {
//             if (j < 12) {
//                 temp[2 * j + 1] = cards[j];
//             }
//             else {
//                 temp[2 * (j - 12)] = cards[j];
//             }
//         }
//         for (int j = 0; j < PACK_SIZE; ++j) {
//             cards[j] = temp[j];
//         }
//     }
// }


bool Pack::empty()const {
    if(next==PACK_SIZE){
        return true;
    }
    return false;
}