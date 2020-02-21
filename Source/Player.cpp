#include "Player.h"

#include "cmath"

Player::Player(SDL_Renderer* renderer)
	:	Character(300, 300, 800 * Player_Scale, 1000 * Player_Scale, Right),
		m_Animation_Stand("Image/Player/Player_Stand9.bmp", 3, 3, 800, 1000, renderer),
		m_Animation_Walk("Image/Player/Player_Walk12.bmp", 4, 3, 800, 1000, renderer),
		m_Animation_Jump("Image/Player/Player_Jump5.bmp", 5, 1, 800, 1000, renderer),
		m_Animation_Gun_Stand("Image/Player/Player_Gun_Stand9.bmp", 3, 3, 800, 1000, renderer),
		m_Animation_Gun_Walk("Image/Player/Player_Gun_Walk12.bmp", 4, 3, 800, 1000, renderer),
		m_Image_Gun_Arm("Image/Player/Player_Arm.bmp", renderer),
		m_Jump_Height(25),
		m_Jump_Wave(Take_Off),
		m_Key_Lock(false),
		m_Angle(0.0),
		m_Gun_Flag(false)
{
	m_Gun_Arm_Position.x = m_Position.x;
	m_Gun_Arm_Position.y = m_Position.y;
	m_Gun_Arm_Position.w = 430 * Player_Scale * 1.6;
	m_Gun_Arm_Position.h = 200 * Player_Scale * 1.6;

	m_Mouse_Position.x = Window_x;
	m_Mouse_Position.y = Window_y;

	// �e�̏����� 10����
	for (int i = 0; i < Bullet_Num; ++i) {
		m_Bullet[i] = nullptr;
	}
}

void Player::Draw(SDL_Renderer* renderer, Map& map)
{
	// ���̓����蔻��
	Collision_Under(map);
	
	//�d��
	Gravity();

	// �}�E�X�̃E�B���h�E��̍��W�𓾂�
	SDL_GetMouseState(&m_Mouse_Position.x, &m_Mouse_Position.y);

	// ��Ԃɂ���ĕ`��G���قȂ�
	switch (m_Situation) {
	case Stand:
		Draw_Stand(renderer); break;

	case Walk:
		Draw_Walk(renderer); break;

	case Jump:
		Draw_Jump(renderer, map); break;
	}

	Draw_Bullet(renderer, map);
}


void Player::Key_Check(SDL_Event event, bool& end, Map& map)
{
	// �E�B���h�E�̃o�c�ŏI��
	// �ړ��L�[�𗣂����Ƃ��ɗ����G�ɂ���
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			end = true;
		}
	}

	// �L�[��񂪓���
	// ���͒��F�P�C����͒��F�O
	const Uint8* t_Key = SDL_GetKeyboardState(NULL);

	// Esc �L�[�ŏI��
	if (t_Key[SDL_SCANCODE_ESCAPE]) {
		end = true;
	}

	// ��L�[�ŃW�����v
	if (t_Key[SDL_SCANCODE_W]) {
		m_Situation = Jump;
	}

	// �����G
	// �E�L�[���L�[���������@�W�����v���łȂ�
	if (t_Key[SDL_SCANCODE_D] && t_Key[SDL_SCANCODE_A] && m_Situation != Jump) {
		m_Situation = Stand;
	}
	// �����G
	// �E�L�[���L�[�ǂ���������Ă��Ȃ��@�W�����v���łȂ�
	else if (!t_Key[SDL_SCANCODE_D] && !t_Key[SDL_SCANCODE_A] && m_Situation != Jump) {
		m_Situation = Stand;
	}
	// ���s�G
	// �E�L�[�Ń}�b�v�����Ɉړ��@�W�����v���͓��ꏈ��
	else if (t_Key[SDL_SCANCODE_D]) {
		if (m_Situation != Jump) {
			m_Situation = Walk;
		}
		m_Direction = Right;
		if (!map.Map_Lim(Right) && Collision_Side(map, 8) && !m_Key_Lock) {
			map.Set_Plus_x(-4);
		}
	}
	// ���s�G
	// ���L�[�Ń}�b�v���E�Ɉړ��@�W�����v���͓��ꏈ��
	else if (t_Key[SDL_SCANCODE_A]) {
		if (m_Situation != Jump) {
			m_Situation = Walk;
		}
		m_Direction = Left;
		if (!map.Map_Lim(Left) && Collision_Side(map, 8) && !m_Key_Lock) {
			map.Set_Plus_x(4);
		}
	}

	// �X�y�[�X�L�[�ŏe�t���O�𗧂Ă�
	// �e�����`��ɂȂ�
	if (t_Key[SDL_SCANCODE_SPACE]) {
		m_Gun_Flag = true;
	}
	else {
		m_Gun_Flag = false;
	}
}

void Player::Draw_Stand(SDL_Renderer* renderer)
{

	// �\���ʒu���� ��ʕ\�����̂�
	m_Position.y += 8;

	// �e�������Ă���ꍇ
	if (m_Gun_Flag) {
		// �v���C���`��
		if (m_Direction == Right) {
			m_Animation_Gun_Stand.Draw(m_Position, renderer, 10);
		}
		else if (m_Direction == Left) {
			m_Animation_Gun_Stand.Draw(m_Position, renderer, 10, true);
		}

		// �r�̍��゙
		m_Gun_Arm_Position.y = m_Position.y + m_Position.h / 2 - 10;

		double t_Difference_x = static_cast<double>(m_Mouse_Position.x) - static_cast<double>(m_Gun_Arm_Position.x);
		double t_Difference_y = static_cast<double>(m_Mouse_Position.y) - static_cast<double>(m_Gun_Arm_Position.y);

		m_Angle = atan2(t_Difference_y, t_Difference_x);

		// �x���\�L
		double t_Angle = m_Angle * 180 / M_PI;

		// �r�̕\��
		if (m_Direction == Right) {
			// �r�̉E����W
			m_Gun_Arm_Position.x = m_Position.x + m_Position.w / 2;
			// ��]���S
			SDL_Point t_Point = { 0,0 };
			// �^���̉E���O�x�ɂ���p�x�����ƕ`��
			m_Image_Gun_Arm.Draw_Rotation(m_Gun_Arm_Position, renderer, t_Angle - 28, &t_Point);
		}
		else if (m_Direction == Left) {
			// �r�̒��S���W
			m_Gun_Arm_Position.x = m_Position.x - m_Position.w / 3;

			// ��]���S
			SDL_Point t_Point = { m_Gun_Arm_Position.w, 0 };
			// �^���̉E���O�x�ɂ���p�x�����ƕ`��
			m_Image_Gun_Arm.Draw_Rotation(m_Gun_Arm_Position, renderer, t_Angle + 28 + 180, &t_Point, true);
		}
	}
	// �����łȂ��ꍇ
	else {
		if (m_Direction == Right) {
			m_Animation_Stand.Draw(m_Position, renderer, 10);
		}
		else if (m_Direction == Left) {
			m_Animation_Stand.Draw(m_Position, renderer, 10, true);
		}
	}
	// �\�����I���������ߖ߂�
	m_Position.y -= 8;
}


void Player::Draw_Walk(SDL_Renderer* renderer)
{
	// �\���ʒu���� ��ʕ\�����̂�
	m_Position.y += 8;

	// �e�������Ă���ꍇ
	if (m_Gun_Flag) {
		// �v���C���`��
		if (m_Direction == Right) {
			m_Animation_Gun_Walk.Draw(m_Position, renderer, 5);
		}
		else if (m_Direction == Left) {
			m_Animation_Gun_Walk.Draw(m_Position, renderer, 5, true);
		}

		// �r�̍��゙
		m_Gun_Arm_Position.y = m_Position.y + m_Position.h / 2 - 10;

		double t_Difference_x = static_cast<double>(m_Mouse_Position.x) - static_cast<double>(m_Gun_Arm_Position.x);
		double t_Difference_y = static_cast<double>(m_Mouse_Position.y) - static_cast<double>(m_Gun_Arm_Position.y);

		m_Angle = atan2(t_Difference_y, t_Difference_x);

		// �x���\�L�ɕϊ����đ��
		double t_Angle = m_Angle * 180 / M_PI;

		// �r�̕\��
		if (m_Direction == Right) {
			// �r�̉E����W
			m_Gun_Arm_Position.x = m_Position.x + m_Position.w / 2;
			// ��]���S
			SDL_Point t_Point = { 0,0 };
			m_Image_Gun_Arm.Draw_Rotation(m_Gun_Arm_Position, renderer, t_Angle - 30.0, &t_Point);
		}
		else if (m_Direction == Left) {
			// �r�̒��S���W
			m_Gun_Arm_Position.x = m_Position.x - m_Position.w / 3;
			// ��]���S
			SDL_Point t_Point = { m_Gun_Arm_Position.w, 0 };
			m_Image_Gun_Arm.Draw_Rotation(m_Gun_Arm_Position, renderer, t_Angle + 180, &t_Point, true);
		}
	}
	// �����łȂ��ꍇ
	else {
		if (m_Direction == Right) {
			m_Animation_Walk.Draw(m_Position, renderer, 5);
		}
		else if (m_Direction == Left) {
			m_Animation_Walk.Draw(m_Position, renderer, 5, true);
		}
	}

	// �\�����I���������ߖ߂�
	m_Position.y -= 8;
}

void Player::Draw_Jump(SDL_Renderer* renderer, Map& map)
{
	// �\���ʒu���� ��ʕ\�����̂�
	m_Position.y += 8;

	switch (m_Jump_Wave) {
	case Take_Off:
		if (m_Animation_Jump.Get_Loop_Count() <= 1) {
			if (m_Direction == Right) {
				m_Animation_Jump.Draw(m_Position, renderer, 3);
			}
			else if (m_Direction == Left) {
				m_Animation_Jump.Draw(m_Position, renderer, 3, true);
			}
			m_Key_Lock = true;
		}
		else {
			m_Key_Lock = false;
			m_Animation_Jump.Reset();
			m_Jump_Wave = Jumping;
			m_Position.y -= m_Jump_Height;
			if (m_Direction == Right) {
				m_Animation_Stand.Draw(m_Position, renderer, 10);
			}
			else if (m_Direction == Left) {
				m_Animation_Stand.Draw(m_Position, renderer, 10, true);
			}
		}
		break;

	case Jumping:
		m_Position.y -= m_Jump_Height;
		Draw_Stand(renderer);
		Collision_Under(map);
		if (m_Ground) {
			m_Jump_Wave = Landing;
		}
		break;

	case Landing:
		if (m_Animation_Jump.Get_Loop_Count() <= 1) {
			if (m_Direction == Right) {
				m_Animation_Jump.Draw(m_Position, renderer, 3);
			}
			else if (m_Direction == Left) {
				m_Animation_Jump.Draw(m_Position, renderer, 3, true);
			}
			m_Key_Lock = true;
		}
		else {
			m_Key_Lock = false;
			m_Animation_Jump.Reset();
			m_Jump_Wave = Take_Off;
			m_Situation = Stand;
			if (m_Direction == Right) {
				m_Animation_Stand.Draw(m_Position, renderer, 10);
			}
			else if (m_Direction == Left) {
				m_Animation_Stand.Draw(m_Position, renderer, 10, true);
			}
		}
		break;
	}

	// �\�����I���������ߖ߂�
	m_Position.y -= 8;
}

void Player::Draw_Bullet(SDL_Renderer* renderer, Map& map)
{
	bool t_Rock = false;	// ��莞�Ԃ����ɂ����e���o�Ȃ��悤�Ƀ��b�N

	static int t_Count = 60;

	// �P�b�����ɂ����e���o�Ȃ�
	if (m_Gun_Flag && t_Count++ == 60) {
		t_Count = 0;
		t_Rock = true;
	}

	if (m_Gun_Flag && !t_Rock) {
		m_Angle = 2 * M_PI - m_Angle;
		// �e���P�O�������؂��Ă��Ȃ��Ȃ�
		for (int i = 0; i < Bullet_Num; ++i) {
			if (m_Bullet[i] == nullptr) {
				if (m_Direction == Right) {
					m_Bullet[i] = new Bullet(m_Gun_Arm_Position, 1, 10.0, m_Angle, m_Direction, renderer);
				}
				else if (m_Direction == Left) {
					m_Bullet[i] = new Bullet(m_Gun_Arm_Position, 1, 10.0, m_Angle, m_Direction, renderer);
				}
			}
		}
	}

	// �������ꂽ�e�𓮂��� ���邢�� �I��点�鏈��
	for (int i = 0; i < Bullet_Num; ++i) {
		if (m_Bullet[i] != nullptr) {
			m_Bullet[i]->Draw(renderer, map);

			if (m_Bullet[i]->End) {
				delete m_Bullet[i];
				m_Bullet[i] = nullptr;
			}
		}
	}
}


