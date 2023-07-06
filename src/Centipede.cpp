#include "Centipede.h"



CentipedeHead::CentipedeHead() 
{
    movement_clock.restart();
    this->init();
}

CentipedeHead::~CentipedeHead()
{

}

void CentipedeHead::run(sf::RenderTarget& target)
{
    sf::Time time1 = movement_clock.getElapsedTime(); 
    bool ishead = false; 
    std::for_each(this->complete_centipede.begin(), this->complete_centipede.end(), [&](std::shared_ptr<sf::Sprite> i) 
     {   
            if (i == *--this->complete_centipede.end())
            {
                ishead = true;
                std::cout << " -------------------- Head -----------------\n"; 
            }
            this->possible_cordinates(i->getPosition(), 20.f, ishead); 
     });
    if (time1.asSeconds() >= 0.1)
    {
        this->movement_clock.restart(); 
        this->move(); 
    }
    return;
}

void CentipedeHead::draw(sf::RenderTarget& target, sf::RenderStates states) const
{ 
    std::for_each(this->complete_centipede.begin(), this->complete_centipede.end(), [&]( std::shared_ptr<sf::Sprite> i) { target.draw(*i, sf::RenderStates::Default);  }); 
    return;
}

void CentipedeHead::init()
{
    this->texture = std::shared_ptr<sf::Texture>(new sf::Texture());
    auto index = 0;
    if (!this->texture->loadFromFile("Moons.png"))
        std::cout << " error \n";
    for (auto i = 0 ; i < 5 ; i++)
    {
        this->complete_centipede.push_back(std::shared_ptr<sf::Sprite>(new sf::Sprite));
    } 
    this->head = std::vector<std::shared_ptr<sf::Sprite>>::iterator(--this->complete_centipede.end());
    this->tail = std::vector<std::shared_ptr<sf::Sprite>>::iterator(this->complete_centipede.begin()); 
    auto xpos = 20.f; 
    for (const auto& i : this->complete_centipede)
    {
        i->setOrigin(10.f, 10.f);
        i->setTexture(*this->texture, false);
        i->setScale(0.05f, 0.05f);
        i->setPosition(xpos, 10.f);
        xpos += 50.f; 
    }
  //  std::for_each(this->complete_centipede.begin(), this->complete_centipede.end(), [&](std::shared_ptr<sf::Sprite> i) { std::cout << i->getPosition().x << "   " << i->getPosition().y << '\n';   });
    return;
}

void CentipedeHead::move()
{
    auto j = 1;
    for (auto i = 0 ; i < this->complete_centipede.size() - 1; i++, j++)
    {
        if (j == this->complete_centipede.size() - 1)
        {
            auto moves1 = this->possible_cordinates((this->complete_centipede.at(j))->getPosition(), 20.f, true);
            if (!moves1.empty())
            {
                (this->complete_centipede.at(j)->setPosition(moves1[0].getPosition()));
                auto moves_tail = this->possible_cordinates((this->complete_centipede.at(j))->getPosition(), 20.f, false);
                if (!moves_tail.empty())
                {
                    (complete_centipede.at(i))->setPosition(moves_tail[0].getPosition());
                }
            }
            // else trapped
        }
        else
        {
            auto moves_tail = this->possible_cordinates(this->complete_centipede.at(j)->getPosition(), 20.f, false);
            if (!moves_tail.empty())
            {
                (complete_centipede.at(i))->setPosition(moves_tail[0].getPosition());
            }
        }
    }
    return;
}

const bool CentipedeHead::check_shape(sf::CircleShape shape, bool ishead)
{
    if (shape.getPosition().x > 790.f)
    {
        if (this->train_direction == Direction::RIGHT && ishead)
        {
            this->train_direction = Direction::LEFT;
        }
        else if (ishead)
            this->train_direction = Direction::RIGHT;
        return false; 
    }
    else if (shape.getPosition().y > 590.f)
    {
        if (this->train_direction == Direction::RIGHT && ishead)
        {
            this->train_direction = Direction::LEFT;
        }
        else if (ishead)
            this->train_direction = Direction::RIGHT;
        return false;
    }
    else if(shape.getPosition().x < 10.f || shape.getPosition().y < 0.f)
    {
        return false;
    }
    for(const auto& i : this->mushroom_bounds) 
    {
        if (shape.getGlobalBounds().intersects(*i))
        {
            return false;
        }
    }
    return true;
}

void CentipedeHead::update_previous_positions()
{
    //if()
   // auto head = this->complete_centipede.size() - 1; 

}

void CentipedeHead::check_train()
{
   // for(auto )
}

void CentipedeHead::feed_mushroom_globalbounds(std::vector<std::shared_ptr<Mushroom>> mushroom_bound, bool did_change)
{
    if (did_change)
    {
        this->mushroom_bounds.clear(); 
        for(const auto& i : mushroom_bound) 
        { 
             mushroom_bounds.push_back(std::shared_ptr<sf::FloatRect>(new sf::FloatRect(i->get_global_bounds())));   
        }
   //     std::for_each(mushroom_bound.begin(), mushroom_bound.end(), [&](std::shared_ptr<Mushroom> i) { std::cout << i->get_cordinates().x << " mushroom-x  " << i->get_cordinates().y << " mushroom y" << '\n';   });
        return; 
    }
    return; 
}

std::vector<sf::CircleShape> CentipedeHead::possible_cordinates(sf::Vector2f cordinates, float movement_radius, bool ishead)
{
    Direction og_direction = this->train_direction;
    if (ishead && this->train_direction == Direction::RIGHT)
    {
        this->train_direction = Direction::LEFT; 
    }
    else if (ishead && this->train_direction == Direction::LEFT)
    {
        this->train_direction = Direction::RIGHT;
    }
    std::vector<sf::CircleShape> return_shapes;
    double theta = 0; 
    if (this->train_direction == Direction::RIGHT)
    {
        theta =  pi ;
    }
    auto init_shape = sf::CircleShape(); 
    init_shape.setRadius(10.f);
    init_shape.setOrigin(10.f, 10.f); 
    init_shape.setPosition(sf::Vector2f(std::polar<float>(movement_radius, theta).real() + cordinates.x, (std::polar<float>(movement_radius, theta).imag() + cordinates.y)));
    if (this->check_shape(init_shape, ishead))
    {
        return_shapes.push_back(init_shape); 
    }
    for (auto i = 1; i < 8; i++)
    {
        if (i < 4)
        {
            theta += pi / 8;
        }
        else if (i == 4)
        {
            if (this->train_direction == Direction::RIGHT)
                theta = pi - pi / 8;
            else if (this->train_direction == Direction::LEFT)
                theta = - pi / 8; 
        }
        else if (i < 8)
        {
             theta -= pi / 8;
        }
        auto init_shape = sf::CircleShape();
        init_shape.setRadius(10.f);
        init_shape.setOrigin(10.f, 10.f);
        init_shape.setPosition(sf::Vector2f(std::polar<float>(movement_radius, theta).real() + cordinates.x, (std::polar<float>(movement_radius, theta).imag() + cordinates.y)));
        if (this->check_shape(init_shape, ishead))
        {
            return_shapes.push_back(init_shape);
        }
    }
    std::cout << cordinates.x << " xcor " << cordinates.y << " ycor \n"; 
    std::for_each(return_shapes.begin(), return_shapes.end(), [&]( sf::CircleShape i) { std::cout << i.getPosition().x << " open-x  " << i.getPosition().y << " open-y" << '\n';   });
    if (ishead)
    {
        this->train_direction = og_direction;
    }
    return return_shapes;
}




/*
/////////////////////////////////////////////////
/// \brief
///
/// \param
/// \param
/// \return
///
/////////////////////////////////////////////////
Centipede::Centipede() : Obstruction{}
{
    this->texture.reset(new sf::Texture());
    this->centipede.reset(new sf::CircleShape(10.f, 30u));
    this->centipede->setPosition(Obstruction::getRandomCordinates(sf::Vector2f(800.f, 10.f)));
    this->centipede->setFillColor(sf::Color::Red);
    this->centipede->setOrigin(10.f, 10.f);
    this->sprite.reset(new sf::Sprite());
    this->sprite->setOrigin(10.f, 10.f);
    this->texture->loadFromFile("Moon.png");
    this->sprite->setTexture(*this->texture, true);
    this->sprite->setScale(0.05f,0.05f);
    this->initialize_movement_combinations(this->sprite->getGlobalBounds().width + this->sprite->getGlobalBounds().height);
}

/////////////////////////////////////////////////
/// \brief
///
/// \param
/// \param
/// \return
///
/////////////////////////////////////////////////
Centipede::~Centipede()
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
void Centipede::run(const sf::RenderTarget& target, std::array<sf::CircleShape, 16> possible_moves)
{
    this->enforce_window_bounds(target);
    if (this->isHead)
    {
        sf::FloatRect tst = { possible_moves[0].getGlobalBounds() };
        this->move(tst, target);
    }
    else
        pick_move(possible_moves);
    return;
}


/// @brief 
/// @param mushroom_map 
/// 
void Centipede::set_nearby_mushrooms(std::vector<std::shared_ptr<Mushroom>> mushrooms)
{
    for (const auto& i : mushrooms)
    {
        if (std::abs(std::complex<float>(i->get_cordinates().x - this->centipede->getPosition().x, i->get_cordinates().y - this->centipede->getPosition().y)) <= 30.f)
        {
            sf::FloatRect compensate = {sf::FloatRect(5.f + i->get_global_bounds().width,5.f + i->get_global_bounds().height,5.f + i->get_global_bounds().width,5.f + i->get_global_bounds().height)};
            //all this horrid syntax to assing a pointer to a tuple to have information about the mushroom map 
            this->nearby_mushrooms.push_back(std::shared_ptr<std::tuple<sf::FloatRect, sf::Vector2f>>(new std::tuple<sf::FloatRect, sf::Vector2f>{i->get_global_bounds(),i->get_cordinates()}));
        }
    }
    return; 
}

std::tuple<sf::Vector2f,sf::Vector2f> Centipede::handle_bullets(const std::vector<Bullet> bullets)
{
    auto& cordinates = this->centipede->getPosition();
    for (const auto& i : bullets)
    {
        if (i.get_global_bounds().intersects(this->centipede->getGlobalBounds()))
        {
            this->centipede.reset(); 
            return std::tuple<sf::Vector2f, sf::Vector2f>(cordinates,i.get_cordinates());
        }
    }
    return std::tuple<sf::Vector2f, sf::Vector2f>(sf::Vector2f(0.f,0.f), sf::Vector2f(0.f,0.f));
}


/////////////////////////////////////////////////
/// \brief
///
/// \param
/// \param
/// \return
///
/////////////////////////////////////////////////
void Centipede::move(const sf::FloatRect global_bounds, const sf::RenderTarget& target)
{
    std::cout <<" I'm here \n"; 
    switch (this->boundry)
    {
    case Obstruction::Boundry::LEFT:
        this->centipede->move(1.f, 0.f);
        if (this->get_open(global_bounds))
        {
            return;
        }
        else
        {
            this->revert(1.f, 0.f);
            if (!this->move_when_collide(global_bounds, 1))
                this->move_when_collide(global_bounds, -1);
            return;
        }
        break;
    case Obstruction::Boundry::RIGHT:
        this->centipede->move(-1.f, 0.f);
        if (this->get_open(global_bounds))
        {
            return;
        }
        else
        {
            this->revert(-1.f, 0.f);
            if (!this->move_when_collide(global_bounds, 1))
                this->move_when_collide(global_bounds, -1);
            return;
        }
        break;
    default:
        this->centipede->move(1.f, 0.f);
        if (this->get_open(global_bounds))
        {
            return;
        }
        else
        {
            this->revert(1.f, 0.f);
            if (!this->move_when_collide(global_bounds, 1))
                this->move_when_collide(global_bounds, -1);
            return;
        }
        break;
    }
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
bool Centipede::get_open(const sf::FloatRect global_bounds)
{
    if (this->centipede->getGlobalBounds().intersects(global_bounds))
    {
        return false;
    }
    else
        return true;
}


/////////////////////////////////////////////////
 /// \brief
///
/// \param
/// \param
/// \return
///
/////////////////////////////////////////////////
void Centipede::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    this->sprite->setPosition(this->centipede->getPosition());
    target.draw(*this->sprite, sf::RenderStates::Default);
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
void Centipede::revert(float xco, float yco)
{
    this->centipede->move(-xco, -yco);
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
bool Centipede::move_when_collide(const sf::FloatRect global_bounds, int sign_)
{
    if(this->boundry == Boundry::LEFT)
    for (const auto& i : this->movement_combinations)
    {
        this->centipede->move(i.x, sign_ * i.y);
        if (this->get_open(global_bounds))
        {
            return true;
        }
        else
        {
            this->revert(i.x, sign_ * i.y);
        }
    }
      this->boundry = Boundry::RIGHT;
    if (this->boundry == Boundry::RIGHT)
        for (const auto& i : this->movement_combinations)
        {
            this->centipede->move(-i.x, sign_ * i.y);
            if (this->get_open(global_bounds))
            {
                return true;
            }
            else
            {
                this->revert(-i.x, sign_ * i.y);
            }
        }

    return false;
}

/////////////////////////////////////////////////
/// \brief
///
/// \param
/// \param
/// \return
///
/////////////////////////////////////////////////

void Centipede::initialize_movement_combinations(float movement_radius)
{
    sf::Vector2f init_vector;
    auto index = 0ull;
    for (auto i = 0.f; i <= movement_radius && index < this->movement_combinations.size(); i += 0.9, index++)
    {
        init_vector.y = sqrt(movement_radius * movement_radius - i * i);
        init_vector.x = i;
        this->movement_combinations[index] = init_vector;
    }
    return;
}

/// @brief 
/// @param cordinates 

void Centipede::initialize(const sf::Vector2f cordinates)
{
    this->texture.reset(new sf::Texture());
    this->sprite.reset(new sf::Sprite());
    if (!this->texture->loadFromFile("Moon.png"))
        std::cout << "cannot load tecture from file \n";
    this->sprite->setTexture(*this->texture, false);
    this->sprite->setScale(0.16f, 0.16f);
    return;
}

/// @brief 
/// @param potential_move 
/// @return 

void Centipede::pick_move(std::array<sf::CircleShape, 16> possible_moves)
{
    if (!nearby_mushrooms.empty())
    {
        for (const auto& j : this->nearby_mushrooms)
        {
            for (const auto& i : possible_moves)
            {
                if (!i.getGlobalBounds().intersects(std::get<0>(*j)))
                {
                    this->centipede->setPosition(i.getPosition());
                    return;
                }
            }
        }
    }
    this->centipede->setPosition(possible_moves[0].getPosition()); 
    return;
}

/// @brief 

void Centipede::move_down()
{
    if (this->copy_boundry == Boundry::TOP && this->boundry == Boundry::RIGHT)
    {
        this->centipede->move(sf::Vector2f(0.f, 10.f)); 
    }
    this->copy_boundry = this->boundry;
    return;
}


void Centipede::enforce_window_bounds(const sf::RenderTarget& target)
{
    this->centipede->getGlobalBounds();
    if (this->centipede->getGlobalBounds().left <= 0.f + this->centipede->getRadius() && this->copy_boundry != Boundry::LEFT)
    {
        this->centipede->setPosition(this->centipede->getRadius() + 30.f, this->centipede->getPosition().y + 30.f);
        this->boundry = Boundry::LEFT;
    }
    if (this->centipede->getGlobalBounds().width + this->centipede->getGlobalBounds().left >= target.getSize().x - this->centipede->getRadius() && this->copy_boundry != Boundry::RIGHT)
    {
        this->centipede->setPosition(target.getSize().x - 2*this->centipede->getRadius(), this->centipede->getPosition().y + 20.f);
        this->centipede->move(-30.f, 0.f);
        this->boundry = Boundry::RIGHT;
    }

    if (this->centipede->getGlobalBounds().top <= this->centipede->getRadius())
    {
        this->centipede->setPosition(this->centipede->getPosition().x, this->centipede->getRadius());
        this->boundry = Boundry::TOP;
    }

    if (-this->centipede->getGlobalBounds().height + this->centipede->getGlobalBounds().top >= target.getSize().y - this->centipede->getRadius())
    {
        this->centipede->setPosition(800.f, 10.f);
        this->boundry = Boundry::BOTTOM;
    }
    return;
}

*/