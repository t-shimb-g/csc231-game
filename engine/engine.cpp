#include "engine.h"

#include <fstream>
#include <iomanip>
#include <sstream>
#include <unordered_map>

#include "builder.h"
#include "decorator.h"
#include "entity.h"
#include "settings.h"
#include "timer.h"

Engine::Engine(const Settings& settings)
    :graphics{settings.title, settings.screen_width, settings.screen_height},
     camera{graphics, settings.tilesize, settings.zoom}, running{false} {

    // load sounds
    audio.load_sounds(settings.sounds);
    audio.play_sound("background", true);
    
    // load sprites
    graphics.load_spritesheet(settings.tiles);
    graphics.load_spritesheet(settings.heros);
    graphics.load_spritesheet(settings.monsters);
    graphics.load_spritesheet(settings.weapons);
    graphics.load_spritesheet(settings.items);
    graphics.load_spritesheet(settings.effects);
    
    // create dungeon layout
    Builder builder(settings.room_placement_attempts);
    auto [layout, rooms] = builder.generate(settings.map_width, settings.map_height);

    // assign sprites to dungeon tiles
    Decorator decorator(graphics, layout, rooms);
    dungeon = decorator.create_dungeon();
}

void Engine::run() {
    if (!hero) {
        throw std::runtime_error("Engine::run(): No hero has been added to the game");
    }
    running = true;
    Timer timer;
    double accumulated_time{0.0};
    constexpr double timestep_per_update{0.1};

    // main game loop
    while (running && hero && hero->is_alive()) {
        // handling input and rendering produce time, whereas the
        // update loop consumes time in fixed steps
        accumulated_time += timer.elapsed(); 

        handle_input();

        // if we have accumulated enough rendering time for an update,
        // then take it
        while (accumulated_time >= timestep_per_update) {
            update();
            accumulated_time -= timestep_per_update;
        }

        // redraw everything on the screen
        render();
    }
}

void Engine::stop() {
    running = false;
}

std::shared_ptr<Entity> Engine::create_hero() {
    Vec position = dungeon.random_open_room_tile();
    hero = std::make_shared<Entity>(*this, position, Team::Hero);
    entities.add(hero);

    // always move camera to where the hero is
    auto center_camera = [](Engine& engine, Entity& entity) {
        engine.camera.move_to(entity.get_position());
    };
    center_camera(*this, *hero);
    hero->on_move.push_back(center_camera);

    // update the visibility of tiles and enemies
    auto update_visibility = [](Engine& engine, Entity& entity) {
        engine.dungeon.update_visibility(entity.get_position());
    };
    update_visibility(*this, *hero);
    hero->on_move.push_back(update_visibility);

    return hero;
}


std::shared_ptr<Entity> Engine::create_monster() {
    Vec position = dungeon.random_open_room_tile();
    std::shared_ptr<Entity> monster = std::make_shared<Entity>(*this, position, Team::Monster);
    entities.add(monster);
    return monster;
}



void Engine::handle_input() {
    std::vector<std::string> events = input.get_all_input_events();
    for (const std::string& event : events) {
        if (event == "Quit") { // game window was closed
            stop();
            break;
        }
        else if (event == "-") {
            camera.zoom_out();
        }
        else if (event == "=") { // also handles + key
            camera.zoom_in();
        }
        else { // otherwise store keypress as most recent
            input.set_last_keypress(event);
        }
    }
}

void Engine::update() {
    camera.update();
    
    // update all dungeon tiles, mostly updating animate sprites
    dungeon.update();

    // let entities know that game has progressed, they may update their sprites
    entities.update();

    while (events.empty() && entities.take_turn(*this)) {
        // if there are no outstanding events, let entities take turns
        // until events are produced or an entity cannot take a turn
    }
    
    // an entity may have produced an event, so process it
    events.execute(*this);
}

void Engine::render() {
    graphics.clear();
    camera.render(dungeon);
    camera.render(entities);
    camera.render_fog(dungeon);
    camera.render_overlays();
    if (hero) {
        auto [health, max_health] = hero->get_health();
        camera.render_healthbar(health, max_health);
    }
    graphics.redraw();
}

void Engine::remove_entity(Entity& entity) {
    //re move from dungeon tile
    Vec position = entity.get_position();
    dungeon.remove_entity(position);

    // remove from active entiteis by setting health to zero
    entity.set_max_health(0);
}