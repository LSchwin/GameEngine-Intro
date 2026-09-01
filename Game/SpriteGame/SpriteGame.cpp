#include "SpriteGame.h"
#include "Engine/Engine.h"
#include "Renderer/Font.h"
#include "PlayerController.h"
//#include "SpriteGame/Enemy.h"
//#include "SpriteGame/Bullet.h"
//#include "SpriteGame/Bomb.h"
//#include "SpriteGame/Assets.h"
#include <memory>

using namespace nu;

bool SpriteGame::Initialize()
{
    SetWorkingDirectory("SpriteGame");
    Game::Initialize();

    m_scene = std::make_unique<Scene>();
    m_scene->SetGame(this);
    m_scene->Load("scenes/scene.json");
    
    Engine::Get().GetAudio().AddSound("laser", "audio/laser.wav"); //add some more sounds later
    Engine::Get().GetAudio().AddSound("bomb", "audio/Blaster.wav"); //add some more sounds later
    Engine::Get().GetAudio().AddSound("BombExplode", "audio/BombExplode.wav"); //add some more sounds later
    Engine::Get().GetAudio().AddLoopSound("MusicLoop", "audio/LoopedMusic.mp3"); 
    
    nu::Engine::Get().GetAudio().PlaySound("MusicLoop");
    
    m_titleText = new Text(Resources().GetWithID<Font>("title_font", "fonts/Tildunk.ttf", 64.0f)); //get with ID
    m_titleText->Create(Engine::Get().GetRenderer(), "SPAAAAAAAACE", Color{ 1.0f, 1.0f, 1.0f });
    
    m_gameFont = Resources().GetWithID<Font>("game_font", "fonts/Tildunk.ttf", 32.0f);
    
    m_scoreText = new Text(Resources().GetWithID<Font>("game_font", "fonts/Tildunk.ttf", 32.0f)); //get with id
    m_livesText = new Text(Resources().GetWithID<Font>("game_font", "fonts/Tildunk.ttf", 32.0f)); //get with id
    m_enemyText = new Text(Resources().GetWithID<Font>("game_font", "fonts/Tildunk.ttf", 32.0f)); //get with id

    return true;
}

void SpriteGame::Update(float dt)
{
    switch (m_gameState)
    {
    case GameState::Title:
        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE))
        {
            m_gameState = GameState::StartGame;
        }
        break;
    case GameState::StartGame:
        m_score = 0;
        m_lives = 3;
        m_spawnTimerMin = 2.0f;
        m_spawnTimerMax = 3.0f;
        m_spawnTimer = 3.0f;
        m_stateTimer = 0.5;
        m_gameState = GameState::StartLevel;
        break;
    case GameState::StartLevel:
        m_stateTimer -= dt;
        if(m_stateTimer > 0)
        {
            break;
        }
        m_scene->RemoveAllActors();
        m_scene->Load("scenes/level.json");


        SpawnPlayer();
        m_gameState = GameState::Game;
        break;
    case GameState::Game:
        m_spawnTimer -= dt;
        if (m_spawnTimer <= 0.0f)
        {
            m_spawnTimer = nu::RandomFloat(m_spawnTimerMin, m_spawnTimerMax);
            SpawnEnemy();
        }
    
        break;
    case GameState::GameOver:
        m_stateTimer -= dt;
        if (m_stateTimer <= 0)
        {
            m_scene->RemoveAllActors();
            m_gameState = GameState::Title;
        }
        break;
    default:
        break;
    }

    Game::Update(dt);
}

void SpriteGame::Draw(nu::Renderer& renderer)
{
    renderer.EnableCamera(false);

    renderer.DrawTexture(*nu::Resources().Get<Texture>("textures/background.png", renderer), 600.0f, 600.0f, 0.0f, 10.0f);
    
    switch (m_gameState)
    {
    case GameState::Title:
        m_titleText->Draw(renderer, 750, 500);
        break;
    case GameState::StartGame:
    case GameState::StartLevel:
    case GameState::Game:
        // draw score / lives
        m_scoreText->Create(renderer, "Score: " + std::to_string(m_score), { 1.0f, 1.0f, 1.0f });
        m_scoreText->Draw(renderer, 30, 30);
    
        m_livesText->Create(renderer, "Lives: " + std::to_string(m_lives), { 1.0f, 1.0f, 1.0f });
        m_livesText->Draw(renderer, (float)renderer.GetWidth() - 150, 100);
    
        m_enemyText->Create(renderer, "Next Wave: " + std::to_string(m_spawnTimer), { 1.0f, 1.0f, 1.0f });
        m_enemyText->Draw(renderer, (float)renderer.GetWidth() - 350, 30);
        break;
    case GameState::GameOver:
        break;
    default:
        break;
    }

    renderer.EnableCamera();
    Game::Draw(renderer);
}

void SpriteGame::SpawnPlayer()
{
    auto player = Factory::Instance().Create<Actor>("PlayerPrototype");
    m_scene->AddActor(std::move(player));
}

void SpriteGame::SpawnEnemy()
{
    m_spawnTimerMin = (m_spawnTimerMin <= 0) ? RandomFloat(0.1f, 0.4f) : m_spawnTimerMin - 0.5f;
    m_spawnTimerMin = (m_spawnTimerMax <= 0) ? RandomFloat(0.1f, 0.4f) : m_spawnTimerMax - 0.5f;
    
    auto enemy = Factory::Instance().Create<Actor>("FlyingEnemyPrototype");
    enemy->SetPosition({ nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetWidth()), nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetWidth()) });
    m_scene->AddActor(std::move(enemy));
}

void SpriteGame::onPlayerDead()
{
    //m_lives--;
    //m_gameState = (m_lives <= 0) ? GameState::GameOver : GameState::StartLevel;
    //
    //m_stateTimer = 3.0f;
}

