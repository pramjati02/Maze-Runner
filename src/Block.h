#include <iostream>
#include <FL/Fl_Box.H>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
using namespace std;

// Block class
class Block : public Fl_Box {
private:
	int x; // x-coordinate
	int y; // y-coordinate
	int value; // value of block
public:
	Block(int x, int y, int value);
	void move(int newx, int newy);
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
    };

Block::Block(int x, int y, int value):Fl_Box(x, y, 20, 20){
	this->box(FL_FLAT_BOX); // Initializing box figure for the block

	// Switch cases for each number in the maze file denoting a different type of block
	switch(this->value=value){
	case 0: // empty space
		this->x = x; // x-cooridinate of block
		this->y = y; // y-coordinate of block
		this->color(FL_GREEN); // Colour of blocck
		break;
	case 1: // wall
		this->x = x;
		this->y = y;
		this->color(FL_RED);
		break;
	case 2: // starting point
		this->x = x;
		this->y = y;
		this->color(FL_BLUE);
		break;
	case 3: // endpoint
		this->x = x;
		this->y = y;
		this->color(FL_YELLOW);
		break;
	case 4: // goggles
		this->x = x;
		this->y = y;
		this->color(FL_DARK_GREEN);
		break;
	case 5: // speed potioj
		this->x = x;
		this->y = y;
		this->color(FL_DARK_YELLOW);
		break;
	case 6: // fog
		this->x = x;
		this->y = y;
		this->color(FL_WHITE);
		break;
	case 7: // slowpoke potion
		this->x = x;
		this->y = y;
		this->color(FL_BLACK);
		break;
	case 8: // Player block
		this->x = x;
		this->y = y;
		this->color(FL_WHITE);
		break;
	}
}

void Block::move(int newx, int newy){
	// hides the block
	this->hide();
	// set the new coordinates
	this->x = newx;
	this->y = newy;
	// repositions the block
	this->position(newx, newy);
	// shows the block
	this->show();
}

int Block::getX(){
	return this->x; // Retrieve x
}

int Block::getY(){
	return this->y; // Retrieve y
}

void Block::setX(int x){
	this->x = x; // set x
}

void Block::setY(int y){
	this->y = y; // set y
}

