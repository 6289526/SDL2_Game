#pragma once
#include "Character.h"
#include "Animation.h"
#include "Player.h"

class Enemy :
	public Character
{
public:
	/* (レンダラ，初期位置，画像のパス，画像の縦の枚数，画像の横の枚数) */
	Enemy(SDL_Renderer* renderer, SDL_Rect position, const char* image_path, int x_num, int y_num);
	/* (レンダラ，マップ) */
	void Draw(SDL_Renderer* renderer, Map& map);
	/* (移動目標とする地点) */
	void Move(SDL_Rect position);
	/* (移動速度) */
	void Set_Speed(int speed) { m_Speed = speed; }
	/* (レンダラ，表示ｘ座標，表示ｙ座標) */
	void Print_Position(SDL_Renderer* renderer, int x, int y);

public:
	int m_Draw_Adjustment;	// 描画時の上下の調整

private:
	Animation m_Animation;	// 移動絵
	int m_Speed;	// 移動スピード
};

