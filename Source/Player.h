#pragma once
#include "Character.h"

#include <string>
#include <sstream>

#include "Animation.h"
#include "Map.h"
#include "Bullet.h"

enum Jump_Wave {
	Take_Off,	// 離陸
	Jumping,	// 空中
	Landing		// 着地
};

const int Bullet_Num = 10;

class Player :
	public Character
{
public:
	/* (レンダラ) */
	Player(SDL_Renderer* renderer);
	/* (レンダラ，マップ) */
	void Draw(SDL_Renderer* renderer, Map& map);
	/* (イベント，エンドフラグ，マップ) */
	void Key_Check(SDL_Event event, bool& end, Map& map);
	/* (レンダラ，表示座標ｘ，表示座標ｙ) */
	void Print_Angle(SDL_Renderer* renderer, int x, int y);
	/* (レンダラ，表示座標ｘ，表示座標ｙ) */
	void Print_Position(SDL_Renderer* renderer, int x, int y);

private:
	/* (レンダラ) */
	void Draw_Stand(SDL_Renderer* renderer);
	/* (レンダラ) */
	void Draw_Walk(SDL_Renderer* renderer);
	/* (レンダラ，マップ) */
	void Draw_Jump(SDL_Renderer* renderer, Map& map);
	/* (レンダラ，マップ) */
	void Draw_Bullet(SDL_Renderer* renderer, Map& map);
	/*(レンダラ)*/
	void Draw_Arm(SDL_Renderer* renderer);
	/* (制限をつける角度) */
	double Arm_Angle_Limit(double angle);

private:
	Animation m_Animation_Stand;	// 立ち絵
	Animation m_Animation_Walk;		// 歩き絵
	Animation m_Animation_Jump;		// ジャンプ絵
	Animation m_Animation_Gun_Stand;// 立ちながらの射撃絵
	Animation m_Animation_Gun_Walk;	// 歩きながらの射撃絵
	Image m_Image_Gun_Arm;	// 射撃の腕絵

	int m_Jump_Height;	// ジャンプの高さ
	Jump_Wave m_Jump_Wave;	// ジャンプの処理に使う
	bool m_Key_Lock;	// true 時キーボード操作不可
	SDL_Rect m_Gun_Arm_Position;	// 射撃絵の腕の表示座標
	double m_Angle_deg;	 // 腕の角度 度数表記
	bool m_Gun_Flag;	// 銃を撃っているときは true
	SDL_Point m_Mouse_Position;	// マウス座標

	Bullet* m_Bullet[Bullet_Num];	// １０発の弾を撃つことができる
};

