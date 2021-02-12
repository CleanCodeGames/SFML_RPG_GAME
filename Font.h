#pragma once
#include "Define.h"

struct Font
{
	sf::Font common;
	sf::Font erica_type;

	Font() {
		cout << "Font Loaded\n";
		common.loadFromFile("Resources/Fonts/common.ttf");
		erica_type.loadFromFile("Resources/Fonts/erica_type.ttf");
	}

	~Font() {

	}
};