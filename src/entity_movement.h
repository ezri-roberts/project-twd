#ifndef ENTITY_MOVEMENT_H
#define ENTITY_MOVEMENT_H

#include "ecs.h"

// Function declarations for entity movement
void update_movement_system(float deltaTime);
void apply_damage(GameEntity *entity, int incomingDamage); // Apply damage, considering resistance

#endif

