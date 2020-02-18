#include <SDL.h>

#include "Core.h"
#include "Fps.h"
#include "Map.h"
#include "Player.h"

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
        fps.Draw(30, 30, core.Get_Font(), Color_Fps, core.Get_Renderer());

        player.Draw(core.Get_Renderer(), map);   // プレイヤー描画

        SDL_RenderPresent(core.Get_Renderer()); // 画面に表示

        fps.Wait(); // 待機
    }

    return 0;
}
