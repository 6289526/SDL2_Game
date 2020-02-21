#include "Bullet.h"

#include "math.h"

#include "Core.h"

Bullet::Bullet(SDL_Rect position, int damage, double speed, double angle, Direction direction, SDL_Renderer* renderer)
	:	End(false),
		m_Speed_x(speed * cos(angle)),
		m_Speed_y(speed * sin(angle)),
		m_Angle(angle),
		m_Direction(direction),
		m_Damage(damage),
		m_Image("Image/Player/Bullet.bmp", renderer)
{
	m_Position.x = position.x;
	m_Position.y = position.y;
	m_Position.w = 40;
	m_Position.h = 20;
}

void Bullet::Draw(SDL_Renderer* renderer, Map& map)
{
	if (Collision(map)) {
		// ��]���S������Ɏw��
		SDL_Point t_Center = { 0, 0 };

		// �x���\�L
		double t_Angle = m_Angle * 180 / M_PI;
		t_Angle = 2 * M_PI - t_Angle;

		if (m_Direction == Right) {
			m_Position.x += m_Speed_x;
			m_Position.y -= m_Speed_y;
			m_Image.Draw_Rotation(m_Position, renderer, t_Angle, &t_Center);
		}
		else if (m_Direction == Left) {
			m_Position.x += m_Speed_x;
			m_Position.y -= m_Speed_y;
			m_Image.Draw_Rotation(m_Position, renderer, t_Angle + 180, &t_Center, true);
		}
	}
	else {
		End = true;
	}
}

// ��Q���ɓ�����Ȃǂ���� false ��Ԃ�
// �ʏ펞 true
bool Bullet::Collision(Map& map) const
{
	// �e���E�B���h�E�̉����Ɏ��܂��Ă��Ȃ��Ȃ� false
	if ((m_Position.x < 0 && m_Position.x + m_Position.w < 0) || (Window_x < m_Position.x && Window_x < m_Position.x + m_Position.w)) {
		return false;
	}
	// �e���E�B���h�E�̏c���Ɏ��܂Ă��Ȃ��Ȃ� false
	if ((m_Position.y < 0 && m_Position.y + m_Position.y < 0) || (Window_y < m_Position.y && Window_y < m_Position.y + m_Position.y)) {
		return false;
	}
	// �e�̉��������������Ⴏ���(���ɓ���������) false
	if (Window_y - m_Position.y - m_Position.h < map.Get_Height(m_Position.x + m_Position.w)
							&& Window_y - m_Position.y - m_Position.h < map.Get_Height(m_Position.x)) {
		return false;
	}


	return true;
}
