#ifndef BULLET_H
#define BULLET_H

#include "Obstruction.h"

class Bullet : public Obstruction
{
public:
    Bullet(const sf::Vector2f cordinates);
    void run(); 
    ~Bullet();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const { target.draw(*this->sprite, sf::RenderStates::Default); }
    std::tuple<int,bool> collide(const std::vector<sf::FloatRect> global_bounds);
    const sf::FloatRect get_global_bounds() const { return this->sprite->getGlobalBounds(); }
    const sf::Vector2f get_cordinates() const { return this->sprite->getPosition();  }
private:

    /// @brief  Private variables
    std::shared_ptr<sf::Sprite> sprite;
    std::shared_ptr<sf::Texture> texture;
    std::shared_ptr<const sf::Vector2i> size; 
    std::shared_ptr<sf::RectangleShape> shape;

    /// @brief Private methods
    void initialize(const sf::Vector2f cordinates);
    void move();
    //virtual void draw(sf::RenderTarget& target, sf::RenderStates& states) const { target.draw(*this->sprite, sf::RenderStates::Default); }

};

#endif // BULLET_H
