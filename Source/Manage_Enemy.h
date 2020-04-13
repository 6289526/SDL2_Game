#pragma once

#include "Enemy.h"

const int Enemy_Num = 3;	// ��ʓ��̓G�L�����̐��̍ő�l

enum Enemy_Type {
	Test,
	Leg,
	Wheel,
	Fly,
};

class Manage_Enemy
{
public:
	/* (�����_��) */
	Manage_Enemy();
	/* (�����_���C�����ʒu�C�L�����̎��) */
	int Create_Enemy(SDL_Renderer* renderer, SDL_Rect position, Enemy_Type type);
	/* (�����_���C�}�b�v) */
	void Draw(SDL_Renderer* renderer, Map& map);
	/* (�ړ��ڕW�̍��W) */
	void Move(SDL_Rect position);
	/* (�G�L�����̎���'�Y����') */
	Enemy* Get_Enemy(int index) { return m_Enemy[index]; }
	/* (�����_���C�\�������W�C�\�������W) */
	void Print_Position(SDL_Renderer* renderer, int x, int y);

private:
	void Destroy_Enemy();

private:
	Enemy* m_Enemy[Enemy_Num];	// �G���
};
