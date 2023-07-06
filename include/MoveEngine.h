#pragma once
#include "Train.h"
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <iostream>
#include "DTBombs.h"
#include "Bullet.h"
#include "plf_colony.h"
#include <array>
#include <ctime>
#include <memory>
#include <vector>
#include <list>


class MoveEngine : public sf::Drawable
{
public:
	MoveEngine(sf::RenderTarget& target);
	~MoveEngine();
	void move(plf::colony<Bullet>& bullets);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void handle_bullets(plf::colony<Bullet>& bullets);
	const bool check_game_over(const sf::FloatRect& player) const;
	const unsigned int get_total_score() const { return this->player_score + train.add_score(); }
	const unsigned int get_level() const { return train.get_level(); }
private:
	/// @brief A lot of insertions, removals, sorting, resizing requires a list of
	/// shared pointers for the best performance
	//std::list<Train> trains;
	Train train;
	unsigned int player_score{ 0 };
	unsigned int amount_of_bombs{ 0 };
	unsigned int amount_of_active_trains{ 0 };
	sf::Clock bomb_spawn_timer; 
	/// @brief A lot of insertions, removals, sorting, resizing requires a list of
	/// shared pointers for the best performance
	plf::colony<std::shared_ptr<Mushroom>> mushrooms;
	void handle_bullets_mushrooms(plf::colony<Bullet>& bullets);
};

