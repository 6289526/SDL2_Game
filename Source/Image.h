#pragma once

#include "Core.h"

class Image
{
public:
	/* (�摜�̃p�X�C�����_��) */
	Image(const char* image_path, SDL_Renderer* renderer);
	/* (�摜�\���ꏊ�C�����_���Ctrue �w��Ŕ��]) */
	void Draw(const SDL_Rect position, SDL_Renderer* renderer, bool inverse = false);
	/* (�摜�\���ꏊ�C�����_���C��]�p�x�C��]���S���W^��������xy��0,0�Ƃ���^�Ctrue �w��Ŕ��]) */
	void Draw_Rotation(const SDL_Rect position, SDL_Renderer* renderer, double angle, SDL_Point* center, bool inverse = false);

protected:
	SDL_Texture* m_Texture;	// �e�N�X�`��
};

