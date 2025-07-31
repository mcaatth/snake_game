#pragma once
#include <SFML/Graphics.hpp>
#include <deque>
#include "constants.h"

enum Direction {UP, DOWN, LEFT, RIGHT};

class Snake {
public:
	Snake();
	void draw(sf::RenderWindow& window); //sf is a namespace for SFML
	void changeDirectionTo(Direction dir);
	void move();
	void grow();

	//We use deque because when moving the snake we won't be moving every segment of snake, instead we will push a new head in front and delete the last segment !!
	//queue (with order from the END of snake to its HEAD) won't work because we won't have access to each element
	std::deque<sf::Vector2i> body;  //each element of body contains its position in window; this (sf::Vector2i) is how you represent pair of numbers in SFML
	Direction direction;
};