#include "Animation.h"

// �R���X�g���N�^
Animation::Animation(const char* image_path, int n_x, int n_y, int w, int h, SDL_Renderer* renderer)
	:	m_Num_x(n_x),
		m_Num_y(n_y),
		m_Count(0),
		m_Loop_Count(1),
		m_Image_Number(1)
{
	// �T�[�t�F�X����
	SDL_Surface* t_Surface = IMG_Load(image_path);
	// �e�N�X�`������
	m_Texture = SDL_CreateTextureFromSurface(renderer, t_Surface);
	// �T�[�t�F�X�j��
	SDL_FreeSurface(t_Surface);

	// ���C�� �͕ς��@���C�� �͕s��
	m_Image_Pos.x = 0;
	m_Image_Pos.y = 0;
	m_Image_Pos.w = w;
	m_Image_Pos.h = h;
}

// �`��
void Animation::Draw(const SDL_Rect position, SDL_Renderer* renderer, int num_frame, bool inverse)
{
	// �摜�؂�ւ�����܂ŃJ�E���^���C���N�������g
	// �摜�؂�ւ��̎��� Switch() ���Ăяo���؂�ւ�
	// �J�E���g���O��
	if (++m_Count == num_frame) {
		m_Count = 0;

		Swicth();

		if (m_Image_Number++ == m_Num_x * m_Num_y) {
			m_Image_Number = 1;

			// ���[�v�񐔂��C���N�������g
			++m_Loop_Count;
		}
	}

	// �C���o�[�X�t���O�������Ă���Δ��]���ĕ\��
	if (inverse) {
		SDL_RenderCopyEx(renderer, m_Texture, &m_Image_Pos, &position, 0.0, NULL, SDL_FLIP_HORIZONTAL);
	}
	else {
		SDL_RenderCopy(renderer, m_Texture, &m_Image_Pos, &position);
	}
}

void Animation::Draw_Rotation(const SDL_Rect position, SDL_Renderer* renderer, int num_frame, double angle, SDL_Point* center, bool inverse)
{
	// �摜�؂�ւ�����܂ŃJ�E���^���C���N�������g
	// �摜�؂�ւ��̎��� Switch() ���Ăяo���؂�ւ�
	// �J�E���g���O��
	if (++m_Count == num_frame) {
		m_Count = 0;

		Swicth();

		if (m_Image_Number++ == m_Num_x * m_Num_y) {
			m_Image_Number = 1;

			// ���[�v�񐔂��C���N�������g
			++m_Loop_Count;
		}
	}

	// �C���o�[�X�t���O�������Ă���Δ��]���ĕ\��
	if (inverse) {
		SDL_RenderCopyEx(renderer, m_Texture, &m_Image_Pos, &position, angle, center, SDL_FLIP_HORIZONTAL);
	}
	else {
		SDL_RenderCopyEx(renderer, m_Texture, &m_Image_Pos, &position, angle, center, SDL_FLIP_NONE);
	}
}

void Animation::Reset()
{
	m_Image_Pos.x = 0;
	m_Image_Pos.y = 0;
	m_Count = 0;
	m_Loop_Count = 1;
	m_Image_Number = 1;
}

// �摜�؂�ւ�
void Animation::Swicth()
{
	// �ǂݍ��݈ʒu����ԉE�Ȃ��i������
	if (m_Image_Pos.w * m_Num_x == m_Image_Pos.x + m_Image_Pos.w) {

		// �ǂݍ��݈ʒu����ԉ��Ȃ��ԏ�̒i�ɂ���
		if (m_Image_Pos.h * m_Num_y == m_Image_Pos.y + m_Image_Pos.h) {
			m_Image_Pos.y = 0;
		}
		// ����ȊO�͈�i������
		else {
			m_Image_Pos.y += m_Image_Pos.h;
		}

		m_Image_Pos.x = 0;
	}
	// ����ȊO�͉E�ɂ��炷
	else {
		m_Image_Pos.x += m_Image_Pos.w;
	}
}
