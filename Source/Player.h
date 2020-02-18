#pragma once
#include "Character.h"

#include "Animation.h"
#include "Map.h"

enum Jump_Wave {
	Take_Off,	// ����
	Jumping,	// ��
	Landing		// ���n
};

class Player :
	public Character
{
public:
	/* (�����_��) */
	Player(SDL_Renderer* renderer);
	/* (�����_���C�}�b�v) */
	void Draw(SDL_Renderer* renderer, Map& map);
	/* (�C�x���g�C�G���h�t���O�C�}�b�v) */
	void Key_Check(SDL_Event event, bool& end, Map& map);

private:
	/* (�����_��) */
	void Draw_Stand(SDL_Renderer* renderer);
	/* (�����_��) */
	void Draw_Walk(SDL_Renderer* renderer);
	/* (�����_���C�}�b�v) */
	void Draw_Jump(SDL_Renderer* renderer, Map& map);

private:
	Animation m_Animation_Stand;	// �����G
	Animation m_Animation_Walk;		// �����G
	Animation m_Animation_Jump;		// �W�����v�G
	Animation m_Animation_Gun_Stand;// �����Ȃ���̎ˌ��G
	Animation m_Animation_Gun_Walk;	// �����Ȃ���̎ˌ��G
	Image m_Image_Gun_Arm;	// �ˌ��̘r�G

	int m_Jump_Height;	// �W�����v�̍���
	Jump_Wave m_Jump_Wave;	// �W�����v�̏����Ɏg��
	bool m_Key_Lock;	// true ���L�[�{�[�h����s��
	SDL_Rect m_Gun_Arm_Position;	// �ˌ��G�̘r�̕\�����W
	double m_Angle;	 // �e�̊p�x
	bool m_Gun_Flag;	// �e�������Ă���Ƃ��� true
};

