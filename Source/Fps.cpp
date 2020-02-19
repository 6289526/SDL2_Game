#include "Fps.h"

// コンストラクタ
Fps::Fps(int fps)
	:	m_StartTime(0),
		m_Count(0),
		m_Fps(0.0),
		m_Fps_ideal(fps)
{
}

// 更新
void Fps::Update()
{
	// １フレーム目なら時刻を記録
	if (m_Count == 0) {
		m_StartTime = SDL_GetTicks();
	}

	// 指定されたフレーム目なら平均を計算
	// カウントのやり直し
	if (m_Count == m_Fps_ideal) {
		unsigned t_Now_Time = SDL_GetTicks();
		m_Fps = 1000.f / ((t_Now_Time - m_StartTime) / static_cast<float> (m_Fps_ideal));
		m_Count = 0;
		m_StartTime = t_Now_Time;
	}

	++m_Count;
}

void Fps::Wait() const
{
	// かかった時間
	int t_Took_Time = SDL_GetTicks() - m_StartTime;
	// １フレームあたりの待ち時間
	int t_Wait_Time = m_Count * 1000 / m_Fps_ideal - t_Took_Time;

	// 待ち
	if (0 < t_Wait_Time) {
		SDL_Delay(t_Wait_Time);
	}
}

std::string Fps::Get_Fps()
{
	std::string t_Str("FPS : ");

	std::ostringstream t_ss;
	t_ss << m_Fps;
	t_Str += t_ss.str();

	return t_Str;
}
