#pragma once

#include "Actor.h"
#include "Player.h"


struct AmmoPickupDesc : public nu::ActorDesc
{
    int ammoRecoverAmount = 0;
};

class AmmoPickup : public nu::Actor
{
public:
    AmmoPickup() = default;

    AmmoPickup(const AmmoPickupDesc& ammoPickupDesc) :
        Actor{ ammoPickupDesc },
        m_ammoRecoverAmount{ ammoPickupDesc.ammoRecoverAmount }
    {}

    //void Draw(const class nu::Renderer& renderer) const override;

    // virtual void Read(const nu::json::value_t& value) override; //need???

private:
    int m_ammoRecoverAmount = 0;
};