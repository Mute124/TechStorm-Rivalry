#pragma once
#include "common.h"

typedef struct {
	Texture albedoMap; // The diffuse texture
	Texture normalMap;
	Texture mraoMap; // metallic, roughness, ao
	Texture emissiveMap;

	float metallic;
	float roughness;
	float ao;

	Color albedoColor;
	Color emissiveColor; // Set transparency to 0 to disable
}MaterialMapProperties;

class GameObjectMaterial {
public:

	GameObjectMaterial(MaterialMapProperties properties, bool usedefaultShader, Shader* shader = nullptr) : mapProperties(properties), useDefaultShader(usedefaultShader) {
		if (useDefaultShader) {
			delete shader;

			this->material.maps[MATERIAL_MAP_ALBEDO].color = properties.albedoColor;
			this->material.maps[MATERIAL_MAP_METALNESS].value = properties.metallic;
			this->material.maps[MATERIAL_MAP_ROUGHNESS].value = properties.roughness;
			this->material.maps[MATERIAL_MAP_OCCLUSION].value = properties.ao;

			bool useEmmisive = properties.emissiveColor.a != 0;
			// check if disabled
			if (useEmmisive) {
				this->material.maps[MATERIAL_MAP_EMISSION].color = properties.emissiveColor;
			}

			this->material.maps[MATERIAL_MAP_ALBEDO].texture = properties.albedoMap;

			// mrao map kinda sounds like meeeeoooooowwww, Who let a kitten into the software? was it you dave? I bet it was.
			this->material.maps[MATERIAL_MAP_METALNESS].texture = properties.mraoMap;

			this->material.maps[MATERIAL_MAP_NORMAL].texture = properties.normalMap;
			// check if disabled
			if (useEmmisive) {
				this->material.maps[MATERIAL_MAP_EMISSION].texture = properties.emissiveMap;
			}
		}
	};

private:

	const bool useDefaultShader;
	MaterialMapProperties mapProperties;

	// instead of doing this every single god damn time manually, we just compile it now.
	Material material;
};