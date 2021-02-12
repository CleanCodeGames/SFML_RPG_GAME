#pragma once
// Скрывает окно консоли при запуске программы
// #pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

// Подключаем набор используемых стандартных библиотек
#include <iostream>
#include <fstream>
#include <memory>
#include <cmath>
#include <list>
#include <algorithm>
#include <thread>
#include <functional>
#include <chrono>

// И конечно же библиотеки SFML
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Network.hpp>

class Timer
{
private:

	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1>>;
	std::chrono::time_point<clock_t> m_beg;

public:

	Timer() : m_beg(clock_t::now()) { }

	void reset() {
		m_beg = clock_t::now();
	}

	double elapsed() const {
		return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}

	~Timer() {
		std::cout << "Time elapsed " << elapsed() << std::endl;
	}
};

// Определяем супер важные константы для просчётов игровой механики
static constexpr auto PI  = 3.141592;
static constexpr auto DEG = 57.29582;
static constexpr auto RAD = 0.017453;

class Base;		// Предопределяем базовый класс
typedef Base B; // Для сокращения при обращении полей и методов к базовому классу B::get()...

// Используем пространство имён для часто используемых функций стандартной библиотеки
// То же самое что и [_ using namespace std _], только для отдельных частей.
using std::cout;
using std::endl;
using std::to_string;
using std::cos;
using std::cosf;
using std::sin;
using std::sinf;
using std::atanf;
using std::make_shared;
using std::make_unique;

using std::list;
using std::vector;
using std::string;
using std::unique_ptr;
using std::shared_ptr;
using std::ifstream;
using std::ofstream;
using std::thread;

// Деваем длинные название переменных и классов в более короткие
typedef unsigned int uint;
typedef sf::Vector2i v2i;
typedef sf::Vector2f v2f;	// v2f проще чем sf::Vector2f... Не так ли? ))
typedef sf::Keyboard Key;
typedef sf::RectangleShape Shape;
typedef sf::Texture IMG;
typedef sf::Color Color;
typedef sf::IntRect IR;

// Перегрузка оператора вывода для v2f
std::ostream& operator << (std::ostream& out, const v2f& p)
{
	out << "X: " << p.x << " | Y: " << p.y;
	return out;
}
// Перегрузка оператора вывода для v2i
std::ostream& operator << (std::ostream& out, const v2i& p)
{
	out << "X: " << p.x << " | Y: " << p.y;
	return out;
}
// Перегрузка оператора вывода для Shape
std::ostream& operator << (std::ostream& out, const Shape& s)
{
	out << "Position: " << s.getPosition() << endl;
	out << "Size: " << s.getSize() << endl;
	const auto& c = s.getFillColor();
	out << "Color: R = " << sf::Uint16(c.r) << " G = " << sf::Uint16(c.g) << " B = " << sf::Uint16(c.b) << endl;
	return out;
}