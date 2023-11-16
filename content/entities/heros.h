#pragma once
#include <memory>

// forward declartation
class Entity;
class Engine;
class Action;

namespace Heros {

    void make_wizard(std::shared_ptr<Entity> entity);

    std::unique_ptr<Action> behavior(Engine& engine, Entity& entity);

}