#pragma once

#ifndef GAME_H
#define GAME_H

#include <vector>
#include "player.h"
#include "deck.h"
#include "card.h"
#include "card_checker.h"

enum Combination { NONE, SINGLE, PAIR, THREE_OF_A_KIND, TWO_PAIR, STRAIGHT, FULL_HOUSE, FOUR_OF_A_KIND };


class Game
{
public:
	Game();
	//Game(/*??*/);
	int init_game();
	
	Deck* get_deck();
	Player* get_current_player();
	Player* get_player(int player_number);	//std::vector<Player> get_player_list();
	std::vector<Card>* get_played_cards();
	int get_turn();
	int get_finisher(int index);

	void increment_turn();
	void deal_hands();
	int play_cards();
	int ai_select_and_play_cards();

	void print_cards();
	void print_playing_field();

	void set_card_type(Combination type);
	void reset_top_card();
	void add_winner();
	int convert_suit(int suit);

	int reset_game();
	int close_game();
	void clear_playing_field();


private:
	Deck deck;
	CardChecker checker;
	Combination combo_type;
	std::vector<Player> players;
	std::vector<Card> played_cards;
	std::vector<int> winners;
	int turn;

	void playing_buffer_to_playing_field();


};


#endif

