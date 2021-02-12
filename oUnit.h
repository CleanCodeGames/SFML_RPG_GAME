#pragma once
#include "UnitAttribs.h"
#include "UnitStates.h"
#include "Animation.h"

using PC = PlayerControll;

// Базовый класс юнита : Содержащий в себе все основные свойства сущности игровых объектов типа Unit
class oUnit
{
private:

	float m_time_corpse_dying = B::gc.unit_time_dying_corpse;

protected:

	TypeUnit m_type_unit;				// Тип юнита TypeUnit::
	WalkState m_walk_state;				// Состояние движения WalkState::
	LiveState m_live_state;				// Состояние живой или мёртвый LiveState::
	PC m_player_controll;				// Номер игрока PlayerControll::
	Shape m_shape_ui_ico_portret;		// Шейп фейс-портрета юнита
	string m_name;						// Имя юнита
	Shape m_shape;						// Спрайт по умолчанию
	shared_ptr<Animation> m_animation;	// Анимация спрайта
	AutoAttack m_auto_attack;			// Автоатака
	HitPoint m_hit_point;				// Здоровье
	ManaPoint m_mana_point;				// Мана
	MovementSpeed m_move_speed;			// Скорость передвижения
	Armor m_armor;						// Защита
	const v2f m_spawn_position;			// Стартовая позиция (точка спавна, где юнит появился впервые)
	uint m_level;						// Уровень
	bool m_is_click_pick = false;		// Выбран ли юнит кликом мышки

public:

	oUnit(const v2f position, const PC player_controll) 
		: m_spawn_position(position),
			m_player_controll(player_controll){
		m_animation = make_shared<Animation>(Animation(m_shape, v2i(), v2i(), 0));
	}

	virtual ~oUnit() = default;

public: // Gets...

	Animation& GetAnimation() {
		return *m_animation;
	}

	Shape& GetIcoPortret() {
		return m_shape_ui_ico_portret;
	}

	// Уровень
	virtual const uint& GetLevel() {
		return m_level;
	}

	// Может ли использовать атаку
	virtual const bool& GetIsAttackUses() {
		if (m_auto_attack.GetAttackType() == TypeAttack::NONE) 
			return false;
		return true;
	}
	// Здоровье
	virtual HitPoint& GetHitPnt() {
		return m_hit_point;
	}
	// Мана
	virtual ManaPoint& GetManaPnt() {
		return m_mana_point;
	}
	// Автоатака
	virtual AutoAttack& GetAutoAttack() {
		return m_auto_attack;
	}
	// Защита
	virtual Armor& GetArmor() {
		return m_armor;
	}
	// Скорость передвижения
	virtual MovementSpeed& GetMoveSpeed() {
		return m_move_speed;
	}
	// Тип
	virtual const TypeUnit&  GetTypeUnit() {
		return m_type_unit;
	}
	// Состояние движения
	virtual const WalkState& GetWalkState() {
		return m_walk_state;
	}
	// Состояние жизни
	virtual const LiveState& GetLiveState() {
		return m_live_state;
	}
	// Номер игрока контролирующего этого юнита
	virtual const PlayerControll& GetPlayerControll() {
		return m_player_controll;
	}
	// Позиция, где изначально появился юнит
	virtual const v2f& GetSpawnPosition() {
		return m_spawn_position;
	}
	// Имя юнита
	virtual const string& GetName() {
		return m_name;
	}
	// Главный спрайт юнита
	virtual Shape& GetShape() {
		return m_shape;
	}

public: // Sets...

	virtual void SetPortretIco(sf::IntRect texture_rect) {
		m_shape_ui_ico_portret = m_shape;
		m_shape_ui_ico_portret.setPosition(v2f(20, 20));
		m_shape_ui_ico_portret.setSize(v2f(48, 48));
		m_shape_ui_ico_portret.setTextureRect(texture_rect);
	}

	// Задать уровень
	virtual void SetLevel(uint level) {
		m_level = level;
	}
	// Задать значения автоатаки
	virtual void SetAutoAttack(const AutoAttack auto_attack) {
		m_auto_attack = auto_attack;
	}
	// Задать значения здоровья
	virtual void SetHitPnt(const HitPoint point) {
		m_hit_point = point;
	}
	// Задать значения Маны
	virtual void SetManaPnt(const ManaPoint point) {
		m_mana_point = point;
	}
	// Задать значения защиты
	virtual void SetArmor(const Armor armor) {
		m_armor = armor;
	}
	// Задать значения скорости передвижения
	virtual void SetMoveSpeed(const MovementSpeed move_speed) {
		m_move_speed = move_speed;
	}
	// Задать тип юнита
	virtual void SetTypeUnit(const TypeUnit type_unit) {
		m_type_unit = type_unit;
	}
	// Задать состояние движения
	virtual void SetWalkState(const WalkState walk_state) {
		m_walk_state = walk_state;
	}
	// Задать состояние жизни
	virtual void SetLiveState(const LiveState live_state) {
		m_live_state = live_state;
	}
	// Задать игрока контролирующего этого юнита
	virtual void SetPlayerControll(const PlayerControll pcontroll) {
		m_player_controll = pcontroll;
	}
	// Задать имя юнита
	virtual void SetName(const string name) {
		m_name = name;
	}

public: // Operations

	// Если юнит выбран ЛКМ, то возвращает true
	virtual const bool GetIsClickPick() {
		return m_is_click_pick;
	}
	// Фиксирует выбор юнита при нажатии на него ЛКМ
	virtual void ClickPick(const bool value) {
		m_is_click_pick = value;
	}

	// Метод регенерации здоровья и маны юнита
	virtual void RegenerationUpdate() {
		m_hit_point.Update();
		m_mana_point.Update();
	}
	// Убить юнита
	virtual void Kill() {
		m_live_state = LiveState::DYING;
		m_hit_point.SetCurrent(0);
	}
	// Разложение трупа
	virtual void Corpse() {
		if (m_live_state == LiveState::DYING) {
			m_time_corpse_dying -= B::time;
			if (m_time_corpse_dying <= 0) 
				m_live_state = LiveState::DELETED;
		}
	}

public: // Update() Action() Draw()

	virtual void Update() {
		Corpse();
	}
	virtual void Action() = 0;
	virtual void Draw() = 0;
};