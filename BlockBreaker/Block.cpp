#include "Block.h"

Block::Block()
{
	grey.loadFromFile("images/element_grey_rectangle_glossy.png");
	blue.loadFromFile("images/element_blue_rectangle_glossy.png");
	green.loadFromFile("images/element_green_rectangle_glossy.png");
	yellow.loadFromFile("images/element_yellow_rectangle_glossy.png");
	purple.loadFromFile("images/element_purple_rectangle_glossy.png");
	red.loadFromFile("images/element_red_rectangle_glossy.png");
	getSprite().setOrigin(BLOCK_WIDTH / 2, BLOCK_HEIGHT / 2);
}

Block::~Block()
{}

void Block::update()
{
	switch (blockState)
	{
	case GREY:
		getSprite().setTexture(grey);
		break;
	case BLUE:
		getSprite().setTexture(blue);
		//load("images/element_blue_rectangle_glossy.png");
		break;
	case GREEN:
		getSprite().setTexture(green);
		//load("images/element_green_rectangle_glossy.png");
		break;
	case YELLOW:
		getSprite().setTexture(yellow);
		break;
	case PURPLE:
		getSprite().setTexture(purple);
		break;
	case RED:
		getSprite().setTexture(red);
		//load("images/element_red_rectangle_glossy.png");
		break;
	}
}



