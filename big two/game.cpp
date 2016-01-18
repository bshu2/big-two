#include "game.h"

#include <iostream>

Game::Game()
{
	
}


int Game::init_game()
{
	//initialize the player
	Player player(false);
	players.push_back(player);

	//initialize the 3 ai
	for (int i = 0; i < 3; i++)
	{
		Player ai(true);
		players.push_back(ai);
	}

	deck.init_deck();

	reset_top_card();

	combo_type = NONE;

	return 0;
}

Deck* Game::get_deck()
{
	return &deck;
}

Player* Game::get_current_player()
{
	return &players[turn];
}

Player* Game::get_player(int player_number)
{
	return &players[player_number];
}

std::vector<Card>* Game::get_played_cards()
{
	return &played_cards;
}

int Game::get_turn()
{
	return turn;
}

int Game::get_finisher(int index)
{
	if (index >= winners.size())
		return -1;
	return winners[index];
}

void Game::increment_turn()
{
	turn = (turn + 1) % 4;
}

/*
Deals out cards from the deck to the four players, and marks to turn to be the player with the 3 of clubs
*/
void Game::deal_hands()
{
	Card three_of_clubs(0, 3);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			if (deck.get_deck_cards()->back() == three_of_clubs)
			{
				turn = i;
			}
			players[i].get_hand()->push_back(deck.get_deck_cards()->back());
			deck.get_deck_cards()->pop_back();
		}
		checker.sort_by_value_and_suit(get_player(i)->get_hand());
	}
}

/*Plays cards for the current player, returning the combination type or -1 for invalid*/
int Game::play_cards()
{
	//push cards to playing buffer
	get_current_player()->push_selected_cards_to_buffer();

	Card* temp;
	//check validity of cards
	if ((combo_type == NONE || combo_type == STRAIGHT) && (temp = checker.check_straight(get_current_player()->get_playing_buffer())) != NULL)
	{
		combo_type = STRAIGHT;
	}
	else if ((combo_type == NONE || combo_type == FULL_HOUSE) && (temp = checker.check_full_house(get_current_player()->get_playing_buffer())) != NULL)
	{
		combo_type = FULL_HOUSE;
	}
	else if ((combo_type == NONE || combo_type == TWO_PAIR) && (temp = checker.check_two_pair(get_current_player()->get_playing_buffer())) != NULL)
	{
		combo_type = TWO_PAIR;
	}
	else if ((combo_type == NONE || combo_type == FOUR_OF_A_KIND) && (temp = checker.check_four_of_a_kind(get_current_player()->get_playing_buffer())) != NULL)
	{
		combo_type = FOUR_OF_A_KIND;
	}
	else if ((combo_type == NONE || combo_type == THREE_OF_A_KIND) && (temp = checker.check_three_of_a_kind(get_current_player()->get_playing_buffer())) != NULL)
	{
		combo_type = THREE_OF_A_KIND;
	}
	else if ((combo_type == NONE || combo_type == PAIR) && (temp = checker.check_pair(get_current_player()->get_playing_buffer())) != NULL)
	{
		combo_type = PAIR;
	}
	else if ((combo_type == NONE || combo_type == SINGLE) && (temp = checker.check_single(get_current_player()->get_playing_buffer())) != NULL)
	{
		combo_type = SINGLE;
	}
	else //invalid combination
	{
		get_current_player()->undo_playing_buffer();
		checker.sort_by_value_and_suit(get_current_player()->get_hand());
		return -1;
	}

	clear_playing_field();//clear the playing field
	playing_buffer_to_playing_field();//put cards into playing field

	return combo_type;
}

int Game::ai_select_and_play_cards()
{
	//select of cards if possible and push them to buffer and play them
	if ((combo_type == NONE || combo_type == STRAIGHT) && checker.ai_select_straight(get_current_player()->get_hand()) != NULL)
	{
		std::cout << "straight found\n";

		get_current_player()->push_selected_cards_to_buffer();
		if (checker.check_straight(get_current_player()->get_playing_buffer()) == NULL)
			return -1;
		combo_type = STRAIGHT;
	}
	else if ((combo_type == NONE || combo_type == FULL_HOUSE) && checker.ai_select_full_house(get_current_player()->get_hand()) != NULL)
	{
		std::cout << "Full house found\n";

		get_current_player()->push_selected_cards_to_buffer();
		if (checker.check_full_house(get_current_player()->get_playing_buffer()) == NULL)
			return -1;
		combo_type = FULL_HOUSE;
	}
	else if ((combo_type == NONE || combo_type == TWO_PAIR) && checker.ai_select_two_pair(get_current_player()->get_hand()) != NULL)
	{
		std::cout << "2p found\n";

		get_current_player()->push_selected_cards_to_buffer();
		if (checker.check_two_pair(get_current_player()->get_playing_buffer()) == NULL)
			return -1;
		combo_type = TWO_PAIR;
	}
	else if ((combo_type == NONE || combo_type == FOUR_OF_A_KIND) && checker.ai_select_four_of_a_kind(get_current_player()->get_hand()) != NULL)
	{
		std::cout << "4k found\n";

		get_current_player()->push_selected_cards_to_buffer();
		if (checker.check_four_of_a_kind(get_current_player()->get_playing_buffer()) == NULL)
			return -1;
		combo_type = FOUR_OF_A_KIND;
	}
	else if ((combo_type == NONE || combo_type == THREE_OF_A_KIND) && checker.ai_select_three_of_a_kind(get_current_player()->get_hand()) != NULL)
	{
		std::cout << "3k found\n";

		get_current_player()->push_selected_cards_to_buffer();
		if (checker.check_three_of_a_kind(get_current_player()->get_playing_buffer()) == NULL)
			return -1;
		combo_type = THREE_OF_A_KIND;
	}
	else if ((combo_type == NONE || combo_type == PAIR) && checker.ai_select_pair(get_current_player()->get_hand()) != NULL)
	{
		std::cout << "p found\n";

		get_current_player()->push_selected_cards_to_buffer();
		if (checker.check_pair(get_current_player()->get_playing_buffer()) == NULL)
			return -1;
		combo_type = PAIR;
	}
	else if ((combo_type == NONE || combo_type == SINGLE) && checker.ai_select_single(get_current_player()->get_hand()) != NULL)
	{
		std::cout << "single found\n";

		get_current_player()->push_selected_cards_to_buffer();
		if (checker.check_single(get_current_player()->get_playing_buffer()) == NULL)
			return -1;
		combo_type = SINGLE;
	}
	else //invalid combination
	{
		return -1;
	}

	get_current_player()->print_playing_buffer();
	std::cout << "Combination " << combo_type << " played\n";

	clear_playing_field();//clear the playing field
	playing_buffer_to_playing_field();//put cards into playing field

	return combo_type;
}

int Game::ai_select_and_play_cards_turn1()
{
	//select of cards if possible and push them to buffer and play them
	if ((combo_type == NONE || combo_type == STRAIGHT) && checker.ai_select_straight_turn1(get_current_player()->get_hand()) != NULL)
	{
		std::cout << "straight found\n";

		get_current_player()->push_selected_cards_to_buffer();
		if (checker.check_straight(get_current_player()->get_playing_buffer()) == NULL)
			return -1;
		combo_type = STRAIGHT;
	}
	else if ((combo_type == NONE || combo_type == FULL_HOUSE) && checker.ai_select_full_house_turn1_type1(get_current_player()->get_hand()) != NULL)
	{
		std::cout << "Full house t1 found\n";

		get_current_player()->push_selected_cards_to_buffer();
		if (checker.check_full_house(get_current_player()->get_playing_buffer()) == NULL)
			return -1;
		combo_type = FULL_HOUSE;
	}
	else if ((combo_type == NONE || combo_type == FULL_HOUSE) && checker.ai_select_full_house_turn1_type2(get_current_player()->get_hand()) != NULL)
	{
		std::cout << "Full house t2 found\n";

		get_current_player()->push_selected_cards_to_buffer();
		if (checker.check_full_house(get_current_player()->get_playing_buffer()) == NULL)
			return -1;
		combo_type = FULL_HOUSE;
	}
	else if ((combo_type == NONE || combo_type == TWO_PAIR) && checker.ai_select_two_pair_turn1(get_current_player()->get_hand()) != NULL)
	{
		std::cout << "2p found\n";

		get_current_player()->push_selected_cards_to_buffer();
		if (checker.check_two_pair(get_current_player()->get_playing_buffer()) == NULL)
			return -1;
		combo_type = TWO_PAIR;
	}
	else if ((combo_type == NONE || combo_type == FOUR_OF_A_KIND) && checker.ai_select_four_of_a_kind_turn1(get_current_player()->get_hand()) != NULL)
	{
		std::cout << "4k found\n";

		get_current_player()->push_selected_cards_to_buffer();
		if (checker.check_four_of_a_kind(get_current_player()->get_playing_buffer()) == NULL)
			return -1;
		combo_type = FOUR_OF_A_KIND;
	}
	else if ((combo_type == NONE || combo_type == THREE_OF_A_KIND) && checker.ai_select_three_of_a_kind_turn1(get_current_player()->get_hand()) != NULL)
	{
		std::cout << "3k found\n";

		get_current_player()->push_selected_cards_to_buffer();
		if (checker.check_three_of_a_kind(get_current_player()->get_playing_buffer()) == NULL)
			return -1;
		combo_type = THREE_OF_A_KIND;
	}
	else if ((combo_type == NONE || combo_type == PAIR) && checker.ai_select_pair_turn1(get_current_player()->get_hand()) != NULL)
	{
		std::cout << "p found\n";

		get_current_player()->push_selected_cards_to_buffer();
		if (checker.check_pair(get_current_player()->get_playing_buffer()) == NULL)
			return -1;
		combo_type = PAIR;
	}
	else if ((combo_type == NONE || combo_type == SINGLE) && checker.ai_select_single_turn1(get_current_player()->get_hand()) != NULL)
	{
		std::cout << "single found\n";

		get_current_player()->push_selected_cards_to_buffer();
		if (checker.check_single(get_current_player()->get_playing_buffer()) == NULL)
			return -1;
		combo_type = SINGLE;
	}
	else //invalid combination
	{
		return -1;
	}

	get_current_player()->print_playing_buffer();
	std::cout << "Combination " << combo_type << " played\n";

	clear_playing_field();//clear the playing field
	playing_buffer_to_playing_field();//put cards into playing field

	return combo_type;
}

void Game::print_cards()
{
	for (int i = 0; i < 4; i++)
	{
		std::cout << "player " << i;
		players[i].print_hand();
	}
}

void Game::print_playing_field()
{
	std::cout << "Playing field: ";
	for (int i = 0; i < (int)played_cards.size(); i++)
	{
		played_cards[i].print_card();
	}
	std::cout << "\n";
}

void Game::set_card_type(Combination type)
{
	combo_type = type;
}

void Game::reset_top_card()
{
	checker.reset_top_card();
}

void Game::add_winner()
{
	winners.push_back(turn);
	get_current_player()->set_won(true);
}

int Game::convert_suit(int suit)
{
	if (suit == 0 || suit == 1)
	{
		return (3 - suit);
	}
	else if (suit == 2 || suit == 3)
	{
		return (suit - 2);
	}
	return -1;
}

/*Collects all cards back into the deck*/
int Game::reset_game()
{
	for (int i = 0; i < 4; i++)
	{
		while (players[i].get_hand()->size() > 0)
		{
			deck.get_deck_cards()->push_back(players[i].get_hand()->back());
			players[i].get_hand()->pop_back();
		}
	}

	while (winners.size() > 0)
	{
		winners.pop_back();
	}

	while (played_cards.size() > 0)
	{
		deck.get_deck_cards()->push_back(played_cards.back());
		played_cards.pop_back();
	}

	return 0;
}

int Game::close_game()
{
	deck.close_deck();

	while (played_cards.size() > 0)
	{
		played_cards.pop_back();
	}

	while (winners.size() > 0)
	{
		winners.pop_back();
	}
	
	for (int i = 0; i < 4; i++)
	{
		players[i].close_player();
	}
	return 0;
}


/*move all played_cards back into the deck*/
void Game::clear_playing_field()
{
	while (played_cards.size() > 0)
	{
		deck.get_deck_cards()->push_back(played_cards.back());
		played_cards.pop_back();
	}
}

//Private helper functions

/*move playing bufer to playing field*/
void Game::playing_buffer_to_playing_field()
{
	//copy cards from playing buffer to playing field
	for (int i = 0; i < (int)get_current_player()->get_playing_buffer()->size(); i++)
	{
		played_cards.push_back(get_current_player()->get_playing_buffer()->at(i));
	}
	//clear playing buffer
	while (get_current_player()->get_playing_buffer()->size() > 0)
	{
		get_current_player()->get_playing_buffer()->pop_back();
	}
}

