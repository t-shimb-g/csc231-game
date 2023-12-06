#pragma once
#include <memory>

class Entity;
class Engine;
class Action;

namespace Chests {
    void make_full_chest(std::shared_ptr<Entity> chest);
    void make_empty_chest(std::shared_ptr<Entity> chest);
    void make_mimic_chest(std::shared_ptr<Entity> chest);

    std::unique_ptr<Action> behavior(Engine& engine, Entity& entity);
};