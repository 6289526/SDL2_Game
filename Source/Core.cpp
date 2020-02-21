#include "Core.h"

// コンストラクタ
Core::Core(int x, int y)
    :   m_Program_End(false)
{
	SDL_Init(SDL_INIT_EVERYTHING);	//SDL2の初期化
    TTF_Init(); // 文字を扱うための

	m_Window = SDL_CreateWindow(
        "window", //ウィンドウタイトル
        SDL_WINDOWPOS_UNDEFINED, //ウィンドウ位置ｘ
        SDL_WINDOWPOS_UNDEFINED, //ウィンドウ位置ｙ
        x, //幅
        y, //高さ
        SDL_WINDOW_OPENGL //flags 詳細はマニュアル参照
    );

    // レンダラ作成
    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);

    // フォント読み込み
    m_Font = TTF_OpenFont("Font/MyricaM/MyricaM.TTC", 24);
}

Core::~Core()
{
    TTF_CloseFont(m_Font);  // フォント破棄
    TTF_Quit(); // 文字の扱いを終了
    SDL_DestroyWindow(m_Window);  // ウィンドウ破棄
    SDL_Quit(); // SDL2終了
}

// 画面に文字を出力する
void Print_Screen(const std::string& str, SDL_Renderer* renderer, int y) {

    TTF_Font* t_Font = TTF_OpenFont("Font/MyricaM/MyricaM.TTC", 24);
    SDL_Color t_Color = { 0xff, 0xff, 0xff }; // 白

    SDL_Surface* t_Surface = TTF_RenderUTF8_Blended(t_Font, str.c_str(), t_Color);

    SDL_Rect t_Print_Rect = { 30, y, t_Surface->w, t_Surface->h };

    SDL_Texture* t_Texture = SDL_CreateTextureFromSurface(renderer, t_Surface);

    SDL_RenderCopy(renderer, t_Texture, nullptr, &t_Print_Rect);
}