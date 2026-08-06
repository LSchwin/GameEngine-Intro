#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"

#include "SpaceGame.h"

#include <map>
#include <fmod.hpp>
#include <memory>
#include <random>

using namespace nu;

uint32_t seed = 1234;

uint32_t RNG()
{
    seed = (seed * 1103515245) + 12345;
    return seed;
}


int main()
{
    //rand()
    for (size_t i = 0; i < 10; i++)
    {
        std::cout << RNG() << " ";
    }
    std::cout << std::endl;

    seed = 1234;
    for (size_t i = 0; i < 10; i++)
    {
        std::cout << RNG() << " ";
    }
    std::cout << std::endl;

    SeedRandom((unsigned int)time(NULL));
    for (size_t i = 0; i < 10; i++)
    {
        std::cout << rand() << " ";
    }
    std::cout << std::endl;


    // <random>
    std::random_device randomDevice;
    std::cout << randomDevice.min() << " " << std::endl;
    std::cout << randomDevice.max() << " " << std::endl;
    std::cout << randomDevice.entropy() << " " << std::endl;

    std::mt19937 generator(randomDevice());
    std::uniform_int_distribution<> dist(0, 20);

    for (size_t i = 0; i < 10; i++)
    {
        int t = dist(generator);
        std::cout << t << " ";
    }
    std::cout << std::endl;

    std::uniform_real_distribution<float> distReal(-10.0f, 20.0f);

    for (size_t i = 0; i < 10; i++)
    {
        float t = distReal(generator);
        std::cout << t << " ";
    }
    std::cout << std::endl;





    //return 0;


    SetWorkingDirectory("assets");
    // INITIALIZATION
    Engine::Get().Initialize();

    SpaceGame::Get().Initialize();

    //SpaceGame game;
    //game.Initialize();


    // create texture, using shared_ptr so texture can be shared
    //std::shared_ptr<Texture> texture = std::make_shared<Texture>();
    //texture->Load("textures/chicken-jockey.png", Engine::Get().GetRenderer());
    

    // MAIN LOOP
    bool quit = false;
    while (!quit) {
        // UPDATE
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
                quit = true;
            }
        }
        Engine::Get().Update();

        float dt = Engine::Get().GetTime().GetDeltaTime();
  
        SpaceGame::Get().Update(dt);

        //RENDER
        Engine::Get().GetRenderer().SetColor(0.0f, 0.0f, 0.0f); // Set render draw color to black
        Engine::Get().GetRenderer().Clear();

        SpaceGame::Get().Draw(Engine::Get().GetRenderer());

        Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());


        //Engine::Get().GetRenderer().DrawTexture(*Resources().Get<Texture>("textures/chicken-jockey.png", Engine::Get().GetRenderer()), 30, 30, 45.0f); //test code


        Engine::Get().GetRenderer().Present(); // Render the screen
    }

    // SHUTDOWN
    Engine::Get().Shutdown();

    return 0;
}
