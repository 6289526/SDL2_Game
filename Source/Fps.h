#pragma once

#include "Core.h"

class Fps
{
public:
	/* (FPS値) */
	Fps(int fps);
	void Update();
	void Wait() const;
	/* (レンダラ，表示ｘ座標，表示ｙ座標) */
	void Print_Fps(SDL_Renderer* renderer, int x, int y);

private:
	unsigned m_StartTime;	// 計測開始時刻
	int m_Count;	// ０から指定されたFPS値までカウント
	float m_Fps;	// 実測値
	const int m_Fps_ideal;	// 指定されえたFPS値
};

