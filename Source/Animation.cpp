#include "Animation.h"

// コンストラクタ
Animation::Animation(const char* image_path, int n_x, int n_y, int w, int h, SDL_Renderer* renderer)
	:	m_Num_x(n_x),
		m_Num_y(n_y),
		m_Count(0),
		m_Loop_Count(1),
		m_Image_Number(1)
{
	// サーフェス生成
	SDL_Surface* t_Surface = IMG_Load(image_path);
	// テクスチャ生成
	m_Texture = SDL_CreateTextureFromSurface(renderer, t_Surface);
	// サーフェス破棄
	SDL_FreeSurface(t_Surface);

	// ｘ，ｙ は変わる　ｗ，ｈ は不変
	m_Image_Pos.x = 0;
	m_Image_Pos.y = 0;
	m_Image_Pos.w = w;
	m_Image_Pos.h = h;
}

// 描画
void Animation::Draw(const SDL_Rect position, SDL_Renderer* renderer, int num_frame, bool inverse)
{
	// 画像切り替えするまでカウンタをインクリメント
	// 画像切り替えの時は Switch() を呼び出し切り替え
	// カウントを０に
	if (++m_Count == num_frame) {
		m_Count = 0;

		Swicth();

		if (m_Image_Number++ == m_Num_x * m_Num_y) {
			m_Image_Number = 1;

			// ループ回数をインクリメント
			++m_Loop_Count;
		}
	}

	// インバースフラグが立っていれば反転して表示
	if (inverse) {
		SDL_RenderCopyEx(renderer, m_Texture, &m_Image_Pos, &position, 0.0, NULL, SDL_FLIP_HORIZONTAL);
	}
	else {
		SDL_RenderCopy(renderer, m_Texture, &m_Image_Pos, &position);
	}
}

void Animation::Draw_Rotation(const SDL_Rect position, SDL_Renderer* renderer, int num_frame, double angle, SDL_Point* center, bool inverse)
{
	// 画像切り替えするまでカウンタをインクリメント
	// 画像切り替えの時は Switch() を呼び出し切り替え
	// カウントを０に
	if (++m_Count == num_frame) {
		m_Count = 0;

		Swicth();

		if (m_Image_Number++ == m_Num_x * m_Num_y) {
			m_Image_Number = 1;

			// ループ回数をインクリメント
			++m_Loop_Count;
		}
	}

	// インバースフラグが立っていれば反転して表示
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

// 画像切り替え
void Animation::Swicth()
{
	// 読み込み位置が一番右なら一段下げる
	if (m_Image_Pos.w * m_Num_x == m_Image_Pos.x + m_Image_Pos.w) {

		// 読み込み位置が一番下なら一番上の段にする
		if (m_Image_Pos.h * m_Num_y == m_Image_Pos.y + m_Image_Pos.h) {
			m_Image_Pos.y = 0;
		}
		// それ以外は一段下げる
		else {
			m_Image_Pos.y += m_Image_Pos.h;
		}

		m_Image_Pos.x = 0;
	}
	// それ以外は右にずらす
	else {
		m_Image_Pos.x += m_Image_Pos.w;
	}
}
