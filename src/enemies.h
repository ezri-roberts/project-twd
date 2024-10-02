#ifndef ENEMIES_H
#define ENEMIES_H

#include "ecs.h"
#include "raylib.h"  // For rendering logic

// Define enemy types and properties
typedef enum {
    ZOMBIE,
    SKELETON,
    SPIDER
} EnemyType;

// Function declarations
GameEntity* create_enemy(EnemyType type, float x, float y, int speed, int damage, float resistance);
void update_enemy_system(float deltaTime);
void render_enemy_system(Camera2D camera);

#endif

