#include "Character.h"

// �R���X�g���N�^
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

// ���W��\��
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

// ���̓����蔻�� adjust �̒l��������̓L�����̓����Ɋ��
bool Character::Collision_Side(Map& map, int adjust) const
{
	// �L�����̑����̍���
	int t_Height = Window_y - m_Position.y - m_Position.h;

	// �i�����P�O�����傫����Γo��Ȃ�
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

// ���̓����蔻��
void Character::Collision_Under(Map& map)
{
	// �����蔻��͂Q�_�ōs��
	// ���Ⴂ�ʒu�ɂ���_���g��
	int t_Min = Window_y - map.Get_Height(m_Position.x + ((m_Position.w / 8) * 3)) - m_Position.h;
	if (Window_y - map.Get_Height(m_Position.x + m_Position.w - ((m_Position.w / 8) * 3)) - m_Position.h < t_Min) {
		t_Min = Window_y - map.Get_Height(m_Position.x + m_Position.w - ((m_Position.w / 8) * 3)) - m_Position.h;
	}

	// �ݒu���Ă��邩�ǂ���
	if (m_Position.y < t_Min) {
		m_Ground = false;
	}
	// �ݒu���Ă���΃L�����̈ʒu�����̍�����
	else {
		m_Position.y = t_Min;
		m_Ground = true;
		m_Gravity = m_Min_Gravity;
	}

	// �E�B���h�E�O�ɍs���Ɓu���v
	if (m_Position.x <= 0 || Window_x < m_Position.x + m_Position.w || m_Position.y < 0 || Window_y < m_Position.y) {
		m_HP = 0;
	}
}

// �d�͂�^����
void Character::Gravity()
{
	// �󒆂ɂ���Ȃ�؋󎞊Ԃɉ������d�͂�t��
	if (m_Ground == false) {
		m_Position.y += m_Gravity++;
	}
}
