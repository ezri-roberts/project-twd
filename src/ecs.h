#ifndef ECS_H
#define ECS_H

#include "raylib.h"
#include "map.h"
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
} GameEntity;

// Function declarations
void init_entities(void);
GameEntity *create_entity(float x, float y, float speed, int health);
void add_entity(const char *key, GameEntity *entity);
void destroy_entity(const char *key);
void update_movement_system(float deltaTime);
void render_system(void);
void destroy_all_entities(void);

#endif

