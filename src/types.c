#include "types.h"


TypeEffectiveness type_effectiveness[] = {
	{ TYPE_GRAVEYARD, TYPE_FOREST, 2.0f }, // Graveyard enemies are strong against Forest type enemies, (example)
};

#define TYPE_EFFECTIVENESS_COUNT (sizeof(type_effectiveness) / sizeof(TypeEffectiveness))

float get_type_multiplier(ElementType attacker, ElementType defender) {
	for (int i = 0; i < TYPE_EFFECTIVENESS_COUNT; i++) {
		if (type_effectiveness[i].attacker == attacker && type_effectiveness[i].defender == defender) {
			return type_effectiveness[i]multiplier;
		}
	}
	return 1.0f;
}

