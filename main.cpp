//------------------------------------------------------------------
//				Libraries & Standards
//------------------------------------------------------------------
#include "includes/ai_header.h"		// AI Stuff
#include "includes/board_header.h"	// Board Stuff
#include "includes/util_header.h"
#include <iostream>			// Input / Output functions
#include <unistd.h>			// usleep() delay functions

using namespace std;		// std::string
//------------------------------------------------------------------
//				The Humble Main()
//------------------------------------------------------------------
int main()
{
	// Make it look pretty
	print_title();

	// Board Stuff
	Board board[4][4];
	reset_board(board);
	make_board(board);
	set_board_values(board);	// W, P, G
	set_board_status(board);	// s, b, g

	// AI Stuff
	AI ai;
	ai.reset_agent();

	// Game loop
	bool game_over = false;
	cout << "\n-------------- Starting the Game --------------\n" << endl;
	do
	{
		ai.place_agent(board);
		ai.read_environment(board);
		ai.evaluate_map_safety();
		print_board(board);
		if (ai.is_safe())
		{
			ai.visit();
			ai.print_agent_senses();
			if (ai.search_gold())
			{
				// Grab some board.gold and gtfo
				ai.grab_gold();
				cout << "Agent wins!\n";
				game_over = true;
			}								
			else if (ai.get_explorables())
			{
				// Start path finding function
				ai.find_path();
			}
			else
			{
				// Say the agent went home and gtfo?
				cout << "Agent went home without the gold because there's no safe spaces left.\n";
				game_over = true;
			}			
		}
		// ELSE with wumpus / in pit:
		else
		{
			// announce agent's situation
			cout << "Agent loses!\n";
			// set game_over
			game_over = true;
			// gtfo lol?
		}
		// Time delay between moves. User will feeling like they're seeing the AI "think"
		usleep(1000000);

	}while(!game_over);	// while the game isn't over

	cout << "\n----------------- Game Over -----------------\n\n";
	
	//gtfo lol
	cout << "Ending program...";
	return 0;
}