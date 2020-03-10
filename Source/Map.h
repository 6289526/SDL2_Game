#pragma once

#include <fstream>
#include <string>

#include "Core.h"
#include "Image.h"

class Map
{
public:
	/* (レンダラ，ウィンドウ内のマップの長さ) */
	Map(SDL_Renderer* renderer, int x);
	~Map();
	/* (レンダラ) */
	void Draw(SDL_Renderer* renderer);
	/* (ウィンドウ内ｘ座標) */
	int Get_Height(int x) const;
	/* (txtファイルのパス，変換開始位置^マップ配列の添え字^，読み出し開始行，読み出し終了行) */
	void Text_to_Map(const char* file_name, int pos, int s, int e);
	/* (マップを動かす値) */
	void Set_Plus_x(int value);
	/* (キャラの向き) */
	bool Map_Lim(Direction direction) const;
	int Get_Move_Value() const { return m_Move_Value; }

private:
	/* (レンダラ) */
	void Draw_Floor(SDL_Renderer* renderer);
	/* (キャラの向き) */
	void Move_Floor(Direction direction);

private:
	Image m_BackGround1;	// 背景１

	SDL_Texture* m_Floor_Texture;
	const int m_Floor_Length;	// ウィンドウ内のマップの長さ
	int* m_Map;	// 床の高さを持つ１次元配列
	int m_Text_Line;	// 現在の txt ファイルの行
	SDL_Rect m_Floor_Information;	//一番左の床の左上ｘ，幅ｗ，(ｙ，ｈは使わない)

	int m_Move_Value;	// マップをどれだけ動かすか
};

