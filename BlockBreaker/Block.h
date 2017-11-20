#ifndef BLOCK_H
#define BLOCK_H

#include "GameObject.h"

const int BLOCK_HEIGHT = 32;
const int BLOCK_WIDTH = 64;
const int ROWS = 8;
const int COLUMNS = 10;
const int BLOCK_NUMBER = ROWS * COLUMNS;
enum Color {INVISIBLE = 0, GREY, BLUE, GREEN, YELLOW, PURPLE, RED};

class Block : public GameObject
{
	
	Color blockState;
	//sf::Vector2f position;
public:
	Block();
	~Block();

	sf::Texture grey, blue, green, yellow, purple, red;
	void setBlockState(Color state) { blockState = state;};
	Color getBlockState() { return blockState;};
	
	void update();
};





#endif
