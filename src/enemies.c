#include "enemies.h"
#include "ecs.h"
#include "raylib.h"
#include "types.h"
#include "entity_movement.h"

// Texture atlas for all enemies
Texture2D enemyTextureAtlas;

// Define UV coordinates for each enemy type in the texture atlas
Rectangle enemyUVs[4] = {
    { 0, 0, 64, 64 },    // ZOMBIE UVs
    { 64, 0, 64, 64 },   // SKELETON UVs
    { 128, 0, 64, 64 },  // SPIDER UVs
    { 192, 0, 64, 64 }   // SLIME UVs
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

    // Assign ElementType based on EnemyType
    switch(type) {
	    case ZOMBIE:
		    enemy->enemy.elementType = TYPE_GRAVEYARD;
		    enemy->enemy.baseSpeed = 50.0f;
		    enemy->health.health = 150;
		    break;
	    case SKELETON:
		    enemy->enemy.elementType = TYPE_GRAVEYARD;
		    enemy->enemy.baseSpeed = 80.0f;
		    enemy->health.health = 80;
	    case SPIDER:
		    enemy->enemy.elementType = TYPE_FOREST;
		    enemy->enemy.baseSpeed = 105.0f;
		    enemy->health.health = 100;
		    break;
	    case SLIME:
		    enemy->enemy.elementType = TYPE_PLAINS;
		    enemy->enemy.baseSpeed = 90.0f;
		    enemy->health.health = 90;
	    default:
		    enemy->enemy.elementType = TYPE_NONE;
		    enemy->enemy.baseSpeed = 80.0f;
		    enemy->health.health = 100;
    }

    enemy->enemy.currentSpeed = enemy->enemy.baseSpeed;

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
    ClearBackground(RAYWHITE);

    BeginMode2D(camera);
    
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

    EndMode2D();
    EndDrawing();
}

