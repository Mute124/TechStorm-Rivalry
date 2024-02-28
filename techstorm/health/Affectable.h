#pragma once

//Now we need to define the string equivilents of the enum types
#define AFFECTABLE_NULL_STR "null"
#define AFFECTABLE_AFFLICTION_STR "affliction"
#define AFFECTABLE_HEALTH_STR "health"
#define AFFECTABLE_BLOOD_FLOW_STR "blood_flow"
#define AFFECTABLE_BLOOD_PRESSURE_STR "blood_pressure"
#define AFFECTABLE_BLOOD_OXYGEN_STR "blood_oxygen"
#define AFFECTABLE_BLOOD_VOLUME_STR "blood_volume"
#define AFFECTABLE_BLOOD_SUGAR_STR "blood_sugar"
#define AFFECTABLE_BLOOD_SODIUM_STR "blood_sodium"
#define AFFECTABLE_BLOOD_CONCENTRATION_STR "blood_concentration"
#define AFFECTABLE_BLOOD_ADRENALIN_STR "blood_adrenalin"
#define AFFECTABLE_BLOOD_DISEASE_STR "blood_disease"
#define AFFECTABLE_BLOOD_TEMPERATURE_STR "blood_temperature"
#define AFFECTABLE_BLOOD_HEALTH_STR "blood_health"

#define AFFECTABLE_BONE_DENSITY_STR "bone_density"
#define AFFECTABLE_BONE_DAMAGE_STR "bone_damage"
#define AFFECTABLE_BONE_HEALTH_STR "bone_health"
#define AFFECTABLE_BONE_DISEASE_STR "bone_disease"
#define AFFECTABLE_BONE_OXYGEN_STR "bone_oxygen"
#define AFFECTABLE_BONE_FATIGUE_STR "bone_fatigue"

#define AFFECTABLE_MUSCLE_OXYGEN_STR "muscle_oxygen"
#define AFFECTABLE_MUSCLE_FATIGUE_STR "muscle_fatigue"

#define AFFECTABLE_MAX 20

// This Enum defines what a affliction can actually affect
typedef enum EAffectable {
	AFFECTABLE_NULL, // No affect
	AFFECTABLE_AFFLICTION, // affects another affliction
	AFFECTABLE_HEALTH, // Overall health
	// Blood
	AFFECTABLE_BLOOD_FLOW, // blood flow (if it is zero, well your heart is dead)
	AFFECTABLE_BLOOD_PRESSURE, // blood pressure
	AFFECTABLE_BLOOD_OXYGEN, // blood oxygen levels
	AFFECTABLE_BLOOD_VOLUME, // blood volume level
	AFFECTABLE_BLOOD_SUGAR, // blood sugar level
	AFFECTABLE_BLOOD_SODIUM, // Blood Sodium Level
	AFFECTABLE_BLOOD_CONCENTRATION, // blood dilution level
	AFFECTABLE_BLOOD_ADRENALIN, // blood adrenalin level
	AFFECTABLE_BLOOD_DISEASE, // blood pathogenic infection, for example, sepsis
	AFFECTABLE_BLOOD_TEMPERATURE, // blood temperature
	AFFECTABLE_BLOOD_HEALTH, // blood health.

	// bone affects
	AFFECTABLE_BONE_DENSITY, // bone density is how strong the bone is
	AFFECTABLE_BONE_DAMAGE, // bone damage is how damaged the bone is
	AFFECTABLE_BONE_FATIGUE, // bone stress is how stressed the bone is mechanically
	AFFECTABLE_BONE_OXYGEN, // bone oxygen levels
	AFFECTABLE_BONE_DISEASE, // bone pathogenic infection, for example, bone based diseases
	AFFECTABLE_BONE_HEALTH, // bone health is how healthy the bone is

	// Muscular
	AFFECTABLE_MUSCLE_OXYGEN, // muscle oxygen levels (this is crucial for them to even work!)
	AFFECTABLE_MUSCLE_FATIGUE, // muscle fatigue
	AFFECTABLE_MUSCLE_ENDURANCE, // muscle endurance
	AFFECTABLE_MUSCLE_STRENGTH, // strength of the muscle (How much weight/stress it can handle)
	AFFECTABLE_MUSCLE_AGILITY, // muscle agility (How fast the muscle can move)
	AFFECTABLE_MUSCLE_DAMAGE, // The damage level of the muscle
	AFFECTABLE_MUSCLE_DEXTERITY, // muscle dexterity (How well the muscle is able to move)
	AFFECTABLE_MUSCLE_DISEASE, // muscle pathogenic infection, for example, muscle based diseases
	AFFECTABLE_MUSCLE_HEALTH, // muscle health

	// Critical organs (heart, brain, lungs)
	AFFECTABLE_LUNG_OXYGEN, // lung tissue oxygen levels
	AFFECTABLE_LUNG_CARBONIZATION, // lung tissue carbonization for example smokers lung
	AFFECTABLE_LUNG_DAMAGE, // lung tissue damage
	AFFECTABLE_LUNG_PLEURAL_EFFUSION, // lung fluid levels
	AFFECTABLE_LUNG_RESPIRATION, // lung gas exchange (How much oxygen gets absorbed)
	AFFECTABLE_LUNG_FATIGUE, // lung fatigue (is character out of breath?)
	AFFECTABLE_LUNG_DISEASE, // lung pathogenic infection, for example, lung based diseases
	AFFECTABLE_LUNG_SIZE, // lung size
	AFFECTABLE_LUNG_HEALTH, // lung health

	// Brain
	AFFECTABLE_BRAIN_OXYGEN, // brain oxygen levels
	AFFECTABLE_BRAIN_DAMAGE,
	AFFECTABLE_BRAIN_DISEASE, // brain pathogenic infection, for example, brain based diseases
	AFFECTABLE_BRAIN_INTERCRANIAL, // brain intercranial pressure
	AFFECTABLE_BRAIN_HEALTH, // brain health

	// Overall needs
	AFFECTABLE_NEED_CALORIES, // Daily caloric need
	AFFECTABLE_NEED_WATER, // daily water need
	AFFECTABLE_NEED_BLOOD, // Healthy threshold for blood level
	AFFECTABLE_NEED_OXYGEN, // Healthy threshold for oxygen level

	// Overall factors
	AFFECTABLE_OXYGEN, // Overall oxygen levels
	AFFECTABLE_FATIGUE, // how sore the character is
	AFFECTABLE_TEMPERATURE, // character temperature
	AFFECTABLE_RESISTANCE, // character resistances to other afflictions
};
