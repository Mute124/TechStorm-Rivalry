#pragma once

// auto updates if you add or remove slots
#define SLOT_COUNT sizeof(EBodySlots)

// Slots on your body.
typedef enum EBodySlots {
	SLOT_NULL,
	SLOT_HEAD,
	SLOT_CHEST,
	SLOT_LEGS,
	SLOT_FEET,
	SLOT_HANDS,
	SLOT_ARMS,
} ebs;
