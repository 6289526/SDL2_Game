#include "Core.h"

// �R���X�g���N�^
Core::Core(int x, int y)
    :   m_Program_End(false)
{
	SDL_Init(SDL_INIT_EVERYTHING);	//SDL2�̏�����
    TTF_Init(); // �������������߂�

	m_Window = SDL_CreateWindow(
        "window", //�E�B���h�E�^�C�g��
        SDL_WINDOWPOS_UNDEFINED, //�E�B���h�E�ʒu��
        SDL_WINDOWPOS_UNDEFINED, //�E�B���h�E�ʒu��
        x, //��
        y, //����
        SDL_WINDOW_OPENGL //flags �ڍׂ̓}�j���A���Q��
    );

    // �����_���쐬
    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);

    // �t�H���g�ǂݍ���
    m_Font = TTF_OpenFont("Font/MyricaM/MyricaM.TTC", 24);
}

Core::~Core()
{
    TTF_CloseFont(m_Font);  // �t�H���g�j��
    TTF_Quit(); // �����̈������I��
    SDL_DestroyWindow(m_Window);  // �E�B���h�E�j��
    SDL_Quit(); // SDL2�I��
}