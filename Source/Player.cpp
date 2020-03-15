#include "Player.h"

#include "Fanction.h"

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
		m_Angle_deg(0.0),
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

// �`��
void Player::Draw(SDL_Renderer* renderer, Map& map)
{	
	// �}�E�X�̃E�B���h�E��̍��W�𓾂�
	SDL_GetMouseState(&m_Mouse_Position.x, &m_Mouse_Position.y);

	// �r�̊p�x�擾 �^�E�������O�ɒ���
	m_Angle_deg = Angle_Degrees(m_Gun_Arm_Position, m_Mouse_Position);

	// �r�̉����ݒ�
	m_Angle_deg = Arm_Angle_Limit(m_Angle_deg);

	// ���̓����蔻��
	Collision_Under(map);

	//�d��
	Gravity();

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

// �L�[������󂯕t����
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
	// �E�L�[���L�[��������
	if (t_Key[SDL_SCANCODE_D] && t_Key[SDL_SCANCODE_A]) {
		// �W�����v���łȂ�
		if (m_Situation != Jump) {
			m_Situation = Stand;
		}

		map.Set_Plus_x(0);
	}
	// �����G
	// �E�L�[���L�[�ǂ���������Ă��Ȃ�
	else if (!t_Key[SDL_SCANCODE_D] && !t_Key[SDL_SCANCODE_A]) {
		// �W�����v���łȂ�
		if (m_Situation != Jump) {
			m_Situation = Stand;
		}

		map.Set_Plus_x(0);
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
		else {
			map.Set_Plus_x(0);
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
		else {
			map.Set_Plus_x(0);
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

// �r�̊p�x��\��
void Player::Print_Angle(SDL_Renderer* renderer, int x, int y)
{
	std::string t_Str = "Player Angle : ";
	Print_Screen(t_Str, renderer, x, y);
	Print_Screen(To_String(m_Angle_deg), renderer, x + 200, y);
}

// �v���C���̍��W��\��
void Player::Print_Position(SDL_Renderer* renderer, int x, int y)
{
	std::string t_Str = "Player Position : ";
	Print_Screen(t_Str, renderer, x, y);
	Character::Print_Position(renderer, x + 220, y);
}

// �����G�`��
void Player::Draw_Stand(SDL_Renderer* renderer)
{

	// �\���ʒu���� ��ʕ\�����̂�
	m_Position.y += 8;

	// �r�̍��゙����
	m_Gun_Arm_Position.y = m_Position.y + m_Position.h / 2 - 10;

	// �e�������Ă���ꍇ
	if (m_Gun_Flag) {
		// �v���C���`��
		if (m_Direction == Right) {
			m_Animation_Gun_Stand.Draw(m_Position, renderer, 10);
		}
		else if (m_Direction == Left) {
			m_Animation_Gun_Stand.Draw(m_Position, renderer, 10, true);
		}

		// �r�`��
		Draw_Arm(renderer);
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

// �����G�`��
void Player::Draw_Walk(SDL_Renderer* renderer)
{
	// �\���ʒu���� ��ʕ\�����̂�
	m_Position.y += 8;

	// �r�̍��゙����
	m_Gun_Arm_Position.y = m_Position.y + m_Position.h / 2 - 10;

	// �e�������Ă���ꍇ
	if (m_Gun_Flag) {
		// �v���C���`��
		if (m_Direction == Right) {
			m_Animation_Gun_Walk.Draw(m_Position, renderer, 5);
		}
		else if (m_Direction == Left) {
			m_Animation_Gun_Walk.Draw(m_Position, renderer, 5, true);
		}

		// �r�`��
		Draw_Arm(renderer);
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

// �W�����v�G�`��
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

// �e��`��
void Player::Draw_Bullet(SDL_Renderer* renderer, Map& map)
{
	bool t_Rock = false;	// ��莞�Ԃ����ɂ����e���o�Ȃ��悤�Ƀ��b�N

	static int t_Count = 30;

	// �O�D1�b�����ɂ����e���o�Ȃ�
	if (t_Count++ < 30) {
		t_Rock = true;
	}

	if (m_Gun_Flag && !t_Rock) {
		// ���W�A���\�L
		double t_Angle_rad = m_Angle_deg * M_PI / 180;
		// ��]�������t�ɂ���
		t_Angle_rad = 2 * M_PI - t_Angle_rad;
		// �e���P�O�������؂��Ă��Ȃ��Ȃ�
		for (int i = 0; i < Bullet_Num; ++i) {
			if (m_Bullet[i] == nullptr) {
				SDL_Rect t_Bullet_Position = m_Gun_Arm_Position;

				if (m_Direction == Right) {
					t_Bullet_Position.x += t_Bullet_Position.w * cos(t_Angle_rad + 0.13);
					t_Bullet_Position.y -= t_Bullet_Position.w * sin(t_Angle_rad + 0.13);

					m_Bullet[i] = new Bullet(t_Bullet_Position, 1, 10.0, t_Angle_rad, m_Direction, renderer);
				}
				else if (m_Direction == Left) {
					// ���̈ʒu�̍��W
					t_Bullet_Position.x += t_Bullet_Position.w;

					t_Bullet_Position.x += t_Bullet_Position.w * 1.3 * cos(t_Angle_rad - 0.13);
					t_Bullet_Position.y -= t_Bullet_Position.w * 1.3 * sin(t_Angle_rad - 0.13);

					
					m_Bullet[i] = new Bullet(t_Bullet_Position, 1, 10.0, t_Angle_rad + 0.05, m_Direction, renderer);
				}
				t_Count = 0;
				break;
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

// �r�`��
void Player::Draw_Arm(SDL_Renderer* renderer)
{
	// �r�̕\��
	if (m_Direction == Right) {
		// �r�̍�����W
		m_Gun_Arm_Position.x = m_Position.x + m_Position.w / 2;
		// ��]���S
		SDL_Point t_Point = { 0,0 };
		// �^���̉E���O�x�ɂ���p�x�����ƕ`��
		m_Image_Gun_Arm.Draw_Rotation(m_Gun_Arm_Position, renderer, m_Angle_deg - 28, &t_Point);
	}
	else if (m_Direction == Left) {
		// �r�̍�����W
		m_Gun_Arm_Position.x = m_Position.x - m_Position.w / 3;

		// ��]���S
		SDL_Point t_Point = { m_Gun_Arm_Position.w, 0 };
		// �^���̉E���O�x�ɂ���p�x�����ƕ`��
		m_Image_Gun_Arm.Draw_Rotation(m_Gun_Arm_Position, renderer, m_Angle_deg + 28 + 180, &t_Point, true);
	}
}

// �r�̉���
double Player::Arm_Angle_Limit(double angle)
{
	
	// ����
	if (m_Direction == Right) {
		if (90.0 < m_Angle_deg && m_Angle_deg < 180.0) {
			m_Angle_deg = 90.0;
		}
		else if (-180.0 < m_Angle_deg && m_Angle_deg < -90.0) {
			m_Angle_deg = -90.0;
		}
	}

	if (m_Direction == Left) {
		if (0.0 < m_Angle_deg && m_Angle_deg < 90.0) {
			m_Angle_deg = 90.0;
		}
		else if (-90.0 < m_Angle_deg && m_Angle_deg < 0.0) {
			m_Angle_deg = -90.0;
		}
	}

	return m_Angle_deg;
}


