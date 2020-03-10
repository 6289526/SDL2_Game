#pragma once

#include "Enemy.h"

const int Enemy_Num = 3;	// ��ʓ��̓G�L�����̐��̍ő�l

class Manage_Enemy
{
public:
	/* (�����_��) */
	Manage_Enemy();
	/* (�����_���C�����ʒu) */
	int Create_Enemy(SDL_Renderer* renderer, SDL_Rect position);
	/* (�����_��) */
	void Draw(SDL_Renderer* renderer, Map& map);

private:
	void Destroy_Enemy();

private:
	Enemy* m_Enemy[Enemy_Num];	// �G���
};

