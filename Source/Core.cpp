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