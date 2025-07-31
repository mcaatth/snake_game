#pragma once
#include <SFML/Graphics.hpp>
#include <set>
#include "constants.h"

class Food {
public:
	Food();
	void generateFoodElement();
	void draw(sf::RenderWindow& window); //sf is a namespace for SFML

	//I wanted to use std::multiset<sf::Vector2i> foodElements here (not sure if multiset is a good option, need to check how it works and fix if needed;
	//probably overloading operator < for sf::Vector2i needed in this case; unordered set not good because of uniqness of its elements),
	//because what if for a moment there exist no foodElement / trash value or two of them? Functions are called in a proper order, but still not sure.
	//But I changed my mind, because it could cause even more problems, so let's have just one element which will be overwritten (also not sure how this will work).
	sf::Vector2i foodElement; //contains its position in window; this (sf::Vector2i) is how you represent pair of numbers in SFML
};