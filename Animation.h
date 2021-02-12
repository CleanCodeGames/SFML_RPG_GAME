#pragma once
#include "Base.h"
 // good job
class Animation
{
protected:

	const v2i m_frame_size;				// Размер кадра (смотреть на текстурах)
	const v2i m_start_position;			// Верхний левый угол начала анимации текстуры
	const float m_timer_next_frime;		// Время смены кадров (250 мс по умолчанию)
	const uint m_num_frames;			// Всего кадров в анимации
	uint m_current_num_frame = 0;		// Номер текущего кадра
	float m_timer = 0;					// Таймер смены кадров (счётчик)
	bool m_is_end = false;				// Конец анимации (Для анимация без зацикливания)
	Shape& m_shape;						// Ссылка на фигуру, к которой будет применена текущая анимация

protected:

	// Возвращает true если пришло время для смены кадра 
	inline const bool IsTimerTick() {
		m_timer += B::time;
		return m_timer >= m_timer_next_frime ? true : false;
	}

public: 

	Animation(Shape& shape, v2i frame_size, v2i start_position, uint nums_frames, float timer_next_frime = 250.f)
		: m_start_position(start_position), 
		m_frame_size(frame_size), 
		m_num_frames(nums_frames-1), 
		m_timer_next_frime(timer_next_frime),
		m_shape(shape) { 
	}

	virtual void Play(bool is_loop = true) {
		if (IsEnd() == false) {								// Если анимация не закончена (зависимость от is_loop)
			m_timer += B::time;
			if (IsTimerTick()) {							// Если таймер достиг времени смены кадров
				m_timer = 0;								// Обнуляем таймер
				if (m_current_num_frame < m_num_frames) {	// Если текущий кадр меньше заданного кол-ва кадров
					m_current_num_frame++;					// То увеличиваем текущий кадр на 1
				}
				else if (is_loop) m_current_num_frame = 0;	// Если зацикливание включено, сбрасываем текущий кадр на 0
						else m_is_end = true;				// Иначе завершаем проигрывание текущей анимации

				m_shape.setTextureRect(
					IR( // Смещаем координаты текстуры вперёд по X размер кадра * на номер текущего кадра
						m_start_position.x + (m_current_num_frame * m_frame_size.x),
						m_start_position.y,
						m_frame_size.x,
						m_frame_size.y));
			}
		}
	}

	virtual void Reset() {
		m_timer -= m_timer_next_frime;
		m_current_num_frame = 0;
	}
	
	bool IsEnd() {
		return m_is_end;
	}
	virtual ~Animation() {
	}
};

// Добавлен метод DrawProgressCast для отображения шкалы прогресса выполнения
class AnimationCast : public Animation {
private:

	Shape m_shape_progress_cast;	// Прогресс бар до совершения заклинания
	float m_timer_to_delay;			// Время выаолнения анимации до окончания
	const float m_TIMER_TO_DELAY;

public:

	AnimationCast(Shape& shape, v2i frame_size, v2i start_position, uint nums_frames, float time_to_delay = 280.f, float timer_next_frime = 100.f)
		:
		Animation(shape, frame_size, start_position, nums_frames, timer_next_frime), m_TIMER_TO_DELAY(time_to_delay) {
		m_timer_to_delay = time_to_delay;
		m_shape_progress_cast = B::CreateShape(v2f(), v2f(0, 6), 1, Color::Green, Color::Yellow);
	}

	void Play(bool is_loop = true) override {
		Animation::Play(is_loop);
		if(m_is_end == false) m_timer_to_delay -= B::time;
		if (m_timer_next_frime <= 0) m_is_end = true;
		m_shape_progress_cast.setSize(v2f(m_shape.getSize().x * (m_timer_to_delay / m_TIMER_TO_DELAY), 6));
		m_shape_progress_cast.setPosition(m_shape.getPosition() - m_shape.getSize());
	}

	void Reset() override {
		m_timer -= m_timer_next_frime;
		m_current_num_frame = 0;
		m_timer_to_delay = m_TIMER_TO_DELAY;
		m_is_end = false;
	}

	void DrawProgressCast() {
		if(m_timer_to_delay > 0)
			B::wnd.draw(m_shape_progress_cast);
	}

	~AnimationCast() {
	}
}; 