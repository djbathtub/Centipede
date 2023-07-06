#include "DTBombs.h"


DTBombs::DTBombs(): Mushroom{ "bomb_anim.png" }
{

}

bool DTBombs::increment_health(plf::colony<std::shared_ptr<Mushroom>>& mushrooms, plf::colony<std::tuple<std::deque<sf::Sprite>, Direction>>& multiple_centipede_trains)
{
    auto blasted_area = sf::CircleShape(75.f, 30u);
    blasted_area.setOrigin(75.f, 75.f);
    blasted_area.setPosition(this->get_cordinates());
    for (auto i = mushrooms.begin(); i < mushrooms.end(); i++)
    {
        if (blasted_area.getGlobalBounds().intersects((*i)->get_global_bounds()) && this->get_cordinates() != (*i)->get_cordinates())
        {
            i = mushrooms.erase(i);
        }
    }
    for (auto train_row  =  multiple_centipede_trains.begin(); train_row < multiple_centipede_trains.end(); train_row++)
    {
        for (auto i = std::get<0>(*train_row).begin(); i != std::get<0>(*train_row).end(); i++)
        {
            if (blasted_area.getGlobalBounds().intersects(i->getGlobalBounds()))
            {
                if (i == std::get<0>(*train_row).end() - 1)
                {
                    i = std::get<0>(*train_row).erase(i);
                    break;
                }
                else
                {
                    i = std::get<0>(*train_row).erase(i);
                }
            }
        }
        if (std::get<0>(*train_row).empty())
            multiple_centipede_trains.erase(train_row); 
    }
    return true;
}
