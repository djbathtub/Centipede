#include "Obstruction.h"


/////////////////////////////////////////////////
/// \brief
///
/// \param
/// \param
/// \return
///
/////////////////////////////////////////////////
float Obstruction::getRandomFloat(float min_float, float max_float)
{
	static constexpr double fraction{ 1.0 / (RAND_MAX + 1.0) };  // static used for efficiency, so we only calculate this value once
	// evenly distribute the random number across our range
	auto integral = min_float + static_cast<float>((max_float - min_float + 1) * (std::rand() * fraction));
	auto decimal = static_cast<float>(((1000) * (std::rand() * fraction)) / 1000);
	return integral + decimal;
}

/////////////////////////////////////////////////
/// \brief Function returns random cordinates within the range { 0 : max_x_max_y.x} in the x position of the return vector and
/// \brief within the range { 0 : max_x_max_y.y } in the y position of the return vector.
///
/// \param A float vector containing the maximum boundry for the x-cordinate in the x position, and the maximum boundry for the y-cordinate in the y position.
/// \param const sf::Vector2f max_x_max_y
/// \return sf::Vector2f of random cordinates in the range of the parameters passed
///
/////////////////////////////////////////////////
const sf::Vector2f Obstruction::getRandomCordinates(const sf::Vector2f& max_x_max_y)
{
	return sf::Vector2f(this->getRandomFloat(20.f, max_x_max_y.x), this->getRandomFloat(20.f, max_x_max_y.y));
}

/// @brief 
/// @param target 
/// @param shape 

void Obstruction::enforce_window_bounds(const sf::RenderTarget& target, sf::CircleShape shape)
{
    this->boundry = Boundry::NONE; 
    if (shape.getGlobalBounds().top <= shape.getRadius())
    {
        shape.setPosition(shape.getPosition().x, shape.getRadius());
        this->boundry = Boundry::TOP;
    }
    if (-shape.getGlobalBounds().height + shape.getGlobalBounds().top >= target.getSize().y - shape.getRadius())
    {
        shape.setPosition(800.f, 10.f);
        this->boundry = Boundry::BOTTOM;
    }
    if (shape.getGlobalBounds().left <= 0.f + shape.getRadius())
    {
        shape.setPosition(shape.getRadius(), shape.getPosition().y);
        this->boundry = Boundry::LEFT;
    }
    if (shape.getGlobalBounds().width + shape.getGlobalBounds().left >= target.getSize().x - shape.getRadius())
    {
        shape.setPosition(target.getSize().x - shape.getRadius(), shape.getPosition().y);
        this->boundry = Boundry::RIGHT;
    }
    return;
}