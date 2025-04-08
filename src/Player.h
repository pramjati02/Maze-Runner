/*
 * Player.H
 *
 *  Created on: 29 Nov 2023
 *      Author: pjati
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <vector>
#include <utility>

using namespace std;

// Player class
class Player: public Block{
private:
	int orientation = 1; // Orientation of player
	int multiple = 0; // Multiple to be used for speed and slowpoke potion
	int score = 0; // Score of total player movement to complete the maze
	int vision = 1; // Vision of player steps at any given time
	vector<pair<int, int>> moveHistory; // Vector for player move history
public:
	Player(int x, int y, int label); // Initializing player and its properties
	int get_orientation();
	void set_orientation(int orientation);
	void rotateLeft();
	void rotateRight();
	int get_multiplier();
	void set_multiplier(int multiple);
	void add_score(int addition);
	int get_score();
	void set_vision(int vision);
	int get_vision();
	void UpdateMoveHistory();
	vector<pair<int, int>> getMoveHistory(); // Initializing a vector space for previous moves
	void updateMoveHistory(int x, int y);
};

Player::Player(int x, int y, int label):Block(x, y, label) {
    this->box(FL_OSHADOW_BOX);// initializing box figure for player
}

int Player::get_orientation(){ // Retrieving the orientation
	return this->orientation;
}
void Player::set_orientation(int orientation){ // Setting the orientation
	this->orientation = orientation;
}

void Player::rotateLeft(){ //changing the orientation so that it rotates left
	set_orientation(orientation - 1);
	if (orientation < 0) {
		orientation += 4;
	}
}

void Player::rotateRight(){ // changing the orientation so that it rotates left
	set_orientation(orientation + 1);
	orientation %=4;
}

int Player::get_multiplier(){ // retrieving the multiplier for speed and slowpoke potion
	return this->multiple;
}

void Player::set_multiplier(int multiple){ // setting the multiplier for the speed and slowpoke potion
	this->multiple = multiple;
}

void Player::add_score(int addition){ // adding to the score
	this->score += addition;
}

int Player::get_score(){ // retrieving the score
	return this->score;
}

void Player::set_vision(int vision){ // Setting the vision space of the player
	this->vision = vision;
}

int Player::get_vision(){ // Retrieving the vision space
	return this->vision;
}

vector < pair<int, int> > Player::getMoveHistory(){ // retrieving the move history of the player
	return moveHistory;
}

void Player::updateMoveHistory(int x, int y){ // adding new coordinates to the move history
	moveHistory.emplace_back(x, y);

}



#endif /* PLAYER_H_ */
