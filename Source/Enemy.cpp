#include "Enemy.h"

Enemy::Enemy(SDL_Renderer* renderer, SDL_Rect position, const char* image_path, int x_num, int y_num)
	:	Character(position.x, position.y, position.w, position.h, Left),
		m_Animation(image_path, x_num, y_num, 800, 1000, renderer),
		m_Speed(1),
		m_Draw_Adjustment(0)
{
}

// �`��
void Enemy::Draw(SDL_Renderer* renderer, Map& map)
{
	//�d��
	Gravity();

	m_Position.x += map.Get_Move_Value();	// �v���C���[�̈ړ��������炷

	m_Position.y += m_Draw_Adjustment;	// �`��ʒu�𒲐� �摜���ƂɈႤ

	if (m_Direction == Right) {
		m_Animation.Draw(m_Position, renderer, 5);
	}
	else if (m_Direction == Left) {
		m_Animation.Draw(m_Position, renderer, 5, true);
	}

	m_Position.y -= m_Draw_Adjustment;	// �`�悪�I�������̂Ŗ߂�

	// ���̓����蔻��
	Collision_Under(map);
}

// �G�L�����𓮂���
void Enemy::Move(SDL_Rect position)
{
	// ���S���W
	int t_Player_Position = position.x + position.w / 2;
	int t_Enemy_Position = m_Position.x + m_Position.w / 2;

	// �v���C������������Ɉړ�����
	if (t_Player_Position < t_Enemy_Position) {
		m_Position.x -= m_Speed;
		m_Direction = Left;
	}
	else if (t_Enemy_Position < t_Player_Position) {
		m_Position.x += m_Speed;
		m_Direction = Right;
	}
}

// ���W��\��
void Enemy::Print_Position(SDL_Renderer* renderer, int x, int y)
{
	std::string t_Str = "Enemy Position : ";
	Print_Screen(t_Str, renderer, x, y);
	Character::Print_Position(renderer, x + 210, y);
}