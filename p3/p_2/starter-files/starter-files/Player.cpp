

#include "Player.h"
#include "Card.h"
#include <cassert>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <ostream>
#include <sstream>
#include <fstream>


class simple : public Player{
    private:
    std:: string name;
    std::vector<Card> cards;
    public:
    simple() {
        name = "NoName";
        cards = { };
    }
    simple(std::string name_in) {
        name = name_in;
        cards = { }; 
    }

    //EFFECTS returns player's name
    const std::string & get_name() const {
        return name;
    }

    void add_card(const Card &c) {
        assert(cards.size() <= MAX_HAND_SIZE);
        cards.push_back(c);
    }

    bool make_trump(const Card &upcard, bool is_dealer,
                          int round, std::string &order_up_suit, std::ostream& os) const {
                            
        if(round == 1){
            int trump_face_card_num = 0;
            for(size_t i=0; i<cards.size(); i++){
                if(cards[i].get_suit(upcard.get_suit())==upcard.get_suit() && cards[i].is_face()){
                    trump_face_card_num = trump_face_card_num + 1;
                }
            }

            if(trump_face_card_num>=2){
                order_up_suit = upcard.get_suit();
                return true;
            }

        }
        else if(round == 2){
            std::string wish_trump = Suit_next(upcard.get_suit());
            if(is_dealer==false){
                int wish_trump_face_card_num = 0;    
                for(size_t i=0; i<cards.size(); i++){
                    if(cards[i].get_suit(wish_trump)==wish_trump && cards[i].is_face()){
                        wish_trump_face_card_num = wish_trump_face_card_num + 1;
                    }
                }

                if(wish_trump_face_card_num>=1){
                order_up_suit = wish_trump;
                return true;
                }
            }
            else{
                order_up_suit = wish_trump;
                return true;
            }

        }
        return false;
    }

    void add_and_discard(const Card &upcard, std::ostream& os) {
        //std::cout<<"add and discard"<<std::endl;
        assert(cards.size() >=1);
        cards.push_back(upcard);
        Card lowerst_card = cards[0];
        int index = 0;
        for(size_t i=0; i<cards.size();i++){
            if(Card_less(cards[i], lowerst_card, upcard.get_suit(upcard.get_suit()))){
                //Returns true if cards[i] is lower value than lowerst_card.
                lowerst_card = cards[i];
                index = i;
            }
        }
        cards.erase(cards.begin()+index);    
    }

    // Card lead_card(const std::string &trump){
    //     Card lead_card = cards[0];
    //     int index = 0;
    //     for(size_t i=0; i<cards.size();i++){
    //         if(cards[i].is_trump(trump)){

    //         }
    //         else{
    //             if(Card_less(lead_card, cards[i], trump)){
    //                 lead_card = cards[i];
    //                 index = i;
    //             }
    //         }
    //     }

    //     if(index==0){
    //         if(cards[0].is_trump==0){
    //             return cards[0];
    //             cards.erase(cards.begin());  
    //         }
    //         else{
    //             Card highest_trump = cards[0];
    //             int index_trump = 0;
    //             for(size_t i=0; i<cards.size();i++){
    //                 if(cards[i].get_suit(trump)==trump){
    //                     if(Card_less(highest_trump, cards[i], trump)){
    //                 highest_trump = cards[i];
    //                 index_trump = i;
    //                     }
    //                 }  
    //             }
    //             return cards[index_trump];
    //             cards.erase(cards.begin()+index_trump); 
    //         }
    //     }
    //     else {
    //         return cards[index];
    //         cards.erase(cards.begin()+index);  
    //     }
    // }
    Card lead_card(const std::string &trump, std::ostream& os){
        Card lead_card = cards[0];
        int num_non_trump = 0;
        int first_non_trump = -1;
        for(size_t i = 0; i<cards.size();i++){
            if(cards[i].get_suit(trump)!=trump){
                num_non_trump = num_non_trump + 1;
                if(first_non_trump==-1){
                    first_non_trump = i;
                }
            }
        }
        //std::cout<<"first_non_trump"<<first_non_trump<<std::endl;
        
        if(num_non_trump==0){
            int index = 0;
            Card highest_trump_card = cards[0];
            for(size_t i=0; i<cards.size();i++){
                if(Card_less(highest_trump_card, cards[i], trump)){
                    highest_trump_card = cards[i];
                    index = i;
                }
            }    
            cards.erase(cards.begin()+index); 
            return highest_trump_card;
        }
       
        Card highest_non_trump_card = cards[first_non_trump];
        int index_l = first_non_trump;
        for(size_t i=first_non_trump; i<cards.size();i++){
            if(cards[i].get_suit(trump)!=trump){
                if(Card_less(highest_non_trump_card,cards[i], trump)){
                highest_non_trump_card = cards[i];
                index_l = i;
                }
            }        
        }
        cards.erase(cards.begin()+index_l);
        return highest_non_trump_card;
        
    }


//     Card play_card(const Card &led_card, const std::string &trump) {
//         Card lowest_non_led = cards[0];
//         int index_low = 0;
//         for(size_t i=0; i<cards.size();i++){
//             if(cards[i].get_suit(trump)==led_card.get_suit(trump)){

//             }
//             else{
//                 if(Card_less(cards[i], lowest_non_led, trump)){
//                 index_low = i;
//                 lowest_non_led = cards[i];
//                 }
//             }
//         }

//         if(index_low==0){
//             if(cards[0].get_suit(trump)!=led_card.get_suit(trump)){
//                 return cards[0];
//                 cards.erase(cards.begin());  
//             }
//             else{
//                 Card highest_led = cards[0];
//                 int index_led = 0;
//                 for(size_t i=0; i<cards.size();i++){
//                     if(cards[i].get_suit(trump)==led_card.get_suit(trump)){
//                         if(Card_less(highest_led, cards[i], led_card,trump)){
//                     highest_led = cards[i];
//                     index_led = i;
//                         }
//                     }                    
//                 }
//                 return cards[index_led];
//                 cards.erase(cards.begin()+index_led); 
//             }
//         }
//         else{
//             return cards[index_low];
//             cards.erase(cards.begin()+index_low); 
//         }
//     }
// };

    Card play_card(const Card &led_card, const std::string &trump, std::ostream& os){
        std::string led_suit = led_card.get_suit(trump);
        //std::cout << "led_suit"<<led_suit<<std::endl;
        //os<< "led_suit"<<led_suit<<std::endl;
        int num_led_card = 0;
        int first_led_card = -1;
        for(size_t i = 0; i<cards.size(); i++){
            if(cards[i].get_suit(trump)==led_suit){
                if(first_led_card==-1){
                    first_led_card = i;
                }
                num_led_card = num_led_card + 1;
            }
        }
        if(num_led_card!=0){
            Card highest_card = cards[first_led_card];
            int index_h = first_led_card;
            for(size_t i = first_led_card; i<cards.size();i++){
                if(cards[i].get_suit(trump)==led_suit){
                    if(Card_less(highest_card,cards[i],led_card,trump)){
                        highest_card = cards[i];
                        index_h = i;
                    }
                } 
            }
            cards.erase(cards.begin()+index_h);
            return highest_card;
        }
        else{
            Card lowest_card = cards[0];
            int index_l = 0;
            for(size_t i = 0; i<cards.size();i++){   
                if(Card_less(cards[i],lowest_card,led_card,trump)){
                       lowest_card = cards[i];
                       index_l = i;
                }
                
            }
            cards.erase(cards.begin()+index_l);
            return lowest_card;
        }
    }
};

class human : public Player{
    private:
    std:: string name;
    std::vector<Card> cards;
    public:
    human() {
    name = "NoName";
    cards = { };
    }
    human(std::string name_in) {
    name = name_in;
    cards = { }; 
    }
    const std::string & get_name() const {
    return name;
    }

    void add_card(const Card &c) {
        assert(cards.size() <= MAX_HAND_SIZE);
        cards.push_back(c);
        std::sort(cards.begin(),cards.end(),operator<);
    }

    bool make_trump(const Card &upcard, bool is_dealer,
                        int round, std::string &order_up_suit, std::ostream& os ) const{
        std::string word;
        for (size_t i = 0; i < cards.size(); ++i) {
        std::cout << "Human player " << name << "'s hand: [" << i << "] " << cards.at(i) << std::endl;
        os << "Human player " << name << "'s hand: [" << i << "] " << cards.at(i) << std::endl;
        }
        std::cout << "Human player "<<name<<", please enter a suit, or \"pass\":" << std::endl;
        os << "Human player "<<name<<", please enter a suit, or \"pass\":" << std::endl;
        if(round == 1){
            // std::cout << "pass or order up" << std::endl;
            // os << "pass or order up" << std::endl;

            std::cin>>word;
            if(word == "pass"){
                return false;
            }
            else{
                order_up_suit = upcard.get_suit();
                return true;
            }
        }

        // std::cout << "Human player "<<name<<", please enter a suit, or \"pass\":" << std::endl;
        // os << "Human player "<<name<<", please enter a suit, or \"pass\":" << std::endl;

        std::cin>>word;
        if(word == "pass"){
            return false;
        }
        order_up_suit = word;
        return true;
    }

    void add_and_discard(const Card &upcard, std::ostream& os) {
        std::sort(cards.begin(),cards.end(),operator<);
        std::string word;
        for (size_t i = 0; i < cards.size(); ++i) {
        std::cout << "Human player " << name << "'s hand: [" << i << "] " << cards.at(i) << std::endl;
        os << "Human player " << name << "'s hand: [" << i << "] " << cards.at(i) << std::endl;
        }
        std::cout<<"Discard upcard: [-1]"<<std::endl;
        std::cout<<"Human player "<<name<<", please select a card to discard:"<<std::endl;
        os<<"Discard upcard: [-1]"<<std::endl;
        os<<"Human player "<<name<<", please select a card to discard:"<<std::endl;
        std::cin>>word;

        int discard_index;
        std::istringstream iss;//istringstream从string读入,和cin一样仅仅重载了>>,可以把string转为int
        iss.clear();//每次使用前先清空
        iss.str(word);
        iss>>discard_index;//将输入流中的内容写入到int n,

        if(discard_index==-1){

        }
        else{
            cards.erase(cards.begin()+discard_index);
            add_card(upcard);
        }
    }

    Card lead_card(const std::string &trump,std::ostream& os){
        std::string word;
        for (size_t i = 0; i < cards.size(); ++i) {
        std::cout << "Human player " << name << "'s hand: [" << i << "] " << cards.at(i) << std::endl;
        os << "Human player " << name << "'s hand: [" << i << "] " << cards.at(i) << std::endl;
        }
        std::cout<<"Human player "<<name<<", please select a card:"<<std::endl;
        os<<"Human player "<<name<<", please select a card:"<<std::endl;
        std::cin>>word;
        int lead_index;
        std::istringstream iss;//istringstream从string读入,和cin一样仅仅重载了>>,可以把string转为int
        iss.clear();//每次使用前先清空
        iss.str(word);
        iss>>lead_index;//将输入流中的内容写入到int n
        Card lead_card = cards[lead_index];
        cards.erase(cards.begin()+lead_index);
        return lead_card;
    }

    Card play_card(const Card &led_card, const std::string &trump,std::ostream& os){
        std::string word;
        for (size_t i = 0; i < cards.size(); ++i) {
        std::cout << "Human player " << name << "'s hand: [" << i << "] " << cards.at(i) << std::endl;
        os<< "Human player " << name << "'s hand: [" << i << "] " << cards.at(i) << std::endl;
        }
        std::cout<<"Human player "<<name<<", please select a card:"<<std::endl;
        os<<"Human player "<<name<<", please select a card:"<<std::endl;
        std::cin>>word;
        int play_index;
        //play_index = stoi(word); 
        std::istringstream iss;//istringstream从string读入,和cin一样仅仅重载了>>,可以把string转为int
        iss.clear();//每次使用前先清空
        iss.str(word);
        iss>>play_index;//将输入流中的内容写入到int n
        Card play_card = cards[play_index];
        cards.erase(cards.begin()+play_index);
        return play_card;
    }

};

//EFFECTS: Returns a pointer to a player with the given name and strategy
//To create an object that won't go out of scope when the function returns,
//use "return new Simple(name)" or "return new Human(name)"
//Don't forget to call "delete" on each Player* after the game is over
Player * Player_factory(const std::string &name, const std::string &strategy){
    if (strategy == "Human") {
		Player *to_return = new human(name);
		return to_return;
	}
	else {
		Player *to_return =  new simple(name);
		return to_return;
	}
}

//EFFECTS: Prints player's name to os
std::ostream & operator<<(std::ostream &os, const Player &p){
    os << p.get_name();
	return os;
}

