#include "Engine.h"
#include "Renderer.h"
#include "Assets.h"
#include "SpaceGame.h"
#include "Player.h"
#include "Bullet.h"
#include "Bomb.h"
#include "AmmoPickup.h"

#include "Texture.h"
#include "ResourceManager.h"

FACTORY_REGISTER(Player)

void Player::Update(float dt)
{

    float thrust = 0.0f;

    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = +m_speed;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -m_speed;

    float rotate = 0.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -180.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +180.0f;

    SetRotation(m_transform.rotation + rotate * dt);

    nu::Vector2 forward{ 1, 0 };
    nu::Vector2 velocity = forward.Rotate(m_transform.rotation * nu::DegToRad) * thrust;
    AddVelocity(velocity * dt);

    //fire
    if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE))
    {
        nu::Engine::Get().GetAudio().PlaySound("laser");

        auto bullet = nu::Factory::Instance().Create<Bullet>("BulletPrototype");
        bullet->SetTransform(m_transform);
        bullet->SetScale(2.0f);
        bullet->SetTag("PlayerBullet");

        m_scene->AddActor(std::move(bullet));
    }

    if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_E) && (m_ammo > 0))
    {
        nu::Engine::Get().GetAudio().PlaySound("bomb");


        auto bomb = nu::Factory::Instance().Create<Bomb>("BombPrototype");
        bomb->SetTransform(m_transform);
        bomb->SetScale(2.0f);
        bomb->SetTag("PlayerBomb");



        //BombDesc desc;
        //desc.name = "Bullet";
        //desc.tag = "PlayerBomb";
        ////desc.model = assets::bombModel;
        //desc.texture = nu::Resources().Get<nu::Texture>("textures/bomb.png", nu::Engine::Get().GetRenderer());
        //desc.transform = m_transform;
        //desc.transform.scale = 2.0f;
        //desc.speed = 6000.0f;
        //desc.lifespan = 2.0f;
        //std::unique_ptr<Bomb> bomb = std::make_unique<Bomb>(desc);

        m_scene->AddActor(std::move(bomb));

        m_ammo--;
    }

    //bullet time
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_X))
    {
        nu::Engine::Get().GetTime().SetTimeScale(0.5f);
    }
    else
    {
        nu::Engine::Get().GetTime().SetTimeScale(1.0f);
    }

    //SetVelocity(GetVelocity() + (force * dt));

    Actor::Update(dt);
}

void Player::OnCollision(Actor* other)
{
    if (other->GetTag() == "Enemy") 
    { 
        SetDestroyed();
        ((SpaceGame*)m_scene->GetGame())->onPlayerDead();

        for (int i = 0; i < 100; i++)
        {
            nu::Particle particle;
            particle.position = m_transform.position;
            //particle.color = { 1.0f, 1.0f, 1.0f };
            particle.lifespan = nu::RandomFloat(0.5f, 2.0f);
            particle.velocity = { nu::RandomFloat(-600.0f, 600.0f), nu::RandomFloat(-600.0f, 600.0f) };
            particle.texture = nu::Resources().Get<nu::Texture>("textures/particle.png", nu::Engine::Get().GetRenderer());

            nu::Engine::Get().GetPS().AddParticle(particle);
        }
    }

    if (other->GetTag() == "AmmoPickup")
    {
        other->SetDestroyed();
        m_ammo++;
    }
}

void Player::Draw(const nu::Renderer& renderer) const
{


    switch (SpaceGame::Get().m_gameState)
    {
    case SpaceGame::GameState::Title:
        break;
    case SpaceGame::GameState::StartGame:
    case SpaceGame::GameState::StartLevel:
    case SpaceGame::GameState::Game:
        //m_ammoText->Create(nu::Engine::Get().GetRenderer(), "Bombs: " + std::to_string(m_ammo), { 1.0f, 1.0f, 1.0f });
        //m_ammoText->Draw(renderer, 30, 100);
        break;
    case SpaceGame::GameState::GameOver:
        break;
    default:
        break;
    }


    //if (m_model)
    //{
    //    renderer.DrawModel(*m_model, m_transform);
    //}
    //if (m_texture)
    //{
    //    renderer.DrawTexture(*m_texture,
    //        m_transform.position.x,
    //        m_transform.position.y,
    //        m_transform.rotation + 90.0f,
    //        m_transform.scale);
    //}


    Actor::Draw(renderer);
}

void Player::Read(const nu::json::value_t& value)
{
    Actor::Read(value);

    JSON_READ_NAME(value, "speed", m_speed);
    JSON_READ_NAME(value, "ammo", m_ammo);
}
