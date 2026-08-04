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
    {}

    void Update(float dt) override;
    //void Draw(const class nu::Renderer& renderer) const override;

private:
    float m_speed = 800.0f;
};