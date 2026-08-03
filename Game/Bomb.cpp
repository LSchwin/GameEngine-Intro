#include "Engine.h"
#include "Bomb.h"
#include "MathUtils.h"
#include "Assets.h"

void Bomb::Update(float dt)
{
    if (!m_exploded)
    {
        nu::Vector2 forward{ 0.2f, 0.0f };
        nu::Vector2 velocity = forward.Rotate(m_transform.rotation * nu::DegToRad) * m_speed;

        SetVelocity(velocity);
    }
    else 
    {
        SetVelocity({0.0f, 0.0f});
    }
	
	Actor::Update(dt);
}

void Bomb::OnCollision(Actor* other)
{
    if (other->GetName() == "Enemy")
    {
        SetModel(assets::bombExplosionModel);
        m_exploded = true;
        m_lifespan = 1.0f;

        nu::Engine::Get().GetAudio().PlaySound("BombExplode");
    }
}