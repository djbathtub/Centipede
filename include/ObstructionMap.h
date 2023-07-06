#ifndef OBSTRUCTIONMAP_H
#define OBSTRUCTIONMAP_H
#include "Centipede.h"
#include "Bullet.h"
#include "Mushroom.h"
#include <vector>
#include <tuple>
#include <cmath>
#include <complex>
#include <map>
#include <tuple>
#include <algorithm>
//#include "CentipedeTrain.h"
#include "Player.h"
#include "Train.h"
#include "MoveEngine.h"
//using tuple_pointer = std::tuple<std::shared_ptr<Mushroom>, std::shared_ptr<Centipede>>;


class ObstructionMap : public sf::Drawable
{
public:
    ObstructionMap(sf::RenderTarget& target);
    ~ObstructionMap();
    void run(sf::RenderTarget& target, plf::colony<Bullet>& bullets);
    void poll(sf::Event event, const sf::RenderTarget& target);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update_bullets(plf::colony<Bullet>& bullets);
    const bool is_life_or_game_over(const sf::FloatRect& player) const; 
    const unsigned int get_score() const { return this->move_engine->get_total_score();  }
    const unsigned int get_level() const { return this->move_engine->get_level(); }
private:
    //!< Private variables
    std::unique_ptr<MoveEngine>  move_engine;

    sf::Clock movement_clock;
    unsigned int sizet{0};
    bool did_change = true; 
    unsigned int level = { 1 }; 
    bool down_up = true; 
    float speed;

    //!< Private functions
    //!< Initialization functions
    void set_map();
    void initialize();

    //!< Functions which run repeatedly to play Centipede within ObstructionMap class
    void update();

};

#endif // OBSTRUCTIONMAP_H
