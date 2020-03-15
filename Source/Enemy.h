#pragma once
#include "Character.h"
#include "Animation.h"
#include "Player.h"

class Enemy :
	public Character
{
public:
	/* (�����_���C�����ʒu) */
	Enemy(SDL_Renderer* renderer, SDL_Rect position);
	/* (�����_���C�}�b�v) */
	void Draw(SDL_Renderer* renderer, Map& map);
	/* (�ړ��ڕW�Ƃ���n�_) */
	void Move(SDL_Rect position);
	/* (�ړ����x) */
	void Set_Speed(int speed) { m_Speed = speed; }
	/* (�����_���C�\�������W�C�\�������W) */
	void Print_Position(SDL_Renderer* renderer, int x, int y);

private:
	Animation m_Animation_Test;	// �e�X�g�G
	int m_Speed;	// �ړ��X�s�[�h
};

