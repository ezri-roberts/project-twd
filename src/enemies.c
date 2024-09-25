#include "enemies.h"
#include <stdlib.h>

// Create a new enemy entity
GameEntity *create_enemy(EnemyType type, float x, float y, int speed, int damage) {
    GameEntity *enemy = create_entity(position, speed, 50); // Create a moving enemy
    EnemyComponent *enemyComp = malloc(sizeof(EnemyComponent));
    enemyComp->speed = speed;
    enemyComp->damage = damage;
    enemyComp->x = x;
    enemyComp->y = y;
    enemyComp->type = type;
    enemyComp->resistance = resitance;

    add_entity("enemy", enemy); // Add enemy to the ECS map

    return enemy;
}

// Update all enemy entities
void update_enemy_system(float deltaTime) {
    map_iter_t iter = map_iter_();
    const char *key;
    
    while ((key = map_next_(&entity_map, &iter))) {
        GameEntity *entity = (GameEntity *)map_get_(&entity_map, key);
        if (entity && entity->entity.isActive) {
            // Movement logic depending on enemy type
            EnemyComponent *enemyComp = (EnemyComponent *)entity->component;

	    switch (enemyComp->type) {
		    case ZOMBIE:
			enemyComp->x += (enemyComp->speed * 0.5f) * deltaTime;
			break;
	   	    case SKELETON:
			enemyComp->x += enemyComp->speed * deltaTime;
			break;
		    case SPIDER:
   			enemyComp->x += (enemyComp->speed * 0.7f) * deltaTime;
			enemyComp->y += (enemyComp->speed * 0.7f) * deltaTime;
			break;
		default:
			break;

        }
	    entity->position.position x = enemyComp->x;
	    entity->position.position y = enemyComp->y;
    }
  }
}

// Render enemies
void render_enemy_system(void) {
    map_iter_t iter = map_iter_();
    const char *key;
    
    while ((key = map_next_(&entity_map, &iter))) {
        GameEntity *entity = (GameEntity *)map_get_(&entity_map, key);
        if (entity && entity->entity.isActive) {
            EnemyComponent *enemyComp = (EnemyComponent *)entity->component;

	    switch(enemyComp ->type) {
		   case ZOMBIE:
			DrawCircle(enemyComp->x, enemyComp->y, 20, GREEN); //ZOMBIE					   
			break;
		   case SKELETON:
			DrawCircle(enemyComp->x, enemyComp->y, 20, WHITE); //SKELETON
			break;
		   case SPIDER:
			DrawCircle(enemyComp->x, enemyComp->y, 20, BLACK); //SPIDER
			break;
		default:
			break;
	    }
        }
    }
}

