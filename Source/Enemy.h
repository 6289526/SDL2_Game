#pragma once
#include "Character.h"
#include "Animation.h"

class Enemy :
	public Character
{
public:
	Enemy(SDL_Renderer* renderer, SDL_Rect position);
	void Draw(SDL_Renderer* renderer, Map& map);

private:
	Animation m_Animation_Test;
	void Move();
};

