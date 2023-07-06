#include "MoveEngine.h"

MoveEngine::MoveEngine(sf::RenderTarget& target)
{
	plf::colony<std::shared_ptr<Mushroom>> mushroom( 0, std::shared_ptr<Mushroom>(new Mushroom())); 
	this->mushrooms.reshape(plf::colony_limits(10, 20)); 
	for (auto i = 0; i < 20; i++)
	{
		this->mushrooms.insert(std::shared_ptr<Mushroom>(new Mushroom())); 
	}
}

MoveEngine::~MoveEngine()
{

}

void MoveEngine::move(plf::colony<Bullet>& bullets)
{
	train.run(this->mushrooms, bullets);
	this->handle_bullets_mushrooms(bullets);
	std::cout << this->mushrooms.memory() << " memory \n"; 
	std::cout << this->mushrooms.capacity() << " capacity \n"; 
	/*if (!this->mushrooms.empty())
		this->mushrooms.shrink_to_fit();
	else
		this->mushrooms.clear(); */
	return;
}

void MoveEngine::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& i : this->mushrooms)
	{
		target.draw(*i);
	}
	target.draw(this->train);
	return;
}


void MoveEngine::handle_bullets(plf::colony<Bullet>& bullets)
{
	this->handle_bullets_mushrooms(bullets);
	train.new_handle_train(bullets, this->mushrooms);
	//bullets.shrink_to_fit();
	return;
}

const bool MoveEngine::check_game_over(const sf::FloatRect& player) const
{
	return train.handle_player_collisions(player);
}

void MoveEngine::handle_bullets_mushrooms(plf::colony<Bullet>& bullets)
{
	train.handle_mushroom_collisions(this->mushrooms, bullets); 

}

