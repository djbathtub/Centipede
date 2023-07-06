#ifndef MUSHROOM_H
#define MUSHROOM_H

#include "Obstruction.h"
#include "plf_colony.h"
#include <complex>
#include <iostream>
#include <algorithm>
#include <string>
#include <deque>
#include "Train.h"

class Mushroom : public Obstruction
{
public:
    Mushroom();
    Mushroom(const std::string& texture_file_name);
    Mushroom(const sf::Vector2f cordinates);
    virtual ~Mushroom() {}
    virtual void run(const sf::RenderTarget& target, const sf::FloatRect globalbounds);
    const sf::Vector2f get_cordinates() const { return this->collision.getPosition(); }
    const sf::FloatRect get_global_bounds() const { return this->sprite->getGlobalBounds(); }
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::Vector2f get_move(Direction movement_direction, std::shared_ptr<sf::CircleShape> sprite, bool up_down);
    virtual bool increment_health(plf::colony<std::shared_ptr<Mushroom>>& mushrooms, plf::colony<std::tuple<std::deque<sf::Sprite>, Direction>>& multiple_centipede_trains);


    /**< functions used in testing software  */
    bool mushroom_global_bounds_test();
    bool mushroom_collision_test();
    bool mushroom_health_test();
    bool mushroom_stationairy_test();
    float get_scale() { return scale; }
    void set_shot_mushroom() { this->shot = true; }
    const unsigned int get_health() const { return this->health; }
    const bool is_shot() const { return this->shot; }

    void set_previous_cordinates() { this->previous_cordinates = this->sprite->getPosition(); }
    const sf::Vector2f get_current_cordinates() { return this->sprite->getPosition(); }
    const sf::Vector2f get_previous_cordinates() { return this->previous_cordinates; }

private:
    //!< Private variables
    unsigned int health{ 0 };
    float scale{ 0.5 };
    bool is_stuck;
    int amount;

    /**< variables used in testing software */
    sf::Vector2f previous_cordinates;
    bool shot{ false };

    std::shared_ptr<sf::Sprite> sprite;
    std::shared_ptr<sf::Texture> texture;
    std::shared_ptr<std::vector<sf::Vector2f>> cordinates;
    std::vector<sf::Vector2f> open_cors;
    sf::CircleShape collision;

    //!< Private Helper functions
    void possible_moves(std::shared_ptr<sf::CircleShape> sprite, Direction movement_direction);
    std::vector<sf::CircleShape> possible_cordinates(float movement_radius, std::shared_ptr<sf::CircleShape> sprite1, Direction movement_direction);
    const sf::Vector2f get_right(std::shared_ptr<sf::CircleShape> sprite, bool up_down, Direction movement_direction);
    bool comparator(sf::Vector2f first, sf::Vector2f last) { return first.y > last.y; }


};

#endif // MUSHROOM_H
