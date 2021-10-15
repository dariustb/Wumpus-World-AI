//-----------------------------
// Include Guards
//-----------------------------
#ifndef BOARD_FUNCTION_HEADER
#define BOARD_FUNCTION_HEADER

//-----------------------------
// Include Libraries
//-----------------------------
#include <iostream>
using namespace std;

//-----------------------------
// Class Definition
//-----------------------------
struct Board	// Represents each square on a board
{
	int safe   = 0;	// 1 = ok, -1 = trap, 0 = unsure
	int wumpus = 0;	// 1 = has wumpus, -1 = no wumpus, 0 = unsure
	int pit    = 0;	// 1 = has pit, -1 = no pit, 0 = unsure
	
	// No need for a gold variable because:
	// The gold always is where the glitter is.
	// The game is over once it's found and knowing it's not found makes no difference to the AI so it'll just go unused.

	bool visited = false;	// visited / unvisited
	
	int stench = 0;	// has / doesn't have stench / unsure
	int breeze = 0;	// has / doesn't have breeze / unsure
	int glitter= 0;	// has / doesn't have glitter / unsure

	string value  = " ";	// holds W, P, G, A
	string status = "";		// holds s, b, g,
	string xy     = "";		// 11 form instead of a1 (11 == 1,1)
};

//-----------------------------
// Close Header Guard
//-----------------------------
#endif