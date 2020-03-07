#pragma once

#include "Core.h"

class Fps
{
public:
	/* (FPS�l) */
	Fps(int fps);
	void Update();
	void Wait() const;
	/* (�����_���C�\�������W�C�\�������W) */
	void Print_Fps(SDL_Renderer* renderer, int x, int y);

private:
	unsigned m_StartTime;	// �v���J�n����
	int m_Count;	// �O����w�肳�ꂽFPS�l�܂ŃJ�E���g
	float m_Fps;	// �����l
	const int m_Fps_ideal;	// �w�肳�ꂦ��FPS�l
};

