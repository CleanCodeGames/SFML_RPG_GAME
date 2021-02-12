#pragma once
#include "Texture.h"
#include "Font.h"
#include "Audio.h"

class ResourcesManager {
public:

	Texture texture;
	Audio audio;
	Font font;

	ResourcesManager() {
	}

	~ResourcesManager() {

	}
};