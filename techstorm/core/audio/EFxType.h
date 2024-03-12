#pragma once

/*
* FX_NULL is the default and denotes an unset type.
* FX_AMBIENT are those that are well ambient, examples of which include room tone, environment mood, etc
* FX_PRIVATE are sounds only the player can hear, NPCs will not react to them.
* FX_GLOBAL are sounds that can be heard by the player and NPCs will react to them.
*
*/
typedef enum EFxType {
	FX_NULL,
	FX_AMBIENT,
	FX_PRIVATE,
	FX_GLOBAL
};
