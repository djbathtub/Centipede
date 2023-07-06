#include "Player.h"



Player::Player()
{
    this->sprite.reset(new sf::Sprite()); 
    this->texture.reset(new sf::Texture()); 
    this->texture->loadFromFile("ship.png"); 
    this->sprite->setScale(0.15f, 0.15f); 
    this->sprite->setOrigin(30.f, 0.f);
    this->sprite->setTexture(*this->texture); 
    this->sprite->setPosition(400.f, 550.f); 
    this->bullets.reserve(4); 
}

/////////////////////////////////////////////////
/// \brief
///
/// \param
/// \param
/// \return
///
/////////////////////////////////////////////////
void Player::run(const sf::RenderTarget& target)
{
    for (auto& i : this->bullets)
    {
        i.run();
    }
    this->update();
    this->enforce_window_bounds(target);
    this->poll();
    return;
}
/////////////////////////////////////////////////
/// \brief
///
/// \param
/// \param
/// \return
///
/////////////////////////////////////////////////
Player::~Player()
{
    //dtor
}

/////////////////////////////////////////////////
/// \brief Draws the player and the bullets which the player fired onto a target passed in the parameters
///
/// \param A target to draw the player and bullet map onto
/// \param
/// \return
///
/////////////////////////////////////////////////
void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto& i : this->bullets)
    {
       target.draw(i, states);
    }
    target.draw(*this->sprite, sf::RenderStates::Default);
    return;
}

void Player::reduce_live_respawn()
{
     this->sprite->setPosition(400.f, 550.f); 
     --lives; 
     if (lives == 0) 
     { 
         end_game = true; 
     } 
     return;  
}


/////////////////////////////////////////////////
/// \brief
///
/// \param
/// \param
/// \return
///
/////////////////////////////////////////////////
void Player::update()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        this->sprite->move(-10.f, 0.f); 
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        this->sprite->move(0.f, 10.f); 
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        this->sprite->move(10.f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        this->sprite->move(0.f, -10.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
    {
        this->shoot(); 
    }
    return;
}

/////////////////////////////////////////////////
/// \brief
///
/// \param
/// \param
/// \return
///
/////////////////////////////////////////////////
void Player::poll()
{
    this->update_bullets();
    return;
}

/// @brief 

void Player::shoot()
{
    auto time_elapsed = this->bullet_clock.getElapsedTime().asSeconds();
    if (time_elapsed == 0.f || time_elapsed >= cooldown_shooting_time)
    {
        this->bullets.insert(Bullet(sf::Vector2f(this->sprite->getPosition().x + 15.f, this->sprite->getPosition().y)));
        this->bullet_clock.restart();
        return; 
    }
    return;
}

/// @brief 
/// @param target 
void Player::enforce_window_bounds(const sf::RenderTarget& target)
{
    if (this->sprite->getGlobalBounds().left <= 0.f + this->player_size.x)
    {
        this->sprite->setPosition(this->player_size.x, this->sprite->getPosition().y);
    }
    if (this->sprite->getGlobalBounds().width + this->sprite->getGlobalBounds().left >= target.getSize().x - this->player_size.x )
    {
        this->sprite->setPosition(target.getSize().x - this->player_size.x - 30.f, this->sprite->getPosition().y);
    }
    if (this->sprite->getGlobalBounds().top <= this->player_size.y + 450.f)
    {
         this->sprite->setPosition(this->sprite->getPosition().x, this->player_size.y + 450.f);
    }
    if (-this->sprite->getGlobalBounds().height + this->sprite->getGlobalBounds().top >= target.getSize().y - this->player_size.y - 30.f)
    {
        this->sprite->setPosition(this->sprite->getPosition().x, target.getSize().y - 20.f);
    }
    return;
}

void Player::update_bullets()
{
    return;
}

/// @brief 
/// 
/// 
void Player::initialize()
{

}
