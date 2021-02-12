#pragma once
#include "oLevel.h"

class Level0 : public oLevel
{
private:

protected:

public:

	Level0() : oLevel() {
		m_player = make_shared<Player>(PC::P_0, "Heisenberg");
		B::resources.texture.ClearMemory();	// Очищаем память от предыдущих загруженных текстур
		B::resources.texture.LoadLevel_0();	// Загружаем текстуры для текущего уровня
		for (int i = 0; i < 360; i+=10) {
			int type = rand() % 6;
			const v2f spawn_pos = B::GetNormalizedPosition(B::cam_p, 400, i);
			if (type == 0)		m_vec_unit.push_back(make_shared<UnitAnimalChicken>(spawn_pos, PC::P_0));
			else if (type == 1) m_vec_unit.push_back(make_shared<UnitAnimalCow>(spawn_pos, PC::P_NEUTRALL));
			else if (type == 2) m_vec_unit.push_back(make_shared<UnitAnimalLama>(spawn_pos, PC::P_NEUTRALL));
			else if (type == 3) m_vec_unit.push_back(make_shared<UnitAnimalPig>(spawn_pos, PC::P_NEUTRALL));
			else if (type == 4) m_vec_unit.push_back(make_shared<UnitAnimalSheep>(spawn_pos, PC::P_NEUTRALL));
			else if (type == 5) m_vec_unit.push_back(make_shared<UnitAnimalSnake>(spawn_pos, PC::P_NEUTRALL));
		}
		m_player->SetUnitGroup(m_vec_unit);
		m_player->SetHeroGroup(m_vec_hero);
	}

	virtual void Update() override {
		oLevel::Update();
	}

	virtual void Action() override {
		oLevel::Action();
	}

	virtual void Draw() override {
		oLevel::Draw();
	}

	virtual ~Level0() {

	}
};