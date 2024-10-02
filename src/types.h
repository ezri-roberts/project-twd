#ifndef TYPES_H
#define TYPES_H

typedef enum {
	TYPE_NONE,
	TYPE_GRAVEYARD,
	TYPE_FOREST,
	TYPE_PLAINS,
} ElementType;

typedef struct {
	ElementType attacker;
	ElementType defender;
	float multiplier;
} TypeEffectiveness;

float get_type_multiplier(ElementType attacker, ElementType defender);

#endif

