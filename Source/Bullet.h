#pragma once

#include "SDL2/SDL.h"

#include "Map.h"

class Bullet
{
public:
	/* (�e�̍��゘�������������C�_���[�W�ʁC�e���C�e�̊p�x�C�e�̐i�ތ����C�����_��) */
	Bullet(SDL_Rect position, int damage, double speed, double angle, Direction direction, SDL_Renderer* renderer);
	/* (�����_��) */
	void Draw(SDL_Renderer* renderer, Map& map);

private:
	/* (�}�b�v) */
	bool Collision(Map& map) const;

public:
	bool End;	// true �Œe�̕`��I��

private:
	SDL_Rect m_Position;	// �e�̈ʒu
	const double m_Speed_x;	// �����W�̑��x
	const double m_Speed_y;	// �����W�̑��x
	double m_Angle;	// �e�̊p�x
	const Direction m_Direction;	// �e�̐i�ތ���
	int m_Damage;	// �_���[�W��

	Image m_Image;	// �e�̊G�̏��
};

