#pragma once

#ifndef CARD_CHECKER_H
#define CARD_CHECKER_H

#include "card.h"
#include <vector>

class CardChecker
{
public:
	CardChecker();

	void sort_by_suit(std::vector<Card>* cards);
	//int sort_by_value(std::vector<Card> cards);
	void sort_by_value_and_suit(std::vector<Card>* cards);

	//combination checking functions
	Card* check_full_house(std::vector<Card>* cards);
	Card* check_straight(std::vector<Card>* cards);
	Card* check_two_pair(std::vector<Card>* cards);
	Card* check_four_of_a_kind(std::vector<Card>* cards);
	Card* check_three_of_a_kind(std::vector<Card>* cards);
	Card* check_pair(std::vector<Card>* cards);
	Card* check_single(std::vector<Card>* cards);

	//ai combination search functions
	Card* ai_select_full_house(std::vector<Card>* cards);
	Card* ai_select_straight(std::vector<Card>* cards);
	Card* ai_select_two_pair(std::vector<Card>* cards);
	Card* ai_select_four_of_a_kind(std::vector<Card>* cards);
	Card* ai_select_three_of_a_kind(std::vector<Card>* cards);
	Card* ai_select_pair(std::vector<Card>* cards);
	Card* ai_select_single(std::vector<Card>* cards);

	//ai combination search functions including 3 of clubs
	Card* ai_select_full_house_turn1_type1(std::vector<Card>* cards);
	Card* ai_select_full_house_turn1_type2(std::vector<Card>* cards);
	Card* ai_select_straight_turn1(std::vector<Card>* cards);
	Card* ai_select_two_pair_turn1(std::vector<Card>* cards);
	Card* ai_select_four_of_a_kind_turn1(std::vector<Card>* cards);
	Card* ai_select_three_of_a_kind_turn1(std::vector<Card>* cards);
	Card* ai_select_pair_turn1(std::vector<Card>* cards);
	Card* ai_select_single_turn1(std::vector<Card>* cards);

	void reset_top_card();
protected:

private:
	Card top_card;
	int select_lowest_unselected_pair(std::vector<Card>* cards);
	int select_lowest_unselected_three_of_a_kind(std::vector<Card>* cards);
};

#endif