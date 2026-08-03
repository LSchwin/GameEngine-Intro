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
    {
    }

    //void AddAmmo(Player& player) { player.SetAmmo(player.GetAmmo() + 1); }

private:
    int m_ammoRecoverAmount = 0;
};