#pragma once
#include "Image.h"

class Animation
{
public:
	/* (画像のパス，画像横の枚数，画像縦の枚数，画像１枚の幅，画像１枚の高さ，レンダラ) */
	Animation(const char* image_path, int n_x, int n_y, int w, int h, SDL_Renderer* renderer);
	/* (画像表示場所，レンダラ，画像切り替えフレーム数，true 指定で反転) */
	void Draw(const SDL_Rect position, SDL_Renderer* renderer, int num_frame, bool inverse = false);
	/* (画像表示場所，レンダラ，画像切り替えフレーム数，回転角度，回転中心座標，true 指定で反転) */
	void Draw_Rotation(const SDL_Rect position, SDL_Renderer* renderer, int num_frame, double angle, SDL_Point* center, bool inverse = false);
	unsigned Get_Loop_Count() const { return m_Loop_Count; }
	int Get_Image_Number() const { return m_Image_Number; }
 	void Reset();

private:
	void Swicth();

private:
	SDL_Texture* m_Texture;	// テクスチャ
	SDL_Rect m_Image_Pos;	// 分割画像の１枚に注目
	const int m_Num_x;	// 分割画像の横の枚数
	const int m_Num_y;	// 分割画像の縦の枚数
	int m_Count;	// カウンタ
	unsigned m_Loop_Count;	// ループ回数
	int m_Image_Number;	// 現在何枚目の写真か
};

