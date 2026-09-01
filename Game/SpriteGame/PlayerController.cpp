#include "PlayerController.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteAnimatorRendererComponent.h"
#include "Engine/Engine.h"

FACTORY_REGISTER(PlayerController)

void PlayerController::Start()
{
	Actor::Start();

	m_physicsComponent = GetComponent<nu::PhysicsComponent>();
	assert(m_physicsComponent);
	m_rendererComponent = GetComponent<nu::SpriteAnimatorRendererComponent>();
	assert(m_rendererComponent);
}

void PlayerController::Update(float dt)
{
	nu::Vector2 velocity = m_physicsComponent->GetVelocity();

	float dir = 0;
	if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) dir = -1.0;
	if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) dir = +1.0;
	if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE) && m_grounded)
	{
		velocity.y = -800.0f;
		m_grounded = false;
		m_jumping = true;
	}

	if (dir != 0)
	{
		velocity.x = dir * 500.0f;
		if (m_grounded == true) m_rendererComponent->Play("run");
		m_dir = dir;
	}
	else if (m_grounded == true) m_rendererComponent->Play("idle");
	
	if (m_grounded == false && m_jumping) m_rendererComponent->Play("jump");
	else if (m_grounded == false && m_jumping == false) m_rendererComponent->Play("fall");
	
	//if ((m_physicsComponent->GetVelocity().y > 0.01f) && (m_jumping == false)) m_rendererComponent->Play("fall");

	m_rendererComponent->SetFlipH(m_dir < 0);

	m_physicsComponent->SetVelocity(velocity);
	nu::Engine::Get().GetRenderer().SetCamera(m_physicsComponent->GetPosition());

	Actor::Update(dt);
}

void PlayerController::OnCollision(nu::Actor* other)
{
	if (other->GetTag() == "Ground")
	{
		m_grounded = true;
		m_jumping = false;
	}
}

void PlayerController::Read(const nu::json::value_t& value)
{
	Actor::Read(value);
}
