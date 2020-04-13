#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include "Fanction.h"

const int Window_x = 1024;	// �E�B���h�E�̕�
const int Window_y =  768;	// �E�B���h�E�̍���

const double Player_Scale = 0.2;	// �v���C���[�摜�̏k����
const double Enemy_Scale = 0.15;	// �G�L�����̏k����

// �L�����̌���
enum Direction {
	Right,
	Left,
};

class Core
{
public:
	/* (�E�B���h�E���C�E�B���h�E����) */
	Core(int x, int y);
	~Core();
	TTF_Font*		Get_Font()			{ return m_Font; }	// �t�H���g�擾
	SDL_Renderer*	Get_Renderer()		{ return m_Renderer; }	// �����_���擾
	SDL_Event		Get_Event()			{ return m_Event; }	// �C�x���g�擾

public:
	bool m_Program_End;	// ture �ŏI��

private:
	SDL_Window* m_Window;	// �E�B���h�E���
	TTF_Font* m_Font;	// �\�������̃t�H���g
	SDL_Renderer* m_Renderer;	// �����_��
	SDL_Event m_Event;	// �C�x���g�֌W
};


