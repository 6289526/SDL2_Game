#pragma once

#include <string>
#include <sstream>

#include "Core.h"

class Fps
{
public:
	/* (FPS値) */
	Fps(int fps);
	void Update();
	/* (文字列表示座標ｘ，文字列表示座標ｙ，フォント，色, レンダラ) */
	void Draw(int x, int y, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer) const;
	void Wait() const;

private:
	unsigned m_StartTime;	// 計測開始時刻
	int m_Count;	// ０から指定されたFPS値までカウント
	float m_Fps;	// 実測値
	const int m_Fps_ideal;	// 指定されえたFPS値
};

