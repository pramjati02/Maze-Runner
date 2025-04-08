//============================================================================
// Name        : maxe2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
using namespace std;
// Fl_Text_Display example. -erco
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Text_Display.H>
#include <Fl_Widget.H>
#include <Fl_Box.H>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <unordered_map>
#include "Maze.h"
#include "Block.h"
#include "Player.h"
#include "timeCallback.h"

int main() {
	cleanMaze("maze.txt", "maze_cleaned.txt"); // Cleaning the maze

    const string filename = "maze_cleaned.txt"; //initialize your file name
    vector<vector<int>> maze = parseMazeFromFile(filename); // parsing maze from clean maze file

    Fl_Window window(700, 700, "Maze"); // Initializing window size

    int cellSize = 30; // Initializing block size

    int playerX; // X-coordinate of starting player position
    int playerY; // y-coordinate of starting player position

    // Iterating through the rows and columns of the maze
    for (std::vector<int>::size_type i = 0; i < maze.size(); i++) {
        for (std::vector<int>::size_type j = 0; j < maze[i].size(); j++) {
            int value = maze[i][j]; // retrieving value in maze
            if (value == 2){ // Player starting position
            	playerX = j;
            	playerY = i*cellSize;
            }
            Block* cell = new Block(j * cellSize, i * cellSize, value); // Initializing block
            window.add(cell); // Adding block to the window
        }
    }

   Player player(playerX,playerY,8); // initializing player figure
   window.add(player); // adding player to the window


   Fl::add_timeout(0.99, timerCallback, static_cast<void*>(&player)); //adding a timeout to player movement
   // using static cast to convert between the same object types

    window.end();
    window.show();

    return Fl::run();
    //return 0;
}

