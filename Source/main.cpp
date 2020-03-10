#include "SDL2/SDL.h"
#include "string"

#include "Core.h"
#include "Fps.h"
#include "Map.h"
#include "Player.h"
#include "Manage_Enemy.h"

int main(int argc, char* argv[]) {

    Core core(1024, 768);   // ��{�I�ȏ��

    Fps fps(60);    // FPS

    Map map(core.Get_Renderer(), 128);  // �}�b�v

    Player player(core.Get_Renderer());  // �v���C���[

    SDL_Rect Enemy1_Position = { 400, 400, 800 * Enemy_Scale, 1000 * Enemy_Scale };

    Manage_Enemy enemy; // �G���
    enemy.Create_Enemy(core.Get_Renderer(), Enemy1_Position);

    // �G���h�t���O�����܂Ŏ��s
    while (!core.m_Program_End) {
      
        fps.Update();   // FPS �X�V
        
        SDL_RenderClear(core.Get_Renderer());   // ��ʃ��Z�b�g

        player.Key_Check(core.Get_Event(), core.m_Program_End, map); // �L�[���슴�m
        
        map.Draw(core.Get_Renderer());  //  �}�b�v�`��

        // FPS�l�\��
        fps.Print_Fps(core.Get_Renderer(), 30, 30);

        player.Draw(core.Get_Renderer(), map);   // �v���C���[�`��

        enemy.Draw(core.Get_Renderer(), map);

        // �v���C���̘r�̊p�x�\��
        player.Print_Angle(core.Get_Renderer(), 30, 60);

        SDL_RenderPresent(core.Get_Renderer()); // ��ʂɕ\��

        fps.Wait(); // �ҋ@
    }

    return 0;
}

