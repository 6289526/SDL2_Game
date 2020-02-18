#pragma once

#include "Core.h"

class Image
{
public:
	/* (画像のパス，レンダラ) */
	Image(const char* image_path, SDL_Renderer* renderer);
	/* (画像表示場所，レンダラ，true 指定で反転) */
	void Draw(const SDL_Rect position, SDL_Renderer* renderer, bool inverse = false);
	/* (画像表示場所，レンダラ，回転角度，回転中心座標^第一引数のxyを0,0とする^，true 指定で反転) */
	void Draw_Rotation(const SDL_Rect position, SDL_Renderer* renderer, double angle, SDL_Point* center, bool inverse = false);

protected:
	SDL_Texture* m_Texture;	// テクスチャ
};

