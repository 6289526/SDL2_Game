#pragma once
#include "Character.h"

#include "Animation.h"
#include "Map.h"

enum Jump_Wave {
	Take_Off,	// 離陸
	Jumping,	// 空中
	Landing		// 着地
};

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

private:
	/* (レンダラ) */
	void Draw_Stand(SDL_Renderer* renderer);
	/* (レンダラ) */
	void Draw_Walk(SDL_Renderer* renderer);
	/* (レンダラ，マップ) */
	void Draw_Jump(SDL_Renderer* renderer, Map& map);

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
	double m_Angle;	 // 銃の角度
	bool m_Gun_Flag;	// 銃を撃っているときは true
};

