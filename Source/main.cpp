#include "SDL2/SDL.h"
#include "string"

#include "Core.h"
#include "Fps.h"
#include "Map.h"
#include "Player.h"

// ��ʂɕ������o�͂���
void Print_Screen(const std::string& str, TTF_Font* font, const SDL_Color& color, SDL_Renderer* renderer, int y);

int main(int argc, char* argv[]) {

    Core core(1024, 768);   // ��{�I�ȏ��

    Fps fps(60);    // FPS
    SDL_Color Color_Fps = { 0xff, 0xff, 0xff }; // ��

    Map map(core.Get_Renderer(), 128);  // �}�b�v

    Player player(core.Get_Renderer());  // �v���C���[

    // �G���h�t���O�����܂Ŏ��s
    while (!core.m_Program_End) {
      
        fps.Update();   // FPS �X�V
        
        SDL_RenderClear(core.Get_Renderer());   // ��ʃ��Z�b�g

        player.Key_Check(core.Get_Event(), core.m_Program_End, map); // �L�[���슴�m
        
        map.Draw(core.Get_Renderer());  //  �}�b�v�`��

        // FPS�l�\��
        Print_Screen(fps.Get_Fps(), core.Get_Font(), Color_Fps, core.Get_Renderer(), 30);

        player.Draw(core.Get_Renderer(), map);   // �v���C���[�`��

        SDL_RenderPresent(core.Get_Renderer()); // ��ʂɕ\��

        fps.Wait(); // �ҋ@
    }

    return 0;
}


/* (�\�����镶���C�t�H���g�C�F�C�����_��, �\�����邙���W) */
void Print_Screen(const std::string& str, TTF_Font* font, const SDL_Color& color, SDL_Renderer* renderer, int y) {

    SDL_Surface* t_Surface = TTF_RenderUTF8_Blended(font, str.c_str(), color);

    SDL_Rect t_Print_Rect = { 30, y, t_Surface->w, t_Surface->h };

    SDL_Texture* t_Texture = SDL_CreateTextureFromSurface(renderer, t_Surface);

    SDL_RenderCopy(renderer, t_Texture, nullptr, &t_Print_Rect);
}
