#pragma once

#include <string>
#include <sstream>

#include "Core.h"

class Fps
{
public:
	/* (FPS�l) */
	Fps(int fps);
	void Update();
	/* (������\�����W���C������\�����W���C�t�H���g�C�F, �����_��) */
	void Draw(int x, int y, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer) const;
	void Wait() const;

private:
	unsigned m_StartTime;	// �v���J�n����
	int m_Count;	// �O����w�肳�ꂽFPS�l�܂ŃJ�E���g
	float m_Fps;	// �����l
	const int m_Fps_ideal;	// �w�肳�ꂦ��FPS�l
};

