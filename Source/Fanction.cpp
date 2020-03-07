#include "Fanction.h"

#include "cmath"
#include "string"
#include "Core.h"

#include <string>
#include <sstream>

// Šp“x‚É”ÍˆÍ‚ð‚Â‚¯‚é
double Angle_Limit(double angle, double min, double max)
{
	if (angle < min) {
		angle = min;
	}
	else if (max < angle) {
		angle = max;
	}

	return angle;
}

// ‰æ–Ê‚É•¶Žš‚ðo—Í‚·‚é
void Print_Screen(const std::string& str, SDL_Renderer* renderer, int x, int y) {

	TTF_Font* t_Font = TTF_OpenFont("Font/MyricaM/MyricaM.TTC", 24);
	SDL_Color t_Color = { 0xff, 0xff, 0xff }; // ”’

	SDL_Surface* t_Surface = TTF_RenderUTF8_Blended(t_Font, str.c_str(), t_Color);

	SDL_Rect t_Print_Rect = { x, y, t_Surface->w, t_Surface->h };

	SDL_Texture* t_Texture = SDL_CreateTextureFromSurface(renderer, t_Surface);

	SDL_RenderCopy(renderer, t_Texture, nullptr, &t_Print_Rect);
}

std::string To_String(double num)
{
	std::string t_Str;

	std::ostringstream t_ss;
	t_ss << num;
	t_Str += t_ss.str();

	return t_Str;
}

std::string To_String(int num)
{
	std::string t_Str;

	std::ostringstream t_ss;
	t_ss << num;
	t_Str += t_ss.str();

	return t_Str;
}

std::string To_String(float num)
{
	std::string t_Str;

	std::ostringstream t_ss;
	t_ss << num;
	t_Str += t_ss.str();

	return t_Str;
}

