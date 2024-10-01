#ifndef ENEMIES_H
#define ENEMIES_H

#include "ecs.h"

typedef enum {
	ZOMBIE,
	SKELETON,
	SPIDER
} EnemyType;


// Enemy-specific components
typedef struct {
    int damage;
    float speed;
    EnemyType type;
    float resistance;
} EnemyComponent;

// Function declarations
GameEntity *create_enemy(EnemyType type, float x, float y, int speed, int damage, float resistance);
void update_enemy_system(float deltaTime);
void render_enemy_system(void);

#endif


