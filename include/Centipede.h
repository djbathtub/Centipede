#ifndef CENTIPEDE_H
#define CENTIPEDE_H

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <iostream>
#include <array>
#include <ctime>
#include <complex>
#include "Mushroom.h"
#include "Obstruction.h"
#include <list>
#include <vector>
#include <memory>

class CentipedeHead : public Obstruction
{
public:
    CentipedeHead();
    ~CentipedeHead();
    void run(sf::RenderTarget& target);
    enum class Direction
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
    };
    const sf::Vector2f get_previous_cordinates() const { return previous_cordinates; }
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void feed_mushroom_globalbounds(std::vector<std::shared_ptr<Mushroom>> mushroom_bounds, bool did_change);
private:
    // Private helper functions 
    void init();
    void move();
    void collide(Mushroom check_collision) {}
    void window_bounds(sf::RenderTarget& target) {}
    const bool check_shape(sf::CircleShape shape, bool ishead); 
    void update_previous_positions();
    void check_train(); 

    // Private member variables
    sf::Vector2f previous_cordinates;
    const double pi = { std::acos(-1) };
    std::vector<std::shared_ptr<sf::Sprite>> complete_centipede;
    std::vector<std::shared_ptr<sf::Sprite>>::iterator tail;
    std::vector<std::shared_ptr<sf::Sprite>>::iterator head;
    std::shared_ptr<sf::Texture> texture;
    std::list<std::shared_ptr<sf::FloatRect>> mushroom_bounds;
    std::vector<sf::CircleShape> possible_cordinates(sf::Vector2f cordinates, float movement_radius, bool ishead);
    std::vector<sf::Vector2f> previous_positions;
    Direction train_direction{Direction::RIGHT};
    sf::Clock movement_clock; 
    bool istrain;
};

#endif


/*
#include "Obstruction.h"
#include "Bullet.h"
#include "Mushroom.h"
#include <vector>
#include <tuple>
#include <cmath>
#include <complex>

/*

class Centipede : public Obstruction
{
public:
    Centipede();

    ~Centipede();

    void run(const sf::RenderTarget& target, std::array<sf::CircleShape, 360> possible_moves);

    void run_head(const sf::RenderTarget& target);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    const sf::FloatRect get_globalbound() const { return this->sprite->getGlobalBounds(); }

    const sf::Vector2f get_cordinates() const { return this->centipede->getPosition(); }

    float get_radius() const { return this->centipede->getRadius(); }

    const bool get_head() const { return this->isHead; }

    void set_head(bool value) { this->isHead = value;  }

    void clear_head() { this->isHead = false; }

    void set_postion(sf::Vector2f cors) { this->centipede->setPosition(cors);  }

    Boundry get_boundry() { return this->boundry;  }

    void set_nearby_mushrooms(std::vector<std::shared_ptr<Mushroom>> mushrooms);

    std::tuple<sf::Vector2f,sf::Vector2f> handle_bullets(const std::vector<Bullet> bullet); 

    void pick_move(std::array<sf::CircleShape, 16> possible_moves);

private:
    //!< Private functions
    bool get_open(const sf::FloatRect globalbounds);
    void move(const sf::FloatRect globalbounds, const sf::RenderTarget& target);
    void revert(float xco, float yco);
    bool move_when_collide(const sf::FloatRect global_bounds, int sign_);
    void initialize_movement_combinations(float movement_radius);
    void initialize(const sf::Vector2f cordinates);
    void move(const sf::Vector2f cordinates) { this->centipede->move(cordinates); };
   // bool pick_move(const sf::CircleShape potential_move); 
    void move_down();
    void enforce_window_bounds(const sf::RenderTarget& target);

    //!< Private variables
    std::shared_ptr<sf::CircleShape> centipede;
    std::shared_ptr<sf::Sprite> sprite; 
    std::shared_ptr<sf::Texture> texture; 
    std::vector<std::shared_ptr<std::tuple<sf::FloatRect, sf::Vector2f>>> nearby_mushrooms;
    bool isHead;
    int sign{1};

    std::array<sf::Vector2f, 21> movement_combinations;
    Boundry copy_boundry{Boundry::NONE};
};

#endif // CENTIPEDE_H
*/
