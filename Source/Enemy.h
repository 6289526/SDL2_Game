#pragma once
#include "Character.h"
#include "Animation.h"
#include "Player.h"

class Enemy :
	public Character
{
public:
	/* (レンダラ，初期位置) */
	Enemy(SDL_Renderer* renderer, SDL_Rect position);
	/* (レンダラ，マップ) */
	void Draw(SDL_Renderer* renderer, Map& map);
	/* (移動目標とする地点) */
	void Move(SDL_Rect position);
	/* (移動速度) */
	void Set_Speed(int speed) { m_Speed = speed; }
	/* (レンダラ，表示ｘ座標，表示ｙ座標) */
	void Print_Position(SDL_Renderer* renderer, int x, int y);

private:
	Animation m_Animation_Test;	// テスト絵
	int m_Speed;	// 移動スピード
};

