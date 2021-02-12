#pragma once
#include "Base.h"
class AbstractButton
{
protected:

	string m_action_id;	// ID возвращаемого действия при нажатии
	Shape m_shape;

public:

	AbstractButton(const Shape& shape, const string action_id) 
		: m_action_id(action_id), m_shape(shape) {
	}
	virtual Shape& GetShape()			= 0;
	virtual const string& GetActionId()	= 0;	// ID возвращаемого действия при нажатии
	virtual void Update()				= 0;
	virtual void Draw()					= 0;
	virtual bool Action()				= 0;	// Возвращает true если кнопка была нажата
	virtual ~AbstractButton()			= default;
};

//#######################################################################################################################################################################
// Кнопка мгновенного срабатывания
//#######################################################################################################################################################################

class ButtonClickActive : public AbstractButton
{
protected: bool m_isClick = false;

public:

	ButtonClickActive(const Shape& shape, const string action_id)
		: AbstractButton(shape, action_id) {
	}

	virtual const string& GetActionId() override {
		return m_action_id;
	}

	virtual void Update() override {
		// Do Nothing...
	}

	virtual void Draw() override {
		B::wnd.draw(m_shape);
	}

	virtual Shape& GetShape() override { 
		return m_shape; 
	}

	virtual bool Action() override {
		// Если курсор мышки находится на шейпе кнопки, то is_contains = true
		const bool is_contains = B::IsContains(m_shape, B::cur_p_wnd);
		
		if (B::IsMousePressed(sf::Mouse::Left)) {
			if (is_contains) {
				m_isClick = true;
				m_shape.setScale(.98, .98);
			}
			else {
				m_isClick = false;
				m_shape.setScale(1, 1);
			}
		}
		else if (B::IsMouseReleased(sf::Mouse::Left) && m_isClick) {
			m_isClick = false;
			m_shape.setScale(1, 1);
			return is_contains;
		}
		return false;
	}

	virtual ~ButtonClickActive() override {
	}
};

//#######################################################################################################################################################################
// Кнопка мгновенного действия с текстом
//#######################################################################################################################################################################

class ButtonClickActiveWithText : public ButtonClickActive
{
private: sf::Text text;

public:

	ButtonClickActiveWithText(const Shape& shape, const string action_id)
		: ButtonClickActive(shape, action_id) {
		text = B::CreateText(m_shape.getPosition(), m_shape.getSize().y, sf::String(m_action_id), B::resources.font.common, Color(40, 40, 40));
	}
	virtual void Draw() override {
		ButtonClickActive::Draw();
		B::wnd.draw(text);
	}
	virtual void Update() override {
		
		ButtonClickActive::Update();
	}
	virtual bool Action() override {
		if (m_shape.getGlobalBounds().contains(B::cur_p_wnd)) {
			text.setFillColor(Color::Yellow);
		}
		else {
			text.setFillColor(Color(40, 40, 40));
		}
		return ButtonClickActive::Action();
	}
	virtual ~ButtonClickActiveWithText() override {
	}

};

//#######################################################################################################################################################################
// Кнопка чек-бокс
//#######################################################################################################################################################################

class ButtonCheckBox : public AbstractButton
{
private: bool m_isChecked;

public:

	ButtonCheckBox(const Shape& shape, const string action_id, const bool isChecked = false)
		: AbstractButton(shape, action_id), m_isChecked(isChecked) {
		m_shape.setOutlineThickness(2);
		m_shape.setOutlineColor(Color::White);
		if (m_isChecked) m_shape.setFillColor(Color(120, 255, 80));
		else m_shape.setFillColor(Color(80, 80, 80));
	}
	virtual Shape& GetShape() override {
		return m_shape;
	}
	virtual const string& GetActionId() override {
		return m_action_id;
	}
	virtual void Update() override {
		// Do nothing...
	}
	virtual void Draw() override {
		B::wnd.draw(m_shape);
	}
	virtual bool Action() override {
		if (B::IsMousePressed(sf::Mouse::Left) && m_shape.getGlobalBounds().contains(B::cur_p_wnd)) {
			m_isChecked = !m_isChecked;
			if (m_isChecked) m_shape.setFillColor(Color(120, 255, 80));
			else m_shape.setFillColor(Color(80, 80, 80));
		}
		return m_isChecked;
	}
	virtual ~ButtonCheckBox() override {

	}
};