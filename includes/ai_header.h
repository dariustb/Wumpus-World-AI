//-----------------------------
// Include Guards
//-----------------------------
#ifndef AI_FUNCTION_HEADER
#define AI_FUNCTION_HEADER

//-----------------------------
// Include Libraries
//-----------------------------
#include <iostream>
#include "board_header.h"
using namespace std;

//-----------------------------
// Global Variables
//-----------------------------
const int COMPASS[4][2]= { {0,1}, {1,0}, {0,-1}, {-1,0} }; //cardinal directions??

//-----------------------------
// Class Definition
//-----------------------------
struct Explorable_square
{
	int x, y;
	int distance;
};

// send in the bots!!
class AI
{
	public:
		// INITIALIZATION FUNCTION
		void reset_agent();	// Initializes agent location and map
			
		// BOARD MANIPULATION/ EXTRACTION FUNCTION
		void place_agent(Board[4][4]);		// Put A into the board where ai.xy (current location) is 
		void read_environment(Board[4][4]);	// Gets all info of the current square
		void print_duals(Board[4][4]);		// Prints the board next to its map
		bool is_safe();		// Returns location safety on map
		void visit();		// Marks current space on map as visited

		// EVALUATION / SENSORY FUNCTIONS
		void print_agent_status();	// Prints "agent falls into a pit!", etc.
		void print_agent_senses();	// Prints "agent smells a stench...", etc.
		void evaluate_map_safety();	// The actual thinking part - determines which square is safe and unsafe.
		void find_path();			// On an iterative basis, finds path from point A to point B without falling into a trap.
		void teleport();			// Sets agent to next explorable location. I used it to avoid making a pathfinding algorithm. BUUUUT I made find_path() so this is unused and just to feel proud about
		bool search_gold();			// Looks for gold in agent's current location
		bool get_explorables();		// Find squares on map that are safe & unvisited. Returns true if there's at least 1 space. Those are the squares we need to get to expand the knowledge of the map and hopefully find gold. Game is over if there are no more explorable spaces and the gold isn't found

		// MOTOR-BASED FUNCTIONS
		void move_up();		// Moves the agent up, then announces it
		void move_down();	// See above
		void move_left();	// See above
		void move_right();	// See above
		void grab_gold();	// Grab function to collect gold.

	private:
		const string letter = "A";		// Agent letter is A
		int x, y;						// X-Y coordinates in 0-3 (instead of 1-4)
		Board map[4][4];				// Map that the agent will use to get around
		bool has_gold = false;			// To give the grab function something to do
		Explorable_square ex_list[13];	// List of explorable squares on map
		int ex_list_size;				// Size of list
};

//-----------------------------
//	AI Class functions
//-----------------------------
void AI::reset_agent()
{
	// Set the initial position
	x = 0;
	y = 0;

	// Set the map
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			map[i][j].xy = char('1' + i) + char('1' + j);
	}
}
void AI::place_agent(Board board[4][4])
{
	// Delete any other agent placement first
	for (int i = 0; i < 4*4; i++)
	{
		if (board[i/4][i%4].value == letter)
		{
			board[i/4][i%4].value = " ";
			break;
		}
	}
	// Places on game board with Agent's xy coordinates
	board[x][y].value = letter;
}
void AI::print_duals(Board board[4][4])
{
	string buffer = "  ";
	
	for (int h = 0; h < 2; h++)
	{
		cout << buffer << "   ";
		for (int i = 0; i < 4; i++)
			cout << " _______";
		cout << " ";
	}
	cout << endl;

	for (int i = 0; i < 4; i++)
	{
		for (int h = 0; h < 2; h++)
		{
			cout << buffer << "   ";
			for (int j = 0; j < 4; j++)
				cout << "|       ";
			cout << "|";
		}
		cout << endl;
		
		cout << buffer << char('1' + (3-i)) << "  ";
		for (int j = 0; j < 4; j++)
			cout << "|   " << board[j][3-i].value << "   ";
		cout << "|";
		
		cout << buffer << char('1' + (3-i)) << "  ";
		for (int j = 0; j < 4; j++)
			cout << "|   " << map[j][3-i].safe << "   ";
		cout << "|";
		
		cout << endl;

		for (int h = 0; h < 2; h++)
		{
			cout << buffer << "   ";
			for (int j = 0; j < 4; j++)
				cout << "|_______";
			cout << "|";
		}
		cout << endl;
	}

	cout << endl;
	for (int h = 0; h < 2; h++)
	{
		cout << buffer << "   ";
		for (int i = 0; i < 4; i++)
				cout << "    " << char('1' + i) << "   ";
	}
	cout << endl << endl;
}
void AI::print_agent_senses()
{
	// Just prints what the agent senses on its own map
	if (map[x][y].stench == 1)
		cout << "Agent smells a stench...\n";
	if (map[x][y].breeze == 1)
		cout << "Agent feels a breeze....\n";
	if (map[x][y].stench == -1 && map[x][y].breeze == -1)
		cout << "The coast looks clear...\n";
	if (map[x][y].glitter == 1)
		cout << "Agent sees a glitter...\n";
}
void AI::read_environment(Board board[4][4])
{
	// Reads only the necessary information for the agent to continue
	map[x][y].wumpus = board[x][y].wumpus;
	map[x][y].pit    = board[x][y].pit;
	
	map[x][y].stench = board[x][y].stench;
	map[x][y].breeze = board[x][y].breeze;

	map[x][y].glitter= board[x][y].glitter;
}

void AI::move_up()
{
	if (y < 3)
	{
		y += 1;
		cout << "Agent moved up\n";
	}
	else
		cout << "AI move_up() failed.\n";
}
void AI::move_down()
{
	if (y > 0)
	{	
		y -= 1;
		cout << "Agent moved down\n";
	}
	else
		cout << "AI move_down() failed.\n";
}
void AI::move_left()
{
	if (x > 0)
	{
		x -= 1;
		cout << "Agent moved left\n";
	}
	else
		cout << "AI move_left() failed.\n";
}
void AI::move_right()
{
	if (x < 3)
	{
		x += 1;
		cout << "Agent moved right\n";
	}
	else
		cout << "AI move_right() failed.\n";
}


void AI::grab_gold()
{
	// Just says that the agent grabbed the gold. Shouldn't be called if the gold isn't there, but that's specified in main()
	if(map[x][y].glitter == 1)
	{
		has_gold = true;
		cout << "Agent has picked up the gold.\n";
		map[x][y].glitter = 0;	// We took the gold so it's not here anymore.
	}
	// We should never see this.
	else
		cout << "AI grab_gold() failed.\n";
}
bool AI::is_safe()
{
	// Just pulls the safety derived in map.
	return (map[x][y].safe);
}
void AI::visit()
{
	// Visits the current square / set square.visited to true
	map[x][y].visited = true;
}
bool AI::search_gold()
{
	// Checks for the glitter in the square
	bool is_gold = ( map[x][y].glitter == 1 );
	if ( is_gold )
		cout << "Agent found gold!\n";
	return is_gold;
}
void AI::evaluate_map_safety()
{
	// Evaluation 1: if there's no breeze/stench here, there's no pit/wump adjacent
	for (int i = 0; i < 4*4; i++)
	{
		if (map[i/4][i%4].breeze == -1)
		{
			for (int j = 0; j < 4; j++)
			{
				if ( (i/4) + COMPASS[j][0] >= 0 && (i/4) + COMPASS[j][0] < 4 && (i%4) + COMPASS[j][1] >= 0 && (i%4) + COMPASS[j][1] < 4 )
					map[(i/4) + COMPASS[j][0]][(i%4) + COMPASS[j][1]].pit = -1;
			}
		}
		if (map[i/4][i%4].stench == -1)
		{
			for (int j = 0; j < 4; j++)
			{
				if ( (i/4) + COMPASS[j][0] >= 0 && (i/4) + COMPASS[j][0] < 4 && (i%4) + COMPASS[j][1] >= 0 && (i%4) + COMPASS[j][1] < 4 )
					map[(i/4) + COMPASS[j][0]][(i%4) + COMPASS[j][1]].wumpus = -1;
			}
		}
	}
	// Evaluation 2: if all but one adjacent square is safe and the current square has a stench/breeze, then the remainder adjacent square *must* be the trap


	// Evaluation 2: if square has no pit nor wumpus, it's safe
	for(int i = 0; i < 4*4; i++)
	{
		if(map[i/4][i%4].wumpus == -1 && map[i/4][i%4].pit == -1)
			map[i/4][i%4].safe = 1;
		if(map[i/4][i%4].wumpus == 1 || map[i/4][i%4].pit == 1)
			map[i/4][i%4].safe = -1;
		//cout << map[i/4][i%4].wumpus << ' ' << map[i/4][i%4].pit << " | " << map[i/4][i%4].stench << ' ' << map[i/4][i%4].breeze << endl;
	}
}
bool AI::get_explorables()
{
	// Initialize explorable list after every turn (unnecessary, I know)
	for (int i = 0; i < 13; i++)
	{
		ex_list[i].x = -1;
		ex_list[i].y = -1;
		ex_list[i].distance = -1;
	}

	// Add the unexplored blocks to list
	int counter = 0;
	for (int ex = 0; ex < 4; ex++)
	{
		for (int ey = 0; ey < 4; ey++)
		{
			if ( map[ex][ey].safe && !map[ex][ey].visited )
			{
				ex_list[counter].x = ex;
				ex_list[counter].y = ey;
				ex_list[counter].distance = (ex - x) + (ey - y);
				counter ++;
			}
		}
	}

	// Sort the list by distance - Sort function is modded bubble sort from GeeksforGeeks
	int list_size = counter;
	counter = 0;
	Explorable_square temp;
 
    for (int i = 0; i < list_size - 1; i++)      
    {  
		// Last i elements are already in place  
		for (int j = 0; j < list_size - i - 1; j++) 
		{
			if (ex_list[j].distance > ex_list[j+1].distance)
			{
				temp = ex_list[j];  
				ex_list[j] = ex_list[j+1];  
				ex_list[j+1] = temp;
			}
		}
	}
	return (list_size > 0);
}
void AI::teleport()
{
	// I'm leaving this here so you'll know I came a long way!
	// Just sets the agent's position to the closest safe, unvisited square
	x = ex_list[0].x;
	y = ex_list[0].y;
}
void AI::find_path()
{
	int goal_x = ex_list[0].x, goal_y = ex_list[0].y;

	// First match the x values then match the y values.
	if( x < goal_x && map[x+1][y].safe )
		move_right();
	else if( x > goal_x && map[x-1][y].safe )
		move_left();
	else if( y < goal_y && map[x][y+1].safe )
		move_up();
	else if( y > goal_y && map[x][y-1].safe )
		move_down();
	else if( x != goal_x || y != goal_y )
	{
		if( ex_list_size > 1 )
			goal_x = ex_list[1].x, goal_y = ex_list[1].y;
		find_path();
	}
}

//-----------------------------
// Close Header Guard
//-----------------------------
#endif