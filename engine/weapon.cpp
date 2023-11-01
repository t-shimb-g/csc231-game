#include "weapon.h"

Weapon::Weapon()
    :name{}, damage{0} {}    

Weapon::Weapon(const std::string& name, int damage)
    :name{name}, damage{damage} {}


void Weapon::use(Engine&, Entity&, Entity&) {}
