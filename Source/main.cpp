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

    // �G�̏����ʒu
    SDL_Rect Enemy1_Position = { 400, 400, 800 * Enemy_Scale * 0.5, 1000 * Enemy_Scale * 0.5 };

    Manage_Enemy enemy; // �G���
    // �K����
    enemy.Create_Enemy(core.Get_Renderer(), Enemy1_Position);
    // �G�̈ړ����x���w��
    enemy.Get_Enemy(0)->Set_Speed(2);

    // �G���h�t���O�����܂Ŏ��s
    while (!core.m_Program_End) {
      
        fps.Update();   // FPS �X�V
        
        SDL_RenderClear(core.Get_Renderer());   // ��ʃ��Z�b�g

        player.Key_Check(core.Get_Event(), core.m_Program_End, map); // �L�[���슴�m
        
        map.Draw(core.Get_Renderer());  //  �}�b�v�`��

        // FPS�l�\��
        fps.Print_Fps(core.Get_Renderer(), 30, 30);

        enemy.Move(player.Get_Position());    // �G�L�����ړ�
        enemy.Draw(core.Get_Renderer(), map);   // �G�L�����`��

        player.Draw(core.Get_Renderer(), map);   // �v���C���`��
        //player.Print_Position(core.Get_Renderer(), 30, 60);

        // �v���C���̘r�̊p�x�\��
        player.Print_Angle(core.Get_Renderer(), 30, 90);

        // �G�̍��W�\��
        enemy.Print_Position(core.Get_Renderer(), 30, 120);

        SDL_RenderPresent(core.Get_Renderer()); // ��ʂɕ\��

        fps.Wait(); // �ҋ@
    }

    return 0;
}

