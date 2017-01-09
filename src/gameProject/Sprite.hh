#pragma once
#include "ID.hh"
#include "Renderer.hh"
#include "Transform.hh"

// Sprite class that serves as part of the Model
struct Sprite {
	Transform transform;
	ObjectID objectID;
	int angle;
	void Draw() { 
		R.Push(objectID, transform, angle);
	};
};