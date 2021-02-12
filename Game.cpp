#pragma once
#include "Game.h"

Game::Game()
{
	m_game_state = GameState::Play;
	// ������ ������������� �������
	m_level = std::move(make_unique<Level0>(Level0()));
	B::SystemUpdate();
}

void Game::Update() {
	// ����� ������ ��������
	switch (m_game_state)
	{
	case GameState::MainMenu:
		// �������� 
		// main_menu.Update();
		break;
	case GameState::Play:

		// �������� 
		 m_level->Update();
		break;
	default: break;
	}
	UpdateUI();
}

void Game::Action() {
	// ��� ������ ������������ �������
	switch (m_game_state)
	{
	case GameState::MainMenu:
		// �������� 
		// main_menu.Action();
		break;
	case GameState::Play:
		// �������� 
		 m_level->Action();
		break;
	default: break;
	}
	ActionUI();
}

void Game::Draw() {
	B::wnd.clear();

	// ���� ��������� ������ ���������
	switch (m_game_state)
	{
	case GameState::MainMenu:
		// �������� 
		// main_menu.Draw();
		break;
	case GameState::Play:
		// �������� 
		 m_level->Draw();
		break;
	default: break;
	}

	// ��������� ����� DrawUI(); ����� wnd.display();
	// �.�. ���� ���������� ������ �������������� ����� ���������
	DrawUI();
	B::wnd.display();
}

void Game::UpdateUI() {
	B::wnd.setView(B::wnd.getDefaultView());	// ������������� ������ �� ���������

	// ��� ��������� �������� ���������� ��������� cur_p_wnd (������� ������� ���� � �������
	// ��������
	// UI_Manager.Update();

	B::wnd.setView(B::cam);	// ���������� ������� ������
}

void Game::ActionUI() {
	B::wnd.setView(B::wnd.getDefaultView());	// ������������� ������ �� ���������

	// ��� ������������ �������� ���������� ��������� cur_p_wnd : ������� ������� ���� � ������� ������� ���������
	// ��������
	// UI_Manager.Action();

	B::wnd.setView(B::cam);	// ���������� ������� ������
}

void Game::DrawUI() {
	B::wnd.setView(B::wnd.getDefaultView());	// ������������� ������ �� ���������

	// ��� ������ �������� ����������
	// ��������
	// UI_Manager.Draw();

	B::wnd.setView(B::cam);	// ���������� ������� ������
}

// ����� Play ������ �� �������
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