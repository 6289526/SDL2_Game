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
		// 回転中心を左上に指定
		SDL_Point t_Center = { 0, 0 };

		// 度数表記
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

// 障害物に当たるなどすると false を返す
// 通常時 true
bool Bullet::Collision(Map& map) const
{
	// 弾がウィンドウの横幅に収まっていないなら false
	if ((m_Position.x < 0 && m_Position.x + m_Position.w < 0) || (Window_x < m_Position.x && Window_x < m_Position.x + m_Position.w)) {
		return false;
	}
	// 弾がウィンドウの縦幅に収まていないなら false
	if ((m_Position.y < 0 && m_Position.y + m_Position.y < 0) || (Window_y < m_Position.y && Window_y < m_Position.y + m_Position.y)) {
		return false;
	}
	// 弾の下部分が床よりも低ければ(床に当たったら) false
	if (Window_y - m_Position.y - m_Position.h < map.Get_Height(m_Position.x + m_Position.w)
							&& Window_y - m_Position.y - m_Position.h < map.Get_Height(m_Position.x)) {
		return false;
	}


	return true;
}
