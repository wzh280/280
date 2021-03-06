#include "Player.h"
#include "Pack.h"
#include "Card.h"
#include <cassert>
#include <string>
#include <cstring>
#include <vector>
#include <array>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

void game_deal(vector<Player *> &player_vec,Pack &pack, int deal_index){
    //round1 3-2-3-2
    //cout<<"deal begins"<<endl;
    int j;
    for(int i=deal_index+1; i<deal_index+5; i++){
        if(i>3){
            j = i-4;
        }
        else{
            j = i;
        }

        if((i-deal_index)%2==0){
            //cout<<"deal*2"<<" to "<<j<<endl;
            player_vec[j]->add_card(pack.deal_one());
            player_vec[j]->add_card(pack.deal_one());

        }
        else{
            //cout<<"deal*3"<<" to "<<j<<endl;
            player_vec[j]->add_card(pack.deal_one());
            player_vec[j]->add_card(pack.deal_one());
            player_vec[j]->add_card(pack.deal_one());
        }
        
    }
    //round2 2-3-2-3
    for(int i=deal_index+1; i<deal_index+5; i++){
        if(i>3){
            j = i-4;
        }
        else{
            j = i;
        }
        if((i-deal_index)%2==0){
            //cout<<"deal*2"<<" to "<<j<<endl;
            player_vec[j]->add_card(pack.deal_one());
            player_vec[j]->add_card(pack.deal_one());
            player_vec[j]->add_card(pack.deal_one());            
        }
        else{
            //cout<<"deal*3"<<" to "<<j<<endl;
            player_vec[j]->add_card(pack.deal_one());
            player_vec[j]->add_card(pack.deal_one());


        }
    }
}


//return maker_index
int game_make_trump(vector<Player *> &player_vec, Card upcard, int dealer_index, string &order_up_suit, ostream& os){
    int maker_index = -1;
    int first_make_trump_index = dealer_index + 1;
    int j;
    for(int round=1;round<3;round++){
        for(int i=first_make_trump_index; i<first_make_trump_index+4; i++){
            if(i>3){
                j = i-4;
            }
            else{
                j = i;
            }
            bool is_dealer=0;
            if(j==dealer_index){is_dealer==1;}
            if(player_vec[j]->make_trump(upcard, is_dealer,round, order_up_suit,os) == 1){
                maker_index = j;
                cout<<player_vec[j]->get_name()<< " orders up "<<order_up_suit<<endl;
                cout<<endl;
                os<<player_vec[j]->get_name()<< " orders up "<<order_up_suit<<endl;
                os<<endl;
                if(round==1){

                    player_vec[dealer_index]->add_and_discard(upcard,os);
                }   
                return maker_index;
            }
            else{
                cout<<player_vec[j]->get_name()<< " passes "<<endl;
                os<<player_vec[j]->get_name()<< " passes "<<endl;

            }
        }
    }

return -100;

}

void game_play(vector<Player *> &player_vec, const string &trump, int &leader_index, ostream& os){
        int j;

        Card lead_card = player_vec[leader_index]->lead_card(trump,os);
        Card win_card =  lead_card;
        cout<<lead_card.get_rank()<<" of "<<lead_card.get_suit()<<" led by "<<player_vec[leader_index]->get_name()<<endl;
        os<<lead_card.get_rank()<<" of "<<lead_card.get_suit()<<" led by "<<player_vec[leader_index]->get_name()<<endl;
        int index = leader_index;
        for(int i=index+1; i<index+4; i++){           
            if(i>3){j=i-4;}
            else{j=i;}
            Card played_card = player_vec[j]->play_card(lead_card, trump,os);
            cout<<played_card.get_rank()<<" of "<<played_card.get_suit()<<" played by "<<player_vec[j]->get_name()<<endl;
            os<<played_card.get_rank()<<" of "<<played_card.get_suit()<<" played by "<<player_vec[j]->get_name()<<endl;
            if(Card_less(win_card, played_card, lead_card,trump)==1){
                win_card = played_card;
                leader_index = j;
            }    
        }
        cout<<player_vec[leader_index]->get_name()<<" takes the trick"<<endl;
        cout<<endl;
        os<<player_vec[leader_index]->get_name()<<" takes the trick"<<endl;
        os<<endl;
}

void game_score(const int maker_index, const int winner_team, const int tricks_0_2, const int tricks_1_3, 
            int &points_0_2, int &points_1_3,ostream& os){
    //cout <<"score"<<endl;
    //cout <<"trick0="<<tricks_0_2<<endl;
    //cout <<"trick1="<<tricks_1_3<<endl;
    int maker_team; //0: player0+player2; 1:player1+player3
    if(maker_index==0 || maker_index==2){maker_team=0;}
    else{maker_team=1;}
    
    if(winner_team==0){
        if(maker_team==winner_team){      
            if(tricks_0_2==3||tricks_0_2==4){
                points_0_2 = points_0_2+1;
            }
            else if(tricks_0_2==5){
                points_0_2 = points_0_2+2;
                cout<<"march!"<<endl;
                os<<"march!"<<endl;

            }
        }
        else{
            if(tricks_0_2==3||tricks_0_2==4||tricks_0_2==5){
                //cout <<"score"<<endl;
                points_0_2 = points_0_2+2;
                cout<<"euchred!"<<endl;
                os<<"euchred!"<<endl;
            }
        }
    }
    else{
        if(maker_team==winner_team){      
            if(tricks_1_3==3||tricks_1_3==4){
                points_1_3 = points_1_3+1;
            }
            else if(tricks_1_3==5){
                points_1_3 = points_1_3+2;
                cout<<"march!"<<endl;
                os<<"march!"<<endl;
            }
        }
        else{
            if(tricks_1_3==3||tricks_1_3==4||tricks_1_3==5){
                points_1_3 = points_1_3+2;
                cout<<"euchred!"<<endl;
                os<<"euchred!"<<endl;
            }
        }

    }
    

}

int main(int argc, char **argv){
    if(argc != 12 || atoi(argv[3])>100 || atoi(argv[3])<1 ||
     !(strcmp(argv[2],"shuffle")==0 || strcmp(argv[2],"noshuffle")==0) ||
     !(strcmp(argv[5],"Simple")==0 || strcmp(argv[5], "Human")==0) ||
     !(strcmp(argv[7],"Simple")==0 || strcmp(argv[7], "Human")==0) ||
     !(strcmp(argv[9],"Simple")==0 || strcmp(argv[9],"Human")==0) ||
     !(strcmp(argv[11],"Simple")==0 || strcmp(argv[11],"Human")==0) 
     ){
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
        << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
        << "NAME4 TYPE4" << endl;
        
        return 0;
    }
    else{
        
        string pack_in_file = argv[1];
        string outfile = "euchre_out";
        ifstream fin;
        ofstream fout;
        fout.open(outfile);
        fin.open(pack_in_file);
        for(int i=0; i<12 ;i++){
            cout<<argv[i];
            fout<<argv[i];
            if(i==11){
                cout<<endl;
                fout<<endl;
            }
            cout<<" ";
            fout<<" ";
        }
        if (!fin.is_open()){
            cout <<  "Error opening "  << pack_in_file << endl;
            return 0;
        }
        else{
            //open pack file, initialize pack
            //cout << "pack file open successfully"<<endl;
            Pack pack(fin);
            
            //initialize win point
            int win_point = atoi(argv[3]);
            //initialize players
            vector <Player * >	player_vec;
            for(int i=4;i<11;i=i+2){
                player_vec.push_back(Player_factory(argv[i],argv[i+1]));
            }

            int points_0_2 = 0;
            int points_1_3 = 0;
            int deal_index = 0;
            int maker_index;
            int hand = 0;

            while(points_0_2<win_point && points_1_3<win_point){
                cout << "Hand "<<hand<<endl;
                fout << "Hand "<<hand<<endl;
                hand = hand + 1;
                //shuffle

                if(strcmp(argv[2],"shuffle")==0){
                pack.shuffle();
                }
                else{
                pack.reset();
                }
                //deal
                game_deal(player_vec,pack,deal_index);
                cout<<player_vec[deal_index]->get_name()<<" deals"<<endl;
                fout<<player_vec[deal_index]->get_name()<<" deals"<<endl;
                //make trump
                Card upcard = pack.deal_one();
                cout<<upcard.get_rank()<< " of "<<upcard.get_suit()<<" turns up"<<endl;
                fout<<upcard.get_rank()<< " of "<<upcard.get_suit()<<" turns up"<<endl;
                string order_up_suit=upcard.get_suit();
                int maker_index,leader_index;
                maker_index=game_make_trump(player_vec, upcard, deal_index,order_up_suit,fout);
                if(deal_index+1>3){
                    leader_index = deal_index - 3;
                }
                else{
                    leader_index = deal_index + 1;
                }
                
                //play*5
                int tricks_0_2 = 0;
                int tricks_1_3 = 0;
                for(int play_round=0; play_round<5; play_round++){
                    //cout<<"round "<< play_round<<endl;
                    game_play(player_vec, order_up_suit, leader_index,fout);    
                    //cout <<"winner = "<< leader_index<<endl;
                    if(leader_index == 0 || leader_index == 2){
                        tricks_0_2 = tricks_0_2 + 1;
                    }
                    else{
                        tricks_1_3 = tricks_1_3 + 1;
                    }
                    //cout <<tricks_0_2<<endl;
                    //cout <<tricks_1_3<<endl;
                }
                  //score
                int winner_team;
                if(tricks_1_3>tricks_0_2){
                    winner_team=1;
                    cout << player_vec[1]->get_name()<<" and "<<player_vec[3]->get_name()<<" win the hand "<<endl; 
                    fout << player_vec[1]->get_name()<<" and "<<player_vec[3]->get_name()<<" win the hand "<<endl; 
                }
                else{
                    winner_team=0;
                    cout << player_vec[0]->get_name()<<" and "<<player_vec[2]->get_name()<<" win the hand "<<endl; 
                    fout << player_vec[0]->get_name()<<" and "<<player_vec[2]->get_name()<<" win the hand "<<endl; 

                }

                game_score(maker_index, winner_team, tricks_0_2, tricks_1_3, points_0_2, points_1_3,fout);
                cout<< player_vec[0]->get_name()<<" and "<<player_vec[2]->get_name()<< " have "
                    <<points_0_2<< " points "<<endl;
                cout<< player_vec[1]->get_name()<<" and "<<player_vec[3]->get_name()<< " have "
                    <<points_1_3<< " points "<<endl;
                cout<<endl;
                fout<< player_vec[0]->get_name()<<" and "<<player_vec[2]->get_name()<< " have "
                    <<points_0_2<< " points "<<endl;
                fout<< player_vec[1]->get_name()<<" and "<<player_vec[3]->get_name()<< " have "
                    <<points_1_3<< " points "<<endl;
                fout<<endl;


                deal_index = deal_index+1;
                if(deal_index>3){deal_index = deal_index-4;}
                else{deal_index=deal_index;}



            }

            if(points_0_2>points_1_3){
                cout<< player_vec[0]->get_name()<<" and "<<player_vec[2]->get_name()<< " win!"<<endl;
                fout<< player_vec[0]->get_name()<<" and "<<player_vec[2]->get_name()<< " win!"<<endl;
            }
            else{
                cout<< player_vec[1]->get_name()<<" and "<<player_vec[3]->get_name()<< " win!"<<endl;
                fout<< player_vec[1]->get_name()<<" and "<<player_vec[3]->get_name()<< " win!"<<endl;
            }


        }
    }
     
    return 1;
}