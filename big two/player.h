#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
#include <vector>

class Player
{
public:
	Player();
	Player(bool ai);
	Player(std::vector<Card> hand, bool ai);

	int get_hand_size();
	std::vector<Card>* get_hand();
	std::vector<Card>* get_playing_buffer();
	Card* get_card(int index);
	int handle_card_click(int index);

	void push_selected_cards_to_buffer();
	void undo_playing_buffer();

	bool is_ai();
	bool is_passed();
	bool already_won();

	void set_passed(bool passed);
	void set_won(bool won);

	void print_hand();
	void print_selected();
	void print_playing_buffer();

	int close_player();

private:
	std::vector<Card> player_hand;
	std::vector<Card> playing_buffer;
	int cards_selected;
	bool ai;
	bool passed;
	bool won;

};

#endif