#pragma once

#include "Actor.h"

struct BombDesc : public nu::ActorDesc
{
    float speed = 0;
};


class Bomb : public nu::Actor
{
public:
    Bomb() = default;

    Bomb(const BombDesc& BombDesc) :
        Actor{ BombDesc },
        m_speed{ BombDesc.speed }
    {
    }

    Bomb(float speed, const nu::Transform& transform) :
        Actor{ transform },
        m_speed{ speed }
    {
    }

    Bomb(float speed, const nu::Transform& transform, const nu::Model& mesh) :
        Actor{ transform, mesh },
        m_speed{ speed }
    {
    }

    void Update(float dt) override;

    void OnCollision(Actor* other) override;

    //void Draw(const class nu::Renderer& renderer) const override;

private:
    float m_speed = 800.0f;
    float m_exploded = false;
};