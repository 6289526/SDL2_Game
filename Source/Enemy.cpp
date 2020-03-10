#include "Enemy.h"

Enemy::Enemy(SDL_Renderer* renderer, SDL_Rect position)
	:	Character(position.x, position.y, position.w, position.h, Left),
		m_Animation_Test("Image/Enemy/Enemy_Test.bmp", 3, 1, 800, 1000, renderer)
{
}

void Enemy::Draw(SDL_Renderer* renderer, Map& map)
{
	//�d��
	Gravity();

	m_Position.x += map.Get_Move_Value();	// �v���C���[�̈ړ��������炷

	if (m_Direction == Right) {
		m_Animation_Test.Draw(m_Position, renderer, 10);
	}
	else if (m_Direction == Left) {
		m_Animation_Test.Draw(m_Position, renderer, 10, true);
	}

	Move();

	// ���̓����蔻��
	Collision_Under(map);

	Print_Screen(To_String(m_Position.y), renderer, 100, 100);
}

void Enemy::Move()
{
	m_Position.x += 2;
}
