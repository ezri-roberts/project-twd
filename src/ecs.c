#include "ecs.h"
#include <stdio.h>
#include "types.h"
#include "entity_movement.h"

// Internal array of entities
static GameEntity entities[MAX_ENTITIES];
static int entity_count = 0;

// Create a new entity
GameEntity* create_entity() {
    if (entity_count >= MAX_ENTITIES) return NULL;
    GameEntity *entity = &entities[entity_count++];
    entity->id = entity_count;
    entity->componentMask = 0; 
    return entity;
}

// Add an entity to the ECS system
void add_entity(GameEntity *entity) {
    if (!entity) return;

    // Check if the entity is already in the system (simple check by ID)
    for (int i = 0; i < entity_count; i++) {
        if (entities[i].id == entity->id) {
            printf("Entity with ID %d already exists in the system.\n", entity->id);
            return;
        }
    }

    // If not already in the system, assign the entity to the internal array
    entities[entity_count] = *entity;
    entity_count++;

    // Log addition for debug purposes
    printf("Entity with ID %d added to the system. Total entities: %d\n", entity->id, entity_count);
}

// Remove an entity from the system
void remove_entity(GameEntity *entity) {
    if (!entity) return;

    // Find the entity in the ECS and remove it by shifting the remaining entities
    for (int i = 0; i < entity_count; i++) {
        if (entities[i].id == entity->id) {
            // Shift all the remaining entities left
            for (int j = i; j < entity_count - 1; j++) {
                entities[j] = entities[j + 1];
            }
            entity_count--;
            printf("Entity with ID %d removed. Total entities: %d\n", entity->id, entity_count);
            return;
        }
    }
    printf("Entity with ID %d not found for removal.\n", entity->id);
}

// Update all entities in the ECS
void update_entity_system(float deltaTime) {
    for (int i = 0; i < entity_count; i++) {
        GameEntity *entity = &entities[i];

        // Movement system: update position based on speed and deltaTime
        if ((entity->componentMask & (COMPONENT_POSITION | COMPONENT_ENEMY)) == (COMPONENT_POSITION | COMPONENT_ENEMY)) {
            entity->position.x += entity->enemy.speed * deltaTime;
            entity->position.y += entity->enemy.speed * deltaTime;
        }
    }
}

// Apply damage to an entity
void apply_damage(GameEntity *entity, int damage, ElementType attackerType) {
    if (entity->componentMask & COMPONENT_HEALTH) {
	ElementType defenderType = TYPE_NONE;
        if (entity->componentMask & COMPONENT_ENEMY) {
            defenderType = entity->enemy.elementType;
        }

	float multiplier = get_type_multiplier(attackerType, defenderType);
	int adjustedDamage = (int)(damage * multiplier);

	entity->health.health -= adjustedDamage;
	printf("Entity ID %d took %d damage (multiplier: %.2f). Remaining health: %d\n",
               entity->id, adjustedDamage, multiplier, entity->health.health);
	if (entity->health.health <= 0) {
		remove_entity(entity);
	}	
    }
}

// Collision detection system: Check for collisions between entities
void handle_collisions() {
    for (int i = 0; i < entity_count; i++) {
        GameEntity *a = &entities[i];

        // Only check entities that have a collision component
        if (!(a->componentMask & COMPONENT_COLLISION)) continue;

        for (int j = i + 1; j < entity_count; j++) {
            GameEntity *b = &entities[j];

            // Both entities must have the collision component to check collisions
            if (!(b->componentMask & COMPONENT_COLLISION)) continue;

            // Check if their bounding boxes overlap
            if (CheckCollisionRecs(a->collision.bounds, b->collision.bounds)) {
                // Determine attacker and defender
                // For simplicity, assume 'a' is the attacker for 'b' and vice versa
                ElementType aType = (a->componentMask & COMPONENT_ENEMY) ? a->enemy.elementType : TYPE_NONE;
                ElementType bType = (b->componentMask & COMPONENT_ENEMY) ? b->enemy.elementType : TYPE_NONE;

                // Apply damage with type effectiveness
                apply_damage(b, a->health.damage, aType);
                apply_damage(a, b->health.damage, bType);
            }
        }
    }
}
