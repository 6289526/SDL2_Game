#include "Character.h"

// コンストラクタ
Character::Character(int x, int y, int w, int h, Direction direction)
	:	m_Direction(direction),
		m_Ground(false),
		m_Min_Gravity(3),
		m_Gravity(m_Min_Gravity),
		m_HP(3)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.w = w;
	m_Position.h = h;
	
	m_Situation = Stand;
}

// 横の当たり判定 adjust の値だけ判定はキャラの内側に寄る
bool Character::Collision_Side(Map& map, int adjust) const
{
	// キャラの足元の高さ
	int t_Height = Window_y - m_Position.y - m_Position.h;

	// 段差が１０よりも大きければ登れない
	if (m_Direction == Right) {
		if (t_Height + 10 < map.Get_Height(m_Position.x + m_Position.w - adjust)) {
			return false;
		}
	}
	else if (m_Direction == Left) {
		if (t_Height + 10 < map.Get_Height(m_Position.x + adjust)) {
			int a = map.Get_Height(m_Position.x + m_Position.w - adjust);
			int b = map.Get_Height(m_Position.x + adjust);
			return false;
		}
	}

	return true;
}

void Character::Collision_Under(Map& map)
{
	// 当たり判定は２点で行う
	// より低い位置にある点を使う
	int t_Min = Window_y - map.Get_Height(m_Position.x + ((m_Position.w / 8) * 3)) - m_Position.h;
	if (Window_y - map.Get_Height(m_Position.x + m_Position.w - ((m_Position.w / 8) * 3)) - m_Position.h < t_Min) {
		t_Min = Window_y - map.Get_Height(m_Position.x + m_Position.w - ((m_Position.w / 8) * 3)) - m_Position.h;
	}

	// 設置しているかどうか
	if (m_Position.y < t_Min) {
		m_Ground = false;
	}
	// 設置していればキャラの位置を床の高さに
	else {
		m_Position.y = t_Min;
		m_Ground = true;
		m_Gravity = m_Min_Gravity;
	}

	// ウィンドウより下に行くと「死」
	if (Window_y <= m_Position.y) {
		m_HP = 0;
	}
}

void Character::Gravity()
{
	// 空中にいるなら滞空時間に応じた重力を付加
	if (m_Ground == false) {
		m_Position.y += m_Gravity++;
	}
}
