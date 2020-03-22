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

// 座標を表示
void Character::Print_Position(SDL_Renderer* renderer, int x, int y)
{
	std::string t_Str = "(";
	Print_Screen(t_Str, renderer, x, y);
	Print_Screen(To_String(m_Position.x), renderer, x + 20, y);
	t_Str = ",";
	Print_Screen(t_Str, renderer, x + 60, y);
	Print_Screen(To_String(m_Position.y), renderer, x + 80, y);
	t_Str = ")";
	Print_Screen(t_Str, renderer, x + 120, y);
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
			return false;
		}
	}

	return true;
}

// 下の当たり判定
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

	// ウィンドウ外に行くと「死」
	if (m_Position.x <= 0 || Window_x < m_Position.x + m_Position.w || m_Position.y < 0 || Window_y < m_Position.y) {
		m_HP = 0;
	}
}

// 重力を与える
void Character::Gravity()
{
	// 空中にいるなら滞空時間に応じた重力を付加
	if (m_Ground == false) {
		m_Position.y += m_Gravity++;
	}
}
