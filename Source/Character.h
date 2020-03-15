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
	/* (キャラ左上ｘ，キャラ左上ｙ，キャラ幅，キャラ高さ，キャラの向き) */
	Character(int x, int y, int w, int h, Direction direction);
	/* (レンダラ，マップ) */
	virtual void Draw(SDL_Renderer* renderer, Map& map) = 0;
	int Get_Hp() const { return m_HP; }
	SDL_Rect Get_Position() const { return m_Position; }
	/* (レンダラ，表示ｘ座標，表示ｙ座標) */
	virtual void Print_Position(SDL_Renderer* renderer, int x, int y);

protected:
	/* (マップ，左右幅の調整^この値だけ判定が内側に寄る^) */
	bool Collision_Side(Map& map, int adjust) const;
	/* (マップ) */
	void Collision_Under(Map& map);
	void Gravity();

protected:
	SDL_Rect m_Position;	// 左上ｘ，左上ｙ，幅ｗ，高さｈ
	Direction m_Direction;	// キャラの向き
	bool m_Ground;	// 接地：true，空中：false
	const int m_Min_Gravity;	// 重力最小値
	int m_Gravity;	// 重力
	int m_HP;	// キャラの体力
	Situation m_Situation;	// キャラの状態(歩き，立ちなど)
};

