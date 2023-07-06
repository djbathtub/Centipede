#include "CentipedeTrain.h"

/*
using namespace std::complex_literals;

/// @brief 

CentipedeTrain::CentipedeTrain(uint8_t train_size)
{
	this->re_intialize_train(train_size); 
}

/// @brief 
CentipedeTrain::~CentipedeTrain()
{

}

void CentipedeTrain::run(const sf::RenderTarget& target)
{
	this->move_train(target); 
	//this->sort_train();
	return;
}

void CentipedeTrain::move_train(const sf::RenderTarget& target)
{
	for (const auto& i : this->trains)
	{
	 //   this->trains.at(i).at(0)->run_head(target);
		//if (this->direction_move == BOUNDRY::LEFT)
		//{
			i.at(0)->set_head(true);
	//	}
	///	else
	//	{
		//	i.at(0)->clear_head();
		//	i.at(i.size() - 1)->set_head(true);
	//	}
		for (auto j = 0; j < i.size() - 1; j++)
		{ 
			auto k = j + 1;
			auto possible_shapes = this->possible_cordinates(i.at(j)->get_cordinates(), 20.f); 
			i.at(k)->run(target, possible_shapes);
			auto possible_shapes1 = this->possible_cordinates(i.at(k)->get_cordinates(), 20.f);
			i.at(j)->run(target, possible_shapes1);
		}
	//	this->direction_move = (BOUNDRY)i.at(0)->get_boundry(); 
		//this->trains.at(i).at(0)->run_head(target);
	}
	return;
}

void CentipedeTrain::feed_nearby_mushroom(std::vector<std::shared_ptr<Mushroom>> mushrooms)
{
	for (const auto& i : this->trains)
	{
		for (const auto& j : i)
		{
			j->set_nearby_mushrooms(mushrooms); 
		}
	}
	return;
}

void CentipedeTrain::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& i : this->trains)
	{
		for (const auto& j : i)
		{
			target.draw(*j, sf::RenderStates::Default); 
		}
	}
	return; 
}
/*
void CentipedeTrain::move_head(std::shared_ptr<Centipede> head, const sf::RenderTarget& target)
{
	auto possible_shapes = this->possible_cordinates(head->get_cordinates(), 20.f);
	for (const auto& i : possible_shapes)
	{
		head->run(target, i); 
	}
	return;
}
*/
/*
bool CentipedeTrain::move_tail(std::shared_ptr<Centipede> lead, std::shared_ptr<Centipede> tail)
{
	auto move_shapes = this->possible_cordinates(lead->get_cordinates(), 20.f); 
	for (const auto& i : move_shapes)
	{
		if (tail->pick_move(i))
		{
			return true;;
		}
	}
	return false; 
}


void CentipedeTrain::re_intialize_train(uint8_t train_size)
{
	this->trains.push_back(std::vector<std::shared_ptr<Centipede>>{std::shared_ptr<Centipede>(new Centipede())});
	auto trailing = 0; 
	for (size_t i = 1; trailing < (int)train_size - 1 && i < (int)train_size; i++, trailing = i - 1)
	{
		this->trains[0].push_back({std::shared_ptr<Centipede>(new Centipede())});
	}
	return; 
}

void CentipedeTrain::sort_train()
{
	for (const auto& i : this->trains)
	{
		for (auto j = 0; j < i.size(); j++) 
		{
			auto sorted = false;
			for (auto k = 0; k < i.size() - 1; k++)
			{
				if (i.at(k)->get_cordinates().x < i.at(k + 1)->get_cordinates().x)
				{
					auto swap = i.at(k + 1)->get_cordinates(); 
					i.at(k + 1)->set_postion(i.at(k)->get_cordinates());
					i.at(k)->set_postion(swap);
					sorted = true; 
				}
			}
			if (!sorted)
				break;
		}
	}
}

std::array<sf::CircleShape, 360> CentipedeTrain::possible_cordinates(sf::Vector2f cordinates, float movement_radius)
{
	std::array<sf::CircleShape, 360> return_shapes;
	double theta{ 0 };
	for (auto i = 0; i < 16; i++, theta += pi/180)
	{
		return_shapes[i].setPosition(sf::Vector2f(std::polar<float>(movement_radius, theta).real() + cordinates.x, (std::polar<float>(movement_radius, theta).imag() + cordinates.y)));
		return_shapes[i].setRadius(10.f);
		return_shapes[i].setOrigin(10.f, 10.f);
	}
	return return_shapes;
}

*/

