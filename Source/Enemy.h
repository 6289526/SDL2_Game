#pragma once
#include "Character.h"
#include "Animation.h"
#include "Player.h"

class Enemy :
	public Character
{
public:
	/* (�����_���C�����ʒu�C�摜�̃p�X�C�摜�̏c�̖����C�摜�̉��̖���) */
	Enemy(SDL_Renderer* renderer, SDL_Rect position, const char* image_path, int x_num, int y_num);
	/* (�����_���C�}�b�v) */
	void Draw(SDL_Renderer* renderer, Map& map);
	/* (�ړ��ڕW�Ƃ���n�_) */
	void Move(SDL_Rect position);
	/* (�ړ����x) */
	void Set_Speed(int speed) { m_Speed = speed; }
	/* (�����_���C�\�������W�C�\�������W) */
	void Print_Position(SDL_Renderer* renderer, int x, int y);

public:
	int m_Draw_Adjustment;	// �`�掞�̏㉺�̒���

private:
	Animation m_Animation;	// �ړ��G
	int m_Speed;	// �ړ��X�s�[�h
};

