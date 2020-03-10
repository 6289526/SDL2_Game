#pragma once

#include "Enemy.h"

const int Enemy_Num = 3;	// 画面内の敵キャラの数の最大値

class Manage_Enemy
{
public:
	/* (レンダラ) */
	Manage_Enemy();
	/* (レンダラ，初期位置) */
	int Create_Enemy(SDL_Renderer* renderer, SDL_Rect position);
	/* (レンダラ) */
	void Draw(SDL_Renderer* renderer, Map& map);

private:
	void Destroy_Enemy();

private:
	Enemy* m_Enemy[Enemy_Num];	// 敵情報
};

