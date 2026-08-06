#include "Engine.h"
#include "Bomb.h"
#include "MathUtils.h"
#include "Assets.h"

#include "Texture.h"
#include "ResourceManager.h"

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
        //SetModel(assets::bombExplosionModel);
        m_texture = nu::Resources().Get<nu::Texture>("textures/bombexplosion.png", nu::Engine::Get().GetRenderer());
        if (!m_exploded) m_transform.scale *= 3.0f;
        m_exploded = true;
        m_lifespan = 1.0f;

        nu::Engine::Get().GetAudio().PlaySound("BombExplode");
    }
}

void Bomb::Draw(const nu::Renderer& renderer) const
{
    if (m_model)
    {
        renderer.DrawModel(*m_model, m_transform);
    }
    if (m_texture)
    {
        renderer.DrawTexture(*m_texture,
            m_transform.position.x,
            m_transform.position.y,
            m_transform.rotation + 90.0f,
            m_transform.scale);
    }
}
