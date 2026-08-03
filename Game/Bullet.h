#pragma once

#include "Actor.h"

struct BulletDesc : public nu::ActorDesc
{
    float speed = 0;
};


class Bullet : public nu::Actor
{
public:
    Bullet() = default;

    Bullet(const BulletDesc& BulletDesc) :
        Actor{ BulletDesc },
        m_speed{ BulletDesc.speed }
    {
    }

    Bullet(float speed, const nu::Transform& transform) :
        Actor{ transform },
        m_speed{ speed }
    {
    }

    Bullet(float speed, const nu::Transform& transform, const nu::Model& mesh) :
        Actor{ transform, mesh },
        m_speed{ speed }
    {
    }

    void Update(float dt) override;
    //void Draw(const class nu::Renderer& renderer) const override;

private:
    float m_speed = 800.0f;
};