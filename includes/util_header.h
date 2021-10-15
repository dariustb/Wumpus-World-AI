//-----------------------------
// Include Guards
//-----------------------------
#ifndef UTIL_FUNCTION_HEADER
#define UTIL_FUNCTION_HEADER

//-----------------------------
// Include Libraries
//-----------------------------
#include "board_header.h"
#include <iostream>
using namespace std;

//-----------------------------
// Global Variables
//-----------------------------
const int MAX_WUMPUSES = 1;	// To make deeper inferences and for setting board
const int MAX_PITS 	   = 3;	// Same
const int MAX_GOLD	   = 1; // Same

//-----------------------------
// Function Prototypes
//-----------------------------
void show_space(Board[4][4]);
void print_title();					// ASCII art "Wumpus World" prints
void print_board(Board[4][4]);		// Shows the board from the board[][] array

void reset_board(Board[4][4]);		// Clears values of the board
void set_board_values(Board[4][4]);	// Sets board.value correlating to s,b,g
void set_board_status(Board[4][4]);	// Sets board.status correlating to W,P,G

void make_board(Board[4][4]);		// Gets user input to initialize board
bool check_trap_location(Board[4][4], string, int); // Input validation for above

//-----------------------------
// Function Definition
//-----------------------------
void print_title()
{
	// Title from ascii art generator app by Patrick Gillespie: 
	// http://patorjk.com/software/taag/#p=display&f=Standard&t=Wumpus%0AWorld
	string buffer = " ";

	cout << buffer <<
	"             Darius Brown presents:         " << endl << buffer << 
	" __        __                               " << endl << buffer <<
	" \\ \\      / /   _ _ __ ___  _ __  _   _ ___ " << endl << buffer <<
	"  \\ \\ /\\ / / | | | '_ ` _ \\| '_ \\| | | / __|" << endl << buffer <<
	"   \\ V  V /| |_| | | | | | | |_) | |_| \\__ \\" << endl << buffer <<
	"    \\_/\\_/  \\__,_|_| |_| |_| .__/ \\__,_|___/" << endl << buffer <<
	"       __        __        |_|    _         " << endl << buffer <<
	"       \\ \\      / /__  _ __| | __| |        " << endl << buffer <<
	"        \\ \\ /\\ / / _ \\| '__| |/ _` |        " << endl << buffer <<
	"         \\ V  V / (_) | |  | | (_| |        " << endl << buffer <<
	"          \\_/\\_/ \\___/|_|  |_|\\__,_|        " << endl << endl;
}
void print_board(Board board[4][4])
{
	string buffer = "    ";

	cout << buffer << "   ";
	for (int i = 0; i < 4; i++)
		cout << " _______";
	cout << endl;
	
	for (int i = 0; i < 4; i++)
	{
		cout << buffer << "   ";
		for (int j = 0; j < 4; j++)
		{
			cout << "|       ";
			/*		// This will show the s,b,g on the board, AI can still sense them without this, though
			cout << "|";
			for (int k = 0; k < (7 - board[i][3-j].status.length())/2; k++)
				cout << " ";
			cout << board[i][3-j].status;
			for (int k = 0; k < 7-(((7 - board[i][3-j].status.length())/2) + board[i][3-j].status.length()); k++)
				cout << " ";
			*/
		}
		cout << "|" << endl;
		
		cout << buffer << char('1' + (3-i)) << "  ";
		for (int j = 0; j < 4; j++)
			cout << "|   " << board[j][3-i].value << "   ";
		cout << "|" << endl;

		cout << buffer << "   ";
		for (int j = 0; j < 4; j++)
			cout << "|_______";
		cout << "|" << endl;
	}

	cout << endl << buffer << "   ";
	for (int i = 0; i < 4; i++)
			cout << "    " << char('1' + i) << "   ";
	cout << endl << endl;
}
void reset_board(Board board[4][4])
{
	int height = 4, width = 4; //idk if I'll extend the board to m x n later
	
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			board[i][j].safe   = 0;
			board[i][j].wumpus = 0;
			board[i][j].pit    = 0;

			board[i][j].visited= false;

			board[i][j].stench = 0;
			board[i][j].breeze = 0;
			board[i][j].glitter= 0;

			board[i][j].value  = " ";
			board[i][j].status = "";
			board[i][j].xy     = char('1' + i) + char('1' + j);
		}
	}
}
void set_board_values(Board board[4][4])
{
	for (int i = 0; i < 4*4; i++)
	{
		if (board[i/4][i%4].wumpus == 1)
			board[i/4][i%4].value = "W";
		else if (board[i/4][i%4].pit == 1)
			board[i/4][i%4].value = "P";
		else if (board[i/4][i%4].glitter == 1)
			board[i/4][i%4].value = "G";
		else
			board[i/4][i%4].value = " ";
	}
}
void set_board_status(Board board[4][4])
{
	// Set the breeze and stench values
	for (int i = 0; i < 4*4; i++)
	{
		if (board[i/4][i%4].wumpus == 1)
		{
			for (int j = 0; j < 4; j++)
			{
				if ( (i/4) + COMPASS[j][0] >= 0 && (i/4) + COMPASS[j][0] < 4 && (i%4) + COMPASS[j][1] >= 0 && (i%4) + COMPASS[j][1] < 4 )
					board[(i/4) + COMPASS[j][0]][(i%4) + COMPASS[j][1]].stench = 1;
			}
		}
		else if (board[i/4][i%4].pit == 1)
		{
			for (int j = 0; j < 4; j++)
			{
				if ( (i/4) + COMPASS[j][0] >= 0 && (i/4) + COMPASS[j][0] < 4 && (i%4) + COMPASS[j][1] >= 0 && (i%4) + COMPASS[j][1] < 4 )
					board[(i/4) + COMPASS[j][0]][(i%4) + COMPASS[j][1]].breeze = 1;
			}
		}
	}

	// Set the non-breeze & stench values
	for (int i = 0; i < 4*4; i++)
	{
		if ( board[i/4][i%4].stench != 1 )
			board[i/4][i%4].stench = -1;
		if ( board[i/4][i%4].breeze != 1 )
			board[i/4][i%4].breeze = -1;
	}

	// Set values for stench and breeze and glitter
	for (int i = 0; i < 4*4; i++)
	{
		if (board[i/4][i%4].wumpus != 1 && board[i/4][i%4].pit != 1)
		{
			if (board[i/4][i%4].stench == 1)
				board[i/4][i%4].status += 's';
			if (board[i/4][i%4].breeze == 1)
				board[i/4][i%4].status += 'b';
			if (board[i/4][i%4].glitter == 1)
				board[i/4][i%4].status += 'g';
		}
		else
		{
			//cout << "Found summ\n";
		}
	}
}
void make_board(Board board[4][4])
{
	string user_input;
	bool valid_input = false;

	cout << "----- Make the Board ( Use X,Y notation ) -----\n\n";
	cout << "Enter location for:\n";

	for (int i = 0; i < MAX_WUMPUSES; i++)
	{
		do
		{
			cout << "Wumpus: ";
			getline(cin, user_input);
		} while ( !check_trap_location(board, user_input, 1) );
	}

	for (int i = 0; i < MAX_PITS; i++)
	{
		do
		{
			cout << "Pit " << i + 1 << ":  ";
			getline(cin, user_input); 
		} while ( !check_trap_location(board, user_input, 2) );
	}

	for (int i = 0; i < MAX_GOLD; i++)
	{
		do
		{
			cout << "Gold:   ";
			getline(cin, user_input); 
		} while ( !check_trap_location(board, user_input, 3) );
	}
	
	// Set the rest of the board in accordance
	for (int i = 0; i < 4*4; i++)
	{
		if ( board[i/4][i%4].wumpus != 1 )
			board[i/4][i%4].wumpus = -1;
		if ( board[i/4][i%4].pit != 1 )
			board[i/4][i%4].pit = -1;
		if ( board[i/4][i%4].glitter != 1)
			board[i/4][i%4].glitter = -1;
	}
}
bool check_trap_location(Board board[4][4], string xy, int trap)
{
	int x = xy[0] - '1', y = xy[2] - '1';
	bool is_valid = false;
	
	// Check valid "x,y" notation
	if(xy.length() != 3 || xy[1] != ',')
		cout << "Error: Invalid input (Use x,y notation)\n";
	// Check bounds
	else if (x < 0 || y < 0 || x > 3 || y > 3)	
		cout << "Error: Input out of bounds\n";
	// Check for agent init position
	else if (xy == "1,1") 
		cout << "Error: Cannot use agent start position\n";
	else if ((board[x][y].wumpus == 1) || (board[x][y].pit == 1)) // Check available space
		cout << "Error: position already taken\n";
	// Set it and get outta here
	else 
	{
		if(trap == 1)			// wumpus
			board[x][y].wumpus = 1;
		else if (trap == 2)		// pit
			board[x][y].pit = 1;
		else if (trap == 3)		// gold
			board[x][y].glitter = 1;
		is_valid = true;
	}

	// Return the input's validity
	return is_valid;
}

//-----------------------------
// Close Header Guard
//-----------------------------
#endif