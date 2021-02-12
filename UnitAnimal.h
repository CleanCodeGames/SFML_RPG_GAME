#pragma once
#include "UnitOrderable.h"
#include "AbilityPassiveRoving.h"

// Класс юнита животное, обычно используется как декорация
// Бегающие нейтральные куры, коровы и т.д.
class UnitAnimal : public UnitOrderable
{
protected:

	AbilityPassiveRoving m_ability_roving;	// Пассивная пособность "Бродячий"
	float m_timer_stand_or_eat = 0;			// Переодичный таймер переключения состояний на движение и есть
	bool m_is_eat = false;					// Флаг переключения состояний  движение и есть
	
public:

	UnitAnimal(const v2f position, const PC player_controll) : UnitOrderable(position, player_controll),
		m_ability_roving(*this) {
		SetTypeUnit(TypeUnit::ANIMAL);
		SetLiveState(LiveState::ALIVE);
		SetWalkState(WalkState::STAND);
		SetAutoAttack(AutoAttack(TypeAttack::NONE));
		SetArmor(Armor(TypeArmor::CLOTH, 0, 0));
		SetHitPnt(HitPoint(5, 5, 0));
		SetManaPnt(ManaPoint(0, 0, 0));
		SetLevel(1);
	}

	virtual void Update() override 
	{ 
		const float angle = 180 + B::GetAngle(m_shape, m_order->GetTargetPosition());
		m_ability_roving.Update();
		m_timer_stand_or_eat -= B::time;
		if (m_timer_stand_or_eat <= 0) {
			m_timer_stand_or_eat = rand() % 2500 + 1500;
			m_is_eat = !m_is_eat;
		}
		UnitOrderable::Update();
	}

	virtual void Action() override 
	{ 
	}

	virtual void Draw() override {
		B::wnd.draw(m_shape);
	}
	virtual ~UnitAnimal() {

	}
};

class UnitAnimalChicken : public UnitAnimal {

public:

	UnitAnimalChicken(const v2f position, const PC player_controll)
		: UnitAnimal(position, player_controll) {
		
		SetName("Chicken");
		SetMoveSpeed(MovementSpeed(0.2));
		m_shape = B::CreateShape(m_spawn_position, v2f(36, 36));
		m_shape.setTexture(&B::resources.texture.units_animal[0]);
		m_shape.setTextureRect(IR(0, 0, 32, 32));
		m_animation = make_shared<Animation>(Animation(m_shape, v2i(32, 32), v2i(0, 0), 4));
	}

	virtual void Update() override {
		UnitAnimal::Update();
	}

	virtual ~UnitAnimalChicken() {

	}
};

class UnitAnimalCow : public UnitAnimal
{
public:

	UnitAnimalCow(const v2f position, const PC player_controll)
		: UnitAnimal(position, player_controll) {
		SetName("Cow");
		SetMoveSpeed(MovementSpeed(0.12));
		m_shape = B::CreateShape(m_spawn_position, v2f(58, 58));
		m_shape.setTexture(&B::resources.texture.units_animal[2]);
		m_shape.setTextureRect(IR(0, 0, 71, 71));
	}

	virtual void Update() override {
		UnitAnimal::Update();
	}

	virtual ~UnitAnimalCow() {

	}
};

class UnitAnimalLama : public UnitAnimal
{
public:

	UnitAnimalLama(const v2f position, const PC player_controll)
		: UnitAnimal(position, player_controll) {

		SetName("Lama");
		SetMoveSpeed(MovementSpeed(0.16));
		m_shape = B::CreateShape(m_spawn_position, v2f(52, 52));
		m_shape.setTexture(&B::resources.texture.units_animal[4]);
		m_shape.setTextureRect(IR(0, 0, 67, 67));
	}

	virtual void Update() override {
		UnitAnimal::Update();
	}

	virtual ~UnitAnimalLama() {

	}
};

class UnitAnimalPig : public UnitAnimal
{
public:

	UnitAnimalPig(const v2f position, const PC player_controll)
		: UnitAnimal(position, player_controll) {

		SetName("Pig");
		SetMoveSpeed(MovementSpeed(0.16));
		m_shape = B::CreateShape(m_spawn_position, v2f(48, 48));
		m_shape.setTexture(&B::resources.texture.units_animal[6]);
		m_shape.setTextureRect(IR(0, 0, 57, 57));
	}

	virtual void Update() override {
		UnitAnimal::Update();
	}

	virtual ~UnitAnimalPig() {

	}
};

class UnitAnimalSheep : public UnitAnimal
{
public:

	UnitAnimalSheep(const v2f position, const PC player_controll)
		: UnitAnimal(position, player_controll) {

		SetName("Sheep");
		SetMoveSpeed(MovementSpeed(0.2));
		m_shape = B::CreateShape(m_spawn_position, v2f(45, 45));
		m_shape.setTexture(&B::resources.texture.units_animal[8]);
		m_shape.setTextureRect(IR(0, 0, 54, 54));
	}

	virtual void Update() override {
		UnitAnimal::Update();
	}

	virtual ~UnitAnimalSheep() {

	}
};

class UnitAnimalSnake : public UnitAnimal
{
public:

	UnitAnimalSnake(const v2f position, const PC player_controll)
		: UnitAnimal(position, player_controll) {

		SetName("Sheep");
		SetMoveSpeed(MovementSpeed(0.08));
		m_shape = B::CreateShape(m_spawn_position, v2f(36, 36));
		m_shape.setTexture(&B::resources.texture.units_animal[rand()%4+10]);
		m_shape.setTextureRect(IR(0, 0, 54, 54));
	}

	virtual void Update() override {
		UnitAnimal::Update();
	}

	virtual ~UnitAnimalSnake() {

	}
};