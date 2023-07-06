#pragma once
#include "Mushroom.h"
#include "Train.h"
class DTBombs : public Mushroom
{
public:
    DTBombs(); 
    virtual ~DTBombs() {}
    virtual bool increment_health(plf::colony<std::shared_ptr<Mushroom>>& mushrooms, plf::colony<std::tuple<std::deque<sf::Sprite>, Direction>>& multiple_centipede_trains);
private:
};

