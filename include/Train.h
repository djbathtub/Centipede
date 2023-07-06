#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <iostream>

enum class Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    CHANGE_RIGHT,
    CHANGE_LEFT,
};

#include "Mushroom.h"
#include "Bullet.h"
#include "plf_colony.h"
#include <tuple>
#include <deque>
#include <array>
#include <ctime>
#include <memory>
#include <vector>
#include <list>

class Mushroom;

class Train : public sf::Drawable
{
public:
    Train();
    ~Train() {};
    void run(plf::colony<std::shared_ptr<Mushroom>>& mushroom_maps, plf::colony<Bullet>& bullets);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    bool is_shot(plf::colony<Bullet>& bullets);
    void new_handle_train(plf::colony<Bullet>& bullets, plf::colony<std::shared_ptr<Mushroom>>& mushrooms);
    const bool handle_player_collisions(const sf::FloatRect& player) const;
    const unsigned int add_score() const;
    const unsigned int get_level() const { return this->level; }
    void handle_mushroom_collisions(plf::colony<std::shared_ptr<Mushroom>>& mushroom_maps, plf::colony<Bullet>& bullets);

private:
    // new variables
    plf::colony<std::tuple<std::deque<sf::Sprite>, Direction>> multiple_centipede_trains;
    std::array<sf::RectangleShape, 6> screen_walls1;
    std::array<sf::Vector2f, 6> direction_offsets_new;
    plf::colony<std::shared_ptr<Mushroom>> collided;
    std::shared_ptr<sf::Texture> texture;
    unsigned int player_score{ 0 };
    unsigned int level{ 0 };

    void new_move(std::tuple<std::deque<sf::Sprite>, Direction>& i);

    // new functions
    void init_multiple_centipede_trains();
    void init_wall_movements();
    void init_texture();
    const sf::Sprite& get_leader(const plf::colony<std::tuple<std::deque<sf::Sprite>, Direction>>::iterator& single_train);
    const bool new_update_collide_enum(std::tuple<std::deque<sf::Sprite>, Direction>& single_train, bool mushroom);
    bool new_ison(plf::colony<std::shared_ptr<Mushroom>>& mushroom_maps);
    void move_around_mushroom(std::tuple<std::deque<sf::Sprite>, Direction>& single_train, Mushroom& mushroom_collided, std::shared_ptr<sf::CircleShape> copy);
    bool is_mushroom(sf::Sprite& potential_mushroom);
    void new_trains(std::tuple<std::deque<sf::Sprite>, Direction>& train_row);
    void updated_train();
    bool is_empty();

    friend Direction operator!(const Direction& direction_invert)
    {
        if (direction_invert == Direction::LEFT)
            return Direction::UP;
        else if (direction_invert == Direction::RIGHT)
            return Direction::DOWN;
        else if (direction_invert == Direction::DOWN)
            return Direction::LEFT;
        else if (direction_invert == Direction::UP)
            return Direction::RIGHT;
    }
};

