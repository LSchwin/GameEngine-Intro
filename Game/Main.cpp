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


class Animal
{
public:
    virtual void Speak() { std::cout << "???"; }
};

class Cat : public Animal
{
    void Speak() override { std::cout << "meow"; }
};

class Dog : public Animal
{
    void Speak() override { std::cout << "bork"; }
};

class Bird : public Animal
{
    void Speak() override { std::cout << "bird"; }
};

enum class Type
{
    Cat = 1,
    Dog,
    Bird
};

Animal* AnimalFactory(Type id)
{
    Animal* animal = nullptr;

    switch (id)
    {
    case Type::Cat:
        animal = new Cat();
        break;
    case Type::Dog:
        animal = new Dog();
        break;
    case Type::Bird:
        animal = new Bird();
        break;
    }


    return animal;
}

Animal* AnimalFactory(const std::string& id)
{
    Animal* animal = nullptr;

    if (nu::EqualsIgnoreCase(id, "Cat")) animal = new Cat();
    else if (ToLower(id) == "dog") animal = new Dog();
    else if (nu::EqualsIgnoreCase(id, "Bird")) animal = new Bird();
   
    return animal;
}

/*
class ICreator
{
public:
    virtual ~ICreator() = default;
    virtual std::unique_ptr<Animal> Create() = 0;
};

template <typename T>
class Creator : public ICreator
{
public:
    
    std::unique_ptr<Animal> Create() override { return  std::make_unique<T>(); }
};


std::map<std::string, std::unique_ptr<ICreator>> registry;
*/


int main()
{
    Factory::Instance().Register<Actor>("Actor");
    auto actor = Factory::Instance().Create<Actor>("Actor");

    //registry["Cat"] = std::make_unique<Creator<Cat>>();
    //registry["Dog"] = std::make_unique<Creator<Dog>>();

    //{
    //    auto animal = registry["Cat"]->Create();
    //    auto animal2 = registry["Dog"]->Create();
    //    animal->Speak();
    //    animal2->Speak();
    //}

    /*std::string selection;
    std::cout << "Select Animal: ";
    std::cin >> selection;

    auto animal = AnimalFactory(selection);
    animal->Speak();*/



    return 0;


    SetWorkingDirectory("assets");

    // load the json data from a file
    std::string buffer;
    if (ReadTextFile("data/data.json", buffer))
    {
        // show the contents of the json file (debug)
        std::cout << buffer << std::endl;

        // create json document from the json file contents
        rapidjson::Document document;
        if (json::Load("data/data.json", document))
        {
            // read the age data (int) from the json
            int age;
            json::Read(document, "age", age);
            // show the age data
            std::cout << age << std::endl;
        }

        std::string name;
        int age;
        float speed;
        bool isAwake;
        nu::Vector2 position;
        nu::Vector3 color;

        // read the json data
        JSON_READ(document, name);
        JSON_READ(document, age);
        JSON_READ(document, speed);
        JSON_READ(document, isAwake);
        JSON_READ(document, position);
        JSON_READ(document, color);

        // show the data
        std::cout << name << " " << age << " " << speed << " " << isAwake << std::endl;
        std::cout << position.x << " " << position.y << std::endl;
        std::cout << color.r << " " << color.g << " " << color.b << " " << std::endl;

    }

    //+ After running the program, the console will display the contents of the** JSON** file and the** age** data.
    //+ In the Json.h file, _add_ the following functions.
    //+ Add new functions to load * *float**, **bool**, **std::string**, ** vec2**, and **vec3**
    //+Include * *Math / Vector2.h * *and **Math / Vector3.h * *
    // read/show the data from the json file
    
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
