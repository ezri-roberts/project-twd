#include "entity_movement.h"
#include <math.h>
#include "raylib.h"
#include "map.h"

// Function to determine if the current path segment is a turn
bool is_on_turn(const GameEntity *entity) {
	if (((int)(entity->position.x) / 300) % 2 == 1) {
		return true;
	}
	return false;
}


// Function to update movement of entities
void update_movement_system(float deltaTime) {
    for (int i = 0; i < entity_count; i++) {
	    GameEntity *entity = &entities[i];

    	    if (entity->componentMask & COMPONENT_ENEMY) {
		    if(entity->enemy.type == SPIDER) {
			    if (is_on_turn(entity)) {
				    entity->enemy.currentSpeed = entity->enemy.baseSpeed * 0.7f;
			    } else {
				    entity->enemy.currentSpeed = entity->enemy.baseSpeed * 1.2f;
			    }
		    } else {
			    entity->enemy.currentSpeed = entity->enemy.baseSpeed;
		    }
	    entity->position.x += entity->enemy.currentSpeed * deltaTime;
	    entity->position.y += entity->enemy.currentSpeed * deltaTime;
	    }
    }
}

// Function to apply damage to an entity, now considering resistance
void apply_damage(GameEntity *entity, int incomingDamage) {
    if (entity) {
        int damage_after_resistance = incomingDamage - (int)(incomingDamage * entity->health.resistance);
        entity->health.health -= damage_after_resistance;
        if (entity->health.health <= 0) {
            destroy_entity(entity); // Destroy if health reaches zero
        }
    }
}

