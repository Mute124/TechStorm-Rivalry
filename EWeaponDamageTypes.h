#pragma once

// translate enums to strings (These come from the .tsr files!)
#define WEAPON_NULL_STR "null"
#define WEAPON_KINETIC_STR "kinetic"
#define WEAPON_HEAT_STR "heat"
#define WEAPON_EXPLOSIVE_STR "explosive"
#define WEAPON_ELECTRIC_STR "electric"
#define WEAPON_TOXIC_STR "toxic"
#define WEAPON_RAD_STR "rad"
#define WEAPON_LASER_STR "laser"
#define WEAPON_SHINY_STR "shiny"


// Should be self explanatory
typedef enum EWeaponDamageTypes {
	WEAPON_NULL,
	WEAPON_KINETIC,
	WEAPON_HEAT,
	WEAPON_EXPLOSIVE,
	WEAPON_ELECTRIC,
	WEAPON_TOXIC,
	WEAPON_RAD,
	WEAPON_LASER,
	WEAPON_SHINY, // oh god if you have this.....
};