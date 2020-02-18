#include "Player.h"

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
}

void Player::Draw(SDL_Renderer* renderer, Map& map)
{
	// 下の当たり判定
	Collision_Under(map);
	
	//重力
	Gravity();

	// 状態によって描画絵が異なる
	switch (m_Situation) {
	case Stand:
		Draw_Stand(renderer); break;

	case Walk:
		Draw_Walk(renderer); break;

	case Jump:
		Draw_Jump(renderer, map); break;
	}
}


void Player::Key_Check(SDL_Event event, bool& end, Map& map)
{
	// ウィンドウのバツで終了
	// 移動キーを離したときに立ち絵にする
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			end = true;
		}
	}

	// キー情報が入る
	// 入力中：１，非入力中：０
	const Uint8* t_Key = SDL_GetKeyboardState(NULL);

	// Esc キーで終了
	if (t_Key[SDL_SCANCODE_ESCAPE]) {
		end = true;
	}

	// 上キーでジャンプ
	if (t_Key[SDL_SCANCODE_UP]) {
		m_Situation = Jump;
	}

	// 立ち絵
	// 右キー左キー同時押し　ジャンプ中でない
	if (t_Key[SDL_SCANCODE_RIGHT] && t_Key[SDL_SCANCODE_LEFT] && m_Situation != Jump) {
		m_Situation = Stand;
	}
	// 立ち絵
	// 右キー左キーどちらも押していない　ジャンプ中でない
	else if (!t_Key[SDL_SCANCODE_RIGHT] && !t_Key[SDL_SCANCODE_LEFT] && m_Situation != Jump) {
		m_Situation = Stand;
	}
	// 歩行絵
	// 右キーでマップを左に移動　ジャンプ中は特殊処理
	else if (t_Key[SDL_SCANCODE_RIGHT]) {
		if (m_Situation != Jump) {
			m_Situation = Walk;
		}
		m_Direction = Right;
		if (!map.Map_Lim(Right) && Collision_Side(map, 8) && !m_Key_Lock) {
			map.Set_Plus_x(-4);
		}
	}
	// 歩行絵
	// 左キーでマップを右に移動　ジャンプ中は特殊処理
	else if (t_Key[SDL_SCANCODE_LEFT]) {
		if (m_Situation != Jump) {
			m_Situation = Walk;
		}
		m_Direction = Left;
		if (!map.Map_Lim(Left) && Collision_Side(map, 8) && !m_Key_Lock) {
			map.Set_Plus_x(4);
		}
	}

	// スペースキーで銃フラグを立てる
	// 銃を撃つ描画になる
	if (t_Key[SDL_SCANCODE_SPACE]) {
		m_Gun_Flag = true;
	}
	else {
		m_Gun_Flag = false;
	}
}

void Player::Draw_Stand(SDL_Renderer* renderer)
{

	// 表示位置調整 画面表示時のみ
	m_Position.y += 8;

	// 銃を撃っている場合
	if (m_Gun_Flag) {
		// プレイヤ描画
		if (m_Direction == Right) {
			m_Animation_Gun_Stand.Draw(m_Position, renderer, 10);
		}
		else if (m_Direction == Left) {
			m_Animation_Gun_Stand.Draw(m_Position, renderer, 10, true);
		}

		// 腕の左上ｙ
		m_Gun_Arm_Position.y = m_Position.y + m_Position.h / 2 - 10;

		// 腕の表示
		if (m_Direction == Right) {
			// 腕の右上座標
			m_Gun_Arm_Position.x = m_Position.x + m_Position.w / 2;
			// 回転中心
			SDL_Point t_Point = { 0,0 };
			m_Image_Gun_Arm.Draw_Rotation(m_Gun_Arm_Position, renderer, m_Angle, &t_Point);
		}
		else if (m_Direction == Left) {
			// 腕の中心座標
			m_Gun_Arm_Position.x = m_Position.x - m_Position.w / 3;
			// 回転中心
			SDL_Point t_Point = { m_Gun_Arm_Position.w, 0 };
			m_Image_Gun_Arm.Draw_Rotation(m_Gun_Arm_Position, renderer, m_Angle, &t_Point, true);
		}
	}
	// そうでない場合
	else {
		if (m_Direction == Right) {
			m_Animation_Stand.Draw(m_Position, renderer, 10);
		}
		else if (m_Direction == Left) {
			m_Animation_Stand.Draw(m_Position, renderer, 10, true);
		}
	}

	// 表示が終了したため戻す
	m_Position.y -= 8;
}


void Player::Draw_Walk(SDL_Renderer* renderer)
{
	// 表示位置調整 画面表示時のみ
	m_Position.y += 8;

	// 銃を撃っている場合
	if (m_Gun_Flag) {
		// プレイヤ描画
		if (m_Direction == Right) {
			m_Animation_Gun_Walk.Draw(m_Position, renderer, 5);
		}
		else if (m_Direction == Left) {
			m_Animation_Gun_Walk.Draw(m_Position, renderer, 5, true);
		}

		// 腕の左上ｙ
		m_Gun_Arm_Position.y = m_Position.y + m_Position.h / 2 - 10;

		// 腕の表示
		if (m_Direction == Right) {
			// 腕の右上座標
			m_Gun_Arm_Position.x = m_Position.x + m_Position.w / 2;
			// 回転中心
			SDL_Point t_Point = { 0,0 };
			m_Image_Gun_Arm.Draw_Rotation(m_Gun_Arm_Position, renderer, m_Angle, &t_Point);
		}
		else if (m_Direction == Left) {
			// 腕の中心座標
			m_Gun_Arm_Position.x = m_Position.x - m_Position.w / 3;
			// 回転中心
			SDL_Point t_Point = { m_Gun_Arm_Position.w, 0 };
			m_Image_Gun_Arm.Draw_Rotation(m_Gun_Arm_Position, renderer, m_Angle, &t_Point, true);
		}
	}
	// そうでない場合
	else {
		if (m_Direction == Right) {
			m_Animation_Walk.Draw(m_Position, renderer, 5);
		}
		else if (m_Direction == Left) {
			m_Animation_Walk.Draw(m_Position, renderer, 5, true);
		}
	}

	// 表示が終了したため戻す
	m_Position.y -= 8;
}

void Player::Draw_Jump(SDL_Renderer* renderer, Map& map)
{
	// 表示位置調整 画面表示時のみ
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

	// 表示が終了したため戻す
	m_Position.y -= 8;
}

