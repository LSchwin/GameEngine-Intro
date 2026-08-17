#include "Bullet.h"
#include "MathUtils.h"
#include "Renderer.h"
#include "Factory.h"

FACTORY_REGISTER(Bullet)

void Bullet::Update(float dt)
{
	nu::Vector2 forward{ 1.0f, 0.0f };
	nu::Vector2 velocity = forward.Rotate(m_transform.rotation * nu::DegToRad) * m_speed;
	
	SetVelocity(velocity);

	Actor::Update(dt);
}

void Bullet::Draw(const nu::Renderer& renderer) const
{
    //if(m_model)
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
}

void Bullet::Read(const nu::json::value_t& value)
{
    Actor::Read(value);

    JSON_READ_NAME(value, "speed", m_speed);
}
