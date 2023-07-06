#pragma once
#ifndef CENTIPEDEHEAD_H
#define CENTIPEDEHEAD_H
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <iostream>
#include <array>
#include <ctime>
#include "Mushroom.h"
#include "Obstruction.h"
#include <list>
#include <memory>

class CentipedeHead : public Obstruction
{
private:
	// Private member variables
	sf::Vector2f previous_cordinates;
	//const float movement_speed;
	std::list<std::shared_ptr<sf::Sprite>> complete_centipede{ 10,std::shared_ptr<sf::Sprite>(new sf::Sprite()) };
	std::list<std::shared_ptr<sf::Sprite>>::iterator tail{ this->complete_centipede.begin() }; 
	std::list<std::shared_ptr<sf::Sprite>>::iterator head{ --this->complete_centipede.end() };
	std::shared_ptr<sf::Texture> texture{ std::shared_ptr<sf::Texture>(new sf::Texture()) };
	std::list<std::shared_ptr<sf::FloatRect>> mushroom_bounds{ 15,std::shared_ptr<sf::FloatRect>(new sf::FloatRect()) };

public: 
	CentipedeHead();
	~CentipedeHead(); 
	void run(sf::RenderTarget& target);
	enum class Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
	};
	const sf::Vector2f get_previous_cordinates() const {  return previous_cordinates;  }
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; 
private: 
	// Private helper functions 
	void init(); 
	void move(); 
	void collide(Mushroom check_collision); 
	void window_bounds(sf::RenderTarget& target); 
};

#endif