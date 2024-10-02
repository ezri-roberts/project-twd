#include "enemies.h"
#include "ecs.h"
#include "raylib.h"

// Texture atlas for all enemies
Texture2D enemyTextureAtlas;

// Define UV coordinates for each enemy type in the texture atlas
Rectangle enemyUVs[3] = {
    { 0, 0, 64, 64 },    // ZOMBIE UVs
    { 64, 0, 64, 64 },   // SKELETON UVs
    { 128, 0, 64, 64 }   // SPIDER UVs
};

// Create a new enemy entity
GameEntity* create_enemy(EnemyType type, float x, float y, int speed, int damage, float resistance) {
    GameEntity *enemy = create_entity();
    if (!enemy) return NULL;

    // Assign enemy-specific components
    enemy->position.x = x;
    enemy->position.y = y;
    enemy->enemy.speed = speed;
    enemy->enemy.resistance = resistance;
    enemy->health.health = 100;
    enemy->health.damage = damage;

    // Set the component mask to include position, enemy, and health
    enemy->componentMask = COMPONENT_POSITION | COMPONENT_ENEMY | COMPONENT_HEALTH;

    // Add the entity to the ECS
    add_entity(enemy);

    return enemy;
}

// Update the enemy system
void update_enemy_system(float deltaTime) {
    // Leverage the ECS to update enemy-specific behavior
    update_entity_system(deltaTime);
}

// Render the enemies using Raylib
void render_enemy_system(Camera2D camera) {
    BeginDrawing();
    
    for (int i = 0; i < entity_count; i++) {
        GameEntity *enemy = &entities[i];
        
        // Check if entity has the necessary components to render
        if (enemy->componentMask & COMPONENT_POSITION) {
            float x = enemy->position.x;
            float y = enemy->position.y;
            
            // Use the appropriate texture UVs for the enemy type
            Rectangle enemyUV = enemyUVs[enemy->enemy.speed];

            // Draw the enemy using the texture atlas
            DrawTextureRec(enemyTextureAtlas, enemyUV, (Vector2){x, y}, RAYWHITE);
        }
    }

    EndDrawing();
}

