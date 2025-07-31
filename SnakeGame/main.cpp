#include "Snake.h"
#include "Food.h"
#include "constants.h"

/*
int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Snake Game"); //sf is a namespace for SFML
	sf::Clock clock;
	float timer = 0.0f, delay = 0.1f; // snake speed
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (clock.getElapsedTime().asSeconds() > delay) { // game updates every 'delay' seconds
			// add update of snake movement, collisions check
			clock.restart();
		}
		window.clear();
		// add drawing snake, food, score
		window.display();
	}
	return 0;
}
*/

//We check only collision of snake with itself, not with the borders of the game window
bool doesCollide(Snake& snake) {
	sf::Vector2i& head = snake.body.front(); //sf is a namespace for SFML
	for (int i = 1; i < snake.body.size(); i++) {
		if (snake.body[i] == head) {
			return true;
		}
	}
	return false;
}

int main(int argc, char ** argv) {
	sf::RenderWindow window(sf::VideoMode(GAME_WINDOW_WIDTH_IN_SEGMENTS * SIZE_OF_SNAKE_AND_FOOD_SEGMENT, GAME_WINDOW_HEIGHT_IN_SEGMENTS * SIZE_OF_SNAKE_AND_FOOD_SEGMENT), "Snake Game");
	// TODO: An idea to maybe apply: user choses game level (ie. snake speed) by pressing a key
	Snake snake;
	Food food;
	sf::Clock clock; //We need a clock to move snake every given period of time. Clock starts counting when created.
	srand(static_cast<unsigned int>(time(nullptr))); //srand() function sets the starting point for producing a series of pseudo-random integers
	//I moved TIME_BETWEEN_SNAKE_MOVEMENTS to constants.h

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				break;
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Up) snake.changeDirectionTo(UP);
				else if (event.key.code == sf::Keyboard::Down) snake.changeDirectionTo(DOWN);
				else if (event.key.code == sf::Keyboard::Left) snake.changeDirectionTo(LEFT);
				else if (event.key.code == sf::Keyboard::Right) snake.changeDirectionTo(RIGHT);
			}
		}

		if (clock.getElapsedTime().asSeconds() > TIME_BETWEEN_SNAKE_MOVEMENTS) {
			// We update the snake according to the food met and draw snake again in the bottom below
			snake.move();
			// Additional part (more than only move()) for the case when eating food:
			const sf::Vector2i& head = snake.body.front(); // snake.body.front() is the head of the snake (.front() is the first element of deque)
			if (head == food.foodElement) {
				snake.grow();
				food.generateFoodElement();
			}
			// Additional part (more than only move()) for the case when snake collides:
			if (doesCollide(snake) == true) {
				break; //TODO: window closes here, fix it, system("PAUSE") doesn't work correctly
			}
			clock.restart();
		}

		window.clear(BACKGROUND_COLOR); //window.clear() clears with black background, but we can change the black background color this way
		snake.draw(window);
		food.draw(window);
		window.display();
	}
	
	// TODO: maybe add a 'GAME OVER' text? how and where?
	return 0;
}