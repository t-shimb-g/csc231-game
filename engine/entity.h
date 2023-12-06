#pragma once

#include "animatedsprite.h"
#include "vec.h"
#include "sprite.h"
#include <memory>

// forward declarations
class Engine;
class Action;
class Weapon;

constexpr int default_speed{8};
enum class Team { Hero, Monster, Chest };

// base class for all interacting beings
class Entity {
public:
    Entity(Engine& engine, Vec position, Team team);

    // movement
    Vec get_position() const;
    void move_to(Vec position);
    Vec get_direction() const;
    void change_direction(Vec direction);
    bool is_visible() const;

    // functions to be called after move_to is called
    std::vector<std::function<void(Engine& engine, Entity& entity)>> on_move;

    // combat
    void take_damage(int amount);
    void set_max_health(int value);
    std::pair<int, int> get_health() const; // returns health, max_health
    bool is_alive() const;
    void set_weapon(std::shared_ptr<Weapon> weapon);
    std::shared_ptr<Weapon> get_weapon() const;
    void set_team(Team team);
    Team get_team() const;

    // taking turns
    std::unique_ptr<Action> take_turn();
    std::function<std::unique_ptr<Action>(Engine& engine, Entity& entity)> behavior;

    // drawing
    void set_sprite(const std::string& name);
    void update();
    std::vector<Sprite> get_sprites() const;

private:
    Engine& engine;
    AnimatedSprite sprite;
    Vec position, direction{1, 0};

    // health gets reduced by calling take damage
    int health{1}, max_health{1};
    bool alive{true};
    
    // teams can be used to determine who can attack whom
    Team team;

    // speed is energy gain per turn, once an entity has enough energy
    // it can take a turn
    int speed{default_speed}, energy{0};

    void adjust_weapon_position();
    
    std::shared_ptr<Weapon> weapon;
    friend class Entities;
};

