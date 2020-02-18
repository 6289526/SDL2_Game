#include "Image.h"

// �R���X�g���N�^
Image::Image(const char* image_path, SDL_Renderer* renderer)
{
	// �T�[�t�F�X����
	SDL_Surface* t_Surface = IMG_Load(image_path);	
	// �e�N�X�`������
	m_Texture = SDL_CreateTextureFromSurface(renderer, t_Surface);
	// �T�[�t�F�X�j��
	SDL_FreeSurface(t_Surface);
}

// �`��
void Image::Draw(const SDL_Rect position, SDL_Renderer* renderer, bool inverse)
{
	// �C���o�[�X�t���O�������Ă���Δ��]���ĕ\��
	if (inverse) {
		SDL_RenderCopyEx(renderer, m_Texture, NULL, &position, 0.0, NULL, SDL_FLIP_HORIZONTAL);
	}
	else {
		SDL_RenderCopy(renderer, m_Texture, NULL, &position);
	}
}

void Image::Draw_Rotation(const SDL_Rect position, SDL_Renderer* renderer, double angle, SDL_Point* center, bool inverse)
{
	// �C���o�[�X�t���O�������Ă���Δ��]���ĕ\��
	if (inverse) {
		SDL_RenderCopyEx(renderer, m_Texture, NULL, &position, angle, center, SDL_FLIP_HORIZONTAL);
	}
	else {
		SDL_RenderCopyEx(renderer, m_Texture, NULL, &position, angle, center, SDL_FLIP_NONE);
	}
}
