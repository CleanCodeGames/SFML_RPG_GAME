#pragma once
#include "Define.h"
class Music
{
public:

	Music() {

	}

	void LoadLevel_0() {
		// ��� �������� ������ ������
		cout << "Music Loaded: [Level 0]\n";
	}
	void LoadLevel_1() {
		cout << "Music Loaded: [Level 1]\n";
		// ��� �������� ������ ������
	}
	void Crlearmemory() {
		cout << "Music Clear Memory: [Level 1]\n";
		// ��� ������� ������
	}

	~Music() {

	}
};

class Sound
{
public:

	Sound() {

	}

	void LoadLevel_0() {
		// ��� �������� ������ ������
		cout << "Sound Loaded: [Level 0]\n";
	}
	void LoadLevel_1() {
		cout << "Sound Loaded: [Level 1]\n";
		// ��� �������� ������ ������
	}
	void Crlearmemory() {
		cout << "Sound Clear Memory: [Level 1]\n";
		// ��� ������� ������
	}

	~Sound() {

	}
};

class Audio
{
public:
	
	Music music;
	Sound sound;

	Audio() {
	}

	void Crlearmemory() {
		cout << "Audio Clear Memory: (Music and Sound)\n";
		music.Crlearmemory();
		sound.Crlearmemory();
	}

	~Audio() {
	}
};