#pragma once
#include "Game.h"

Game::Game()
{
	m_game_state = GameState::Play;
	// Пример инициализации уровней
	m_level = std::move(make_unique<Level0>(Level0()));
	B::SystemUpdate();
}

void Game::Update() {
	// Здесь только апдейтим
	switch (m_game_state)
	{
	case GameState::MainMenu:
		// Например 
		// main_menu.Update();
		break;
	case GameState::Play:

		// Например 
		 m_level->Update();
		break;
	default: break;
	}
	UpdateUI();
}

void Game::Action() {
	// Тут только обрабатываем события
	switch (m_game_state)
	{
	case GameState::MainMenu:
		// Например 
		// main_menu.Action();
		break;
	case GameState::Play:
		// Например 
		 m_level->Action();
		break;
	default: break;
	}
	ActionUI();
}

void Game::Draw() {
	B::wnd.clear();

	// Сюда вставляем только отрисовку
	switch (m_game_state)
	{
	case GameState::MainMenu:
		// Например 
		// main_menu.Draw();
		break;
	case GameState::Play:
		// Например 
		 m_level->Draw();
		break;
	default: break;
	}

	// Оставляем метод DrawUI(); перед wnd.display();
	// т.к. слой интерфейса должен отрисовываться самым последним
	DrawUI();
	B::wnd.display();
}

void Game::UpdateUI() {
	B::wnd.setView(B::wnd.getDefaultView());	// Устанавливаем камеру по умолчанию

	// Тут обновляем элементы интерфейса используя cur_p_wnd (Позиция курсора мыши в оконном
	// Например
	// UI_Manager.Update();

	B::wnd.setView(B::cam);	// Возвращаем игровую камеру
}

void Game::ActionUI() {
	B::wnd.setView(B::wnd.getDefaultView());	// Устанавливаем камеру по умолчанию

	// Тут обрабатываем элементы интерфейса используя cur_p_wnd : Позиция курсора мыши в оконной системе координат
	// Например
	// UI_Manager.Action();

	B::wnd.setView(B::cam);	// Возвращаем игровую камеру
}

void Game::DrawUI() {
	B::wnd.setView(B::wnd.getDefaultView());	// Устанавливаем камеру по умолчанию

	// Тут рисуем элементы интерфейса
	// Например
	// UI_Manager.Draw();

	B::wnd.setView(B::cam);	// Возвращаем игровую камеру
}

// Метод Play вообще не трогаем
void Game::Play() {
	float timer = 0;
	int fps = 0;
	while (B::wnd.isOpen()) {
		//Timer timer;
		B::SystemUpdate();
		timer += B::time;
		fps++;
		if (timer >= 1000) {
			timer = 0;
			cout << "FPS: " << fps << endl;
			fps = 0;
		}
		Update();
		while (B::wnd.pollEvent(B::event)) {
			B::CloseEvent();
			Action();
		}
		Draw();
	}
}

Game::~Game() { }

int main()
{
	Base("init");
	Game game;
	game.Play();
	return 0;
}