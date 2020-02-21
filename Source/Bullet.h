#pragma once

#include "SDL2/SDL.h"

#include "Map.h"

class Bullet
{
public:
	/* (弾の左上ｘｙ幅ｗ高さｈ，ダメージ量，弾速，弾の角度，弾の進む向き，レンダラ) */
	Bullet(SDL_Rect position, int damage, double speed, double angle, Direction direction, SDL_Renderer* renderer);
	/* (レンダラ) */
	void Draw(SDL_Renderer* renderer, Map& map);

private:
	/* (マップ) */
	bool Collision(Map& map) const;

public:
	bool End;	// true で弾の描画終了

private:
	SDL_Rect m_Position;	// 弾の位置
	const double m_Speed_x;	// ｘ座標の速度
	const double m_Speed_y;	// ｙ座標の速度
	double m_Angle;	// 弾の角度
	const Direction m_Direction;	// 弾の進む向き
	int m_Damage;	// ダメージ量

	Image m_Image;	// 弾の絵の情報
};

