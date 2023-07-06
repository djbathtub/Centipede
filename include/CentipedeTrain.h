#pragma once
#include "Centipede.h"
#include <tuple>
#include <cmath>
#include <complex>
#include <algorithm>
#include <numbers>
#include <iomanip>

/*

class CentipedeTrain : public sf::Drawable
{
public:
	enum class BOUNDRY
	{
		TOP,
		BOTTOM,
		LEFT,
		RIGHT,
		NONE,
	};
     CentipedeTrain(uint8_t train_size);
	 ~CentipedeTrain(); 
	 const std::vector<std::vector<std::shared_ptr<sf::Vector2f>>> get_trains_globalbounds() const { return this->trains_globalbounds; };
	 void run(const sf::RenderTarget& target);
	 const std::vector<std::vector<std::shared_ptr<sf::Vector2f>>> return_deallocated_cordinates(const std::vector<std::vector<std::shared_ptr<bool>>> did_collide) const;
	 std::array<sf::CircleShape, 36> possible_cordinates(sf::Vector2f cordinates, float movement_radius);
	 void move_train(const sf::RenderTarget& target);
	 void feed_nearby_mushroom(std::vector<std::shared_ptr<Mushroom>> mushrooms);
	 virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; 
private:
	/// @brief  Private variables 
	std::vector<std::vector<std::shared_ptr<Centipede>>> trains; 
	std::vector<std::vector<std::shared_ptr<sf::Vector2f>>> trains_globalbounds; 
	std::vector<sf::FloatRect> mushroom_globalbounds;
	bool is_train_empty = { false }; 
	const double pi =  static_cast<const double>(std::acos(-1));
	BOUNDRY direction_move { BOUNDRY::LEFT };
	sf::Clock movement_clock;

	/// @brief Private member functions 
	void update(const std::vector<std::vector<std::shared_ptr<bool>>> did_collide);
	//void move_head(std::shared_ptr<Centipede> head, const sf::RenderTarget& target);
	//bool move_tail(std::shared_ptr<Centipede> lead, std::shared_ptr<Centipede> tail);
	void set_positions_in_circle(float movement_radius);
	void re_intialize_train(uint8_t train_size); 
	void sort_train();

	friend class Centipede;
};

*/