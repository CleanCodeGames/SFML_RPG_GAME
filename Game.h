#pragma once
#include "Player.h"
#include "oLevel.h"
#include "Level0.h"

enum class GameState : uint {
	MainMenu,
	Play
};

class Game
{
public:

	// Вызывается в main() функции 
	// Она находится в самом низу файла Game.cpp
	void Play();

	Game();
	~Game();

private:

	GameState m_game_state;
	unique_ptr<oLevel> m_level;
	// MainMenu main_menu;

private:

	// Архитектура содержит простое правило трёх UAD - Update, Action и Draw.

	void Update();
	void Action();
	void Draw();

	void UpdateUI();
	void ActionUI();
	void DrawUI();
};