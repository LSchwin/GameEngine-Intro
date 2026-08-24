#include "Engine/Engine.h"

#include "SpaceGame.h"

#include <map>
#include <fmod.hpp>
#include <memory>
#include <random>
#include <fstream>

using namespace nu;


int main()
{
    //NO TOUCHY
    SetWorkingDirectory("assets"); 
    //NO TOUCHY
    

    // INITIALIZATION
    Engine::Get().Initialize();

    SpaceGame::Get().Initialize();

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

        Engine::Get().GetRenderer().Present(); // Render the screen
    }

    // SHUTDOWN
    Engine::Get().Shutdown();

    return 0;
}
