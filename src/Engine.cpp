#include "Engine.h"

/////////////////////////////////////////////////
/// \brief
///
/// \param
/// \param
/// \return
///
/////////////////////////////////////////////////
Engine::Engine()
{
    if (!this->font.loadFromFile("Amiga_Forever.ttf"))
        std::cout << " could not load font from file \n"; 
    this->level.setFont(this->font); 
    this->score.setFont(this->font); 
    this->level.setCharacterSize(20); 
    this->score.setCharacterSize(20); 
    this->score.setStyle(sf::Text::Italic); 
    this->level.setStyle(sf::Text::Italic); 
    this->initialize();
}

/////////////////////////////////////////////////
/// \brief
///
/// \param
/// \param
/// \return
///
/////////////////////////////////////////////////
Engine::~Engine()
{

}

/////////////////////////////////////////////////
/// \brief
///
/// \param
/// \param
/// \return
///
/////////////////////////////////////////////////
void Engine::set_mode()
{
    this->video_mode.reset(new sf::VideoMode(800, 600, 32));
    return;
}

/////////////////////////////////////////////////
/// \brief
///
/// \param
/// \param
/// \return
///
/////////////////////////////////////////////////
void Engine::set_window()
{
    this->window.reset(new sf::RenderWindow(*this->video_mode, "Centipede", sf::Style::Close | sf::Style::Titlebar));
    this->window->setFramerateLimit(60);
    return;
}

/////////////////////////////////////////////////
/// \brief
///
/// \param
/// \param
/// \return
///
/////////////////////////////////////////////////
void Engine::set_event()
{
    this->event.reset(new sf::Event());
    return;
}

/////////////////////////////////////////////////
/// \brief
///
/// \param
/// \param
/// \return
///
/////////////////////////////////////////////////
void Engine::set_player()
{
    this->player.reset(new Player()); 
    return;
}

/////////////////////////////////////////////////
/// \brief
///
/// \param
/// \param
/// \return
///
/////////////////////////////////////////////////
void Engine::set_obstruction_map()
{
    this->obstruction_map.reset(new ObstructionMap(*this->window));
    return;
}

/////////////////////////////////////////////////
/// \brief
///
/// \param
/// \param
/// \return
///
/////////////////////////////////////////////////
void Engine::initialize()
{
    this->set_mode();
    this->set_window();
    this->set_event();
    this->set_player();
    this->set_obstruction_map();
    this->set_background(); 
    return;
}

void Engine::set_background()
{
    this->background_texture.reset(new sf::Texture()); 
    this->background.reset(new sf::Sprite()); 
    this->background->setTextureRect(sf::IntRect(0.f, 0.f, this->window->getSize().x, this->window->getSize().y)); 
    this->background_texture->loadFromFile("back_ground.JPG"); 
    this->background->setTexture(*this->background_texture); 
    this->background->setPosition(0.f, 0.f); 
}

/////////////////////////////////////////////////
/// \brief
///
/// \param
/// \param
/// \return
///
/////////////////////////////////////////////////
void Engine::poll()
{
    while (this->window->pollEvent(*this->event) && (this->event->type == sf::Event::KeyPressed || this->event->type == sf::Event::MouseButtonPressed))
    {
        this->update(); 
        if (this->event->key.code == sf::Keyboard::Escape)
        {
            this->window->close();
        }
    }
    return;
}

/////////////////////////////////////////////////
/// \brief
///
/// \param
/// \param
/// \return
/////////////////////////////////////////////////
void Engine::update()
{
    this->player->run(*this->window);
    auto bullets = this->player->get_bullets();
    this->obstruction_map->run(*this->window, bullets);
    this->player->update_bullets(bullets); 
    if (this->obstruction_map->is_life_or_game_over(this->player->get_global_bounds()))
    {
        this->player->reduce_live_respawn();
        if (this->player->is_game_end())
            game_over = true; 
    }
    this->level = sf::Text("Level: " + std::to_string(this->obstruction_map->get_level()), this->font, 30u);
    this->score = sf::Text("Score: " + std::to_string(this->obstruction_map->get_score()), this->font, 30u);
    this->lives = sf::Text("Lives: " + std::to_string(this->player->get_lives()), this->font, 30u);
    this->level.setPosition(200.f, 0.f); 
    this->lives.setPosition(400.f, 0.f);
    this->level.setScale(0.5f, 0.5f); 
    this->score.setScale(0.5f, 0.5f); 
    this->lives.setScale(0.5f, 0.5f); 
    return;
}

/////////////////////////////////////////////////
/// \brief
///
/// \param
/// \param
/// \return
///
/////////////////////////////////////////////////
void Engine::draw()
{
    //!< clear the window before displaying
    this->window->clear();
    this->window->draw(*this->background); 
    //!< draw all game objects onto the window in Engine
    this->window->draw(*this->player);
    this->window->draw(*this->obstruction_map, sf::RenderStates::Default);
    this->window->draw(this->score);
    this->window->draw(this->level);
    this->window->draw(this->lives);
     //!< display the drawn objects onto the render window object
    this->window->display();
    return;
}

/////////////////////////////////////////////////
/// \brief
///
/// \param
/// \param
/// \return
///
/////////////////////////////////////////////////
void Engine::run()
{
    while (this->window->isOpen() && !game_over)
    {
        this->update();
        this->draw();
        this->poll();
    }
    return;
}





