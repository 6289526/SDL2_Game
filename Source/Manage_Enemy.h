#pragma once

#include "Enemy.h"

const int Enemy_Num = 3;	// 画面内の敵キャラの数の最大値

enum Enemy_Type {
	Test,
	Leg,
	Wheel,
	Fly,
};

class Manage_Enemy
{
public:
	/* (レンダラ) */
	Manage_Enemy();
	/* (レンダラ，初期位置，キャラの種類) */
	int Create_Enemy(SDL_Renderer* renderer, SDL_Rect position, Enemy_Type type);
	/* (レンダラ，マップ) */
	void Draw(SDL_Renderer* renderer, Map& map);
	/* (移動目標の座標) */
	void Move(SDL_Rect position);
	/* (敵キャラの識別'添え字') */
	Enemy* Get_Enemy(int index) { return m_Enemy[index]; }
	/* (レンダラ，表示ｘ座標，表示ｙ座標) */
	void Print_Position(SDL_Renderer* renderer, int x, int y);

private:
	void Destroy_Enemy();

private:
	Enemy* m_Enemy[Enemy_Num];	// 敵情報
};
