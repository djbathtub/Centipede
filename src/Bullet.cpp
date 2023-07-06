#include "Bullet.h"

/// @brief 
/// @param cordinates 

Bullet::Bullet(const sf::Vector2f cordinates)
{
    this->initialize(cordinates); 
}

void Bullet::run()
{
    this->move(); 
    return;
}

////////////////////////////////
/// \brief 
/// \param
/// \param
/// \return 
///
////////////////////////////////
Bullet::~Bullet()
{
    //dtor
}

/////////////////////////////////////////////////
/// \brief
///
/// \param
/// \param
/// \return
///
/////////////////////////////////////////////////
void Bullet::initialize(const sf::Vector2f cordinates)
{
    this->texture.reset(new sf::Texture());
    this->sprite.reset(new sf::Sprite());
    this->texture->create(1u, 2u);
    this->texture->loadFromFile("bullet_texture.jpg");
    this->sprite->setTexture(*this->texture, true);
    this->sprite->setScale(0.025, 0.05);
    this->sprite->setOrigin(sf::Vector2f(0.025f, 0.025f));
    this->sprite->setPosition(cordinates);
    return;
}

void Bullet::move()
{
    this->sprite->move(0.f, -20.f); 
    return;
}

std::tuple<int,bool> Bullet::collide(const std::vector<sf::FloatRect> global_bounds)
{
    for (auto i  = 0 ; i < global_bounds.size(); i++)
    {
        if (this->sprite->getGlobalBounds().intersects(global_bounds.at(i)))
        {
            this->sprite.reset();
            return std::make_tuple(i,true);
        }
    }
    return std::make_tuple(0, false);
}
