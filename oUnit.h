#pragma once
#include "UnitAttribs.h"
#include "UnitStates.h"
#include "Animation.h"

using PC = PlayerControll;

// ������� ����� ����� : ���������� � ���� ��� �������� �������� �������� ������� �������� ���� Unit
class oUnit
{
private:

	float m_time_corpse_dying = B::gc.unit_time_dying_corpse;

protected:

	TypeUnit m_type_unit;				// ��� ����� TypeUnit::
	WalkState m_walk_state;				// ��������� �������� WalkState::
	LiveState m_live_state;				// ��������� ����� ��� ������ LiveState::
	PC m_player_controll;				// ����� ������ PlayerControll::
	Shape m_shape_ui_ico_portret;		// ���� ����-�������� �����
	string m_name;						// ��� �����
	Shape m_shape;						// ������ �� ���������
	shared_ptr<Animation> m_animation;	// �������� �������
	AutoAttack m_auto_attack;			// ���������
	HitPoint m_hit_point;				// ��������
	ManaPoint m_mana_point;				// ����
	MovementSpeed m_move_speed;			// �������� ������������
	Armor m_armor;						// ������
	const v2f m_spawn_position;			// ��������� ������� (����� ������, ��� ���� �������� �������)
	uint m_level;						// �������
	bool m_is_click_pick = false;		// ������ �� ���� ������ �����

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

	// �������
	virtual const uint& GetLevel() {
		return m_level;
	}

	// ����� �� ������������ �����
	virtual const bool& GetIsAttackUses() {
		if (m_auto_attack.GetAttackType() == TypeAttack::NONE) 
			return false;
		return true;
	}
	// ��������
	virtual HitPoint& GetHitPnt() {
		return m_hit_point;
	}
	// ����
	virtual ManaPoint& GetManaPnt() {
		return m_mana_point;
	}
	// ���������
	virtual AutoAttack& GetAutoAttack() {
		return m_auto_attack;
	}
	// ������
	virtual Armor& GetArmor() {
		return m_armor;
	}
	// �������� ������������
	virtual MovementSpeed& GetMoveSpeed() {
		return m_move_speed;
	}
	// ���
	virtual const TypeUnit&  GetTypeUnit() {
		return m_type_unit;
	}
	// ��������� ��������
	virtual const WalkState& GetWalkState() {
		return m_walk_state;
	}
	// ��������� �����
	virtual const LiveState& GetLiveState() {
		return m_live_state;
	}
	// ����� ������ ��������������� ����� �����
	virtual const PlayerControll& GetPlayerControll() {
		return m_player_controll;
	}
	// �������, ��� ���������� �������� ����
	virtual const v2f& GetSpawnPosition() {
		return m_spawn_position;
	}
	// ��� �����
	virtual const string& GetName() {
		return m_name;
	}
	// ������� ������ �����
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

	// ������ �������
	virtual void SetLevel(uint level) {
		m_level = level;
	}
	// ������ �������� ���������
	virtual void SetAutoAttack(const AutoAttack auto_attack) {
		m_auto_attack = auto_attack;
	}
	// ������ �������� ��������
	virtual void SetHitPnt(const HitPoint point) {
		m_hit_point = point;
	}
	// ������ �������� ����
	virtual void SetManaPnt(const ManaPoint point) {
		m_mana_point = point;
	}
	// ������ �������� ������
	virtual void SetArmor(const Armor armor) {
		m_armor = armor;
	}
	// ������ �������� �������� ������������
	virtual void SetMoveSpeed(const MovementSpeed move_speed) {
		m_move_speed = move_speed;
	}
	// ������ ��� �����
	virtual void SetTypeUnit(const TypeUnit type_unit) {
		m_type_unit = type_unit;
	}
	// ������ ��������� ��������
	virtual void SetWalkState(const WalkState walk_state) {
		m_walk_state = walk_state;
	}
	// ������ ��������� �����
	virtual void SetLiveState(const LiveState live_state) {
		m_live_state = live_state;
	}
	// ������ ������ ��������������� ����� �����
	virtual void SetPlayerControll(const PlayerControll pcontroll) {
		m_player_controll = pcontroll;
	}
	// ������ ��� �����
	virtual void SetName(const string name) {
		m_name = name;
	}

public: // Operations

	// ���� ���� ������ ���, �� ���������� true
	virtual const bool GetIsClickPick() {
		return m_is_click_pick;
	}
	// ��������� ����� ����� ��� ������� �� ���� ���
	virtual void ClickPick(const bool value) {
		m_is_click_pick = value;
	}

	// ����� ����������� �������� � ���� �����
	virtual void RegenerationUpdate() {
		m_hit_point.Update();
		m_mana_point.Update();
	}
	// ����� �����
	virtual void Kill() {
		m_live_state = LiveState::DYING;
		m_hit_point.SetCurrent(0);
	}
	// ���������� �����
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