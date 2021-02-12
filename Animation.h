#pragma once
#include "Base.h"
 // good job
class Animation
{
protected:

	const v2i m_frame_size;				// ������ ����� (�������� �� ���������)
	const v2i m_start_position;			// ������� ����� ���� ������ �������� ��������
	const float m_timer_next_frime;		// ����� ����� ������ (250 �� �� ���������)
	const uint m_num_frames;			// ����� ������ � ��������
	uint m_current_num_frame = 0;		// ����� �������� �����
	float m_timer = 0;					// ������ ����� ������ (�������)
	bool m_is_end = false;				// ����� �������� (��� �������� ��� ������������)
	Shape& m_shape;						// ������ �� ������, � ������� ����� ��������� ������� ��������

protected:

	// ���������� true ���� ������ ����� ��� ����� ����� 
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
		if (IsEnd() == false) {								// ���� �������� �� ��������� (����������� �� is_loop)
			m_timer += B::time;
			if (IsTimerTick()) {							// ���� ������ ������ ������� ����� ������
				m_timer = 0;								// �������� ������
				if (m_current_num_frame < m_num_frames) {	// ���� ������� ���� ������ ��������� ���-�� ������
					m_current_num_frame++;					// �� ����������� ������� ���� �� 1
				}
				else if (is_loop) m_current_num_frame = 0;	// ���� ������������ ��������, ���������� ������� ���� �� 0
						else m_is_end = true;				// ����� ��������� ������������ ������� ��������

				m_shape.setTextureRect(
					IR( // ������� ���������� �������� ����� �� X ������ ����� * �� ����� �������� �����
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

// �������� ����� DrawProgressCast ��� ����������� ����� ��������� ����������
class AnimationCast : public Animation {
private:

	Shape m_shape_progress_cast;	// �������� ��� �� ���������� ����������
	float m_timer_to_delay;			// ����� ���������� �������� �� ���������
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