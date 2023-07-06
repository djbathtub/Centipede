#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <iostream>
#include <array>
#include "Mushroom.h"
#include "plf_colony.h"
#include "Train.h"
#include "Player.h"
#include "Bullet.h"
#include "MoveEngine.h"

enum class GameStates
{
    MUSHROOMS_ONLY,
    BULLETS_ONLY,
    CENTIPEDE_ONLY,
    DTBOMBS_ONLY,
    CENTIPEDE_MUSHROOMS,
    CENTIPEDE_MUSHROOMS_DTBOMBS,
    CENTIPEDE_MUSHROOMS_BULLETS,
    PLAYER_ONLY,
    PLAYER_BULLETS,
    PLAYER_BULLETS_MUSHROOMS,
    PLAYER_CENTIPEDE_BULLETS_MUSHROOMS,
    DTBOMBS_BULLETS_MUSHROOMS,
    DTBOMBS_BULLETS_CENTIPEDE_MUSHROOMS_PLAYER,
    DTBOMBS_PLAYER_BULLETS,
};

enum class TestType
{
    MOVEMENT_TEST,
    COLLISION_TEST,
    DIRECTION_CHANGE_TEST,
    STATE_CHANGE_TEST,
    DESTROYING_TEST,
    LIVES_TEST,
};

enum class ObjectToTest
{
    CENTIPEDE,
    MUSHROOMS,
    DT_BOMBS,
    BULLETS,
    PLAYER,
};

struct Test_obj
{
    TestType testing_type;
    ObjectToTest object_to_test;
    GameStates state_to_test;
};


class GameSimulator
{
private:
    /**< Variables used to simulate a specific game state */
    std::unique_ptr<MoveEngine> move_engine;
    Train train_;
    Player player;
    std::vector<Bullet> test_bullets;
    std::unique_ptr<sf::RenderWindow> window;
    sf::VideoMode video_mode; 
    sf::Event event;

    /**< Variables used to indicate which states in the game to test for a specific object */

    unsigned int level_to_run_test_towards{ 0 };
    unsigned int number_of_passed_cases{ 0 };
    unsigned int number_of_failed_cases{ 0 };
    unsigned int number_of_frames_tested{ 0 };
    unsigned int number_of_frames_to_test{ 0 };
    bool game_over{ false }; 

    /**<  For example the tolerance allowed in the test, with collisions, how much
    is the object allowed to overlap ?, for the test to still deliver a pass result */
    float test_tolerance;

    std::vector<Test_obj> all_centipede_tests;
    std::vector<Test_obj> all_player_tests;
    std::vector<Test_obj> all_bullets_tests;
    std::vector<Test_obj> all_mushroom_tests;
    std::vector<Test_obj> all_dt_bombs_tests;

    /**< Methods used in testing software */
    void poll(); 

    /**< Methods used to conduct the tests for the train(Centipede) */
    bool train_movement_distance_test(plf::colony<std::tuple<std::deque<sf::Sprite>, Direction>> multiple_centipede_trains);
    bool train_movement_collision_test(plf::colony<std::tuple<std::deque<sf::Sprite>, Direction>> multiple_centipede_trains);
    bool train_mushroom_collision_test(plf::colony<std::shared_ptr<Mushroom>> mushrooms, plf::colony<std::tuple<std::deque<sf::Sprite>, Direction>> multiple_centipede_trains);
    bool train_window_bounds_test(plf::colony<std::tuple<std::deque<sf::Sprite>, Direction>> multiple_centipede_trains);

    /**< Methods used to conduct the tests for the mushrooms  */
    bool mushroom_movement_test(plf::colony<std::shared_ptr<Mushroom>> mushrooms, unsigned int& pass_rate_movement_mushrooms);
    bool mushroom_window_bounds_test(plf::colony<std::shared_ptr<Mushroom>> mushrooms, unsigned int& pass_rate_window_bounds_mushrooms);
    bool mushroom_bullet_collision_test(plf::colony<std::shared_ptr<Mushroom>> mushrooms, unsigned int& pass_rate_collision_mushrooms);

    /**< Methods used to test bullets  */
    bool bullet_movement_test();
    bool bullet_collision_test();
    bool bullet_window_bounds_test();
    bool bullet_spawn_test();
    bool bullet_cooldown_test();

    /**< Methods used to test player  */
    bool player_movement_test(sf::Vector2f previous_cordinates);
    bool player_collision_test();
    bool player_window_bounds_test();
    bool player_spawn_test();
    bool player_lives_test();

    /**< Methods used to test DTBombs */
    bool DTBombs_movement_test();
    bool DTBombs_collision_test();
    bool DTBombs_window_bounds_test();
    bool DTBombs_blast_radius_test();

    /**< Methods used to simulate the given game states for player */
    void run_player_dtbombs();
    void run_player_centipede();
    void run_player_bullets_mushrooms();
    void run_player_bullets_mushrooms_centipede();
    void run_player_bullets_mushrooms_centipede_dtbombs();

    /**< Methods used to simulate the game states for bullets */
    void run_bullets_only();
    void run_bullets_mushrooms();
    void run_bullets_dtbombs();
    void run_bullets_mushrooms_centipede();
    void run_bullets_mushrooms_centipede_dtbombs();

    /**< Methods used to simulate the game states for mushrooms */
    void run_mushrooms_only();
    void run_mushrooms_centipede();
    void run_mushrooms_centipede_dtbombs();
    void run_mushrooms_bullets();


public:
    GameSimulator(ObjectToTest game_object);
    ~GameSimulator();
    void run_player_only();
    void run_player_bullets();
    void run(GameStates desired_simulation);
    void run_testing_software(const Test_obj& desired_testing_software);
    unsigned int get_number_of_passed_cases();
    unsigned int get_amount_of_frames_tested();
    float get_pass_rate();
    float get_failure_rate();
};
