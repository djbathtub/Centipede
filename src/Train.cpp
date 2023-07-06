#include "Train.h"

Train::Train()
{
    this->init_wall_movements();
    this->init_texture();
    this->init_multiple_centipede_trains();
}

void Train::run(plf::colony<std::shared_ptr<Mushroom>>& mushroom_maps, plf::colony<Bullet>& bullets)
{
    if (this->is_empty())
    {
        this->init_multiple_centipede_trains();
    }
    this->new_handle_train(bullets, mushroom_maps);
    mushroom_maps.splice(this->collided);
    this->new_ison(mushroom_maps);
    return;
}

void Train::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto& i : this->multiple_centipede_trains)
    {
        for (const auto& j : std::get<0>(i))
            target.draw(j, sf::RenderStates::Default);
    }
    return;
}

void Train::new_move(std::tuple<std::deque<sf::Sprite>, Direction>& i)
{
    if (new_update_collide_enum(i, false))
    {
        return;
    }
    else if (!new_update_collide_enum(i, false))
    {
        std::get<0>(i).back().move(this->direction_offsets_new.at((int)std::get<1>(i)));
        return;
    }
}

void Train::init_multiple_centipede_trains()
{
    ++this->level;
    auto length_of_train = 10;
    auto amount_of_trains = 1;
    auto train_init = std::deque<sf::Sprite>();
    auto xpos = 100.f;
    for (size_t i = 0; i < length_of_train; i++)
    {
        train_init.push_back(sf::Sprite());
        train_init.back().setOrigin(10.f, 10.f);
        train_init.back().setTexture(*this->texture, false);
        train_init.back().setScale(0.05f, 0.05f);
        train_init.back().setPosition(xpos, 10.f);
        xpos += 20.f;
    }
    for (auto i = 0; i < amount_of_trains; i++)
    {
        this->multiple_centipede_trains.insert(std::tuple<std::deque<sf::Sprite>, Direction>(train_init, Direction::RIGHT));
    }
    return;
}

void Train::init_wall_movements()
{
    this->screen_walls1 = { sf::RectangleShape(sf::Vector2f(800u, 1u)), sf::RectangleShape(sf::Vector2f(800u,1u)), sf::RectangleShape(sf::Vector2f(1u, 600u)), sf::RectangleShape(sf::Vector2f(1u, 600u)), sf::RectangleShape(sf::Vector2f(1u, 600u)), sf::RectangleShape(sf::Vector2f(1u, 600u)) };
    this->screen_walls1.at((int)Direction::RIGHT).setPosition(sf::Vector2f(799.f, 0.f));
    this->screen_walls1.at((int)Direction::DOWN).setPosition(sf::Vector2f(0.f, 600.f));
    this->screen_walls1.at((int)Direction::UP).setPosition(sf::Vector2f(0.f, 0.f));
    this->screen_walls1.at((int)Direction::LEFT).setPosition(sf::Vector2f(0.f, 0.f));
    this->screen_walls1.at((int)Direction::CHANGE_RIGHT).setPosition(sf::Vector2f(799.f, 0.f));
    this->screen_walls1.at((int)Direction::CHANGE_LEFT).setPosition(sf::Vector2f(0.f, 0.f));
    this->direction_offsets_new =
    {
      sf::Vector2f(0.f, -20.f),
      sf::Vector2f(0.f, 20.f),
      sf::Vector2f(-20.f, 0.f),
      sf::Vector2f(20.f, 0.f),
      sf::Vector2f(0.f, 20.f),
      sf::Vector2f(0.f, 20.f),
    };
    return;
}

void Train::init_texture()
{
    this->texture = std::shared_ptr<sf::Texture>(new sf::Texture());
    if (!this->texture->loadFromFile("Moons.png"))
        std::cout << " error \n";
    return;
}

const bool Train::new_update_collide_enum(std::tuple<std::deque<sf::Sprite>, Direction>& single_train, bool is_mushroom)
{
    if (this->screen_walls1.at((int)std::get<1>(single_train)).getGlobalBounds().intersects((std::get<0>(single_train).back()).getGlobalBounds()) || std::get<1>(single_train) == Direction::DOWN || std::get<1>(single_train) == Direction::UP || std::get<1>(single_train) == Direction::CHANGE_LEFT || std::get<1>(single_train) == Direction::CHANGE_RIGHT)
    {
        if (std::get<1>(single_train) == Direction::RIGHT || std::get<1>(single_train) == Direction::LEFT || is_mushroom || std::get<1>(single_train) == Direction::CHANGE_LEFT || std::get<1>(single_train) == Direction::CHANGE_RIGHT)
        {
            (std::get<0>(single_train).back()).move(sf::Vector2f(0.f, 20.f));
        }
        if (std::get<1>(single_train) == Direction::RIGHT || std::get<1>(single_train) == Direction::CHANGE_RIGHT)
        {
            std::get<1>(single_train) = Direction::DOWN;
            return true;
        }
        else if (std::get<1>(single_train) == Direction::LEFT || std::get<1>(single_train) == Direction::CHANGE_LEFT)
        {
            std::get<1>(single_train) = Direction::UP;
            return true;
        }
        else if (std::get<1>(single_train) == Direction::DOWN || std::get<1>(single_train) == Direction::UP)
        {
            auto direction_invert = std::get<1>(single_train);
            if (direction_invert == Direction::DOWN)
                std::get<1>(single_train) = Direction::LEFT; 
            else if (direction_invert == Direction::UP)
                std::get<1>(single_train) = Direction::RIGHT;
            (std::get<0>(single_train).back()).move(this->direction_offsets_new.at((int)std::get<1>(single_train)));
            return true;
        }
    }
    return false;
}

void Train::move_around_mushroom(std::tuple<std::deque<sf::Sprite>, Direction>& single_train, Mushroom& mushroom_collided, std::shared_ptr<sf::CircleShape> copy)
{
    auto check = mushroom_collided.get_move((Direction)std::get<1>(single_train), copy, false);
    std::get<0>(single_train).back().setPosition(mushroom_collided.get_move((Direction)std::get<1>(single_train), copy, false));
}

bool Train::is_mushroom(sf::Sprite& potential_mushroom)
{
    for (const auto& i : this->collided)
    {
        if (potential_mushroom.getPosition() == i->get_cordinates())
        {
            return true;
        }
    }
    return false;
}

bool Train::new_ison(plf::colony<std::shared_ptr<Mushroom>>& mushroom_maps)
{
    std::shared_ptr<sf::CircleShape> tstsprite(new sf::CircleShape(10.f, 30u));
    tstsprite->setOrigin(10.f, 10.f);
    auto value = false;
    auto check = 0u;
    bool did_move = { false };
    for (auto& i : this->multiple_centipede_trains)
    {
        auto previous_leader_cordinates = std::get<0>(i).back().getPosition();
        tstsprite->setPosition(std::get<0>(i).back().getPosition() + this->direction_offsets_new.at(((int)std::get<1>(i))));
        did_move = false;
        std::get<0>(i).front().setPosition(previous_leader_cordinates);
        std::get<0>(i).push_back(std::get<0>(i).front());
        std::get<0>(i).pop_front();
        for (auto& j : mushroom_maps)
        {
            if (j->get_global_bounds().intersects(tstsprite->getGlobalBounds()))
            {
                move_around_mushroom(i, *j, tstsprite);
                did_move = true;
                break;
            }
        }
        if (mushroom_maps.empty() || !did_move)
        {
            this->new_move(i);
        }
    }
    return value;
}

bool Train::is_shot(plf::colony<Bullet>& bullets)
{
    auto return_bool = false;
    for (auto& i : this->multiple_centipede_trains)
    {
        for (auto j = bullets.begin(); j < bullets.end(); j++)
        {
            for (const auto& k : std::get<0>(i))
            {
                if (k.getGlobalBounds().intersects(j->get_global_bounds()))
                {
                    collided.insert(std::shared_ptr<Mushroom>(new Mushroom(k.getPosition())));
                    player_score += 3;
                    j = bullets.erase(j);
                    return_bool = true;
                    break;
                }
            }
        }
    }
    return return_bool;
}

void Train::new_trains(std::tuple<std::deque<sf::Sprite>, Direction>& train_row)
{
    auto iteratable_train = std::get<0>(train_row);
    for (auto i = 0; i < iteratable_train.size(); i++)
    {
        auto is_collided_mushroom = this->is_mushroom(iteratable_train.at(i));
        if (is_collided_mushroom && i != 0 && i < iteratable_train.size() - 1)
        {
            auto new_colony = std::tuple<std::deque<sf::Sprite>, Direction>();
            auto new_colony_copy = std::get<0>(new_colony);
            for (auto j = 0; j < i; j++, iteratable_train.pop_front())
            {
                new_colony_copy.push_back(iteratable_train.front());
            }
            iteratable_train.pop_front();
            i = 0;
            std::get<0>(new_colony) = new_colony_copy;

            if (std::get<1>(train_row) == Direction::LEFT)
                std::get<1>(new_colony) = Direction::CHANGE_LEFT;
            else if (std::get<1>(train_row) == Direction::RIGHT)
                std::get<1>(new_colony) = Direction::CHANGE_RIGHT;
            else if (std::get<1>(train_row) == Direction::CHANGE_LEFT)
                std::get<1>(new_colony) = Direction::CHANGE_RIGHT;
            else if (std::get<1>(train_row) == Direction::CHANGE_RIGHT)
                std::get<1>(new_colony) = Direction::CHANGE_LEFT;

            this->multiple_centipede_trains.insert(new_colony);
        }
        else if (is_collided_mushroom)
        {
            iteratable_train.erase(i + iteratable_train.begin());
            --i;
        }
    }
    std::get<0>(train_row) = iteratable_train;
    return;
}

void Train::updated_train()
{
    for (auto i = this->multiple_centipede_trains.begin(); i < this->multiple_centipede_trains.end(); i++)
    {
        this->new_trains(*i);
        if (std::get<0>(*i).empty())
        {
            i = this->multiple_centipede_trains.erase(i);
        }
    }
    return;
}

void Train::new_handle_train(plf::colony<Bullet>& bullets, plf::colony<std::shared_ptr<Mushroom>>& mushrooms)
{
    if (this->is_shot(bullets))
    {
        this->updated_train();
        mushrooms.splice(this->collided);
        this->collided.shrink_to_fit();
        return;
    }
    else
        return;
}

const bool Train::handle_player_collisions(const sf::FloatRect& player) const
{
    for (const auto& i : this->multiple_centipede_trains)
    {
        for (const auto& j : std::get<0>(i))
        {
            if (j.getGlobalBounds().intersects(player))
                return true;
        }
    }
    return false;
}

const unsigned int Train::add_score() const
{
    return this->player_score;
}

void Train::handle_mushroom_collisions(plf::colony<std::shared_ptr<Mushroom>>& mushrooms, plf::colony<Bullet>& bullets)
{
    auto must_shrink = false; 
    for (auto i = mushrooms.begin(); i < mushrooms.end(); i++)
    {
        for (auto j = bullets.begin(); j < bullets.end(); j++)
        {
            if (j->get_global_bounds().intersects((*i)->get_global_bounds()))
            {
                j = bullets.erase(j);
                if ((*i)->increment_health(mushrooms,this->multiple_centipede_trains))
                {
                    must_shrink = true; 
                    i = mushrooms.erase(i);
                    player_score++;
                    break;
                }
                else
                    continue;
                break;
            }
        }
    }
}

bool Train::is_empty()
{
    if (this->multiple_centipede_trains.empty())
    {
        return true;
    }
    else
    {
        for (auto i = this->multiple_centipede_trains.begin(); i < this->multiple_centipede_trains.end(); i++)
        {
            for (auto j = std::get<0>(*i).begin(); j != std::get<0>(*i).end(); j++)
            {
                if (j->getPosition().y <= 590.f)
                {
                    return false;
                }
            }
            std::cout << this->multiple_centipede_trains.memory(); 
            i = this->multiple_centipede_trains.erase(i); 
        }
        return true;
    }
}


