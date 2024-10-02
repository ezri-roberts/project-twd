#ifndef ECS_H
#define ECS_H

#define MAX_ENTITIES 1000  // Maximum number of entities in the ECS

#include "raylib.h"  // For Rectangle, Vector2, etc.
#include "types.h"

// Define enemy types and properties

typedef enum {
	ZOMBIE,
	SKELETON,
	SPIDER,
	SLIME,
	MUMMY
} EnemyType;

typedef enum {
    COMPONENT_POSITION = (1 << 0),
    COMPONENT_HEALTH = (1 << 1),
    COMPONENT_ENEMY = (1 << 2),
    COMPONENT_COLLISION = (1 << 3),
    COMPONENT_TYPE = (1 << 4) 
} ComponentType;

// Position component for movement
typedef struct {
    float x, y;
} PositionComponent;

// Health component for storing health/damage
typedef struct {
    int health;
    int damage;
} HealthComponent;

// Enemy-specific component for enemies
typedef struct {
    float baseSpeed; //Base speed w/o modifiers
    float currentSpeed; //Current speed, can be modified
    int resistance; // General resistance to damage
    EnemyType type; // Type of enemy
    ElementType elementType; // Element type for type-based interactions
} EnemyComponent;

// Collision component (bounding box)
typedef struct {
    Rectangle bounds;
} CollisionComponent;

// Game entity structure
typedef struct {
    int id;
    unsigned int componentMask;
    PositionComponent position;
    HealthComponent health;
    EnemyComponent enemy;
    CollisionComponent collision;
    TypeComponent type;
} GameEntity;

// Function declarations
GameEntity* create_entity();
void add_entity(GameEntity *entity);
void remove_entity(GameEntity *entity);
void update_entity_system(float deltaTime);
void apply_damage(GameEntity *entity, int damage, ElementType attackerType);
void handle_collisions();

#endif

