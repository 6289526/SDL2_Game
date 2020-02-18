#pragma once
#include "Image.h"

class Animation
{
public:
	/* (�摜�̃p�X�C�摜���̖����C�摜�c�̖����C�摜�P���̕��C�摜�P���̍����C�����_��) */
	Animation(const char* image_path, int n_x, int n_y, int w, int h, SDL_Renderer* renderer);
	/* (�摜�\���ꏊ�C�����_���C�摜�؂�ւ��t���[�����Ctrue �w��Ŕ��]) */
	void Draw(const SDL_Rect position, SDL_Renderer* renderer, int num_frame, bool inverse = false);
	/* (�摜�\���ꏊ�C�����_���C�摜�؂�ւ��t���[�����C��]�p�x�C��]���S���W�Ctrue �w��Ŕ��]) */
	void Draw_Rotation(const SDL_Rect position, SDL_Renderer* renderer, int num_frame, double angle, SDL_Point* center, bool inverse = false);
	unsigned Get_Loop_Count() const { return m_Loop_Count; }
	int Get_Image_Number() const { return m_Image_Number; }
 	void Reset();

private:
	void Swicth();

private:
	SDL_Texture* m_Texture;	// �e�N�X�`��
	SDL_Rect m_Image_Pos;	// �����摜�̂P���ɒ���
	const int m_Num_x;	// �����摜�̉��̖���
	const int m_Num_y;	// �����摜�̏c�̖���
	int m_Count;	// �J�E���^
	unsigned m_Loop_Count;	// ���[�v��
	int m_Image_Number;	// ���݉����ڂ̎ʐ^��
};

