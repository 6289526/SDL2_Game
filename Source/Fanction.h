#pragma once

#include "SDL2/SDL.h"
#include <string>
#include <cmath>

// 角度計算(度数)
template <typename T, typename U>
/* (座標１，座標２) */
double Angle_Degrees(const T& point_1, const U& point_2)
{
	double angle = Angle_Radians(point_1, point_2);

	return angle * 180 / M_PI;
}
// 角度計算(ラジアン)
template <typename T, typename U>
/* (座標１，座標２) */
double Angle_Radians(const T& point_1, const U& point_2)
{
	double t_Difference_x = static_cast<double>(point_2.x) - static_cast<double>(point_1.x);
	double t_Difference_y = static_cast<double>(point_2.y) - static_cast<double>(point_1.y);

	return atan2(t_Difference_y, t_Difference_x);
}

/* (角度，角度最小値，角度最大値) */
double Angle_Limit(double angle, double min, double max);

/* (表示する文字，レンダラ, 表示するｘ座標，表示するｙ座標) */
void Print_Screen(const std::string& str, SDL_Renderer* renderer, int x, int y);

/* (文字に変換する数値) */
std::string To_String(double num);
std::string To_String(int num);
std::string To_String(float num);
