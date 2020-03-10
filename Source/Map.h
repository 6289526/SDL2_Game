#pragma once

#include <fstream>
#include <string>

#include "Core.h"
#include "Image.h"

class Map
{
public:
	/* (�����_���C�E�B���h�E���̃}�b�v�̒���) */
	Map(SDL_Renderer* renderer, int x);
	~Map();
	/* (�����_��) */
	void Draw(SDL_Renderer* renderer);
	/* (�E�B���h�E�������W) */
	int Get_Height(int x) const;
	/* (txt�t�@�C���̃p�X�C�ϊ��J�n�ʒu^�}�b�v�z��̓Y����^�C�ǂݏo���J�n�s�C�ǂݏo���I���s) */
	void Text_to_Map(const char* file_name, int pos, int s, int e);
	/* (�}�b�v�𓮂����l) */
	void Set_Plus_x(int value);
	/* (�L�����̌���) */
	bool Map_Lim(Direction direction) const;
	int Get_Move_Value() const { return m_Move_Value; }

private:
	/* (�����_��) */
	void Draw_Floor(SDL_Renderer* renderer);
	/* (�L�����̌���) */
	void Move_Floor(Direction direction);

private:
	Image m_BackGround1;	// �w�i�P

	SDL_Texture* m_Floor_Texture;
	const int m_Floor_Length;	// �E�B���h�E���̃}�b�v�̒���
	int* m_Map;	// ���̍��������P�����z��
	int m_Text_Line;	// ���݂� txt �t�@�C���̍s
	SDL_Rect m_Floor_Information;	//��ԍ��̏��̍��゘�C�����C(���C���͎g��Ȃ�)

	int m_Move_Value;	// �}�b�v���ǂꂾ����������
};

