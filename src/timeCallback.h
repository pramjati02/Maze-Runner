/*
 * timeCallback.h
 *
 *  Created on: 30 Nov 2023
 *      Author: pjati
 */

#ifndef TIMERCALLBACK_H_
#define TIMERCALLBACK_H_

#include <iostream>    // For input and output operations
#include <vector>       // For using the vector container
#include <string>       // For using strings
#include <unordered_map> // For using unordered_map
#include <algorithm>    // For using algorithms like remove
#include <cstdlib>      // For using functions involving pseudo-random numbers (e.g., rand)
#include <ctime>        // For using functions related to time (e.g., time)
#include <FL/Fl.H>      // Assuming you are using the FLTK library for GUI components

using namespace std;


// Function to check if the new orientation is a 180-degree turn from the current orientation
bool is180DegreeTurn(int currentOrientation, const string& newDirection) {
    if (newDirection == "leftOption" && currentOrientation == 1){
        return true;
    } else if (newDirection == "rightOption" && currentOrientation == 3) {
        return true;
    } else if (newDirection == "upOption" && currentOrientation == 2) {
        return true;
    } else if (newDirection == "downOption" && currentOrientation == 0) {
        return true;
    }
    return false;
}

static void timerCallback(void *data){
	// Getting the maze the cleaned maze file and parsing it as a vector
    const string filename = "maze_cleaned.txt";
    vector<vector<int>> maze = parseMazeFromFile(filename);

    Player* player = static_cast<Player*>(data);
    int currentX = player->getX(); // getting player position x-coordinate
    int currentY = player->getY(); // getting player position y-coordinate

    // Calculate options for movement
    // Original options without powerups
    int leftOption = (currentX > 0) ? maze[currentY / 30][(currentX - 30) / 30] : 1;
    int rightOption = (currentX < 600) ? maze[currentY / 30][(currentX + 30) / 30] : 1;
    int upOption = (currentY > 30) ? maze[(currentY - 30) / 30][currentX / 30] : 1;
    int downOption = (currentY < 630) ? maze[(currentY + 30) / 30][currentX / 30] : 1;

    // Movement and direction of player are randomized.
    string stroptions[] = {"leftOption", "rightOption", "upOption", "downOption"};
    string random_options[4] = {};


   // Initializing the option dictionary for one move ahead
    unordered_map<string, vector<int>> optionDictionary;

    optionDictionary["leftOption"] = {leftOption};
    optionDictionary["rightOption"] = {rightOption};
    optionDictionary["upOption"] = {upOption};
    optionDictionary["downOption"] = {downOption};

    // If vision is greater than 1, increase the number of options in the dictionary
    if (player->get_vision() > 1){
    	for (int i = 1; i < player->get_vision()+1; i++){
    		int newXLeft = ((currentX - 30) / 30) - i;
    		int newXRight = ((currentX + 30) / 30) + i;
    		int newYUp = ((currentY - 30) / 30) - i;
    		int newYDown = ((currentY + 30) / 30) + i;
			int leftOptionAlt = (newXLeft > 0) ? maze[currentY / 30][newXLeft] : 1; // New left option
			int rightOptionAlt = (newXRight < 21) ? maze[currentY / 30][newXRight] : 1; // New right option
			int upOptionAlt = (newYUp > 0) ? maze[newYUp][currentX / 30] : 1; // New up option
			int downOptionAlt = (newYDown < 21) ? maze[newYDown][currentX / 30] : 1; // New down option
			// Adding these options to the option dictionary
			optionDictionary["leftOption"].push_back(leftOptionAlt);
			optionDictionary["rightOption"].push_back(rightOptionAlt);
			optionDictionary["upOption"].push_back(upOptionAlt);
			optionDictionary["downOption"].push_back(downOptionAlt);
    		}
    	}

    // Creating a vector for all the options that are "valid" to move into
    vector<string> validOptions;
    // Iterating through the option dictionary to determine which moves are valid
    for (auto it = optionDictionary.begin(); it != optionDictionary.end(); ++it) {

        if ( is180DegreeTurn(player->get_orientation(), it->first) == true ){
        	continue; // If combination between orientation of player and string of the option is "true", skip it.
        }
        else{
            // Check if the first element in the vector is not 1
            if (!it->second.empty() && it->second[0] != 1) {
                validOptions.push_back(it->first);
            }
        }
    }

    // Initialize integer variables for potential moves on x and y coordinates
    int potentialnewX;
    int potentialnewY;
    //unordered_map< string, vector< pair<int, int> >> previous_movesCheck;

    // Initilializing a vector space to check previous moves against current moves
    vector<string> previousMoveCheck;

    // If move history is not empty, continue with the conditional
    if (!player->getMoveHistory().empty()){
    	// As there is only one option that is valid, continue the program and skip the conditional
    	if (validOptions.size() == 1){
    		cout << "Only one option that is valid. Continue" << endl;
    	}
    	else{
    		// Iterating through valid options and coordinates in the move history
            for (const string& option : validOptions) {
                for (const auto& coordinates : player->getMoveHistory()) {
                    // Every option has its own potential move set
                    if (option == "leftOption"){
                    	potentialnewX = currentX - 30;
                    	potentialnewY = currentY;
                    }
                    else if (option == "rightOption"){
                    	potentialnewX = currentX + 30;
                    	potentialnewY = currentY;
                    }
                    else if (option == "upOption"){
                    	potentialnewX = currentX;
                    	potentialnewY = currentY - 30;
                    }
                    else if (option == "downOption"){
                    	potentialnewX = currentX;
                    	potentialnewY = currentY + 30;
                    }

                    // if the potential move set is already in previous moves, add it to the previous move check
                    if (coordinates.first == potentialnewX && coordinates.second == potentialnewY) {
                    	//previous_movesCheck[option].push_back({potentialnewX, potentialnewY});
                    	previousMoveCheck.push_back(option);
                    }
                }
        	}
    	}
    }

    // If the previous move check is not empty, continue with the conditional
    if (!previousMoveCheck.empty()){
    	if (previousMoveCheck.size() == validOptions.size()){
    		cout << "continue" << endl;
    	}
    	// There has to be less options in the previous move check than valid options.
    	// Or else the program will skip this step
    	else if(previousMoveCheck.size() < validOptions.size()){
    		// Iterating through the options in the previous move check
    		for (const string& option_previous : previousMoveCheck) {
    			// remove the previous move check option from the valid options
				validOptions.erase(remove(validOptions.begin(), validOptions.end(), option_previous), validOptions.end());
			}
    		// Display the updated validOptions
			cout << "Updated validOptions: ";
			for (const auto& option : validOptions) {
				cout << option << " ";
			}
			cout << endl;
    	}
    	else{
    		cout << "continue" << endl;
    	}
    }

    // Getting the choices for options that were deemed valid
    cout << "Processing options: ";
    for (const string& option : validOptions) {
		cout << option << " ";
		}
    cout << endl;

    // Initializing random index
    srand(static_cast<unsigned int>(time(0)));
    int randomIndex;

    // Initializing extra steps variables for speed potion/slowpoke potion
    int extraStepRight = 0;
    int extraStepLeft = 0;
    int extraStepDown = 0;
    int extraStepUp = 0;


    // Check if there are valid options
    if (!validOptions.empty()) {
        // Randomly choose an option from the valid ones
        randomIndex = rand() % validOptions.size();
        string random_choice = validOptions[randomIndex];
        cout << "Randomly chosen option: " << random_choice << endl;
        // Set the appropriate orientation based on the chosen direction
        if (random_choice == "leftOption") {
            player->set_orientation(3);
            // If the multiplier is greater than 0, iterate to increase steps according to current position
            if (player->get_multiplier() > 0){
        		for (int i = 0; i < player->get_multiplier()+1; i++){
        			int newX = ((currentX - 30) / 30) - i; // Retrieiving the new x-coordinate
        			int LeftOptionNew = (newX > 0) ? maze[currentY / 30][newX] : 1; // Getting position in maze
        			// if the option is not 1, and iterator is more than 0, add 30 to the extra step
					if (LeftOptionNew != 1 and i > 0){
						extraStepLeft += 30;
					}
					// else, output the length of the extra step and break the iteration
					else if (LeftOptionNew == 1){
						break;
					}
        		}
            }
        } else if (random_choice == "rightOption") {
            player->set_orientation(1);
            if (player->get_multiplier() > 0){
        		for (int i = 0; i < player->get_multiplier()+1; i++){
        			int newX = ((currentX + 30) / 30) + i;
        			int rightOptionNew = (newX < 21) ? maze[currentY / 30][newX] : 1;
					if (rightOptionNew != 1 and i > 0){
						extraStepRight += 30;
					}
					else if (rightOptionNew == 1){
						break;
					}
        		}
            }
        } else if (random_choice == "upOption") {
            player->set_orientation(0);
            if (player->get_multiplier() > 0){
        		for (int i = 0; i < player->get_multiplier()+1; i++){
        			int newY = ((currentY - 30) / 30) - i;
        			int UpOptionNew = (newY > 0) ? maze[newY][currentX / 30] : 1;
        			if (UpOptionNew != 1 and i > 0){
        				extraStepUp += 30;
        			}
        			else if (UpOptionNew == 1){
        				break;
        			}
        		}
            }
        } else if (random_choice == "downOption") {
            player->set_orientation(2);
            if (player->get_multiplier() > 0){
        		for (int i = 0; i < player->get_multiplier()+1; i++){
        			int newY = ((currentY + 30) / 30) + i;
        			int downOptionNew = (newY < 21) ? maze[newY][currentX / 30] : 1;

        			if (downOptionNew != 1 and i > 0){
        				extraStepDown += 30;
        			}
        			else if (downOptionNew == 1){
        				break;
        			}
        		}
            }
        }
    }
    else {
        // No valid options, handle the case (e.g., rotateRight)
        cout << "No valid options, rotating right." << endl;
        player->rotateRight();
    }

    int orientation = player->get_orientation(); // Get the orientation
    cout << "current orientation: " << orientation << endl;

    // Based on the orientation, move the player accordingly
    int newX = currentX, newY = currentY;
    switch (orientation){
        case 0: newY -= (30 + extraStepUp); break; // up
        case 1: newX += (30 + extraStepRight); break; // right
        case 2: newY += (30 + extraStepDown); break; // down
        case 3: newX -= (30 + extraStepLeft); break; // left
    }

    player->updateMoveHistory(newX, newY); //Add these new coordinates to the move history

    // Check if the new coordinates are within bounds
    if (newX > -1 and newX < 630 and newY > 0 and newY < 660){
        int newBlockType = maze[newY / 30][newX / 30];  // Assuming cellSize is 30

        // Perform actions based on the type of the new block
        switch (newBlockType) {
            case 0:  // Move into an open space (block with value 0)
                // Print the value at the new coordinates in the maze
                cout << "Value at (" << newX / 30 << ", " << newY / 30 << "): " << maze[newY / 30][newX / 30] << endl;
                player->move(newX, newY);
                player->add_score(1); //adding to player score after each case
                break;
            case 1:  // Wall encountered (block with value 1)
				cout << "Cannot move into a wall." << endl;
				player->rotateRight();
				orientation = player->get_orientation();
				cout << "right rotation" << endl;
				cout << "orientation after turn: " << orientation << endl;
				player->add_score(1); //adding to player score after each case
                break;
            case 2: // starting point
            	cout << "Value at (" << newX / 30 << ", " << newY / 30 << "): " << maze[newY / 30][newX / 30] << endl;
            	player->move(newX, newY);
            	player->add_score(1); //adding to player score after each case
                break;
            case 3: // endpoint
            	cout << "Value at (" << newX / 30 << ", " << newY / 30 << "): " << maze[newY / 30][newX / 30] << endl;
                player->move(newX, newY);
                cout << "Agent has reached the end of the maze. Game has ended." << endl;
                player->add_score(1); //adding to player score after each case
                cout << "score: " << player->get_score() << endl;
                exit(0);
                break;
            case 4: // goggles
            	cout << "Value at (" << newX / 30 << ", " << newY / 30 << "): " << maze[newY / 30][newX / 30] << endl;
                player->set_vision(player->get_vision()+1);
                cout << "Vision increased: " << player->get_vision() << endl;
                player->move(newX, newY);
                player->add_score(1); //adding to player score after each case
                break;
            case 5: // speed potion
            	cout << "Value at (" << newX / 30 << ", " << newY / 30 << "): " << maze[newY / 30][newX / 30] << endl;
            	if (player->get_multiplier() != 2){
            		player->set_multiplier(player->get_multiplier()+1);
            	}
            	cout << "Speed potion activated with " << player->get_multiplier()+1 << " steps" << endl;
                player->move(newX, newY);
                player->add_score(1); //adding to player score after each case
                break;
            case 6: // fog
            	cout << "Value at (" << newX / 30 << ", " << newY / 30 << "): " << maze[newY / 30][newX / 30] << endl;
                player->move(newX, newY);
                if (player->get_vision() == 1){
                	cout << "Vision is at its minimum. Cannot lower any further." << endl;
                }
                else{
                	player->set_vision(player->get_vision()-1);
                	cout << "Vision decreased at " << player->get_vision() << " steps" << endl;
                }
                player->add_score(1); //adding to player score after each case
                break;
            case 7: // slowpoke potion
            	cout << "Value at (" << newX / 30 << ", " << newY / 30 << "): " << maze[newY / 30][newX / 30] << endl;
                player->move(newX, newY);
            	if (player->get_multiplier() != 0){
            		player->set_multiplier(player->get_multiplier()-1);
            	}
            	cout << "Slowpoke potion activated with " << player->get_multiplier() << " steps" << endl;
                player->move(newX, newY);
                player->add_score(1); //adding to player score after each case
                break;
            // Add more cases for other block types as needed
        }

        int score = player->get_score(); // retrieving player score
        cout << "score: " << score << endl;

    } else {
        // Player is trying to move outside the boundaries
        cout << "Cannot move outside the boundaries of the maze." << endl;
        player->rotateRight();
        orientation = player->get_orientation();
        cout << "right rotation" << endl;
        cout << "orientation after turn: " << orientation << endl;
    }

    cout << " " << endl;
    //player->move(newX, newY);
    Fl::repeat_timeout(0.2, timerCallback, data); // repeat timer
}



#endif /* TIMERCALLBACK_H_ */
