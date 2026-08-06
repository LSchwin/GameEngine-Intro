#include "SpaceGame.h"
#include "Engine.h"
#include "Font.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"
#include <memory>

using namespace nu;

bool SpaceGame::Initialize()
{
    Game::Initialize();

    m_scene = new Scene();
    m_scene->SetGame(this);

    Engine::Get().GetAudio().AddSound("laser", "audio/laser.wav"); //add some more sounds later
    Engine::Get().GetAudio().AddSound("bomb", "audio/Blaster.wav"); //add some more sounds later
    Engine::Get().GetAudio().AddSound("BombExplode", "audio/BombExplode.wav"); //add some more sounds later
    Engine::Get().GetAudio().AddLoopSound("MusicLoop", "audio/LoopedMusic.mp3"); 

    nu::Engine::Get().GetAudio().PlaySound("MusicLoop");

    //Resources().Get<Texture>("textures/player.png", Engine::Get().GetRenderer());


    //m_titleFont = Resources().Get<Font>("fonts/Tildunk.ttf", 64.0f);
    m_titleText = new Text(Resources().GetWithID<Font>("title_font", "fonts/Tildunk.ttf", 64.0f)); //get with ID
    m_titleText->Create(Engine::Get().GetRenderer(), "SPAAAAAAAACE", Color{ 1.0f, 1.0f, 1.0f });

    m_gameFont = Resources().GetWithID<Font>("game_font", "fonts/Tildunk.ttf", 32.0f);

    m_scoreText = new Text(Resources().GetWithID<Font>("game_font", "fonts/Tildunk.ttf", 32.0f)); //get with id
    m_livesText = new Text(Resources().GetWithID<Font>("game_font", "fonts/Tildunk.ttf", 32.0f)); //get with id
    m_enemyText = new Text(Resources().GetWithID<Font>("game_font", "fonts/Tildunk.ttf", 32.0f)); //get with id

    return true;
}

void SpaceGame::Update(float dt)
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

void SpaceGame::Draw(nu::Renderer& renderer)
{
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

    Game::Draw(renderer);
}

void SpaceGame::SpawnPlayer()
{
    PlayerDesc playerDesc;
    playerDesc.name = "Player";
    //playerDesc.model = assets::playerModel;
    playerDesc.texture = Resources().Get<Texture>("textures/player.png", Engine::Get().GetRenderer());
    playerDesc.transform = Transform{ Vector2{640.0f, 512.0f}, 0.0f, 0.2f }; //position, rotation, scale
    playerDesc.velocity = Vector2{ 0.0f, 0.0f };
    playerDesc.damping = 3.0f;
    playerDesc.speed = 2000.0f;
    
    std::unique_ptr<Player> player = std::make_unique<Player>(playerDesc);
    player->m_ammoText = new Text(m_gameFont);
    m_scene->AddActor(std::move(player));
}

void SpaceGame::SpawnEnemy()
{
    m_spawnTimerMin = (m_spawnTimerMin <= 0) ? RandomFloat(0.1f, 0.4f) : m_spawnTimerMin - 0.5f; //here
    m_spawnTimerMin = (m_spawnTimerMax <= 0) ? RandomFloat(0.1f, 0.4f) : m_spawnTimerMax - 0.5f; //here

    EnemyDesc enemyDesc;
    enemyDesc.name = "Enemy";
    //enemyDesc.model = assets::enemyModel;
    enemyDesc.texture = Resources().Get<Texture>("textures/enemy.png", Engine::Get().GetRenderer());
    enemyDesc.transform = Transform{ Vector2{nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetWidth()), nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetWidth())}, 90.0f, 0.2f };
    enemyDesc.velocity = Vector2{ 0.0f, 0.0f };
    enemyDesc.damping = 3.0f;
    enemyDesc.speed = RandomFloat(1000.0f, 2000.0f);

    //Enemy* enemy = new Enemy{ enemyDesc };
    m_scene->AddActor(std::move(std::make_unique<Enemy>(enemyDesc)));
}

void SpaceGame::onPlayerDead()
{
    m_lives--;
    m_gameState = (m_lives <= 0) ? GameState::GameOver : GameState::StartLevel;

    m_stateTimer = 3.0f;
}

