#pragma once

// Child represents what is actually in the slot. The ID is the id of the child type and slotIndex is the slot index
typedef struct BodySlot {
	int childID;
	int slotIndex;
} bs; // No this is not bullshit...