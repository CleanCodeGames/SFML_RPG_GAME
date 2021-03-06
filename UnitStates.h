#pragma once
// ����� ������, �������� ����������� ����
// �� �������, ���� ����� ������� ������� ������ ����
enum class PlayerControll : uint {
	P_0, P_1, P_2, P_3, P_4, P_5, P_6, P_7, P_8, P_9, P_10, P_11, P_12,
	P_13, P_14, P_15, P_16, P_17, P_18, P_19, P_20, P_21, P_22, P_23, // ������

	P_NEUTRALL,				// ���������� ��������� (��������, ��������, ��������)
	P_HOSTILE_AND_NEUTRALL,	// ���������� ����������, �� �������� �������.
	P_HOSTILE				// ������������� ���������� ����.
};

// ����� ����� ������, �������� �� �����������
// T_0 = Team_0
enum class PlayerClan : uint {
	T_0, T_1, T_2, T_3, T_4, T_5, T_6, T_7, T_8, T_9, T_10, T_11, T_12,
	T_13, T_14, T_15, T_16, T_17, T_18, T_19, T_20, T_21, T_22, T_23
};

// ���� ������, ��� ������������ � ����������� 
// - ����������� ���������� ������������ �� ����������� ���
enum class TypeUnit : uint {
	ANIMAL,		// �������� (���������� ���������)
	BEAST,		// �����	
	DEMON,		// �����	
	HUMANOID,	// ��������	
	GHOST,		// �������	
	MECHANICAL,	// ������������
	BUILDING	// ������
};

// ��������� ���������� �� ����� �����
enum class LiveState : uint {
	ALIVE,		// ���
	DYING,		// �����
	DELETED		// ����������, ����� ������� �� ������
};

// ��������� ��������
enum class WalkState : uint {
	STAND,	// ����� �� �����
	WALK,	// �������������
	ATTACK,	// �������
	CAST	// ������ ����������
};