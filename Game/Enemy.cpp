#include "Enemy.h"
#include "Player.h"
#include "Renderer.h"
#include "Engine.h"
#include "SpaceGame.h"
#include "Random.h"
#include "AmmoPickup.h"
#include "Assets.h"

#include <iostream>

void Enemy::Update(float dt)
{
    Player* player = m_scene->GetActorByName<Player>("Player");
    if (player)
    {
        nu::Vector2 direction = player->GetTransform().position - m_transform.position;
        float rotation = direction.Angle();
        SetRotation(rotation * nu::RadToDeg);

        nu::Vector2 forward{ 1, 0 };
        forward = forward.Rotate(m_transform.rotation * nu::DegToRad);
        AddVelocity(forward * m_speed * dt);
    }

    float thrust = 0.0f;
    float rotate = 0.0f;

    nu::Vector2 forward{ 1, 0 };
    nu::Vector2 velocity = forward.Rotate(m_transform.rotation * nu::DegToRad) * thrust;
    AddVelocity(velocity * dt);

    Actor::Update(dt);
}

void Enemy::OnCollision(Actor* other)
{
    
    if (other->GetTag() == "PlayerBullet")
    {
        for (int i = 0; i < 100; i++)
        {
            nu::Particle particle;
            particle.position = m_transform.position;
            particle.color = { 1.0f, 1.0f, 1.0f };
            particle.lifespan = nu::RandomFloat(0.5f, 2.0f);
            particle.velocity = { nu::RandomFloat(-600.0f, 600.0f), nu::RandomFloat(-600.0f, 600.0f) };

            nu::Engine::Get().GetPS().AddParticle(particle);
        }

        SetDestroyed();
        other->SetDestroyed();

        ((SpaceGame*)m_scene->GetGame())->AddPoints(100);

        if (nu::RandomInt(3) == 1)
        {
            AmmoPickupDesc desc;
            desc.name = "AmmoPickup";
            desc.tag = "AmmoPickup";
            desc.model = assets::AmmoPickupModel;
            desc.transform = m_transform;
            desc.lifespan = 30.0f;
            desc.ammoRecoverAmount = 1;

            std::unique_ptr<AmmoPickup> pickup = std::make_unique<AmmoPickup>( desc );
            m_scene->AddActor(std::move(pickup));
        }

    }
    else if (other->GetTag() == "PlayerBomb")
    {
        for (int i = 0; i < 100; i++)
        {
            nu::Particle particle;
            particle.position = m_transform.position;
            particle.color = { 1.0f, 1.0f, 1.0f };
            particle.lifespan = nu::RandomFloat(0.5f, 2.0f);
            particle.velocity = { nu::RandomFloat(-600.0f, 600.0f), nu::RandomFloat(-600.0f, 600.0f) };

            nu::Engine::Get().GetPS().AddParticle(particle);
        }

        SetDestroyed();

        ((SpaceGame*)m_scene->GetGame())->AddPoints(100);
    }
}

void Enemy::Draw(const nu::Renderer& renderer) const
{
    Actor::Draw(renderer);
}