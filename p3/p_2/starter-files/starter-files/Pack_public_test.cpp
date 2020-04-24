// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Pack.h"
#include "Card.h"
#include "unit_test_framework.h"
#include <cassert>
#include <iostream>
#include <fstream>
using namespace std;

// THESE TEST CASES ARE NOT VERY THOROUGH.
// YOU NEED TO WRITE YOUR OWN COMPREHENSIVE TEST CASES IN Pack_tests.cpp

static const int PACK_SIZE = 24;

TEST(test_pack_default_ctor) {
  Pack pack;
  Card first_card = pack.deal_one();
  ASSERT_EQUAL(first_card, Card(Card::RANK_NINE, Card::SUIT_SPADES));
  Card second_card = pack.deal_one();
  ASSERT_EQUAL(second_card, Card(Card::RANK_NINE, Card::SUIT_HEARTS));
  Card card_3 = pack.deal_one();
  ASSERT_EQUAL(card_3, Card(Card::RANK_NINE, Card::SUIT_CLUBS));
  Card card_4 = pack.deal_one();
  ASSERT_EQUAL(card_4, Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
  Card card_5 = pack.deal_one();
  ASSERT_EQUAL(card_5, Card(Card::RANK_TEN, Card::SUIT_SPADES));
  Card card_6 = pack.deal_one();
  ASSERT_EQUAL(card_6, Card(Card::RANK_TEN, Card::SUIT_HEARTS));
  Card card_7 = pack.deal_one();
  ASSERT_EQUAL(card_7, Card(Card::RANK_TEN, Card::SUIT_CLUBS));
  Card card_8 = pack.deal_one();
  ASSERT_EQUAL(card_8, Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
  Card card_9 = pack.deal_one();
  ASSERT_EQUAL(card_9, Card(Card::RANK_JACK, Card::SUIT_SPADES));
  Card card_10 = pack.deal_one();
  ASSERT_EQUAL(card_10, Card(Card::RANK_JACK, Card::SUIT_HEARTS));
  Card card_11 = pack.deal_one();
  ASSERT_EQUAL(card_11, Card(Card::RANK_JACK, Card::SUIT_CLUBS));
  Card card_12 = pack.deal_one();
  ASSERT_EQUAL(card_12, Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
}

TEST(test_pack_istream_ctor) {
  const string filename = "pack.in";
  ifstream ifs(filename);
  assert(ifs.is_open());
  Pack pack(ifs);
  Card first_card = pack.deal_one();
  ASSERT_EQUAL(first_card, Card(Card::RANK_NINE, Card::SUIT_SPADES));
}

TEST(test_pack_reset) {
  Pack pack;
  pack.deal_one();
  pack.reset();
  Card first_card = pack.deal_one();
  ASSERT_EQUAL(first_card, Card(Card::RANK_NINE, Card::SUIT_SPADES));
}

TEST(test_pack_empty) {
  Pack pack;
  for (int i = 0; i < PACK_SIZE - 1; ++i) {
    pack.deal_one();
    ASSERT_FALSE(pack.empty());
  }
  pack.deal_one();
  ASSERT_TRUE(pack.empty());
}

TEST(test_pack_shuffle) {
  Pack pack;
  pack.shuffle();
  Card first_card = pack.deal_one();
  ASSERT_EQUAL(first_card, Card(Card::RANK_KING, Card::SUIT_CLUBS));//???????????
}

//   const string filename = "pack_1.in.txt";
//   ifstream ifs(filename);
//   assert(ifs.is_open());
//   Pack pack(ifs);
//   pack.shuffle();
//   Card first_card = pack.deal_one();
//   ASSERT_EQUAL(first_card, Card(Card::RANK_ACE, Card::SUIT_HEARTS));
// }

TEST_MAIN()
