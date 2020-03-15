#include "SDL2/SDL.h"
#include "string"

#include "Core.h"
#include "Fps.h"
#include "Map.h"
#include "Player.h"
#include "Manage_Enemy.h"

int main(int argc, char* argv[]) {

    Core core(1024, 768);   // 基本的な情報

    Fps fps(60);    // FPS

    Map map(core.Get_Renderer(), 128);  // マップ

    Player player(core.Get_Renderer());  // プレイヤー

    // 敵の初期位置
    SDL_Rect Enemy1_Position = { 400, 400, 800 * Enemy_Scale * 0.5, 1000 * Enemy_Scale * 0.5 };

    Manage_Enemy enemy; // 敵情報
    // 適生成
    enemy.Create_Enemy(core.Get_Renderer(), Enemy1_Position);
    // 敵の移動速度を指定
    enemy.Get_Enemy(0)->Set_Speed(2);

    // エンドフラグが立つまで実行
    while (!core.m_Program_End) {
      
        fps.Update();   // FPS 更新
        
        SDL_RenderClear(core.Get_Renderer());   // 画面リセット

        player.Key_Check(core.Get_Event(), core.m_Program_End, map); // キー操作感知
        
        map.Draw(core.Get_Renderer());  //  マップ描画

        // FPS値表示
        fps.Print_Fps(core.Get_Renderer(), 30, 30);

        enemy.Move(player.Get_Position());    // 敵キャラ移動
        enemy.Draw(core.Get_Renderer(), map);   // 敵キャラ描画

        player.Draw(core.Get_Renderer(), map);   // プレイヤ描画
        //player.Print_Position(core.Get_Renderer(), 30, 60);

        // プレイヤの腕の角度表示
        player.Print_Angle(core.Get_Renderer(), 30, 90);

        // 敵の座標表示
        enemy.Print_Position(core.Get_Renderer(), 30, 120);

        SDL_RenderPresent(core.Get_Renderer()); // 画面に表示

        fps.Wait(); // 待機
    }

    return 0;
}

