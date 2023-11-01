#pragma once

#include "audio.h"
#include "camera.h"
#include "dungeon.h"
#include "entities.h"
#include "events.h"
#include "graphics.h"
#include "input.h"
#include "settings.h"

class Engine {
public:
    Engine(const Settings& settings);

    // Add a hero to the game
    std::shared_ptr<Entity> create_hero();

    // add a monster to the game
    std::shared_ptr<Entity> create_monster();

    // starting and stopping the game
    void run();
    void stop();

    // access to engine components
    Input input;       // handles button presses and mouse clicks
    Audio audio;
    Entities entities;     // manages entities and when they can take their turn
    Graphics graphics; 
    Camera camera;     
    Dungeon dungeon;
    Events events;
    
    std::shared_ptr<Entity> hero;
    
private:
    bool running;
    void handle_input();
    void update();
    void render();
};

