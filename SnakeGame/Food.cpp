#include "Food.h"
#include <cstdlib>

//TODO: What happens when food is generated on snake - check and fix this
Food::Food() {
	generateFoodElement();
}

void Food::generateFoodElement() {
	sf::Vector2i element;
	element.x = rand() % GAME_WINDOW_WIDTH_IN_SEGMENTS;
	element.y = rand() % GAME_WINDOW_HEIGHT_IN_SEGMENTS;
	foodElement = { element.x, element.y };
}

void Food::draw(sf::RenderWindow& window) {
	//In brackets below (when creating a sf::RectangleShape) we put size of the sf::RectangleShape
	//The position of sf::RectangleShape is set later with function setPosition() from the class sf::RectangleShape
	sf::RectangleShape rect(sf::Vector2f(SIZE_OF_SNAKE_AND_FOOD_SEGMENT - 2, SIZE_OF_SNAKE_AND_FOOD_SEGMENT - 2)); // minus 2 so that we see nice separate segments
	rect.setFillColor(FOOD_COLOR);
	rect.setPosition(foodElement.x * SIZE_OF_SNAKE_AND_FOOD_SEGMENT + 1, foodElement.y * SIZE_OF_SNAKE_AND_FOOD_SEGMENT + 1); // cause we substracted 2 above
	window.draw(rect);
}

// TODO: Try to draw some image instead of only rectangle, example online:
// dev.to/dwarft/displaying-images-in-sfml-b6m