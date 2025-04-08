#include <iostream>
using namespace std;

// Block class
class Block : public Fl_Box {
private:
	int x;
	int y;
	int label;
public:
	Block(int x, int y, int label);
	void move(int newx, int newy);
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
    };

Block::Block(int x, int y, int label):Fl_Box(x, y, 20, 20){
	this->box(FL_FLAT_BOX); // Initializing box figure for the block

	// Switch cases for each number in the maze file denoting a different type of block
	switch(this->label=label){
	case 0:
		this->x = x;
		this->y = y;
		this->color(FL_GREEN);
		break;
	case 1:
		this->x = x;
		this->y = y;
		this->color(FL_RED);
		break;
	case 2:
		this->x = x;
		this->y = y;
		this->color(FL_BLUE);
		break;
	case 3:
		this->x = x;
		this->y = y;
		this->color(FL_YELLOW);
		break;
	case 4:
		this->x = x;
		this->y = y;
		this->color(FL_DARK_GREEN);
		break;
	case 5:
		this->x = x;
		this->y = y;
		this->color(FL_DARK_YELLOW);
		break;
	case 6:
		this->x = x;
		this->y = y;
		this->color(FL_WHITE);
		break;
	case 7:
		this->x = x;
		this->y = y;
		this->color(FL_BLACK);
		break;
	case 8: // player case
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
