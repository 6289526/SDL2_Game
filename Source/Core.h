#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include "Fanction.h"

const int Window_x = 1024;	// ウィンドウの幅
const int Window_y =  768;	// ウィンドウの高さ

const double Player_Scale = 0.2;	// プレイヤー画像の縮小率
const double Enemy_Scale = 0.15;	// 敵キャラの縮小率

// キャラの向き
enum Direction {
	Right,
	Left,
};

class Core
{
public:
	/* (ウィンドウ幅，ウィンドウ高さ) */
	Core(int x, int y);
	~Core();
	TTF_Font*		Get_Font()			{ return m_Font; }	// フォント取得
	SDL_Renderer*	Get_Renderer()		{ return m_Renderer; }	// レンダラ取得
	SDL_Event		Get_Event()			{ return m_Event; }	// イベント取得

public:
	bool m_Program_End;	// ture で終了

private:
	SDL_Window* m_Window;	// ウィンドウ情報
	TTF_Font* m_Font;	// 表示文字のフォント
	SDL_Renderer* m_Renderer;	// レンダラ
	SDL_Event m_Event;	// イベント関係
};


