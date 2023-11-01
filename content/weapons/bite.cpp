#include "bite.h"

Bite::Bite(int damage)
    :Weapon{"none", damage} {}

void Bite::use(Engine&, Entity&, Entity&) {}
