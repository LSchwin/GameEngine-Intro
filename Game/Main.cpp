#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"

#include "SpaceGame.h"

#include <map>
#include <fmod.hpp>
#include <memory>
#include <random>
#include <fstream>

using namespace nu;


int main()
{
    SetWorkingDirectory("assets");

    {
        // read file (input file)
        std::ifstream file("data/test.txt");
        if (file.is_open())
        {
            std::string str;
            while (std::getline(file, str))
            {
                std::cout << str << std::endl;
            }
            
        }
        else
        {
            std::cout << "could not load" << std::endl;
        }
        file.close();
    }

    {
        // write file(input file)
        std::ofstream file("data/test.txt", std::ios::app);
        if (file.is_open())
        {
            file << "woaw so based\n";
        }
    }
    
    {
        // read / write input (input / output file)
        std::fstream file("data/test.txt", std::ios::in | std::ios::out | std::ios::app);
        if (file.is_open())
        {
            //input
            file << "adeline\n";
            file.seekg(0);
            //output
            std::string str;
            while (std::getline(file, str))
            {
                std::cout << str << std::endl;
            }
        }
    }

    {
        //save game data
        std::string name;
        int score;
        bool isAlive;

        bool save = false;
        if (save)
        {
            name = "blurbous the blorg";
            score = 21;
            isAlive = true;

            std::ofstream file("data/game.txt");
            if (file.is_open())
            {
                file << name << "\n";
                file << score << "\n";
                file << std::boolalpha << isAlive << "\n";
            }
        }

        //load game data
        bool load = true;
        if (load)
        {
            // read file
            std::ifstream file("data/game.txt");
            if (file.is_open())
            {
                std::getline(file, name);

                std::string str;
                std::getline(file, str);
                score = std::stoi(str);
                //file >> score;

                file >> std::boolalpha >> isAlive;
            }
        }

        //display game data
        std::cout << name << "\n";
        std::cout << score << "\n";
        std::cout << isAlive << "\n";

    }

    return 0;


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
