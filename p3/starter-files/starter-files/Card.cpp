// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"
// add any necessary #include or using directives here

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

// add your code below
Card::Card():rank(Card::RANK_TWO),suit(Card::SUIT_SPADES){

}

Card::Card(const std::string &rank_in, const std::string &suit_in):rank(rank_in),suit(suit_in){

}

std::string Card::get_rank() const {
    return rank;
} 

std::string Card::get_suit() const{
    return suit;
}

std::string Card::get_suit(const std::string &trump) const{
    if(rank == Card::RANK_JACK){
        if(suit == trump){
            return suit;
        }
        else{
            std::string true_suit = Suit_next(suit);
            if(true_suit == trump){
                return trump;
            }
        }
    }
    return suit;
}

bool Card::is_face() const{
    if(rank == Card::RANK_JACK || rank == Card::RANK_QUEEN || rank == Card::RANK_KING || 
    rank == Card:: RANK_ACE){
        return true;
    }
    return false;
}

bool Card::is_right_bower(const std::string &trump) const{
    if(suit == trump && rank == Card::RANK_JACK){
        return true;
    }
    return false;
}

bool Card::is_left_bower(const std::string &trump) const{
    if(Suit_next(suit)== trump && rank == Card::RANK_JACK){
        return true;
    }
    return false;
}

bool Card::is_trump(const std::string &trump) const{
    if(is_left_bower(trump)==true){
        return true;
    }
    else if(suit == trump){
        return true;
    }
    return false;
}





//////////////////////////////////////////////////////////////////////
int index_rank(const Card &a){
    int index = -1;
    for (int i = 0; i < NUM_RANKS ; i++){
        if(RANK_NAMES_BY_WEIGHT[i] == a.get_rank()){
            index = i;
        }
    }
    return index;
}

int index_suit(const Card &a){
    int index = -1;
    for (int i = 0; i < NUM_SUITS ; i++){
        if(SUIT_NAMES_BY_WEIGHT[i] == a.get_suit()){
            index = i;
        }
    }
    return index;
}

bool operator<(const Card &lhs, const Card &rhs){
    int rank_indexl = index_rank(lhs);
    int rank_indexr = index_rank(rhs);
    int suit_indexl = index_suit(lhs);
    int suit_indexr = index_suit(rhs);
    if(rank_indexl < rank_indexr){
        return true;
    }
    else if(rank_indexl == rank_indexr){
        if(suit_indexl<suit_indexr){
            return true;
        }
    }
    return false;
}

bool operator>(const Card &lhs, const Card &rhs){
    int rank_indexl = index_rank(lhs);
    int rank_indexr = index_rank(rhs);
    int suit_indexl = index_suit(lhs);
    int suit_indexr = index_suit(rhs);
    if(rank_indexl > rank_indexr){
        return true;
    }
    else if(rank_indexl == rank_indexr){
        if(suit_indexl>suit_indexr){
            return true;
        }
    }
    return false;
}

bool operator==(const Card &lhs, const Card &rhs){
    int rank_indexl = index_rank(lhs);
    int rank_indexr = index_rank(rhs);
    int suit_indexl = index_suit(lhs);
    int suit_indexr = index_suit(rhs);
    if(rank_indexl == rank_indexr && suit_indexl == suit_indexr){
        return true;
    }
    return false;
}

bool operator!=(const Card &lhs, const Card &rhs){
    int rank_indexl = index_rank(lhs);
    int rank_indexr = index_rank(rhs);
    int suit_indexl = index_suit(lhs);
    int suit_indexr = index_suit(rhs);
    if(rank_indexl == rank_indexr && suit_indexl == suit_indexr){
        return false;
    }
    return true;
}



std::string Suit_next(const std::string &suit){
    if(suit == Card::SUIT_SPADES){
        return Card::SUIT_CLUBS;
    }
    else if(suit == Card::SUIT_HEARTS){
        return Card::SUIT_DIAMONDS;
    }
    else if(suit == Card::SUIT_DIAMONDS){
        return Card::SUIT_HEARTS;
    }
    else {
        return Card::SUIT_SPADES;
    }
}

std::ostream & operator<<(std::ostream &os, const Card &card){
    return os << card.get_rank() << " of " << card.get_suit();
}

bool Card_less(const Card &a, const Card &b, const std::string &trump){
    if(a==b){return false;}
    else if(b.is_right_bower(trump)){
        return true;
    }
    else if(b.is_left_bower(trump)){
        if(a.is_right_bower(trump)){return false;}
        else return true;
    }
    else if(b.is_trump(trump)){
        if(a.is_trump(trump)){
            return a<b;
        }
        else {return true;}
    }
    else {
        if(a.is_trump(trump)){
            return false;
        }
        else{
            return a<b;
        }
    }
}

bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const std::string &trump){
    std::string led_suit = led_card.get_suit();               
    if(a==b){return false;}
    else if(b.is_right_bower(trump)){
        return true;
    }
    else if(b.is_left_bower(trump)){
        if(a.is_right_bower(trump)){return false;}
        else return true;
    }
    else if(b.is_trump(trump)){
        if(a.is_trump(trump)){
            return a<b;
        }
        else{
            return true; 
        }
        
    }
    else if(b.get_suit()==led_suit){
        if(a.get_suit()==led_suit){
            return a<b;
        }
        else if(a.get_suit()==trump){
            return false;
        }
        else return true;
    }
    else{
        if(a.is_trump(trump)){
            return false;
        }
        else if(a.get_suit()==led_suit){
            return false;
        }
        else return a<b;
    }                 
}