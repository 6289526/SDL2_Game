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

	// 弾の初期化 10発分
	for (int i = 0; i < Bullet_Num; ++i) {
		m_Bullet[i] = nullptr;
	}
}

void Player::Draw(SDL_Renderer* renderer, Map& map)
{
	// 下の当たり判定
	Collision_Under(map);
	
	//重力
	Gravity();

	// マウスのウィンドウ上の座標を得る
	SDL_GetMouseState(&m_Mouse_Position.x, &m_Mouse_Position.y);

	// 状態によって描画絵が異なる
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
	if (t_Key[SDL_SCANCODE_W]) {
		m_Situation = Jump;
	}

	// 立ち絵
	// 右キー左キー同時押し　ジャンプ中でない
	if (t_Key[SDL_SCANCODE_D] && t_Key[SDL_SCANCODE_A] && m_Situation != Jump) {
		m_Situation = Stand;
	}
	// 立ち絵
	// 右キー左キーどちらも押していない　ジャンプ中でない
	else if (!t_Key[SDL_SCANCODE_D] && !t_Key[SDL_SCANCODE_A] && m_Situation != Jump) {
		m_Situation = Stand;
	}
	// 歩行絵
	// 右キーでマップを左に移動　ジャンプ中は特殊処理
	else if (t_Key[SDL_SCANCODE_D]) {
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
	else if (t_Key[SDL_SCANCODE_A]) {
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

		double t_Difference_x = static_cast<double>(m_Mouse_Position.x) - static_cast<double>(m_Gun_Arm_Position.x);
		double t_Difference_y = static_cast<double>(m_Mouse_Position.y) - static_cast<double>(m_Gun_Arm_Position.y);

		m_Angle = atan2(t_Difference_y, t_Difference_x);

		// 度数表記
		double t_Angle = m_Angle * 180 / M_PI;

		// 腕の表示
		if (m_Direction == Right) {
			// 腕の右上座標
			m_Gun_Arm_Position.x = m_Position.x + m_Position.w / 2;
			// 回転中心
			SDL_Point t_Point = { 0,0 };
			// 真横の右を０度にする角度調整と描画
			m_Image_Gun_Arm.Draw_Rotation(m_Gun_Arm_Position, renderer, t_Angle - 28, &t_Point);
		}
		else if (m_Direction == Left) {
			// 腕の中心座標
			m_Gun_Arm_Position.x = m_Position.x - m_Position.w / 3;

			// 回転中心
			SDL_Point t_Point = { m_Gun_Arm_Position.w, 0 };
			// 真横の右を０度にする角度調整と描画
			m_Image_Gun_Arm.Draw_Rotation(m_Gun_Arm_Position, renderer, t_Angle + 28 + 180, &t_Point, true);
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

		double t_Difference_x = static_cast<double>(m_Mouse_Position.x) - static_cast<double>(m_Gun_Arm_Position.x);
		double t_Difference_y = static_cast<double>(m_Mouse_Position.y) - static_cast<double>(m_Gun_Arm_Position.y);

		m_Angle = atan2(t_Difference_y, t_Difference_x);

		// 度数表記に変換して代入
		double t_Angle = m_Angle * 180 / M_PI;

		// 腕の表示
		if (m_Direction == Right) {
			// 腕の右上座標
			m_Gun_Arm_Position.x = m_Position.x + m_Position.w / 2;
			// 回転中心
			SDL_Point t_Point = { 0,0 };
			m_Image_Gun_Arm.Draw_Rotation(m_Gun_Arm_Position, renderer, t_Angle - 30.0, &t_Point);
		}
		else if (m_Direction == Left) {
			// 腕の中心座標
			m_Gun_Arm_Position.x = m_Position.x - m_Position.w / 3;
			// 回転中心
			SDL_Point t_Point = { m_Gun_Arm_Position.w, 0 };
			m_Image_Gun_Arm.Draw_Rotation(m_Gun_Arm_Position, renderer, t_Angle + 180, &t_Point, true);
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

void Player::Draw_Bullet(SDL_Renderer* renderer, Map& map)
{
	bool t_Rock = false;	// 一定時間おきにしか弾が出ないようにロック

	static int t_Count = 60;

	// １秒おきにしか弾が出ない
	if (m_Gun_Flag && t_Count++ == 60) {
		t_Count = 0;
		t_Rock = true;
	}

	if (m_Gun_Flag && !t_Rock) {
		m_Angle = 2 * M_PI - m_Angle;
		// 弾を１０発撃ち切っていないなら
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

	// 生成された弾を動かす あるいは 終わらせる処理
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


