#include "player.h"
#include "card_checker.h"
#include <iostream>

Player::Player()
{
	ai = 1;
	passed = false;
	cards_selected = 0;
}

Player::Player(bool ai)
{
	this->ai = ai;
	passed = false;
	cards_selected = 0;
}

//unused
Player::Player(std::vector<Card> hand, bool ai)
{
	player_hand = hand;
	this->ai = ai;
	passed = false;
	cards_selected = 0;

}

int Player::get_hand_size()
{
	return player_hand.size();
}

std::vector<Card>* Player::get_hand()
{
	return &player_hand;
}

std::vector<Card>* Player::get_playing_buffer()
{
	return &playing_buffer;
}

Card* Player::get_card(int index)
{
	Card* ret_card = &player_hand[index];
	return ret_card;
}

/*Called when a card is clicked for selection/deselection*/
int Player::handle_card_click(int index)
{
	if (index >= (int)player_hand.size())
		return -1;
	if (!player_hand[index].is_selected()) //select the card if it is not selected and 5 cards are not selected yet
	{
		if (cards_selected >= 5)
			return -1;
		player_hand[index].set_selected(true);
		cards_selected++;
	}
	else //deselect the card if it is already selected
	{
		player_hand[index].set_selected(false);
		cards_selected--;
	}
	return 0;
}

/*
Moves selected cards to the playing_buffer
*/
void Player::push_selected_cards_to_buffer()
{
	cards_selected = 0;
	int offset = 0;
	int index = 0;
	for (int i = 0; i < (int)player_hand.size() + offset; i++)
	{
		index = i - offset;
		if (player_hand[index].is_selected())//deselect card and move it to playing_buffer if it is selected
		{
			player_hand[index].set_selected(false);
			playing_buffer.push_back(player_hand[index]);
			player_hand.erase(player_hand.begin() + index);
			offset++;
		}
	}
}

/*
Puts all cards from playing buffer back into the hand 
*/
void Player::undo_playing_buffer()
{
	while (playing_buffer.size() > 0)
	{
		player_hand.push_back(playing_buffer.back());
		playing_buffer.pop_back();
	}
}

bool Player::is_ai()
{
	return ai;
}

bool Player::is_passed()
{
	return passed;
}

bool Player::already_won()
{
	return won;
}

void Player::set_passed(bool passed)
{
	this->passed = passed;
}

void Player::set_won(bool won)
{
	this->won = won;
}

void Player::print_hand()
{
	std::cout << "Hand: ";
	for (int i = 0; i < (int)player_hand.size(); i++)
	{
		player_hand[i].print_card();
	}
	std::cout << "\n";
}

void Player::print_selected()
{
	std::cout << "Selected cards: ";
	for (int i = 0; i < (int)player_hand.size(); i++)
	{
		if (player_hand[i].is_selected())
		{
			player_hand[i].print_card();
		}
	}
	std::cout << "\n";
}

void Player::print_playing_buffer()
{
	std::cout << "Playing: ";
	for (int i = 0; i < (int)playing_buffer.size(); i++)
	{
		playing_buffer[i].print_card();
	}
	std::cout << "\n";
}


int Player::close_player()
{
	while (player_hand.size() > 0)
	{
		player_hand.pop_back();
	}
	while (playing_buffer.size() > 0)
	{
		playing_buffer.pop_back();
	}
	return 0;
}