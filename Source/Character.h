#pragma once

#include "Core.h"

#include "Map.h"

enum Situation {
	Stand,
	Walk,
	Jump
};

class Character
{
public:
	/* (�L�������゘�C�L�������゙�C�L�������C�L���������C�L�����̌���) */
	Character(int x, int y, int w, int h, Direction direction);
	/* (�����_���C�}�b�v) */
	virtual void Draw(SDL_Renderer* renderer, Map& map) = 0;

protected:
	/* (�}�b�v�C���E���̒���^���̒l�������肪�����Ɋ��^) */
	bool Collision_Side(Map& map, int adjust) const;
	/* (�}�b�v) */
	void Collision_Under(Map& map);
	void Gravity();

protected:
	SDL_Rect m_Position;	// ���゘�C���゙�C�����C������
	Direction m_Direction;	// �L�����̌���
	bool m_Ground;	// �ڒn�Ftrue�C�󒆁Ffalse
	const int m_Min_Gravity;	// �d�͍ŏ��l
	int m_Gravity;	// �d��
	int m_HP;	// �L�����̗̑�
	Situation m_Situation;	// �L�����̏��(�����C�����Ȃ�)
};

