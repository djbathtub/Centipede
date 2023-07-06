
#include "GameSimulator.h"

/** \brief Check if the distance between Centipede segments is 20.f, or the diameter
 *
 * \param
 * \param
 * \return
 *
 */

void GameSimulator::poll()
{
    while (this->window->pollEvent(this->event) && (this->event.type == sf::Event::KeyPressed || this->event.type == sf::Event::MouseButtonPressed))
    {
        if (this->event.key.code == sf::Keyboard::Escape)
        {
            this->window->close();
        }
    }
    return;
}



bool GameSimulator::train_movement_distance_test(plf::colony<std::tuple<std::deque<sf::Sprite>, Direction>> multiple_centipede_trains)
{
    for (const auto& i : multiple_centipede_trains)
    {
        auto k = std::get<0>(i).begin();
        for (auto j = std::get<0>(i).begin(); j != std::get<0>(i).end() && k != std::get<0>(i).end(); j++)
        {
            auto distance = 0.f;
            k = j + 1;
            if (k != std::get<0>(i).end())
                distance = std::abs(std::complex<float>(k->getPosition().x - j->getPosition().x, k->getPosition().y - j->getPosition().y));
            else
                break;
            if (distance == 20.f)
                continue;
            else
                return false;
        }
    }
    return true;
}

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
bool GameSimulator::train_movement_collision_test(plf::colony<std::tuple<std::deque<sf::Sprite>, Direction>> multiple_centipede_trains)
{
    for (const auto& i : multiple_centipede_trains)
    {
        auto k = std::get<0>(i).begin();
        for (auto j = std::get<0>(i).begin(); j != std::get<0>(i).end() && k != std::get<0>(i).end(); j++)
        {
            auto collision = true;
            auto overlap = sf::FloatRect();
            k = j + 1;
            if (k != std::get<0>(i).end())
                collision = j->getGlobalBounds().intersects(k->getGlobalBounds(), overlap);
            else
                break;
            if (!collision || overlap.width < 0.f || overlap.height < 0.f)
                continue;
            else if (collision)
                return false;
        }
    }
    return true;
}

/** \brief Returns true when the centipede trains does not collide with any of the mushrooms
 *  false when they do collide, so the test then fails
 * \param
 * \param
 * \return
 *
 */

bool GameSimulator::train_mushroom_collision_test(plf::colony<std::shared_ptr<Mushroom>> mushrooms, plf::colony<std::tuple<std::deque<sf::Sprite>, Direction>> multiple_centipede_trains)
{
    for (auto& i : multiple_centipede_trains)
    {
        for (auto& j : std::get<0>(i))
        {
            for (auto& k : mushrooms)
            {
                auto overlap = sf::FloatRect();
                auto check = j.getGlobalBounds().intersects(k->get_global_bounds(), overlap);
                if (!check)
                {
                    continue;
                }
                else
                    return false;
            }
        }
    }
    return true;
}

/** \brief Checks that DT BOMBS and mushrooms do not move
 *dd
 * \param
 * \param
 * \return
 *
 */
bool GameSimulator::mushroom_movement_test(plf::colony<std::shared_ptr<Mushroom>> mushrooms, unsigned int& pass_rate_movement_mushrooms)
{
    for (const auto& i : mushrooms)
    {
        if (i->get_current_cordinates() != i->get_previous_cordinates() && !i->is_shot())
        {
            return false;
        }
    }
    ++pass_rate_movement_mushrooms;
    return true;
}

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
bool GameSimulator::mushroom_window_bounds_test(plf::colony<std::shared_ptr<Mushroom>> mushrooms, unsigned int& pass_rate_window_bounds_mushrooms)
{
    for (const auto& i : mushrooms)
    {
        if (i->get_current_cordinates().x < 10.f || i->get_current_cordinates().x > 790.f || i->get_current_cordinates().y < 5.f || i->get_current_cordinates().y > 595.f)
        {
            return false;
        }
    }
    ++pass_rate_window_bounds_mushrooms;
    return true;
}

/** \brief Testing software for the health mechanic, and lives mechanic
 * also detects that if a bullet has been shot certain criteria must be met
   also tests the scaling mechanic of the mushroom, when a bullet has collided with the
   mushroom.
 * \param
 * \param
 * \return
 *
 */
bool GameSimulator::mushroom_bullet_collision_test(plf::colony<std::shared_ptr<Mushroom>> mushrooms, unsigned int& pass_rate_collision_mushrooms)
{
    for (const auto& i : mushrooms)
    {
        if (i->is_shot() && i->get_health() == 0)
        {
            return false;
        }
        else if ((!i->is_shot()) && (!i->get_health() == 0))
        {
            return false;
        }
        else if (i->get_health() >= 3)
        {
            return false;
        }
        else if (i->is_shot() && i->get_scale() == 0.5)
        {
            return false;
        }
    }
    ++pass_rate_collision_mushrooms;
    return true;
}


/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
bool GameSimulator::train_window_bounds_test(plf::colony<std::tuple<std::deque<sf::Sprite>, Direction>> multiple_centipede_trains)
{
    for (auto& i : multiple_centipede_trains)
    {
        for (auto& j : std::get<0>(i))
        {
            if (j.getPosition().x < 0.f || j.getPosition().x > 800.f || j.getPosition().y < 0.f || j.getPosition().y > 600.f)
            {
                return false;
            }
        }
    }
    return true;
}

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */

/// @brief 
/// @return 
bool GameSimulator::bullet_movement_test()
{
    return false;
}

/// @brief 
/// @return 
bool GameSimulator::bullet_collision_test()
{
    return false;
}

/// @brief 
/// @return 
bool GameSimulator::bullet_window_bounds_test()
{
    return false;
}

/// @brief 
/// @return 
bool GameSimulator::bullet_spawn_test()
{
    return false;
}

/// @brief 
/// @return 
bool GameSimulator::bullet_cooldown_test()
{
    return false;
}

/// @brief 
/// @return 
bool GameSimulator::player_movement_test(sf::Vector2f previous_cordinates)
{
    std::unique_ptr<sf::Sprite> sprite; 
    sprite.reset(new sf::Sprite(this->player.get_sprite())); 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        sprite->move(10.f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        sprite->move(0.f, -10.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        sprite->move(-10.f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        sprite->move(0.f, 10.f);
    }
    if (sprite->getPosition() == previous_cordinates)
    {
        ++this->number_of_passed_cases;
        return true;
    }
    else
    {
        ++this->number_of_failed_cases; 
        return false;
    }
}

/// @brief 
/// @return 
bool GameSimulator::player_collision_test()
{
    return false;
}

/// @brief 
/// @return 
bool GameSimulator::player_window_bounds_test()
{
    if (this->player.get_cordinates().x < 10.f || this->player.get_cordinates().x > 790.f || this->player.get_cordinates().y < 5.f || this->player.get_cordinates().y > 595.f)
    {
        ++this->number_of_failed_cases; 
        return false;
    }
    ++this->number_of_passed_cases; 
    return true;
}

/// @brief 
/// @return 
bool GameSimulator::player_spawn_test()
{
    return false;
}

/// @brief 
/// @return 
bool GameSimulator::player_lives_test()
{
    return false;
}

/// @brief 
/// @return 
bool GameSimulator::DTBombs_movement_test()
{
    return false;
}

/// @brief 
/// @return 
bool GameSimulator::DTBombs_collision_test()
{
    return false;
}

/// @brief 
/// @return 
bool GameSimulator::DTBombs_window_bounds_test()
{
    return false;
}

/// @brief 
/// @return 
bool GameSimulator::DTBombs_blast_radius_test()
{
    return false;
}

/// @brief 
void GameSimulator::run_player_only()
{
    this->number_of_frames_to_test = 10; 
    auto movement_passed = 0; 
    auto bounds_passed = 0; 
    std::cout << " Press W(up),S(down),A(left),D(right) keys to test the movement functions of the player \n"; 
    for (auto i = 0; i < number_of_frames_to_test; true)
    {
        if (this->window->pollEvent(this->event) && this->event.type == sf::Event::KeyPressed)
        {
            auto previous_cordinates = this->player.get_cordinates();
            if ((this->event.key.code == sf::Keyboard::Escape))
            {
                std::cout << this->number_of_passed_cases;
                return;
            }
            this->player.run(*this->window);
            ++i;
            this->number_of_passed_cases = 0;
            this->player_movement_test(previous_cordinates);
            movement_passed += this->number_of_passed_cases;
            this->number_of_passed_cases = 0;
            this->player_window_bounds_test();
            bounds_passed += this->number_of_passed_cases;
        }
        while (!this->event.type == sf::Event::KeyPressed)
        {
            void;
        }
    }
    std::cout << bounds_passed/number_of_frames_to_test * 100; 
    return;
}

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
void GameSimulator::run_player_bullets()
{
    this->number_of_frames_to_test = 10;
    auto movement_passed_player = 0;
    auto bounds_passed_player = 0;
    auto bounds_passed_bullets = 0; 
    auto movement_passed_bullets = 0; 

    std::cout << " Press W(up),S(down),A(left),D(right) keys to test the movement functions of the player and whether it remains inside the window  \n";
    std::cout << " Press the left mouse button or spacebar to test the movement functions of the bullet and whether it remains inside the window \n";

    for (auto i = 0; i < number_of_frames_to_test; true)
    {
        if (this->window->pollEvent(this->event) && (this->event.type == sf::Event::KeyPressed || this->event.type == sf::Event::MouseButtonPressed))
        {
            auto previous_cordinates_player = this->player.get_cordinates();
            if ((this->event.key.code == sf::Keyboard::Escape))
            {
                std::cout << this->number_of_passed_cases;
                return;
            }
            this->player.run(*this->window);
            ++i;
            this->number_of_passed_cases = 0;
            this->player_movement_test(previous_cordinates_player);
            movement_passed_player += this->number_of_passed_cases;
            this->number_of_passed_cases = 0;
            this->bullet_movement_test(previous_cordinates_player);
            movement_passed_player += this->number_of_passed_cases;
            this->number_of_passed_cases = 0;
            this->player_window_bounds_test();
            bounds_passed_player += this->number_of_passed_cases;
        }
        while (!this->event.type == sf::Event::KeyPressed)
        {
            void;
        }
    }
    std::cout << bounds_passed_player / number_of_frames_to_test * 100;
    return;
}

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */


void GameSimulator::run_player_dtbombs()
{
    return;
}

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */


void GameSimulator::run_player_centipede()
{
    return;
}

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */


void GameSimulator::run_player_bullets_mushrooms()
{
    return;
}

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */


void GameSimulator::run_player_bullets_mushrooms_centipede()
{
    return;
}

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */


void GameSimulator::run_player_bullets_mushrooms_centipede_dtbombs()
{
    return;
}

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */


void GameSimulator::run_bullets_only()
{
    return;
}

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */


void GameSimulator::run_bullets_mushrooms()
{
    return;
}

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */


void GameSimulator::run_bullets_dtbombs()
{
    return;
}

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */


void GameSimulator::run_bullets_mushrooms_centipede()
{
    return;
}

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */


void GameSimulator::run_bullets_mushrooms_centipede_dtbombs()
{
    return;
}

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */


void GameSimulator::run_mushrooms_only()
{
    return;
}

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
void GameSimulator::run_mushrooms_centipede()
{
    return;
}

/// @brief 
void GameSimulator::run_mushrooms_centipede_dtbombs()
{
    return; 
}

/// @brief 
void GameSimulator::run_mushrooms_bullets()
{
    return; 
}

/// @brief 
/// @param game_object 
GameSimulator::GameSimulator(ObjectToTest game_object)
{
    this->window.reset(new sf::RenderWindow(sf::VideoMode(800, 600, 32), "Centipede", sf::Style::None)); 
    this->window->setFramerateLimit(60); 
    this->move_engine.reset(new MoveEngine(*this->window)); 
}

/// @brief 
GameSimulator::~GameSimulator()
{

}

/// @brief 
/// @param desired_simulation 
void GameSimulator::run(GameStates desired_simulation)
{
    while (this->window->isOpen() && !game_over)
    {
        this->poll();
    }
    return; 
}

/// @brief 
/// @param desired_testing_software 
void GameSimulator::run_testing_software(const Test_obj& desired_testing_software)
{
    return; 
}

/// @brief 
/// @return 
unsigned int GameSimulator::get_number_of_passed_cases()
{
    return 0;
}

/// @brief 
/// @return 
unsigned int GameSimulator::get_amount_of_frames_tested()
{
    return 0;
}

/// @brief 
/// @return 
float GameSimulator::get_pass_rate()
{
    return 0.0f;
}

/// @brief 
/// @return 
float GameSimulator::get_failure_rate()
{
    return 0.0f;
}
