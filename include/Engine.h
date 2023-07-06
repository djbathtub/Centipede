#ifndef ENGINE_H
#define ENGINE_H

#include "ObstructionMap.h"
#include "Player.h"
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <iostream>
#include <thread>
#include <array>
#include <memory>

/////////////////////////////////////////////////
/// \brief Game engine class runs the game
///
/// \param
/// \param
/// \return
///
/////////////////////////////////////////////////
class Engine
{
public:
    Engine();
    virtual ~Engine();
    void run();
private:
    //!< Private variables
    std::unique_ptr<ObstructionMap> obstruction_map;
    std::unique_ptr<sf::Event> event;
    std::unique_ptr<Player> player; 
    std::unique_ptr<sf::RenderWindow> window;
    std::unique_ptr<sf::VideoMode> video_mode;
    std::unique_ptr<sf::Sprite> background; 
    std::unique_ptr<sf::Texture> background_texture; 
    sf::Text level;
    sf::Text score; 
    sf::Text lives;
    sf::Font font; 
    bool game_over{ false };

    //!< Private functions

    //!< Initialization functions(called once)
    void set_window();
    void set_event();
    void set_mode();
    void set_player();
    void set_obstruction_map();
    void initialize();
    void set_background(); 

    //!< Functions called repeatedly to play Centipede
    void poll();
    void update();
    void draw();
};

#endif // ENGINE_H
