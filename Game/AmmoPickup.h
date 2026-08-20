#pragma once

#include "Actor.h"
#include "Player.h"


class AmmoPickup : public nu::Actor
{
public:
    AmmoPickup() = default;



    //void Draw(const class nu::Renderer& renderer) const override;

    virtual void Read(const nu::json::value_t& value) override
    {
        Actor::Read(value);
    }
};

