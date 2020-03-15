#include "Manage_Enemy.h"

Manage_Enemy::Manage_Enemy()
{
	// “Gî•ñ‚Ì‰Šú‰»
	for (int i = 0; i < Enemy_Num; ++i) {
		m_Enemy[i] = nullptr;
	}
}

// “K¶¬
int Manage_Enemy::Create_Enemy(SDL_Renderer* renderer, SDL_Rect position)
{
	for (int i = 0; i < Enemy_Num; ++i) {
		if (m_Enemy[i] == nullptr) {
			m_Enemy[i] = new Enemy(renderer, position);
			return i;
		}
	}

	return -1;
}

// •`‰æ
void Manage_Enemy::Draw(SDL_Renderer* renderer, Map& map)
{
	for (int i = 0; i < Enemy_Num; ++i) {
		if (m_Enemy[i] != nullptr) {
			m_Enemy[i]->Draw(renderer, map);
		}
	}

	Destroy_Enemy();
}

// “GƒLƒƒƒ‰‚ğ“®‚©‚·	
void Manage_Enemy::Move(SDL_Rect position)
{
	for (int i = 0; i < Enemy_Num; ++i) {
		if (m_Enemy[i] != nullptr) {
			m_Enemy[i]->Move(position);
		}
	}
}

// “GƒLƒƒƒ‰‚ÌÀ•W‚ğ•\¦
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

// “GƒLƒƒƒ‰‚Ì”j‰ó
void Manage_Enemy::Destroy_Enemy()
{
	for (int i = 0; i < Enemy_Num; ++i) {
		if (m_Enemy[i] != nullptr) {
			// HP ‚ª 0@‚È‚ç
			if (m_Enemy[i]->Get_Hp() == 0) {
				delete m_Enemy[i];
				m_Enemy[i] = nullptr;
			}
		}
	}
}
