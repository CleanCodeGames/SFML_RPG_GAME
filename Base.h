#pragma once
#include "ResourcesManager.h"
#include "GameConstants.h"

class Base
{
public:

	// ================================= //
	// ���������� ������ �������� ������ //
	// ================================= //

	// ���������� ����� �������� ������
	// �������� ������ � ������ ������ Update() � ������ Game � ����� ������
	static void SystemUpdate() {
		// ���������� ���������� ������� ������� ����
		time = float(clock.getElapsedTime().asMicroseconds()) / 1000.f, clock.restart();
		// ���������� ������� ������� � ���������� ������� ���������
		cur_p = wnd.mapPixelToCoords(sf::Mouse::getPosition(wnd));
		// ���������� ������� ������� � ������� ������� ���������
		cur_p_wnd = v2f(sf::Mouse::getPosition(wnd));
		// ���������� ������� ������ ������ ����
		cam_p = cam.getCenter();
	}

	// ���������� ������� �������� ����
	static void CloseEvent() {
		if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == Key::Escape)) wnd.close();
	}

	// ���������� ������� ��������� ������
	static const sf::FloatRect GetCamVisible() {
		return sf::FloatRect(
			cam.getCenter().x - (cam.getSize().x / 2),	// X ����� ����� ������
			cam.getCenter().y - (cam.getSize().y / 2),	// Y ������� ����� ������
			cam.getSize().x,							// X ������ ������
			cam.getSize().y);							// Y ������ ������
	}

	// ���������� ������� ������������ pos �� ���������� dist � ����������� angle
	static const v2f GetNormalizedPosition(const v2f& pos, float dist, float angle) {
		const float& A = angle * RAD;
		return pos + v2f(cosf(A), sinf(A)) * dist;
	}

	// ���������� ������� ������������ ������ ������ shape �� ���������� dist � ����������� angle
	static const v2f GetNormalizedPosition(Shape& shape, float dist, float angle) {
		const float& A = angle * RAD;
		return shape.getPosition() + v2f(cosf(A), sinf(A)) * dist;
	}

	// ���������� ���������� pos � ������ shape
	static const bool IsContains(Shape& shape, const v2f& pos) {
		return shape.getGlobalBounds().contains(pos);
	}

	// ���������� ��������� ��������������� ���� �����������
	// ��������� ������� sf::RectangleShape, ������������ ��� ����� 
	// � �������� ���������� � ������������� ������
	// �� ����� �� ������ ����������� ����� ��� sf::CircleShape
	static const bool GetCollisionCircle(Shape& c1, Shape& c2) {
		const float r1 = c1.getSize().x / 2.f;
		const float r2 = c2.getSize().x / 2.f;
		const v2f& p1 = c1.getPosition();
		const v2f& p2 = c2.getPosition();
		return GetDistance(p1, p2) > float(r1 + r2) ? false : true;
	}

	// ���������� ��������� ��������������� ���� ���������������
	// ��������� ������� sf::RectangleShape
	static const bool GetCollisionRect(Shape& s1, Shape& s2) {
		return s1.getGlobalBounds().intersects(sf::FloatRect(
			s2.getPosition().x - (s2.getSize().x / 2.f), 
			s2.getPosition().y - (s2.getSize().y / 2.f), 
			s2.getSize().x, 
			s2.getSize().y));
	}

	// ���������� ������������ ��� ������������ � ������������� ��������
	// ������������ ������ ������������� �� ������������
	// �������� ������ ����� ����� ������������� �� ������� �����
	static void CollisionUpdate(Shape& static_s1, Shape& dynamic_s2) {
		if (GetCollisionCircle(static_s1, dynamic_s2)) {
			dynamic_s2.setPosition(GetNormalizedPosition(static_s1.getPosition(),
				(dynamic_s2.getSize().x + static_s1.getSize().x) / 1.99f, GetAngle(static_s1, dynamic_s2)));
		}
	}

	// ���������� ���������� ����� ����� ������� v2f
	static const float GetDistance(const v2f& p1, const v2f& p2) {
		return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
	}

	// ���������� ���������� ����� ����� ��������� Shape
	static const float GetDistance(Shape& s1, Shape& s2) {
		const v2f& p1 = s1.getPosition();
		const v2f& p2 = s2.getPosition();
		return GetDistance(p1, p2);
	}

	// ���������� ���������� ����� Shape � v2f
	static const float GetDistance(Shape& s1, const  v2f& pos) {
		const v2f& p1 = s1.getPosition();
		return GetDistance(p1, pos);
	}

	// ��������������� �����-����������� ��� �������� Shape
	// ������ ������������� - Shape shape = CreateShape(v2f(0,0), v2f(10,10), texture.my_loaded_image);
	static const Shape CreateShape(v2f pos, v2f siz, IMG& png) {
		Shape shp;
		shp.setOrigin(siz / 2.f);
		shp.setSize(siz);
		shp.setPosition(pos);
		shp.setTexture(&png);
		return shp;
	}

	// ��������������� �����-����������� ��� �������� Shape
	// ������ ������������� - Shape shape = CreateShape(v2f(0,0), v2f(10,10));
	static const Shape CreateShape(v2f pos, v2f siz) {
		Shape shp;
		shp.setOrigin(siz / 2.f);
		shp.setSize(siz);
		shp.setPosition(pos);
		return shp;
	}

	// ��������������� �����-����������� ��� �������� Shape
	// ������ ������������� - Shape shape = CreateShape(v2f(0,0), v2f(10,10), Color::Yellow);
	static const Shape CreateShape(v2f pos, v2f siz, Color color) {
		Shape shp;
		shp.setSize(siz);
		shp.setOrigin(siz / 2.f);
		shp.setFillColor(color);
		shp.setPosition(pos);
		return shp;
	}

	// ��������������� �����-����������� ��� �������� Shape
	// ������ ������������� - Shape shape = CreateShape(v2f(0,0), v2f(10,10), -3, Color::Red, Color::Yellow);
	static const Shape CreateShape(v2f pos, v2f siz, float out_siz, Color color = Color::White, Color out_color = Color::White) {
		Shape shp;
		shp.setSize(siz);
		shp.setOrigin(siz / 2.f);
		shp.setFillColor(color);
		shp.setPosition(pos);
		shp.setOutlineThickness(out_siz);
		shp.setOutlineColor(out_color);
		return shp;
	}

	// ��������������� �����-����������� ��� �������� sf::Text
	// ������ ������������� sf::Text text = CreateText(v2f(0,0), 16, "�����-�� �����", font.my_loaded_font, Color::Magenta);
	static const sf::Text CreateText(v2f pos, uint siz, sf::String str, sf::Font& font, Color col) {
		sf::Text text;
		text.setFont(font);
		text.setCharacterSize(siz);
		text.setFillColor(col);
		text.setString(str);
		//text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
		text.setPosition(pos.x, pos.y - siz / 3);
		return text;
	}

	// ���������� ����������� � �������� ������������ ����� p1 � ����� p2
	static const float GetAngle(const v2f& p1, const v2f& p2) {
		return atan2f(p2.y - p1.y, p2.x - p1.x) * DEG;
	}

	// ���������� ����������� � �������� ������������ ������ shp � ����� p
	static const float GetAngle(Shape& shp, const v2f& p) {
		return atan2f(p.y - shp.getPosition().y, p.x - shp.getPosition().x) * DEG;
	}

	// ���������� ����������� � �������� ������������ ������ shp1 � ������ shp2
	static const float GetAngle(Shape& shp1, Shape& shp2) {
		const v2f& p1 = shp1.getPosition();
		const v2f& p2 = shp2.getPosition();
		return atan2f(p2.y - p1.y, p2.x - p1.x) * DEG;
	}

	// ������� ���� � ��������� �����������
	static void MoveToAngle(Shape& shape, float angle, float speed) {
		const float& A = angle * RAD;
		shape.move(v2f(cos(A), sin(A)) * speed);
	}

	// ���������� ������� ������ � ��� �����
	// ����������� ����� ���������� my_text.setString("�����-�� �����");
	static void CenteringText(sf::Text& text) {
		text.setOrigin(text.getGlobalBounds().width / 2.f, text.getGlobalBounds().height / 1.5f);
	}

	// ���������� ��������� ������� �� ������ ����������
	// ������ ������������� if(IsKeyPressed(Key::F1)) { Condition... }
	static bool IsKeyPressed(const sf::Keyboard::Key& code) {
		if (event.type == sf::Event::KeyPressed)
			if (event.key.code == code) return true;
		return false;
	}

	// ���������� ��������� ������� ������� ������ ����������
	// ������ ������������� if(IsKeyReleased(Key::F1)) { Condition... }
	static bool IsKeyReleased(const sf::Keyboard::Key& code) {
		if (event.type == sf::Event::KeyReleased)
			if (event.key.code == code) return true;
		return false;
	}

	// ���������� ��������� ������� ������� ������ �����
	// ������ ������������� if(IsMousePressed(sf::Mouse::Left)) { Condition... }
	static bool IsMousePressed(const sf::Mouse::Button& code) {
		if (event.type == sf::Event::MouseButtonPressed)
			if (event.key.code == code) return true;
		return false;
	}

	// ���������� ��������� ������� ������� ������ �����
	// ������ ������������� if(IsMouseReleased(sf::Mouse::Left)) { Condition... }
	static bool IsMouseReleased(const sf::Mouse::Button& code) {
		if (event.type == sf::Event::MouseButtonReleased)
			if (event.key.code == code) return true;
		return false;
	}

	// ���������� ��������� ��������� �������� �����
	static bool IsMouseWheelUp(const sf::Mouse::Wheel code)
	{
		if (event.mouseWheel.x == code) return true;
		return false;
	}

	// ����������� �������������
	// ���������� ������ ���� ��� �� ������ ���������
	Base(string init) {
		if (init == "init")
		{
			// =================================== //
			// �������������� ���� �������� ������ //
			// =================================== //

			scr_h = sf::VideoMode::getDesktopMode().height;
			scr_w = sf::VideoMode::getDesktopMode().width;
			wnd.create(sf::VideoMode(scr_w, scr_h), "RPG Lesson", sf::Style::Close, sf::ContextSettings(0, 0, 8));
			cam.reset(sf::FloatRect(0, 0, scr_w, scr_h));
			cam.setCenter(0, 0);
			cam_p = cam.getCenter();
			cur_p = v2f(0, 0);
			cur_p_wnd = v2f(0, 0);
			wnd.setView(cam);
			wnd.setMouseCursorVisible(true);
			//wnd.setFramerateLimit(30);
			srand(::time(0));
			clock.restart();
		}
	}

	Base(void) {
	}

		// ============================== //
		// ��������� ���� �������� ������ //
		// ============================== //

	static sf::RenderWindow wnd;		// ����
	static ResourcesManager	resources;	// ����� �������, �������, ������ � ������ (audio.sound.my_sound | audio.music.my_music)
	static sf::Event event;				// ������� SFML
	static sf::View cam;				// ������ ����
	static int scr_w;					// ������ �������� �����
	static int scr_h;					// ������ �������� �����
	static v2f cam_p;					// ������� ������
	static v2f cur_p;					// ������� ������� � ���������� ������� ���������
	static v2f cur_p_wnd;				// ������� ������� � ������� ������� ��������� (��� ��������� UI)
	static float time;					// ��������� ����� ������� ����
	static GameConstatnts gc;			// ����� ����� ������� ��������

private: 
	static sf::Clock clock;
};

// ������� ����������� ���� � ���������� ������� ���������

sf::RenderWindow		B::wnd;			// ����
ResourcesManager		B::resources;	// ����� �������, �������, ������ � ������ (audio.sound.my_sound | audio.music.my_music)
sf::Event				B::event;		// ��� ����������� ������� while(wnd.pollEvent(event)) { Conditions... }
sf::View				B::cam;			// ������ ����
int						B::scr_w;		// ������ �������� �����
int						B::scr_h;		// ������ �������� �����
v2f						B::cam_p;		// ������� ������
v2f						B::cur_p;		// ������� ������� � ���������� ������� ���������
v2f						B::cur_p_wnd;	// ������� ������� � ������� ������� ��������� (��� ��������� UI)
float					B::time;		// ��������� ����� ������� ����
GameConstatnts			B::gc;			// ����� ����� ������� ��������
sf::Clock				B::clock;