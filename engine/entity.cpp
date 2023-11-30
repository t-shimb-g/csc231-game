#include "entity.h"

#include <sstream>

#include "action.h"
#include "engine.h"
#include "weapon.h"

Entity::Entity(Engine& engine, Vec position, Team team)
    : engine{engine},
      position{position},
      team{team},
      weapon{std::make_shared<Weapon>()} {
    
    // place entity onto its dungeon tile
    Tile& tile = engine.dungeon.get_tile(position);
    if (tile.entity == nullptr) {
        tile.entity = this;
    } else {  // an entity is already on this tile, throw error
        std::stringstream ss{"An entity is already on tile: "};
        ss << position;
        throw std::runtime_error(ss.str());
    }
}

void Entity::change_direction(Vec direction) {
    this->direction = direction;
    if (direction.x == 1) {
        sprite.flip(false);
    } else if (direction.x == -1) {
        sprite.flip(true);
    }
    adjust_weapon_position();
}

void Entity::move_to(Vec new_position) {
    Tile& old_tile = engine.dungeon.get_tile(position);
    Tile& new_tile = engine.dungeon.get_tile(new_position);
    std::swap(old_tile.entity, new_tile.entity);
    position = new_position;
    for (auto func : on_move) {
        func(engine, *this);
    }
}

Vec Entity::get_position() const {
    return position;
}

Vec Entity::get_direction() const {
    return direction;
}

bool Entity::is_visible() const {
    // an entity is visible if its tile is visible
    const Tile& tile = engine.dungeon.get_tile(position);
    return tile.visible;
}

void Entity::take_damage(int amount) {
    health -= amount;
    health = std::clamp(health, 0, max_health);
    if (health == 0) {
        alive = false;
    }
}

void Entity::set_max_health(int value) {
    max_health = health = value;
}

std::pair<int, int> Entity::get_health() const {
    return {health, max_health};
}

bool Entity::is_alive() const {
    return alive;
}

void Entity::set_weapon(std::shared_ptr<Weapon> weapon) {
    this->weapon = weapon;
    this->weapon->sprite = engine.graphics.get_sprite(this->weapon->name);
    adjust_weapon_position();
    this->weapon->sprite.center = {this->weapon->sprite.size.x / 2, this->weapon->sprite.size.y};
}

std::shared_ptr<Weapon> Entity::get_weapon() const {
    return weapon;
}

void Entity::set_team(Team team) {
    this->team = team;
}

Team Entity::get_team() const {
    return team;
}

std::unique_ptr<Action> Entity::take_turn() {
    if (behavior) {
        return behavior(engine, *this);
    }
    return nullptr;
}

void Entity::set_sprite(const std::string& name) {
    sprite = engine.graphics.get_animated_sprite(name, 1, true);
}

void Entity::update() {
    sprite.update();
}

std::vector<Sprite> Entity::get_sprites() const {
    auto s = sprite.get_sprite();
    return {weapon->sprite, s};
}


void Entity::adjust_weapon_position() {
    if (direction.x == 1) {
        weapon->sprite.flip = false;
        weapon->sprite.shift.x = sprite.get_sprite().size.x/8;
        weapon->sprite.angle = 20;
    } else if (direction.x == -1) {
        weapon->sprite.flip = true;
        weapon->sprite.shift.x = -sprite.get_sprite().size.x/2;
        weapon->sprite.angle = -20;
    }
}
