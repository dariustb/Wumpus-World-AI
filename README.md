![Wumpus World Title Card](https://i.ibb.co/8rDDm12/ww-shot.png)
# Wumpus World &mdash; AI Game Console App
> A simple environment-reading AI game app.

## Table of contents
* [General Info](#general-info)
* [Screenshots](#screenshots)
* [Technologies](#technologies)
* [Setup](#setup)
* [Features](#features)
* [Status](#status)
* [Inspiration](#inspiration)
* [Contact](#contact)

## General Info
### Rules of the Game
The game is relatively simple.
- The agent is in a 4x4-block cave.
- In the cave are a man-eating wumpus, 3 pit traps, and a gold bar.
- Squares adjacent to the wumpus are smelly, squares adjacent to pits are breezy, and the square with the gold has a glitter.
- The agent doesn't know where *any* of these items are.
- It'll sense a smell, breeze, or glitter when it moves to the block that has it.
- The goal is to find the gold without getting eaten by the wumpus or falling into a pit.

### Running the Code
When you run the code, the app will prompt you to enter locations for a man-eating wumpus, 3 pit traps, and the winning gold. Use X,Y notation (no space between the comma) when you enter the values. <br>
👇 Try the examples below or create your own: 👇

```cpp
Wumpus: 1,4
Pit 1:  2,4
Pit 2:  3,4
Pit 3:  4,4

Gold:   4,3
```
```cpp
Wumpus: 1,3
Pit 1:  3,1
Pit 2:  3,3
Pit 3:  4,4

Gold:   2,3
```
```cpp
Wumpus: 3,1
Pit 1:  1,4
Pit 2:  4,2
Pit 3:  4,3

Gold:   2,4
```

All spaces and elements on the map will be visible to the user and will look like so:
![Starting Board](https://i.ibb.co/jbcRJ7f/ww-startboard.png)

Each letter represents an element on the board
- A = agent AI	
- G = gold
- W = wumpus
- P = pit

The AI agent will not know about the locations of the gold or the obstacles and will have to "sense" where they are to determine those locations

At this point the AI will start and move around to sense its surroundings. Each sense found will be printed below the board.

After collecting all new information, the AI will make the best move with what it knows
![AI in motion](https://i.ibb.co/qJqtwsy/ww-gameplay.gif)

The game will end in 3 possible ways:
- Agent finds the gold and wins
- Agent falls in pit/gets captured by wumpus and loses
- Agent leaves due to no safe spaces being left to choose and loses

The status will be printed and the game will be over.

## Screenshots
![Wumpus World Title Card](https://i.ibb.co/8rDDm12/ww-shot.png)

## Technologies
Project is created with:
* C++ clang - version: 7.5.0 or higher
* G++ - version: 7.5.0 or higher

Project is hosted on [Repl.it Online IDE](https://repl.it)

## Setup
To run this code on Repl.it's online IDE, go to https://repl.it/@dariustb/Wumpus-World-AI, then click the green "Run" button at the top of the page (alternately, you can press ctrl + enter on your keyboard).

## Features
* AI agent to play the game itself
* Time delay for a more interactive feel

## Status
Project is: *finished*, after receiving the grade for this assignment.

## Inspiration
Project inspired by the early Atari game, [*Hunt the Wumpus*](https://www.atariarchives.org/bcc1/showpage.php?page=247). Additionally, this was assigned in a programming course to showcase ability in creating simple environment assessing artificial intelligence.

## Contact
W u m p u s &nbsp; W o r l d &nbsp; A I <br>
by [Darius Brown](https://dariusbrown.dev)<br>
Created: October 29, 2019 - November 11, 2019 <br>
Questions or comments? Feel free to contact me [via email](mailto:dariustb@tech-center.com)!