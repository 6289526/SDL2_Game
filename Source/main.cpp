#include "SDL2/SDL.h"
#include "string"

#include "Core.h"
#include "Fps.h"
#include "Map.h"
#include "Player.h"

// 画面に文字を出力する
void Print_Screen(const std::string& str, TTF_Font* font, const SDL_Color& color, SDL_Renderer* renderer, int y);

int main(int argc, char* argv[]) {

    Core core(1024, 768);   // 基本的な情報

    Fps fps(60);    // FPS
    SDL_Color Color_Fps = { 0xff, 0xff, 0xff }; // 白

    Map map(core.Get_Renderer(), 128);  // マップ

    Player player(core.Get_Renderer());  // プレイヤー

    // エンドフラグが立つまで実行
    while (!core.m_Program_End) {
      
        fps.Update();   // FPS 更新
        
        SDL_RenderClear(core.Get_Renderer());   // 画面リセット

        player.Key_Check(core.Get_Event(), core.m_Program_End, map); // キー操作感知
        
        map.Draw(core.Get_Renderer());  //  マップ描画

        // FPS値表示
        Print_Screen(fps.Get_Fps(), core.Get_Font(), Color_Fps, core.Get_Renderer(), 30);

        player.Draw(core.Get_Renderer(), map);   // プレイヤー描画

        SDL_RenderPresent(core.Get_Renderer()); // 画面に表示

        fps.Wait(); // 待機
    }

    return 0;
}


/* (表示する文字，フォント，色，レンダラ, 表示するｙ座標) */
void Print_Screen(const std::string& str, TTF_Font* font, const SDL_Color& color, SDL_Renderer* renderer, int y) {

    SDL_Surface* t_Surface = TTF_RenderUTF8_Blended(font, str.c_str(), color);

    SDL_Rect t_Print_Rect = { 30, y, t_Surface->w, t_Surface->h };

    SDL_Texture* t_Texture = SDL_CreateTextureFromSurface(renderer, t_Surface);

    SDL_RenderCopy(renderer, t_Texture, nullptr, &t_Print_Rect);
}
