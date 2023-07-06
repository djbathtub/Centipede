#include "ObstructionMap.h"

/////////////////////////////////////////////////
/// \brief
///
/// \param
/// \param
/// \return
///
/////////////////////////////////////////////////
ObstructionMap::ObstructionMap(sf::RenderTarget& target)
{
    move_engine.reset(new MoveEngine(target)); 
    this->movement_clock.restart();
    this->initialize();
    did_change = false;

}

/////////////////////////////////////////////////
/// \brief
///
/// \param
/// \param
/// \return
///
/////////////////////////////////////////////////
ObstructionMap::~ObstructionMap()
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
void ObstructionMap::set_map()
{
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
void ObstructionMap::initialize()
{
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
void ObstructionMap::update()
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
void ObstructionMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*this->move_engine); 
    return;
}

void ObstructionMap::update_bullets(plf::colony<Bullet>& bullets)
{
    this->move_engine->handle_bullets(bullets);
    return;
}

const bool ObstructionMap::is_life_or_game_over(const sf::FloatRect& player) const
{
    return this->move_engine->check_game_over(player);
}

/////////////////////////////////////////////////
/// \brief
///
/// \param
/// \param
/// \return
///
/////////////////////////////////////////////////
void ObstructionMap::run(sf::RenderTarget& target, plf::colony<Bullet>& bullets)
{
    auto level_delay = (this->level - 1);
    this->move_engine->handle_bullets(bullets);
    if (this->movement_clock.getElapsedTime().asSeconds() >= 0.05 - level_delay )
    {
        this->move_engine->move(bullets); 
        this->movement_clock.restart();
    }
    return;
}

void ObstructionMap::poll(sf::Event event, const sf::RenderTarget& target)
{

}

