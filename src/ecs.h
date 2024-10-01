#ifndef ECS_H
#define ECS_H

#include "raylib.h"
#include "map.h"
#include "enemies.h" // Assuming EnemyType is declared here
#include <stdbool.h>

// Entity Components
typedef struct {
    float x, y; // Separate x and y coordinates instead of Vector2
} PositionComponent;

typedef struct {
    float speed;
} SpeedComponent;

typedef struct {
    int health;
    float resistance; // Add resistance to health component
} HealthComponent;

typedef struct {
    bool isActive;
} Entity;

// Struct to represent a full game entity
typedef struct {
    Entity entity;
    PositionComponent position;
    SpeedComponent speed;
    HealthComponent health;
    EnemyComponent *component; 
} GameEntity;

// Initializes the entity map
void init_entities(void);

// Creates a new game entity
GameEntity *create_entity(EnemyType type, float x, float y, float speed, int health);

// Adds an entity to the entity map
void add_entity(const char *key, GameEntity *entity);

// Destroys an entity in the entity map
void destroy_entity(const char *key);

// Updates the movement system for all active entities
void update_movement_system(float deltaTime);

// Renders all active entities
void render_system(void);

// Destroys all entities and frees resources
void destroy_all_entities(void);

// Applies damage to a game entity
void apply_damage(GameEntity *enemy, int incomingDamage);

#endif

