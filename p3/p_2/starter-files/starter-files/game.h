#include "Player.h"
#include "Pack.h"
#include "Card.h"
#include <vector>
using namespace std;

void game_deal(vector<Player *> &player_vec,Pack &pack, int deal_index);


//return maker_index
int game_make_trump(vector<Player *> &player_vec, Card upcard,
int dealer_index, string &order_up_suit, ostream& os);


void game_play(vector<Player *> &player_vec, const string &trump, 
int &leader_index, ostream& os);


void game_score(const int maker_index, const int winner_team, const int tricks_0_2, const int tricks_1_3, 
            int &points_0_2, int &points_1_3,ostream& os);
