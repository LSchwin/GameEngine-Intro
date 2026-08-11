#pragma once

#include "Random.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Transform.h"
#include "MathUtils.h"
#include "StringUtils.h"

#include "Text.h"

#include "Factory.h"

// systems
#include "Renderer.h"
#include "Input.h"
#include "GameTime.h"
#include "File.h"
#include "Audio.h"
#include "ParticleSystem.h"
#include "Texture.h"
#include "JSON.h"

// framework
#include "Actor.h"
#include "Scene.h"
#include "Game.h"

#include <iostream>
#include <vector>

namespace nu
{
	class Engine
	{
	public:

		static Engine& Get() { static Engine engine; return engine; }

		bool Initialize();
		void Shutdown();

		void Update();

		Input& GetInput() { return m_input; }
		Renderer& GetRenderer() { return m_renderer; }
		Time& GetTime() { return m_time; }

		Engine(const Engine&) = delete;
		Engine& operator = (const Engine&) = delete;

		Audio& GetAudio() { return m_audio; }

		ParticleSystem& GetPS() { return m_particleSystem; }

	private:
		Engine() = default;


	private:
		Input m_input;
		Renderer m_renderer;
		Audio m_audio;
		Time m_time;
		ParticleSystem m_particleSystem;
	};
}