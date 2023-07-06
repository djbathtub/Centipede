#ifndef OBSTRUCTION_H
#define OBSTRUCTION_H

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <array>
#include <ctime>
#include <memory>



class Obstruction : public sf::Drawable
{
public:
    enum class Boundry
    {
        TOP,
        BOTTOM,
        LEFT,
        RIGHT,
        NONE,
    };
    //!< might cluster the base class to much check and test
    Obstruction() {};
    virtual ~Obstruction() {};
    //!< Random cordinate functions for respawning objects randomly
    float getRandomFloat(float min_f, float max_f);
    const sf::Vector2f getRandomCordinates(const sf::Vector2f& max_x_max_y);
    void enforce_window_bounds(const sf::RenderTarget& target, sf::CircleShape shape);
    //!<
protected:
    Boundry boundry{Boundry::NONE};
private:
    //!< Functions called repeatedly to perform operations on different states of the base object
};

#endif // OBSTRUCTION_H
