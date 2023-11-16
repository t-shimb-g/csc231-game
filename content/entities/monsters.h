#pragma once
#include <memory>

class Entity;
class Engine;
class Action;

namespace Monsters {
    void make_orc_masked(std::shared_ptr<Entity> monster);

    std::unique_ptr<Action> behavior(Engine& engine, Entity& entity);
}