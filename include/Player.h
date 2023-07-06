#ifndef PLAYER_H
#define PLAYER_H


#include "Bullet.h"
#include "Obstruction.h"
#include "Mushroom.h"
#include "plf_colony.h"
#include <list>
#include <tuple>


class Player : public Obstruction
{
public:
    Player();
    ~Player();
    void run(const sf::RenderTarget& window);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    plf::colony<Bullet>& get_bullets() { return this->bullets;  }
    void update_bullets(plf::colony<Bullet> new_bullets) { this->bullets.clear(); this->bullets.splice(new_bullets);   }
    const sf::FloatRect get_global_bounds() const { return this->sprite->getGlobalBounds();  }
    void reduce_live_respawn(); 
    const bool is_game_end() { return this->end_game; }
    const unsigned int get_lives() { return this->lives;  }
    const sf::Vector2f get_cordinates() { return this->sprite->getPosition();  }
    sf::Sprite get_sprite() { return *this->sprite;  }
private:
    //!< Private variables
    std::shared_ptr<sf::Sprite> sprite; 
    std::shared_ptr<sf::Texture> texture; 
    plf::colony<Bullet> bullets;
    std::vector<sf::FloatRect> bullet_globalbounds; 
    sf::Clock bullet_clock;
    const float cooldown_shooting_time{ 0.2f };
    const sf::Vector2f player_size{ 10.f,20.f }; 
    unsigned int score{ 0 }; 
    unsigned int lives{ 3 }; 
    bool end_game{ false }; 

    //!< Private member functions
    void update();
    void poll();
    void shoot(); 
    void enforce_window_bounds(const sf::RenderTarget& window); 
    void update_bullets(); 
    //!< Initialization funtions
    void initialize();

};

#endif // PLAYER_H
