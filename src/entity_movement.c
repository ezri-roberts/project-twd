#include "entity_movement.h"
#include "map.h"

// Declare entity_map as an external variable
extern map_base_t entity_map;

// Function to update movement of entities
void update_movement_system(float deltaTime) {
    map_iter_t iter = map_iter_();
    const char *key;

    while ((key = map_next_(&entity_map, &iter))) {
        GameEntity *entity = (GameEntity *)map_get_(&entity_map, key);
        if (entity && entity->entity.isActive) {
            entity->position.x += entity->speed.speed * deltaTime;
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

