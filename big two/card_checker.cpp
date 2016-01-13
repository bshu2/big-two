#include "card_checker.h"

#include <algorithm>
#include <iostream>

CardChecker::CardChecker()
{
	top_card = Card(0,3);
}

void CardChecker::sort_by_suit(std::vector<Card>* cards)
{
	//TODO
}

/*	//possibly not needed at all
int CardChecker::sort_by_value(std::vector<Card> cards)
{
	int j;
	Card temp;
	for (int i = 0; i < cards.size(); i++)
	{
		j = i;
		while (j > 0 && cards[j].get_value() < cards[j - 1].get_value())
		{
			temp = cards[j];
			cards[j] = cards[j - 1];
			cards[j - 1] = temp;
			j--;
		}
	}
}
*/

void CardChecker::sort_by_value_and_suit(std::vector<Card>* cards)
{
	int j;
	Card temp;
	for (int i = 0; i < (int)cards->size(); i++)
	{
		j = i;
		while (j > 0 && cards->at(j) < cards->at(j - 1))
		{
			temp = cards->at(j);
			cards->at(j) = cards->at(j - 1);
			cards->at(j - 1) = temp;
			j--;
		}
	}
}

//combination checking functions

Card* CardChecker::check_full_house(std::vector<Card>* cards)
{
	if (cards->size() != 5)
		return NULL;
	sort_by_value_and_suit(cards);
	
	if (cards->at(0).get_value() != cards->at(1).get_value() || cards->at(3).get_value() != cards->at(4).get_value() || (cards->at(1).get_value() != cards->at(2).get_value() && cards->at(2).get_value() != cards->at(3).get_value()))
		return NULL;

	
	//reorder if needed to get the triple in front of the pair
	if (cards->at(2).get_value() == cards->at(3).get_value())
	{
		cards->push_back(cards->at(0));
		cards->push_back(cards->at(1));
		cards->erase(cards->begin());
		cards->erase(cards->begin());
	}
	/*std::cout << "top card = ";
	top_card.print_card();
	std::cout << "\ncards = ";
	for (int i = 0; i < cards->size(); i++)
	{
		cards->at(i).print_card();
	}
	std::cout << "\n";*/
	if (top_card > cards->at(2))
		return NULL;
	

	top_card = cards->at(2);
	return &cards->at(2);
}

Card* CardChecker::check_straight(std::vector<Card>* cards)
{
	if (cards->size() != 5)
		return NULL;
	sort_by_value_and_suit(cards);
	if (cards->at(0).get_comparable_value() != cards->at(1).get_comparable_value() - 1 || cards->at(1).get_comparable_value() != cards->at(2).get_comparable_value() - 1 || cards->at(2).get_comparable_value() != cards->at(3).get_comparable_value() - 1 || cards->at(3).get_comparable_value() != cards->at(4).get_comparable_value() - 1)
		return NULL;
	if (top_card > cards->at(4))
		return NULL;
	top_card = cards->at(4);
	return &cards->at(4);
}

Card* CardChecker::check_two_pair(std::vector<Card>* cards)
{
	if (cards->size() != 4)
		return NULL;
	sort_by_value_and_suit(cards);
	if (cards->at(0).get_value() != cards->at(1).get_value() || cards->at(1).get_value() == cards->at(2).get_value() || cards->at(2).get_value() != cards->at(3).get_value())
		return NULL;
	if (top_card > cards->at(3))
		return NULL;
	top_card = cards->at(3);
	return &cards->at(3);
}

Card* CardChecker::check_four_of_a_kind(std::vector<Card>* cards)
{
	if (cards->size() != 4 || cards->at(0).get_value() != cards->at(1).get_value() || cards->at(1).get_value() != cards->at(2).get_value() || cards->at(2).get_value() != cards->at(3).get_value())
		return NULL;
	if (top_card > cards->at(3))
		return NULL;
	top_card = cards->at(3);
	return &cards->at(3);
}

Card* CardChecker::check_three_of_a_kind(std::vector<Card>* cards)
{
	if (cards->size() != 3 || cards->at(0).get_value() != cards->at(1).get_value() || cards->at(1).get_value() != cards->at(2).get_value())
		return NULL;
	if (top_card > cards->at(2))
		return NULL;
	top_card = cards->at(2);
	return &cards->at(2);
}

Card* CardChecker::check_pair(std::vector<Card>* cards)
{
	if (cards->size() != 2 || cards->at(0).get_value() != cards->at(1).get_value())
		return NULL;
	if (top_card > cards->at(1))
		return NULL;
	top_card = cards->at(1);
	return &cards->at(1);
}

Card* CardChecker::check_single(std::vector<Card>* cards)
{
	//std::cout << "single\n";
	//std::cout << "card = " << cards->at(0).get_value() << " of " << cards->at(0).get_suit();

	if (cards->size() != 1)
	{
		std::cout << "size test for single failed with size " << cards->size() << "\n";
		return NULL;
	}
	if (top_card > cards->at(0))
	{
		std::cout << "comparison test for single failed";
		return NULL;
	}
	top_card = cards->at(0);
	return &cards->at(0);
}


/*ai combination search functions*/

Card* CardChecker::ai_select_full_house(std::vector<Card>* cards)
{
	if (cards->size() < 5)
		return NULL;
	Card top_card_copy = top_card;
	Card* temp = ai_select_three_of_a_kind(cards);
	if (temp == NULL)
		return NULL;
	else if (select_lowest_unselected_pair(cards) == -1)
	{
		//restore top_card
		top_card = top_card_copy;
		//deselect all cards
		for (int i = 0; i < (int)cards->size(); i++)
		{
			if (cards->at(i).is_selected())
			{
				cards->at(i).set_selected(false);
			}
		}
		return NULL;
	}
	//top_card = *temp
	return temp;
}

Card* CardChecker::ai_select_straight(std::vector<Card>* cards)
{
	//return NULL;
	//TODO straight logic
	if (cards->size() < 5)
		return NULL;
	sort_by_value_and_suit(cards);
	int off1, off2, off3, off4;
	for (int i = 0; i < (int)cards->size() - 4; i++)
	{
		off1 = 1;
		off2 = 1;
		off3 = 1;
		off4 = 1;
		if (i + off1 >= (int)cards->size())
			return NULL;
		while (i + 1 < (int)cards->size() && cards->at(i).get_value() == cards->at(i + off1).get_value())
		{
			off1++;
			if (i + off1 >= (int)cards->size())
				return NULL;
		}
		if (cards->at(i).get_value() != cards->at(i + off1).get_value() - 1)
		{
			continue;
		}
		if (i + off1 + off2 >= (int)cards->size())
			return NULL;
		while (i + off1 + 1 < (int)cards->size() && cards->at(i + off1).get_value() == cards->at(i + off1 + off2).get_value())
		{
			off2++;
			if (i + off1 + off2>= (int)cards->size())
				return NULL;
		}
		if (cards->at(i + off1).get_value() != cards->at(i + off1 + off2).get_value() - 1)
		{
			continue;
		}
		if (i + off1 + off2 + off3 >= (int)cards->size())
			return NULL;
		while (i + off1 + off2 + 1 < (int)cards->size() && cards->at(i + off1 + off2).get_value() == cards->at(i + off1 + off2 + off3).get_value())
		{
			off3++;
			if (i + off1 + off2 + off3 >= (int)cards->size())
				return NULL;
		}
		if (cards->at(i + off1 + off2).get_value() != cards->at(i + off1 + off2 + off3).get_value() - 1)
		{
			continue;
		}
		if (i + off1 + off2 + off3 + off4 >= (int)cards->size())
			return NULL;
		while (i + off1 + off2 + off3 + 1 < (int)cards->size() && cards->at(i + off1 + off2 + off3).get_value() == cards->at(i + off1 + off2 + off3 + off4).get_value())
		{
			off4++;
			if (i + off1 + off2 + off3 + off4 >= (int)cards->size())
				return NULL;
		}
		if (cards->at(i + off1 + off2 + off3).get_value() != cards->at(i + off1 + off2 + off3 + off4).get_value() - 1)
		{
			continue;
		}

		
		//top_card = cards->at(i + off1 + off2 + off3 + off4);
		cards->at(i).set_selected(true);
		cards->at(i + off1).set_selected(true);
		cards->at(i + off1 + off2).set_selected(true);
		cards->at(i + off1 + off2 + off3).set_selected(true);
		cards->at(i + off1 + off2 + off3 + off4).set_selected(true);
		return &cards->at(i + off1 + off2 + off3 + off4);
	}
	return NULL;
}

Card* CardChecker::ai_select_two_pair(std::vector<Card>* cards)
{
	if (cards->size() < 4)
		return NULL;
	Card top_card_copy = top_card;
	Card* temp = ai_select_pair(cards);
	if (temp == NULL)
		return NULL;
	else if (select_lowest_unselected_pair(cards) == -1)
	{
		//restore top_card
		top_card = top_card_copy;
		//deselect all cards
		for (int i = 0; i < (int)cards->size(); i++)
		{
			if (cards->at(i).is_selected())
			{
				cards->at(i).set_selected(false);
			}
		}
		return NULL;
	}
	//top_card = *temp
	return temp;
}

Card* CardChecker::ai_select_four_of_a_kind(std::vector<Card>* cards)
{
	if (cards->size() < 4)
		return NULL;
	sort_by_value_and_suit(cards);
	for (int i = 0; i < (int)cards->size() - 3; i++)
	{
		if (cards->at(i).get_value() == cards->at(i + 1).get_value() && cards->at(i + 1).get_value() == cards->at(i + 2).get_value() 
			&& cards->at(i + 2).get_value() == cards->at(i + 3).get_value() && cards->at(i + 3) > top_card)
		{
			//top_card = cards->at(i + 3);
			cards->at(i).set_selected(true);
			cards->at(i + 1).set_selected(true);
			cards->at(i + 2).set_selected(true);
			cards->at(i + 3).set_selected(true);
			return &cards->at(i + 3);
		}
	}
	return NULL;
}

Card* CardChecker::ai_select_three_of_a_kind(std::vector<Card>* cards)
{
	if (cards->size() < 3)
		return NULL;
	sort_by_value_and_suit(cards);
	for (int i = 0; i < (int)cards->size() - 2; i++)
	{
		if (cards->at(i).get_value() == cards->at(i + 1).get_value() && cards->at(i + 1).get_value() == cards->at(i + 2).get_value() && cards->at(i + 2) > top_card)
		{
			//top_card = cards->at(i + 2);
			cards->at(i).set_selected(true);
			cards->at(i + 1).set_selected(true);
			cards->at(i + 2).set_selected(true);
			return &cards->at(i + 2);
		}
	}
	return NULL;
}

Card* CardChecker::ai_select_pair(std::vector<Card>* cards)
{
	if (cards->size() < 2)
		return NULL;
	sort_by_value_and_suit(cards);
	for (int i = 0; i < (int)cards->size() - 1; i++)
	{
		if (cards->at(i).get_value() == cards->at(i + 1).get_value() && cards->at(i + 1) > top_card)
		{
			//top_card = cards->at(i + 1);
			cards->at(i).set_selected(true);
			cards->at(i + 1).set_selected(true);
			return &cards->at(i + 1);
		}
	}
	return NULL;
}

Card* CardChecker::ai_select_single(std::vector<Card>* cards)
{
	std::cout << "starting ai select single...\n";
	if (cards->size() < 1)
	{
		std::cout << "size test failed with size " << cards->size() << "\n";
		return NULL;
	}
	std::cout << "top card = ";
	top_card.print_card();
	std::cout << "\n";
	sort_by_value_and_suit(cards);
	for (int i = 0; i < (int)cards->size(); i++)
	{
		cards->at(i).print_card();

		if (cards->at(i) > top_card || cards->at(i) == top_card)
		{
			//top_card = cards->at(i);
			cards->at(i).set_selected(true);
			return &cards->at(i);
		}
	}
	return NULL;
}

Card* CardChecker::ai_select_full_house_turn1_type1(std::vector<Card>* cards)//333XX
{
	//code below accounts for 333XX but not XXX33
	if (cards->size() < 5)
		return NULL;
	sort_by_value_and_suit(cards);
	if (cards->at(0) != Card(0, 3))
		return NULL;
	Card top_card_copy = top_card;
	Card* temp = ai_select_three_of_a_kind_turn1(cards);
	if (temp == NULL)
		return NULL;
	else if (select_lowest_unselected_pair(cards) == -1)
	{
		//restore top_card
		top_card = top_card_copy;
		//deselect all cards
		for (int i = 0; i < (int)cards->size(); i++)
		{
			if (cards->at(i).is_selected())
			{
				cards->at(i).set_selected(false);
			}
		}
		return NULL;
	}

	return temp;
}

Card* CardChecker::ai_select_full_house_turn1_type2(std::vector<Card>* cards)//XXX33
{
	//TODO code below accounts for XXX33 but not 333XX
	if (cards->size() < 5)
		return NULL;
	sort_by_value_and_suit(cards);
	if (cards->at(0) != Card(0, 3))
		return NULL;
	Card top_card_copy = top_card;
	Card* temp = ai_select_pair_turn1(cards);
	if (temp == NULL)
		return NULL;
	else if (select_lowest_unselected_three_of_a_kind(cards) == -1)
	{
		//restore top_card
		top_card = top_card_copy;
		//deselect all cards
		for (int i = 0; i < (int)cards->size(); i++)
		{
			if (cards->at(i).is_selected())
			{
				cards->at(i).set_selected(false);
			}
		}
		return NULL;
	}

	return temp;
}

Card* CardChecker::ai_select_straight_turn1(std::vector<Card>* cards)
{
	if (cards->size() < 5)
		return NULL;
	sort_by_value_and_suit(cards);
	if (cards->at(0) != Card(0, 3))
		return NULL;
	int off1 = 1, off2 = 1, off3 = 1, off4 = 1;
		if (off1 >= (int)cards->size())
			return NULL;
		while (1 < (int)cards->size() && cards->at(0).get_value() == cards->at(off1).get_value())
		{
			off1++;
			if (off1 >= (int)cards->size())
				return NULL;
		}
		if (cards->at(0).get_value() != cards->at(off1).get_value() - 1)
		{
			return NULL;
		}
		if (off1 + off2 >= (int)cards->size())
			return NULL;
		while (off1 + 1 < (int)cards->size() && cards->at(off1).get_value() == cards->at(off1 + off2).get_value())
		{
			off2++;
			if (off1 + off2 >= (int)cards->size())
				return NULL;
		}
		if (cards->at(off1).get_value() != cards->at(off1 + off2).get_value() - 1)
		{
			return NULL;
		}
		if (off1 + off2 + off3 >= (int)cards->size())
			return NULL;
		while (off1 + off2 + 1 < (int)cards->size() && cards->at(off1 + off2).get_value() == cards->at(off1 + off2 + off3).get_value())
		{
			off3++;
			if (off1 + off2 + off3 >= (int)cards->size())
				return NULL;
		}
		if (cards->at(off1 + off2).get_value() != cards->at(off1 + off2 + off3).get_value() - 1)
		{
			return NULL;
		}
		if (off1 + off2 + off3 + off4 >= (int)cards->size())
			return NULL;
		while (off1 + off2 + off3 + 1 < (int)cards->size() && cards->at(off1 + off2 + off3).get_value() == cards->at(off1 + off2 + off3 + off4).get_value())
		{
			off4++;
			if (off1 + off2 + off3 + off4 >= (int)cards->size())
				return NULL;
		}
		if (cards->at(off1 + off2 + off3).get_value() != cards->at(off1 + off2 + off3 + off4).get_value() - 1)
		{
			return NULL;
		}


		//top_card = cards->at(i + off1 + off2 + off3 + off4);
		cards->at(0).set_selected(true);
		cards->at(off1).set_selected(true);
		cards->at(off1 + off2).set_selected(true);
		cards->at(off1 + off2 + off3).set_selected(true);
		cards->at(off1 + off2 + off3 + off4).set_selected(true);
		return &cards->at(off1 + off2 + off3 + off4);
	
	return NULL;
}

Card* CardChecker::ai_select_two_pair_turn1(std::vector<Card>* cards)
{
	if (cards->size() < 4)
		return NULL;
	Card top_card_copy = top_card;
	Card* temp = ai_select_pair_turn1(cards);
	if (temp == NULL)
		return NULL;
	else if (select_lowest_unselected_pair(cards) == -1)
	{
		//restore top_card
		top_card = top_card_copy;
		//deselect all cards
		for (int i = 0; i < (int)cards->size(); i++)
		{
			if (cards->at(i).is_selected())
			{
				cards->at(i).set_selected(false);
			}
		}
		return NULL;
	}

	return temp;
}

Card* CardChecker::ai_select_four_of_a_kind_turn1(std::vector<Card>* cards)
{
	if (cards->size() < 4)
		return NULL;
	sort_by_value_and_suit(cards);
	if (cards->at(0) != Card(0, 3))
		return NULL;
	if (cards->at(0).get_value() != cards->at(1).get_value() || cards->at(1).get_value() != cards->at(2).get_value() || cards->at(2).get_value() != cards->at(3).get_value())
		return NULL;
	cards->at(0).set_selected(true);
	cards->at(1).set_selected(true);
	cards->at(2).set_selected(true);
	cards->at(3).set_selected(true);

	return &cards->at(3);
}

Card* CardChecker::ai_select_three_of_a_kind_turn1(std::vector<Card>* cards)
{
	if (cards->size() < 3)
		return NULL;
	sort_by_value_and_suit(cards);
	if (cards->at(0) != Card(0, 3))
		return NULL;
	if (cards->at(0).get_value() != cards->at(1).get_value() || cards->at(1).get_value() != cards->at(2).get_value())
		return NULL;
	cards->at(0).set_selected(true);
	cards->at(1).set_selected(true);
	cards->at(2).set_selected(true);

	return &cards->at(2);
}

Card* CardChecker::ai_select_pair_turn1(std::vector<Card>* cards)
{
	if (cards->size() < 2)
		return NULL;
	sort_by_value_and_suit(cards);
	if (cards->at(0) != Card(0, 3))
		return NULL;
	if (cards->at(0).get_value() != cards->at(1).get_value())
		return NULL;
	cards->at(0).set_selected(true);
	cards->at(1).set_selected(true);

	return &cards->at(1);
}

Card* CardChecker::ai_select_single_turn1(std::vector<Card>* cards)
{
	if (cards->size() < 1)
		return NULL;
	sort_by_value_and_suit(cards);
	if (cards->at(0) != Card(0, 3))
		return NULL;
	cards->at(0).set_selected(true);
	return &cards->at(0);
}


void CardChecker::reset_top_card()
{
	top_card = Card(0, 3);
}


//private helper functions
int CardChecker::select_lowest_unselected_pair(std::vector<Card>* cards)
{
	sort_by_value_and_suit(cards);
	for (int i = 0; i < (int)cards->size() - 1; i++)
	{
		if (cards->at(i).get_value() == cards->at(i + 1).get_value() && !cards->at(i).is_selected() && !cards->at(i + 1).is_selected())
		{
			cards->at(i).set_selected(true);
			cards->at(i + 1).set_selected(true);
			return 0;
		}
	}
	return -1;
}

int CardChecker::select_lowest_unselected_three_of_a_kind(std::vector<Card>* cards)
{
	sort_by_value_and_suit(cards);
	for (int i = 0; i < (int)cards->size() - 2; i++)
	{
		if (cards->at(i).get_value() == cards->at(i + 1).get_value() && cards->at(i + 1).get_value() == cards->at(i + 2).get_value() && !cards->at(i).is_selected() && !cards->at(i + 1).is_selected() && !cards->at(i + 2).is_selected())
		{
			cards->at(i).set_selected(true);
			cards->at(i + 1).set_selected(true);
			cards->at(i + 2).set_selected(true);
			return 0;
		}
	}
	return -1;
}