#include "Image.h"

// コンストラクタ
Image::Image(const char* image_path, SDL_Renderer* renderer)
{
	// サーフェス生成
	SDL_Surface* t_Surface = IMG_Load(image_path);	
	// テクスチャ生成
	m_Texture = SDL_CreateTextureFromSurface(renderer, t_Surface);
	// サーフェス破棄
	SDL_FreeSurface(t_Surface);
}

// 描画
void Image::Draw(const SDL_Rect position, SDL_Renderer* renderer, bool inverse)
{
	// インバースフラグが立っていれば反転して表示
	if (inverse) {
		SDL_RenderCopyEx(renderer, m_Texture, NULL, &position, 0.0, NULL, SDL_FLIP_HORIZONTAL);
	}
	else {
		SDL_RenderCopy(renderer, m_Texture, NULL, &position);
	}
}

void Image::Draw_Rotation(const SDL_Rect position, SDL_Renderer* renderer, double angle, SDL_Point* center, bool inverse)
{
	// インバースフラグが立っていれば反転して表示
	if (inverse) {
		SDL_RenderCopyEx(renderer, m_Texture, NULL, &position, angle, center, SDL_FLIP_HORIZONTAL);
	}
	else {
		SDL_RenderCopyEx(renderer, m_Texture, NULL, &position, angle, center, SDL_FLIP_NONE);
	}
}
