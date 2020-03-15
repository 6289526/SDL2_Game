#include "Enemy.h"

Enemy::Enemy(SDL_Renderer* renderer, SDL_Rect position)
	:	Character(position.x, position.y, position.w, position.h, Left),
		m_Animation_Test("Image/Enemy/Enemy_Test.bmp", 3, 1, 800, 1000, renderer),
		m_Speed(1)
{
}

// 描画
void Enemy::Draw(SDL_Renderer* renderer, Map& map)
{
	//重力
	Gravity();

	m_Position.x += map.Get_Move_Value();	// プレイヤーの移動分をずらす

	if (m_Direction == Right) {
		m_Animation_Test.Draw(m_Position, renderer, 10);
	}
	else if (m_Direction == Left) {
		m_Animation_Test.Draw(m_Position, renderer, 10, true);
	}

	// 下の当たり判定
	Collision_Under(map);
}

// 敵キャラを動かす
void Enemy::Move(SDL_Rect position)
{
	// 中心座標
	int t_Player_Position = position.x + position.w / 2;
	int t_Enemy_Position = m_Position.x + m_Position.w / 2;

	// プレイヤがいる方向に移動する
	if (t_Player_Position - t_Enemy_Position < 0) {
		m_Position.x -= m_Speed;
	}
	else if (0 < t_Player_Position - t_Enemy_Position) {
		m_Position.x += m_Speed;
	}
}

// 座標を表示
void Enemy::Print_Position(SDL_Renderer* renderer, int x, int y)
{
	std::string t_Str = "Enemy Position : ";
	Print_Screen(t_Str, renderer, x, y);
	Character::Print_Position(renderer, x + 210, y);
}
