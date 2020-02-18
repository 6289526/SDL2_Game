#include "Map.h"

// コンストラクタ
Map::Map(SDL_Renderer* renderer, int x)
	:	m_BackGround1("Image/Map/Background.bmp", renderer),
		m_Floor_Length(x + 2)
{
	m_Floor_Information.w = Window_x / (m_Floor_Length - 2);
	m_Floor_Information.h = 0;
	m_Floor_Information.x = -m_Floor_Information.w;
	m_Floor_Information.y = 0;

	// サーフェス生成
	SDL_Surface* t_Surface = IMG_Load("Image/Map/Floor.bmp");
	// テクスチャ生成
	m_Floor_Texture = SDL_CreateTextureFromSurface(renderer, t_Surface);
	// サーフェス破棄
	SDL_FreeSurface(t_Surface);
	// マップ配列生成
	m_Map = new int[m_Floor_Length];
	// マップ配列初期化
	Text_to_Map("Source/Map.txt", 0, 1, m_Floor_Length + 1);
}

// デストラクタ
Map::~Map()
{
	delete[] m_Map;
}

// 描画
void Map::Draw(SDL_Renderer* renderer)
{
	// 最背面描画
	SDL_Rect t_Pos_BackGrount = { 0, 0, Window_x, Window_y };
	m_BackGround1.Draw(t_Pos_BackGrount, renderer);
	// 床描画
	Draw_Floor(renderer);
}

// 床の高さを返す
int Map::Get_Height(int x) const
{
	x = (x - m_Floor_Information.x) / m_Floor_Information.w;

	return m_Map[x];
}

// txt ファイルから int 型配列に格納
void Map::Text_to_Map(const char* file_name, int pos, int s, int e)
{
	std::ifstream t_Ifs(file_name);
	std::string t_Str;

	for (int i = 1; i < s; ++i) {
		std::getline(t_Ifs, t_Str);
	}

	for (int i = s, j = pos; i < e; ++i, ++j) {
		std::getline(t_Ifs, t_Str);
		m_Map[j] = std::stoi(t_Str);
	}
}

// マップの端に達したら true それ以外は false
bool Map::Map_Lim(Direction direction) const
{
	switch (direction) {
	case Right:
		if (m_Map[m_Floor_Length - 1] == -1) {
			return true;
		}
		break;
	case Left:
		if (m_Map[0] == -1) {
			return true;
		}
		break;
	}
	return false;
}

// 床描画
void Map::Draw_Floor(SDL_Renderer* renderer)
{
	SDL_Rect t_Draw_Rect = {0, 0, m_Floor_Information.w, 0};
	t_Draw_Rect.x = m_Floor_Information.x;

	for (int i = 0; i < m_Floor_Length; ++i) {
		t_Draw_Rect.y = Window_y - m_Map[i];
		t_Draw_Rect.h = m_Map[i];

		SDL_RenderCopy(renderer, m_Floor_Texture, nullptr, &t_Draw_Rect);
		t_Draw_Rect.x += m_Floor_Information.w;
	}

	if (0 <= m_Floor_Information.x) {
		Move_Floor(Left);
		m_Floor_Information.x = -m_Floor_Information.w;
	}
	else if (m_Floor_Information.x <= -m_Floor_Information.w * 2) {
		Move_Floor(Right);
		m_Floor_Information.x = -m_Floor_Information.w;
	}
}

// 床を左右にずらす
void Map::Move_Floor(Direction direction)
{
	if (direction == Right) {
		++m_Text_Line;
		for (int i = 0; i < m_Floor_Length - 1; ++i) {
			m_Map[i] = m_Map[i + 1];
		}
		Text_to_Map("Source/Map.txt", m_Floor_Length - 1, m_Text_Line + m_Floor_Length - 1, m_Text_Line + m_Floor_Length);
	}
	else if (direction == Left) {
		--m_Text_Line;
		for (int i = m_Floor_Length - 1; i > 0; --i) {
			m_Map[i] = m_Map[i - 1];
		}
		Text_to_Map("Source/Map.txt", 0, m_Text_Line, m_Text_Line + 1);
	}
}
