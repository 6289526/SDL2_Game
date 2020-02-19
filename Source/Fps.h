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
	void Wait() const;
	std::string Get_Fps();

private:
	unsigned m_StartTime;	// 計測開始時刻
	int m_Count;	// ０から指定されたFPS値までカウント
	float m_Fps;	// 実測値
	const int m_Fps_ideal;	// 指定されえたFPS値
};

