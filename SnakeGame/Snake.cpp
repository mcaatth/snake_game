#include "Snake.h"

Snake::Snake() {
	//In the beginning snake has three segments and is placed in the middle of window
	body.push_back(sf::Vector2i(GAME_WINDOW_WIDTH_IN_SEGMENTS / 2, GAME_WINDOW_HEIGHT_IN_SEGMENTS / 2)); //sf is a namespace for SFML
	direction = RIGHT;
	if (GAME_WINDOW_WIDTH_IN_SEGMENTS > 6) { //so that snake is not too long for smaller window causing errors
		body.push_back(sf::Vector2i(GAME_WINDOW_WIDTH_IN_SEGMENTS / 2 - 1, GAME_WINDOW_HEIGHT_IN_SEGMENTS / 2));
		body.push_back(sf::Vector2i(GAME_WINDOW_WIDTH_IN_SEGMENTS / 2 - 2, GAME_WINDOW_HEIGHT_IN_SEGMENTS / 2));
	}
}

//We will need a function draw() from the class sf::RenderWindow to use here in draw().
void Snake::draw(sf::RenderWindow& window) {
	//In brackets below (when creating a sf::RectangleShape) we put size of the sf::RectangleShape
	//The position of sf::RectangleShape is set later with function setPosition() from the class sf::RectangleShape
	sf::RectangleShape rect(sf::Vector2f(SIZE_OF_SNAKE_AND_FOOD_SEGMENT - 2, SIZE_OF_SNAKE_AND_FOOD_SEGMENT - 2)); // minus 2 so that we see nice separate segments of snake
	rect.setFillColor(SNAKE_COLOR);
	for (auto& segment : body) {
		rect.setPosition(static_cast<float>(segment.x) * SIZE_OF_SNAKE_AND_FOOD_SEGMENT + 1, static_cast<float>(segment.y) * SIZE_OF_SNAKE_AND_FOOD_SEGMENT + 1); // cause we substracted 2 above
		window.draw(rect);
	}
}

void Snake::changeDirectionTo(Direction dir) {
	//Prevent reversing direction. Unfortunately it is still possible to reverse direction by for example for direction == UP pressing
	//quickly (less than TIME_BETWEEN_SNAKE_MOVEMENTS) LEFT and then DOWN or RIGHT then DOWN, the game ends in this case (snake collides). TODO: Fix this
	if ((direction == UP && dir != DOWN) || (direction == DOWN && dir != UP) ||
		(direction == LEFT && dir != RIGHT) || (direction == RIGHT && dir != LEFT)) {
		direction = dir;
	}
}

//We won't be moving every segment of snake, instead we will push a new head in front and delete the last segment
void Snake::move() {
	sf::Vector2i headCopy = body.front();

	switch (direction) {
	case UP:
		headCopy.y--;
		break;
	case DOWN:
		headCopy.y++;
		break;
	case LEFT:
		headCopy.x--;
		break;
	case RIGHT:
		headCopy.x++;
		break;
	}

	// Wrap if doesn't fit in the window
	if (headCopy.x < 0) {
		headCopy.x = GAME_WINDOW_WIDTH_IN_SEGMENTS - 1;
	}
	if (headCopy.x >= GAME_WINDOW_WIDTH_IN_SEGMENTS) {
		headCopy.x = 0;
	}
	if (headCopy.y < 0) {
		headCopy.y = GAME_WINDOW_HEIGHT_IN_SEGMENTS - 1;
	}
	if (headCopy.y >= GAME_WINDOW_HEIGHT_IN_SEGMENTS) {
		headCopy.y = 0;
	}

	body.push_front(headCopy);
	body.pop_back();
}

void Snake::grow() {
	auto lastSegment = body.back();
	this->move();
	body.push_back(lastSegment);
}

// TODO: Try to draw some image as the snake's head instead of only rectangle, example online:
// dev.to/dwarft/displaying-images-in-sfml-b6m
