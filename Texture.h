#pragma once
#include "Define.h"

enum class TXR_Animal: uint {
	CHICKEN_EAT__128x128__4x4, CHICKEN_WALK__128x128__4x4,
	COW_EAT__512x512__4x4, COW_WALK__512x512__4x4,
	LAMMA_EAT__512x512_4x4, LAMMA_WALK__512x512_4x4,
	PIG_EAT__512x512__4x4, PIG_WALK__512x512__4x4,
	SHEEP_EAT__512x512__4x4, SHEEP_WALK__512x512__4x4
};

enum class TXR_Civilian : uint {
	CIVILIAN__624x576__4x2__3x4__52x72
};

class Texture
{
private:

	IMG Load(const string file, bool isSmooth = false) {
		IMG texture;
		texture.loadFromFile("resources/images/" + file);
		texture.setSmooth(isSmooth); // Применяйте сглаживание только для вращающихся объектов
		return texture;
	}

public:

	vector<IMG> terrains;		// Набор текстур поверхности земли
	vector<IMG> trees;			// Набор текстур деревьев
	vector<IMG> borders;		// Набор текстур ограждений
	vector<IMG> decorations;	// Набор текстур декораций (Камни, кусты и т.д)
	vector<IMG> grass;			// Набор текстур травы
	vector<IMG> units_animal;	// Набор текстур юнитов (животные, куры, коровы...)
	vector<IMG> units_civilian;	// Набор текстур юнитов (мирные жители)
	vector<IMG> units_enemies;	// Набор текстур юнитов нейтрально враждебных (Мобы)
	vector<IMG> effects;		// Набор текстур спецэффектов

	IMG click_picked;

	static constexpr uint NUM_TERRAIN		= 50;
	static constexpr uint NUM_GRASS			= 10;
	static constexpr uint NUM_DECORATION	= 19;
	static constexpr uint NUM_TREE			=  7;
	static constexpr uint NUM_BORDER		=  3;
	static constexpr uint NUM_UNIT_ANIMAL	= 14;
	static constexpr uint NUM_UNIT_HOSTILE	= 75;
	static constexpr uint NUM_UNIT_CIVILIAN = 9;

	Texture() {
		
	}

	// Загрузка текстур для тестового уровня 0
	void LoadLevel_0() {
		cout << "Texture Loaded: [Level 0]\n";
		for (int i = 0; i < NUM_TERRAIN; i++)		terrains.push_back(Load("Map/Terrain/terrain" + to_string(i) + ".png"));
		for (int i = 0; i < NUM_GRASS; i++)			grass.push_back(Load("Map/Grass/grass" + to_string(i) + ".png"));
		for (int i = 0; i < NUM_DECORATION; i++)	decorations.push_back(Load("Map/Decor/decor" + to_string(i) + ".png"));
		for (int i = 0; i < NUM_TREE; i++)			trees.push_back(Load("Map/Tree/tree" + to_string(i) + ".png"));
		for (int i = 0; i < NUM_BORDER; i++)		borders.push_back(Load("Map/Border/border" + to_string(i) + ".png"));
		for (int i = 0; i < NUM_UNIT_ANIMAL; i++)	units_animal.push_back(Load("Unit/Animal/animal" + to_string(i) + ".png"));
		for (int i = 0; i < NUM_UNIT_HOSTILE; i++)	units_enemies.push_back(Load("Unit/NeutrallHostile/neutrallHostile" + to_string(i) + ".png"));
		for (int i = 0; i < NUM_UNIT_CIVILIAN; i++)	units_civilian.push_back(Load("Unit/Civilian/civilian" + to_string(i) + ".png"));
		click_picked = Load("Unit/clickpicked.png", true);
	}

	void LoadLevel_1() {
		cout << "Texture Loaded: [Level 1]\n";
		// Код загрузки текстур для первого уровня
	}

	void ClearMemory() {
		terrains.clear();
		trees.clear();
		borders.clear();
		decorations.clear();
		grass.clear();
		units_animal.clear();
		units_civilian.clear();
		effects.clear();
	}

	~Texture(void) {
	}
};