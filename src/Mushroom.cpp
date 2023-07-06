#include "Mushroom.h"

Mushroom::Mushroom() : Obstruction{}
{
    this->texture.reset(new sf::Texture());
    this->sprite.reset(new sf::Sprite());
    if (!this->texture->loadFromFile("mushroom_house.png"))
        std::cout << "cannot load tecture from file \n";
    this->sprite->setTexture(*this->texture, true);
    this->sprite->setScale(0.5f, 0.5f);
    this->sprite->setPosition(Obstruction::getRandomCordinates(sf::Vector2f(800.f, 400.f)));
    this->collision.setOrigin(0.f, 0.f);
    this->collision.setPosition(this->sprite->getPosition());
    this->collision.setRadius(5.f);

}

Mushroom::Mushroom(const std::string& file_name) : Obstruction{}
{
    this->texture.reset(new sf::Texture());
    this->sprite.reset(new sf::Sprite());
    if (!this->texture->loadFromFile(file_name))
        std::cout << "cannot load tecture from file \n";
    this->sprite->setTexture(*this->texture, true);
    this->sprite->setScale(0.1f, 0.1f);
    this->sprite->setPosition(Obstruction::getRandomCordinates(sf::Vector2f(800.f, 400.f)));
    this->collision.setOrigin(0.f, 0.f);
    this->collision.setPosition(this->sprite->getPosition());
    this->collision.setRadius(5.f);
}

Mushroom::Mushroom(const sf::Vector2f cordinates) : Obstruction{}
{
    this->texture.reset(new sf::Texture());
    this->sprite.reset(new sf::Sprite());
    this->sprite->setPosition(cordinates);
    this->sprite->setOrigin(sf::Vector2f(10.f, 10.f));
    if (!this->texture->loadFromFile("mushroom_house.png"))
        std::cout << "cannot load tecture from file \n";
    this->sprite->setTexture(*this->texture, false);
    this->sprite->setScale(0.5f, 0.5f);
    this->collision.setOrigin(10.f, 10.f);
    this->collision.setPosition(this->sprite->getPosition());
    this->collision.setRadius(10.f);
}

/////////////////////////////////////////////////
/// \brief
///
/// \param
/// \param
/// \return
///
/////////////////////////////////////////////////
void Mushroom::run(const sf::RenderTarget& target, const sf::FloatRect globalbounds)
{
    // this->enforce_window_bounds(target, *this->mushroom);
    // this->is_kill(globalbounds);
    return;
}

void Mushroom::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // this->sprite->setPosition(this->mushroom->getPosition());
    target.draw(*this->sprite, sf::RenderStates::Default);
    return;
}

// POSSIBLE_MOVES_FUNCTION IMPLEMENTATION AND COMMENTS

// get right, so thus a centipede moving from the right boundry to the left boundry
// move of preference would be downward towards the player
//        -            RIGHT              +        |      -       LEFT        +
//                 | | |            | | |          |                | | |
//                |  M  |   <----- |  C  |         |           --> |  M  |
//                 | | |  X         | | |          |              X | | |
//                       X                         |                X
//                X  X  X                          |                  X  X X
//                                                 |
//  " X " marks the path of cordinates we want to give the centipede object to know where to move
//  Coming from the right boundry towards the left boundry
//  the return map, will be enum sorted, bear in mind "C" indicates the origin of the Centipede sprite, and
//  "M" the mushroom sprite origin. Also bear in mind these X spots can't intersect with other mushrooms, hence the globalbounds
//  parameter we pass into this function of other mushrooms.
//  We will create hypothetical circleshapes at X to test if we move a centipede into this area, it will intersect or not.
//  There X spots must be a Diameter away from the Centipede Origin

// Method of modelling the cordinates.
// ------------->  Polar format with "C" as the origin
// the imaginairy segment of the polar comlpex number is Y-cordinate
// the real segment of the polar comlpex number is X-cordinate
// OUTPUT one sf::Vector2f of open cordinates
// now we'll call thus recursively in Train class, if we find that the normal offset will produce an intersection
// between the leader and the mushroom until it does not produce any intersection
// if the mushroom finds that the Centipede is trapped in it's normal position,
// we move the centipede upward, leftward or downward, until there is no intersection bewteen these objects

sf::Vector2f Mushroom::get_move(Direction movement_direction, std::shared_ptr<sf::CircleShape> sprite1, bool up_down)
{
    this->possible_moves(sprite1, movement_direction);
    auto ret = sf::Vector2f(0.f, 0.f);
    switch (movement_direction)
    {
    case Direction::RIGHT:
        ret = this->get_right(sprite1, up_down, movement_direction);
        return ret;
    case Direction::LEFT:
        ret = this->get_right(sprite1, up_down, movement_direction);
        return ret;
    default:
        ret = this->get_right(sprite1, up_down, movement_direction);
        return ret;
    }
    return ret;
}


void Mushroom::possible_moves(std::shared_ptr<sf::CircleShape> sprite1, Direction movement_direction)
{
    this->open_cors.clear();
    auto check_shapes = this->possible_cordinates(20.f, sprite1, movement_direction);
    return;
}

std::vector<sf::CircleShape> Mushroom::possible_cordinates(float movement_radius, std::shared_ptr<sf::CircleShape> sprite1, Direction movement_direction)
{
    std::vector<sf::CircleShape> return_shapes;
    for (auto i = 0; i < 16; i++)
    {
        return_shapes.push_back(sf::CircleShape());
    }
    const double pi{ std::acos(-1) };
    double theta = -pi / 2;
    auto increment = -pi / 8;
    if (movement_direction == Direction::RIGHT)
    {
        double theta = -pi / 2;
        increment = pi / 8;
    }
    for (auto i = 0; i < 16; i++, theta += increment)
    {
        auto check_x = std::polar<float>(movement_radius, theta).real() + (sprite1)->getPosition().x;
        auto check_y = std::polar<float>(movement_radius, theta).imag() + (sprite1)->getPosition().y;
        if ((5.f <= check_x) && check_x <= 800.f && (5.f <= check_y) && check_y <= 600.f && (check_y > sprite1->getPosition().y + 2.f || check_y < sprite1->getPosition().y - 2.f))
        {
            return_shapes[i].setRadius(10.f);
            return_shapes[i].setOrigin(10.f, 10.f);
            return_shapes[i].setPosition(sf::Vector2f(std::polar<float>(movement_radius, theta).real() + (sprite1)->getPosition().x, (std::polar<float>(movement_radius, theta).imag() + (sprite1)->getPosition().y)));
            if (!return_shapes[i].getGlobalBounds().intersects(this->collision.getGlobalBounds()) && !sprite1->getGlobalBounds().intersects(return_shapes[i].getGlobalBounds()))
            {
                this->open_cors.push_back(return_shapes[i].getPosition());
            }
        }
    }
    sort(this->open_cors.begin(), this->open_cors.end(), [&](const sf::Vector2f& first, const sf::Vector2f& last) { return first.y > last.y; });
    return return_shapes;
}

/// @brief rerturns a group of cordinates closest to the diameter distance of the centipede of 20.f
/// these cordinates will have the following properties: (Refer to the above diagram for more understanding)
/// ----> 1.) be smaller than the centipede's x-cordinate and larger then the centipede's y cordinate
/// ----> 2.) be at a diameter distance away from the mushroom and the centipede
/// ----> 3.) if impossible to be a diameter distance away from the mushroom, calculate a new point, free from self intersection
/// ----> and mushroom intersection. Diameter distance away from centipede, and larger than a diameter distance away from mushroom
/// ----> stil satisfying condition 1.) above
/// @param sprite, mushroom map globalbounds
/// @return cordinates with above attributes

const sf::Vector2f Mushroom::get_right(std::shared_ptr<sf::CircleShape> sprite1, bool up_down, Direction movement_direction)
{
    for (const auto& i : this->open_cors)
    {
        if (i.y > this->sprite->getPosition().y) // && 18.f <= (std::abs(std::complex(i.x - sprite->getPosition().x, i.y - sprite->getPosition().y)) <= 21.f))
        {
            return sf::Vector2f(i.x, i.y);
        }
        else if (i.y > this->sprite->getPosition().y) // && 18.f <= (std::abs(std::complex(i.x - sprite->getPosition().x, i.y - sprite->getPosition().y)) <= 21.f))
        {
            return sf::Vector2f(i.x, i.y);
        }
        if (i.y < this->sprite->getPosition().y) // && 18.f <= (std::abs(std::complex(i.x - sprite->getPosition().x, i.y - sprite->getPosition().y)) <= 21.f))
        {
            return sf::Vector2f(i.x, i.y);
        }
        else if (i.y < this->sprite->getPosition().y) // && 18.f <= (std::abs(std::complex(i.x - sprite->getPosition().x, i.y - sprite->getPosition().y)) <= 21.f))
        {
            return sf::Vector2f(i.x, i.y);
        }
    }
    return sf::Vector2f(0.f, 0.f);
}

bool Mushroom::increment_health(plf::colony<std::shared_ptr<Mushroom>>& mushrooms, plf::colony<std::tuple<std::deque<sf::Sprite>, Direction>>& multiple_centipede_trains)
{
    ++health;
    scale = scale - 0.05;
    sprite->setScale(this->scale, this->scale);
    if (health < 3)
        return false;
    else
        return true;
}




