#include "Manage_Enemy.h"

Manage_Enemy::Manage_Enemy()
{
	// �G���̏�����
	for (int i = 0; i < Enemy_Num; ++i) {
		m_Enemy[i] = nullptr;
	}
}

// �K����
int Manage_Enemy::Create_Enemy(SDL_Renderer* renderer, SDL_Rect position, Enemy_Type type)
{
	for (int i = 0; i < Enemy_Num; ++i) {
		if (m_Enemy[i] == nullptr) {
			if (type == Test) {
				m_Enemy[i] = new Enemy(renderer, position, "Image/Enemy/Enemy_Test.bmp", 4, 1);
			}
			else if (type == Leg) {
				m_Enemy[i] = new Enemy(renderer, position, "Image/Enemy/Enemy1_Walk.bmp", 3, 2);
				m_Enemy[i]->m_Draw_Adjustment = 20;	// �\�����̏㉺�̒���
			}
			
			return i;
		}
	}

	return -1;
}

// �`��
void Manage_Enemy::Draw(SDL_Renderer* renderer, Map& map)
{
	for (int i = 0; i < Enemy_Num; ++i) {
		if (m_Enemy[i] != nullptr) {
			m_Enemy[i]->Draw(renderer, map);
		}
	}

	Destroy_Enemy();
}

// �G�L�����𓮂���	
void Manage_Enemy::Move(SDL_Rect position)
{
	for (int i = 0; i < Enemy_Num; ++i) {
		if (m_Enemy[i] != nullptr) {
			m_Enemy[i]->Move(position);
		}
	}
}

// �G�L�����̍��W��\��
void Manage_Enemy::Print_Position(SDL_Renderer* renderer, int x, int y)
{
	int t_Line = 0;
	for (int i = 0; i < Enemy_Num; ++i) {
		if (m_Enemy[i] != nullptr) {
			m_Enemy[i]->Print_Position(renderer, x, y + t_Line * 30);
			++t_Line;
		}
	}
}

// �G�L�����̔j��
void Manage_Enemy::Destroy_Enemy()
{
	for (int i = 0; i < Enemy_Num; ++i) {
		if (m_Enemy[i] != nullptr) {
			// HP �� 0�@�Ȃ�
			if (m_Enemy[i]->Get_Hp() == 0) {
				delete m_Enemy[i];
				m_Enemy[i] = nullptr;
			}
		}
	}
}
