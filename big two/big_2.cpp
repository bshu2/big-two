#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "game.h"
#include "deck.h"
#include "hand.h"
#include "card.h"
#include "button.h"

#include <iostream>
#include <time.h>

enum GameState { START_SCREEN, PLAYING, END_SCREEN, EXIT };
enum PlayingState { PREPARE_GAME, START_FIRST_ROUND, START_ROUND, CONTINUE_ROUND, END_ROUND, END_PLAY };
//enum PlayerTurnState { AWAITING_INPUT, PLAYER_PASSED, CARD_SELECTED, PLAY_SELECTED_CARDS, END_TURN};

int main(int argc, char* args[])
{
	Game game;
	GameState game_state = START_SCREEN;
	PlayingState playing_state = PREPARE_GAME;
	int passed_players = 0;
	int won_players = 0;
	int player_hand_offset;
	int playing_field_offset;

	//CardSetType card_type = NONE;

	game.init_game();

	//game.get_deck()->print_deck();

	
	/*
	game.get_deck()->print_deck();
	game.get_deck()->shuffle_deck();
	game.get_deck()->print_deck();
	game.deal_hands();
	game.get_deck()->print_deck();
	for (int i = 0; i < 4; i++)
	{
		game.get_player(i)->print_hand();
	}

	while (true)
	{

	}
	*/

	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

	// load font
	sf::Font font;
	if (!font.loadFromFile("secret_of_mana.ttf"))
		return EXIT_FAILURE;

	//start screen text
	sf::Text title("Big 2", font, 70);
	title.setPosition(280, 200);
	sf::Text start_message("Click Anywhere to Start", font, 30);
	start_message.setPosition(180, 400);

	//empty turn and place text
	sf::Text turn_text("ERROR", font, 30);
	sf::Text place_text("ERROR", font, 50);
	place_text.setPosition(120,150);

	//exit screen text
	sf::Text play_again_message("Play again", font, 25);
	play_again_message.setPosition(115, 510);
	sf::Text exit_message("Exit", font, 25);
	exit_message.setPosition(565, 510);

	//load card textures
	sf::Texture card_sheet, smaller_card_sheet;
	sf::Image card_sheet_image;
	if (!card_sheet_image.loadFromFile("card_spritesheet_small.jpg"))
		return EXIT_FAILURE;
	for (int s = 0; s < 4; s++)
	{
		for (int v = 0; v < 13; v++)
		{
			int offsetx = v * 90, offsety = s * 126;
			//top left corner
			card_sheet_image.setPixel(offsetx, offsety, sf::Color(0, 0, 0, 0));
			card_sheet_image.setPixel(offsetx + 1, offsety, sf::Color(0, 0, 0, 0));
			card_sheet_image.setPixel(offsetx + 2, offsety, sf::Color(0, 0, 0, 0));
			card_sheet_image.setPixel(offsetx + 3, offsety, sf::Color(0, 0, 0, 0));
			card_sheet_image.setPixel(offsetx + 1, offsety + 1, sf::Color(0, 0, 0, 0));
			card_sheet_image.setPixel(offsetx, offsety + 1, sf::Color(0, 0, 0, 0));
			card_sheet_image.setPixel(offsetx, offsety + 2, sf::Color(0, 0, 0, 0));
			card_sheet_image.setPixel(offsetx, offsety + 3, sf::Color(0, 0, 0, 0));
			//top right corner
			card_sheet_image.setPixel(offsetx + 89, offsety, sf::Color(0, 0, 0, 0));
			card_sheet_image.setPixel(offsetx + 88, offsety, sf::Color(0, 0, 0, 0));
			card_sheet_image.setPixel(offsetx + 87, offsety, sf::Color(0, 0, 0, 0));
			card_sheet_image.setPixel(offsetx + 86, offsety, sf::Color(0, 0, 0, 0));
			card_sheet_image.setPixel(offsetx + 88, offsety + 1, sf::Color(0, 0, 0, 0));
			card_sheet_image.setPixel(offsetx + 89, offsety + 1, sf::Color(0, 0, 0, 0));
			card_sheet_image.setPixel(offsetx + 89, offsety + 2, sf::Color(0, 0, 0, 0));
			card_sheet_image.setPixel(offsetx + 89, offsety + 3, sf::Color(0, 0, 0, 0));
			//bottom left corner
			card_sheet_image.setPixel(offsetx, offsety + 125, sf::Color(0, 0, 0, 0));
			card_sheet_image.setPixel(offsetx + 1, offsety + 125, sf::Color(0, 0, 0, 0));
			card_sheet_image.setPixel(offsetx + 2, offsety + 125, sf::Color(0, 0, 0, 0));
			card_sheet_image.setPixel(offsetx + 3, offsety + 125, sf::Color(0, 0, 0, 0));
			card_sheet_image.setPixel(offsetx + 1, offsety + 124, sf::Color(0, 0, 0, 0));
			card_sheet_image.setPixel(offsetx, offsety + 124, sf::Color(0, 0, 0, 0));
			card_sheet_image.setPixel(offsetx, offsety + 123, sf::Color(0, 0, 0, 0));
			card_sheet_image.setPixel(offsetx, offsety + 122, sf::Color(0, 0, 0, 0));
			//bottom right corner
			card_sheet_image.setPixel(offsetx + 89, offsety + 125, sf::Color(0, 0, 0, 0));
			card_sheet_image.setPixel(offsetx + 88, offsety + 125, sf::Color(0, 0, 0, 0));
			card_sheet_image.setPixel(offsetx + 87, offsety + 125, sf::Color(0, 0, 0, 0));
			card_sheet_image.setPixel(offsetx + 86, offsety + 125, sf::Color(0, 0, 0, 0));
			card_sheet_image.setPixel(offsetx + 88, offsety + 124, sf::Color(0, 0, 0, 0));
			card_sheet_image.setPixel(offsetx + 89, offsety + 124, sf::Color(0, 0, 0, 0));
			card_sheet_image.setPixel(offsetx + 89, offsety + 123, sf::Color(0, 0, 0, 0));
			card_sheet_image.setPixel(offsetx + 89, offsety + 122, sf::Color(0, 0, 0, 0));
		}
	}
	if (!card_sheet.loadFromImage(card_sheet_image))
		return EXIT_FAILURE;
	if (!smaller_card_sheet.loadFromFile("card_spritesheet_smaller.jpg"))
		return EXIT_FAILURE;

	//card sprites
	sf::Sprite playing_field_sprites[5];
	sf::Sprite player_hand_sprites[13];

	//card and exit screen buttons
	Button player_card_buttons[13];
	Button play_again_button(100, 500, 200, 50);
	Button exit_button(500, 500, 200, 50);

	//exit screen button rectangles
	sf::RectangleShape play_again_rect(sf::Vector2f(200, 50));
	play_again_rect.setOutlineColor(sf::Color(255, 255, 255));
	play_again_rect.setOutlineThickness(2.0);
	play_again_rect.setFillColor(sf::Color(0, 0, 0));
	play_again_rect.setPosition(100, 500);
	sf::RectangleShape exit_rect(sf::Vector2f(200, 50));
	exit_rect.setOutlineColor(sf::Color(255, 255, 255));
	exit_rect.setOutlineThickness(2.0);
	exit_rect.setFillColor(sf::Color(0, 0, 0));
	exit_rect.setPosition(500, 500);

	sf::Texture chara_texture;
	if (!chara_texture.loadFromFile("Chara.png"))
		return EXIT_FAILURE;
	sf::Sprite chara(chara_texture);
	chara.setPosition(375,300);






	sf::Event event;

	while (window.isOpen())
	{
		window.clear();//clear screen
		
		



		switch (game_state)
		{
		case START_SCREEN:
			// wait for user input and process events
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
					// window closed
				case sf::Event::Closed:
					game_state = EXIT;//window.close();
					break;

				case sf::Event::MouseButtonPressed:
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						game_state = PLAYING;//game_state = END_SCREEN;
					}
					break;

					// key pressed
				case sf::Event::KeyPressed:
					switch (event.key.code)
					{
					case sf::Keyboard::Escape:
						game_state = EXIT;//window.close();
						break;
					default:
						break;
					}
					break;

					// we don't process other types of events
				default:
					break;
				}
			}
			// Draw text
			window.draw(title);
			window.draw(start_message);
			window.display();

			break;
		case PLAYING:

			switch (playing_state)
			{
			case PREPARE_GAME:
				// prepare for a new game
				game.get_deck()->shuffle_deck();
				game.deal_hands();
				playing_state = START_FIRST_ROUND;
				break;
			case START_FIRST_ROUND:
				game.set_card_type(NONE);
				game.reset_top_card();

				//display cards for the human player
				player_hand_offset = 175 + (13 - game.get_player(0)->get_hand_size()) * 15;
				for (int i = 0; i < game.get_player(0)->get_hand_size(); i++)
				{
					player_hand_sprites[i].setTexture(card_sheet);
					player_hand_sprites[i].setTextureRect(sf::IntRect((game.get_player(0)->get_hand()->at(i).get_value() - 1) * 90, game.convert_suit(game.get_player(0)->get_hand()->at(i).get_suit()) * 126, 90, 126));
					player_hand_sprites[i].setPosition(player_hand_offset + 30 * i, 450 - 10* game.get_player(0)->get_hand()->at(i).is_selected());
					window.draw(player_hand_sprites[i]);
				}
				//display turn text
				if (game.get_turn() == 0)
					turn_text.setString("Your turn"); 
				else if (game.get_turn() == 1)
					turn_text.setString("Computer 1 turn");
				else if (game.get_turn() == 2)
					turn_text.setString("Computer 2 turn");
				else if (game.get_turn() == 3)
					turn_text.setString("Computer 3 turn");
				window.draw(turn_text);

				if (game.get_player(game.get_turn())->is_ai()) //logic for ai
				{
					while (window.pollEvent(event))
					{
						switch (event.type)
						{
							// window closed
						case sf::Event::Closed:
							window.close();
							break;

						case sf::Event::MouseButtonPressed:
							if (event.mouseButton.button == sf::Mouse::Left)
							{
								std::cout << "\nPlayer " << game.get_turn() << " starts first\n";
								std::cout << "START_FIRST_ROUND\n";
								game.print_playing_field();
								game.get_current_player()->print_hand();

								int pause;

								if (game.ai_select_and_play_cards() == -1)
								{
									std::cout << "no playable cards?? BUG";
									std::cin >> pause;
								}

								game.increment_turn();
								playing_state = CONTINUE_ROUND;
							}
							break;
						default:
							break;
						}
					}

					/*//TODO ai stuff
					std::cout << "\nPlayer " << game.get_turn() << " starts first\n";
					std::cout << "START_FIRST_ROUND\n";
					game.print_playing_field();
					game.get_current_player()->print_hand();

					int pause;

					if (game.ai_select_and_play_cards() == -1)
					{
						std::cout << "no playable cards?? BUG";
						std::cin >> pause;
					}
					
					game.increment_turn();
					playing_state = CONTINUE_ROUND;

					std::cout << "\nPause\n";
					std::cin >> pause;*/
				}
				else //logic for human player
				{
					//TODO await player input
					if (!game.get_player(0)->get_hand()->at(0).is_selected())
					{
						game.get_current_player()->handle_card_click(0);
					}
					player_hand_offset = 175 + (13 - game.get_player(0)->get_hand_size()) * 15;

					while (window.pollEvent(event))
					{
						switch (event.type)
						{
							// window closed
						case sf::Event::Closed:
							window.close();
							break;

						case sf::Event::MouseButtonPressed:
							if (event.mouseButton.button == sf::Mouse::Left)
							{
								
								for (int i = 0; i < game.get_current_player()->get_hand_size(); i++)
								{
									if (i == game.get_current_player()->get_hand_size() - 1)
										player_card_buttons[i].set_trigger_box(player_hand_offset + 30 * i, 450 - 10 * game.get_player(0)->get_hand()->at(i).is_selected(), 90, 126);
									else
										player_card_buttons[i].set_trigger_box(player_hand_offset + 30 * i, 450 - 10 * game.get_player(0)->get_hand()->at(i).is_selected(), 30, 126);
									if (player_card_buttons[i].handle_event(&event))
									{
										if (i == 0)
										{
											//game.get_current_player()->handle_card_click(0);
											std::cout << "Cannot deselect the 3 of clubs\n";
											continue;
										}
										else
										{
											//std::cout << "index " << i << " selected\n";
											game.get_current_player()->handle_card_click(i);
										}
									}

								}
							}
							break;

							// key pressed
						case sf::Event::KeyPressed:
							switch (event.key.code)
							{
							case sf::Keyboard::Space:
								int combo_type;
								combo_type = game.play_cards(); //check validity and play cards if valid

								if (combo_type == -1)
								{
									std::cout << "Invalid play\n";
									continue;
								}
								else
								{
									std::cout << "Combination " << combo_type << " was played\n";
								}

								//set card type
								game.set_card_type((Combination)combo_type);
								//increment turn
								game.increment_turn();
								playing_state = CONTINUE_ROUND;
								break;
							default:
								break;
							}
							break;

							// we don't process other types of events
						default:
							break;
						}
					}

					/*while (awaiting_input)
					{
						int action;


						std::cout << "\nPlayer " << game.get_turn() << " starts first\n";
						game.print_playing_field();
						game.get_current_player()->print_hand();
						game.get_current_player()->print_selected();
						
						std::cout << "Enter 0 to select/deselect a card, 2 to play cards:";
						std::cin >> action;

						if (action == 0 )//player clicks on card
						{
							int selected_index;
							std::cout << "Enter index of card to select:";
							std::cin >> selected_index;
							if (selected_index == 0)
							{
								std::cout << "Cannot deselect the 3 of clubs\n";
								continue;
							}
							
							//add to selected
							game.get_current_player()->handle_card_click(selected_index);
							
						}
						else if (action == 2)//player plays cards
						{
							int combo_type;
							combo_type = game.play_cards(); //check validity and play cards if valid

							if (combo_type == -1)
							{
								std::cout << "Invalid play\n";
								continue;
							}
							else
							{
								std::cout << "Combination " << combo_type << " was played\n";
							}

							//set card type
							game.set_card_type((Combination)combo_type);
							//increment turn
							game.increment_turn();

							awaiting_input = 0;
							break;
						}
						
					}*/
					
					
					
				}
				
				window.display();
				break;
			case START_ROUND:

				game.set_card_type(NONE);
				game.reset_top_card();

				//display cards for the human player
				player_hand_offset = 175 + (13 - game.get_player(0)->get_hand_size()) * 15;
				for (int i = 0; i < game.get_player(0)->get_hand_size(); i++)
				{
					player_hand_sprites[i].setTexture(card_sheet);
					player_hand_sprites[i].setTextureRect(sf::IntRect((game.get_player(0)->get_hand()->at(i).get_value() - 1) * 90, game.convert_suit(game.get_player(0)->get_hand()->at(i).get_suit()) * 126, 90, 126));
					player_hand_sprites[i].setPosition(player_hand_offset + 30 * i, 450 - 10 * game.get_player(0)->get_hand()->at(i).is_selected());
					window.draw(player_hand_sprites[i]);
				}
				//display playing field
				playing_field_offset = 295 + (5 - game.get_played_cards()->size()) * 15; //400 - (game.get_played_cards()->size())* 23;
				for (int i = 0; i < (int)game.get_played_cards()->size(); i++)
				{
					//game.get_played_cards()->at(i).print_card();
					playing_field_sprites[i].setTexture(card_sheet);//smaller_card_sheet
					playing_field_sprites[i].setTextureRect(sf::IntRect((game.get_played_cards()->at(i).get_value() - 1) * 90, game.convert_suit(game.get_played_cards()->at(i).get_suit()) * 126, 90, 126));//45,62
					playing_field_sprites[i].setPosition(playing_field_offset + 30 * i, 250);//45
					window.draw(playing_field_sprites[i]);
				}
				//display turn text
				if (game.get_turn() == 0)
					turn_text.setString("Your turn");
				else if (game.get_turn() == 1)
					turn_text.setString("Computer 1 turn");
				else if (game.get_turn() == 2)
					turn_text.setString("Computer 2 turn");
				else if (game.get_turn() == 3)
					turn_text.setString("Computer 3 turn");
				window.draw(turn_text);

				//if player already won, then pass (this means player just emptied his hand and had board control)
				if (game.get_current_player()->already_won())
				{
					std::cout << "Player " << game.get_turn() << " has already won\n";
					if (!game.get_current_player()->is_passed())//if the player is not passed, then pass
					{
						passed_players++;
						game.get_player(game.get_turn())->set_passed(true);
					}
					game.increment_turn();
					break;
				}
				else if (game.get_player(game.get_turn())->is_ai()) //logic for ai
				{
					//TODO ai stuff
					while (window.pollEvent(event))
					{
						switch (event.type)
						{
							// window closed
						case sf::Event::Closed:
							window.close();
							break;

						case sf::Event::MouseButtonPressed:
							if (event.mouseButton.button == sf::Mouse::Left)
							{
								std::cout << "\nPlayer " << game.get_turn() << "'s turn\n";
								std::cout << "START_ROUND\n";
								game.print_playing_field();
								game.get_current_player()->print_hand();

								int pause;

								if (game.ai_select_and_play_cards() == -1)
								{
									std::cout << "no playable cards?? BUG";
									std::cin >> pause;
								}
								//if no cards left, mark player as won
								if (game.get_current_player()->get_hand_size() == 0)
								{
									std::cout << "Player " << game.get_turn() << " won!";
									game.add_winner();
									won_players++;
								}
								game.increment_turn();
								playing_state = CONTINUE_ROUND;
								
								
							}
							break;
						default:
							break;
						}
					}


					/*std::cout << "\nPlayer " << game.get_turn() << "'s turn\n";
					std::cout << "START_ROUND\n";
					game.print_playing_field();
					game.get_current_player()->print_hand();

					int pause;

					if (game.ai_select_and_play_cards() == -1)
					{
						std::cout << "no playable cards?? BUG";
						std::cin >> pause;
					}
					//if no cards left, mark player as won
					if (game.get_current_player()->get_hand_size() == 0)
					{
						std::cout << "Player " << game.get_turn() << " won!";
						game.add_winner();
						won_players++;
					}
					game.increment_turn();
					playing_state = CONTINUE_ROUND;
					if (passed_players + won_players >= 3)
					{
						playing_state = END_ROUND;
					}
					if (won_players == 4)
					{
						playing_state = END_PLAY;
					}
					std::cout << "\nPause\n";
					std::cin >> pause;*/
				}
				else //logic for human player
				{
					//TODO await player input
					player_hand_offset = 175 + (13 - game.get_current_player()->get_hand_size()) * 15;

					while (window.pollEvent(event))
					{
						switch (event.type)
						{
							// window closed
						case sf::Event::Closed:
							window.close();
							break;

						case sf::Event::MouseButtonPressed:
							if (event.mouseButton.button == sf::Mouse::Left)
							{
								for (int i = 0; i < game.get_current_player()->get_hand_size(); i++)
								{
									if (i == game.get_current_player()->get_hand_size() - 1)
										player_card_buttons[i].set_trigger_box(player_hand_offset + 30 * i, 450 - 10 * game.get_player(0)->get_hand()->at(i).is_selected(), 90, 126);
									else
										player_card_buttons[i].set_trigger_box(player_hand_offset + 30 * i, 450 - 10 * game.get_player(0)->get_hand()->at(i).is_selected(), 30, 126);
									if (player_card_buttons[i].handle_event(&event))
									{
										//std::cout << "index " << i << " selected\n";
										game.get_current_player()->handle_card_click(i);
									}

								}
							}
							break;

							// key pressed
						case sf::Event::KeyPressed:
							switch (event.key.code)
							{
							case sf::Keyboard::Space:
								int combo_type;
								combo_type = game.play_cards(); //check validity and play cards if valid

								if (combo_type == -1)
								{
									std::cout << "Invalid play\n";
									continue;
								}
								else
								{
									std::cout << "Combination " << combo_type << " was played\n";
								}

								//set card type
								game.set_card_type((Combination)combo_type);

								//if no cards left, mark player as won
								if (game.get_current_player()->get_hand_size() == 0)
								{
									std::cout << "Player " << game.get_turn() << " won!";
									game.add_winner();
									won_players++;
								}

								//increment turn
								game.increment_turn();
								playing_state = CONTINUE_ROUND;
								break;
							default:
								break;
							}
							break;

							// we don't process other types of events
						default:
							break;
						}
					}
					
					
					
					/*int awaiting_input = 1;
					while (awaiting_input)
					{
						int action;

						std::cout << "\nPlayer " << game.get_turn() << "'s turn\n";
						game.print_playing_field();
						game.get_current_player()->print_hand();
						game.get_current_player()->print_selected();

						std::cout << "Enter 0 to select/deselect a card, 2 to play cards:";
						std::cin >> action;

						if (action == 0 )//player clicks on card
						{
							int selected_index;
							std::cout << "Enter index of card to select:";
							std::cin >> selected_index;

							//add to selected
							game.get_current_player()->handle_card_click(selected_index);

						}
						else if (action == 2)//player plays cards
						{
							int combo_type;
							combo_type = game.play_cards(); //check validity and play cards if valid

							if (combo_type == -1)
							{
								std::cout << "Invalid play\n";
								continue;
							}
							else
							{
								std::cout << "Combination " << combo_type << " was played\n";
							}

							//if no cards left, mark player as won
							if (game.get_current_player()->get_hand_size() == 0)
							{
								std::cout << "Player " << game.get_turn() << " won!";
								game.add_winner();
								won_players++;
							}

							//set card type
							game.set_card_type((Combination)combo_type);
							//increment turn
							game.increment_turn();

							awaiting_input = 0;
							break;
						}

					}*/
					
				}
				if (passed_players >= 3)
				{
					playing_state = END_ROUND;
				}
				if (won_players == 4)
				{
					playing_state = END_PLAY;
				}
				window.display();
				break;
			case CONTINUE_ROUND:

				//display cards for the human player
				player_hand_offset = 175 + (13 - game.get_player(0)->get_hand_size()) * 15;
				for (int i = 0; i < game.get_player(0)->get_hand_size(); i++)
				{
					player_hand_sprites[i].setTexture(card_sheet);
					player_hand_sprites[i].setTextureRect(sf::IntRect((game.get_player(0)->get_hand()->at(i).get_value() - 1) * 90, game.convert_suit(game.get_player(0)->get_hand()->at(i).get_suit()) * 126, 90, 126));
					player_hand_sprites[i].setPosition(player_hand_offset + 30 * i, 450 - 10 * game.get_player(0)->get_hand()->at(i).is_selected());
					window.draw(player_hand_sprites[i]);
				}

				//std::cout << "pf size = " << game.get_played_cards()->size() << "\n";
				//display playing field
				playing_field_offset = 295 + (5 - game.get_played_cards()->size()) * 15; //400 - (game.get_played_cards()->size())* 23;
				for (int i = 0; i < (int)game.get_played_cards()->size(); i++)
				{
					//game.get_played_cards()->at(i).print_card();
					playing_field_sprites[i].setTexture(card_sheet);//smaller_card_sheet
					playing_field_sprites[i].setTextureRect(sf::IntRect((game.get_played_cards()->at(i).get_value() - 1) * 90, game.convert_suit(game.get_played_cards()->at(i).get_suit()) * 126, 90, 126));//45,62
					playing_field_sprites[i].setPosition(playing_field_offset + 30 * i, 250);//45
					window.draw(playing_field_sprites[i]);
				}
				//std::cout << "\n";

				//display turn text
				if (game.get_turn() == 0)
					turn_text.setString("Your turn");
				else if (game.get_turn() == 1)
					turn_text.setString("Computer 1 turn");
				else if (game.get_turn() == 2)
					turn_text.setString("Computer 2 turn");
				else if (game.get_turn() == 3)
					turn_text.setString("Computer 3 turn");
				window.draw(turn_text);


				//skip the player if he has already won 
				if (game.get_current_player()->already_won())
				{
					
					if (!game.get_current_player()->is_passed())//if the player is not passed, then pass
					{
						passed_players++;
						game.get_player(game.get_turn())->set_passed(true);
					}
					
					std::cout << "Player " << game.get_turn() << " has already won\n";
					game.increment_turn();
					break;
				}
				//skip the player if he already passed 
				if (game.get_current_player()->is_passed())
				{
					std::cout << "Player " << game.get_turn() << " has already passed this round\n";
					game.increment_turn();
					break;
				}

				if (game.get_player(game.get_turn())->is_ai()) //logic for ai
				{
					//TODO ai stuff
					while (window.pollEvent(event))
					{
						switch (event.type)
						{
							// window closed
						case sf::Event::Closed:
							window.close();
							break;

						case sf::Event::MouseButtonPressed:
							if (event.mouseButton.button == sf::Mouse::Left)
							{
								std::cout << "\nPlayer " << game.get_turn() << "'s turn\n";
								std::cout << "CONTINUE_ROUND\n";
								game.print_playing_field();
								game.get_current_player()->print_hand();

								if (game.ai_select_and_play_cards() == -1)
								{
									std::cout << "Player " << game.get_turn() << " passed\n";
									passed_players++;
									game.get_current_player()->set_passed(true);
									std::cout << passed_players << " player(s) have passed\n";
									//pass if cant play anything
								}
								//if no cards left, mark player as won
								if (game.get_current_player()->get_hand_size() == 0)
								{
									std::cout << "Player " << game.get_turn() << " won!";
									game.add_winner();
									won_players++;
								}
								game.increment_turn();
								playing_state = CONTINUE_ROUND;
							}
							break;
						default:
							break;
						}
					}


					/*std::cout << "\nPlayer " << game.get_turn() << "'s turn\n";
					std::cout << "CONTINUE_ROUND\n";
					game.print_playing_field();
					game.get_current_player()->print_hand();

					int pause;
					if (game.ai_select_and_play_cards() == -1)
					{
						std::cout << "Player " << game.get_turn() << " passed\n";
						passed_players++;
						game.get_current_player()->set_passed(true);
						std::cout << passed_players << " player(s) have passed\n";
						//pass if cant play anything
					}
					//if no cards left, mark player as won
					if (game.get_current_player()->get_hand_size() == 0)
					{
						std::cout << "Player " << game.get_turn() << " won!";
						game.add_winner();
						won_players++;
					}
					game.increment_turn();
					playing_state = CONTINUE_ROUND;
					if (passed_players + won_players >= 3)
					{
						playing_state = END_ROUND;
					}
					if (won_players == 4)
					{
						playing_state = END_PLAY;
					}					
					std::cout << "\nPause\n";
					std::cin >> pause;*/
				}
				else //logic for human player
				{
					//TODO await player input

					player_hand_offset = 175 + (13 - game.get_player(0)->get_hand_size()) * 15;

					while (window.pollEvent(event))
					{
						switch (event.type)
						{
							// window closed
						case sf::Event::Closed:
							window.close();
							break;

						case sf::Event::MouseButtonPressed:
							if (event.mouseButton.button == sf::Mouse::Left)
							{
								for (int i = 0; i < game.get_current_player()->get_hand_size(); i++)
								{
									if (i == game.get_current_player()->get_hand_size() - 1)
										player_card_buttons[i].set_trigger_box(player_hand_offset + 30 * i, 450 - 10 * game.get_player(0)->get_hand()->at(i).is_selected(), 90, 126);
									else
										player_card_buttons[i].set_trigger_box(player_hand_offset + 30 * i, 450 - 10 * game.get_player(0)->get_hand()->at(i).is_selected(), 30, 126);
									if (player_card_buttons[i].handle_event(&event))
									{
										//std::cout << "index " << i << " selected\n";
										game.get_current_player()->handle_card_click(i);
									}

								}
							}
							break;

							// key pressed
						case sf::Event::KeyPressed:
							switch (event.key.code)
							{
							case sf::Keyboard::Escape:
								std::cout << "Player " << game.get_turn() << " passed\n";
								passed_players++;
								game.get_current_player()->set_passed(true);
								game.increment_turn();
								std::cout << passed_players << " player(s) have passed\n";
								break;
							case sf::Keyboard::Space:
								int combo_type;
								combo_type = game.play_cards(); //check validity and play cards if valid

								if (combo_type == -1)
								{
									std::cout << "Invalid play\n";
									continue;
								}
								else
								{
									std::cout << "Combination " << combo_type << " was played\n";
								}

								//set card type
								game.set_card_type((Combination)combo_type);

								//if no cards left, mark player as won
								if (game.get_current_player()->get_hand_size() == 0)
								{
									std::cout << "Player " << game.get_turn() << " won!";
									game.add_winner();
									won_players++;
								}

								//increment turn
								game.increment_turn();
								playing_state = CONTINUE_ROUND;
								break;
							default:
								break;
							}
							break;

							// we don't process other types of events
						default:
							break;
						}
					}

					/*int awaiting_input = 1;
					while (awaiting_input)
					{
						int action;

						std::cout << "\nPlayer " << game.get_turn() << "'s turn\n";
						game.print_playing_field();
						game.get_current_player()->print_hand();
						game.get_current_player()->print_selected();

						std::cout << "Enter 0 to select/deselect a card, 1 to pass, 2 to play cards:";
						std::cin >> action;

						if (action == 0 )//player clicks on card
						{
							int selected_index;
							std::cout << "Enter index of card to select:";
							std::cin >> selected_index;

							//add to selected
							game.get_current_player()->handle_card_click(selected_index);
						}
						else if (action == 1)//player_passes
						{
							std::cout << "Player " << game.get_turn() << " passed\n";
							passed_players++;
							game.get_current_player()->set_passed(true);
							awaiting_input = 0;
							game.increment_turn();
							std::cout << passed_players << " player(s) have passed\n";
							break;
						}

						else if (action == 2)//player plays cards
						{
							int combo_type;
							combo_type = game.play_cards(); //check validity and play cards if valid
							if (combo_type == -1)
							{
								std::cout << "Invalid play\n";
								continue;
							}
							else
							{
								std::cout << "Combination " << combo_type << " was played\n";
							}

							//if no cards left, mark player as won
							if (game.get_current_player()->get_hand_size() == 0)
							{
								std::cout << "Player " << game.get_turn() << " won!";
								game.add_winner();
								won_players++;
							}

							//set card type
							game.set_card_type((Combination)combo_type);
							//increment turn
							game.increment_turn();

							awaiting_input = 0;
							

							break;
						}

					}
					playing_state = CONTINUE_ROUND;*/

				}

				if (passed_players >= 3)
				{
					playing_state = END_ROUND;
				}
				if (won_players == 4)
				{
					playing_state = END_PLAY;
				}
				window.display();
				break;
			case END_ROUND:
				std::cout << "END_ROUND\n";
				
				//increment the turn to the only unpassed player
				while (game.get_current_player()->is_passed() ) //TODO address the case where player just emptied hand and everyone passed
				{

					game.increment_turn();
				}
				//increment the turn to a player that has not won yet
				while(game.get_current_player()->already_won())
				{
					game.increment_turn();
				}
				//set all players to unpassed
				for (int i = 0; i < 4; i++)
				{
					game.get_player(i)->set_passed(false);
				}
				passed_players = 0;

				game.clear_playing_field();
				std::cout << "Board control goes to player " << game.get_turn() << "\n";
				playing_state = START_ROUND;
				break;
			case END_PLAY:
				std::cout << "END_PLAY\n";
				passed_players = 0;
				won_players = 0;
				//set all players to unpassed and unfinished
				for (int i = 0; i < 4; i++)
				{
					game.get_player(i)->set_passed(false);
					game.get_player(i)->set_won(false);
				}

				playing_state = PREPARE_GAME;
				game_state = END_SCREEN;

				break;
			}
			break;
		case END_SCREEN:
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
					// window closed
				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::MouseButtonPressed:
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						if (play_again_button.handle_event(&event))
						{
							game.reset_game();
							game_state = START_SCREEN;
						}
						else if (exit_button.handle_event(&event))
						{
							game_state = EXIT;
						}
					}
				}
			}
			
			std::cout << "winners: ";
			for (int i = 0; i < 4; i++)
			{
				std::cout << game.get_finisher(i) << " ";
			}
			std::cout << "\n";


			//calculate message
			for (int i = 0; i < 4; i++)
			{
				if (game.get_finisher(i) == 0)
				{
					if (i == 0)
						place_text.setString("You finished 1st!");
					else if (i == 1)
						place_text.setString("You finished 2nd!");
					else if (i == 2)
						place_text.setString("You finished 3rd!");
					else if (i == 3)
						place_text.setString("You finished 4th!");
					break;
				}
			}

			//draw stuff
			window.draw(place_text);
			window.draw(play_again_rect);
			window.draw(exit_rect);
			window.draw(play_again_message);
			window.draw(exit_message);
			window.draw(chara);
			window.display();



			/*std::cout << "Enter 0 to play again, 1 to exit";
			std::cin >> action;
			if (action == 0)
			{
				game_state = START_SCREEN;
			}
			else
			{
				game.reset_game();
				game_state = END_SCREEN;
			}*/
			//TODO display end game screen with "play again" and "quit" options (and score?)
			// "play again" moves to START_SCREEN
			// "quit" moves to EXIT
			break;
		case EXIT:
			game.close_game();
			window.close();

			break;
		}

		//display the window
		//window.display();
	}

	return 0;
}

