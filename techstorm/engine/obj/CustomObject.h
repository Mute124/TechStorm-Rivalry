#pragma once
#include "Gameobject.h"

// Example game object
class CustomObject : public GameObject {
public:
	CustomObject(Vector3 pos, Model model, Shader shdr, Texture texture, Color tint) : position(position), model(model), texture(texture), tint(tint) {
	}

	CustomObject(Vector3 pos, Model model, Shader shdr, Texture texture) : position(position), model(model), texture(texture) {
	}

	void draw() override {
		DrawModel(this->model, position, 1.0f, tint);
	}

	void onUpdate() override {
	}

	// What to do when destroyed.
	void onDestroy() const override {
		delete this;
	}

private:
	Texture texture;
	Model model;

	Vector3 position;
	// set to white unless otherwise is true
	Color tint = WHITE;
};
