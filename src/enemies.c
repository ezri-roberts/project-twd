#include "enemies.h"
#include <stdlib.h>

static int enemyID = 0;  // Global/static variable for unique ID generation

GameEntity *create_enemy(EnemyType type, float x, float y, int speed, int damage, float resistance) {
    // Create the enemy entity
    GameEntity *enemy = create_entity(type, x, y, speed, 50);
    if (!enemy) return NULL;

    // Allocate memory for enemy-specific components
    EnemyComponent *enemyComp = malloc(sizeof(EnemyComponent));
    if (!enemyComp) {
        free(enemy); 
        return NULL;
    }

    // Initialize the enemy component
    enemyComp->speed = speed;
    enemyComp->damage = damage;
    enemyComp->type = type;
    enemyComp->resistance = resistance;

    // Assigns position directly to PositionComponent
    enemy->position.x = x;
    enemy->position.y = y;

    // Attach the component to the enemy entity
    enemy->component = enemyComp; 

    // Add enemy to the ECS map
    char key[20];
    sprintf(key, "enemy_%d", enemyID++);  // Generate unique key for each enemy
    add_entity(key, enemy); 

    return enemy;
}

