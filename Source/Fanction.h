#pragma once

#include "SDL2/SDL.h"
#include <string>
#include <cmath>

// �p�x�v�Z(�x��)
template <typename T, typename U>
/* (���W�P�C���W�Q) */
double Angle_Degrees(const T& point_1, const U& point_2)
{
	double angle = Angle_Radians(point_1, point_2);

	return angle * 180 / M_PI;
}
// �p�x�v�Z(���W�A��)
template <typename T, typename U>
/* (���W�P�C���W�Q) */
double Angle_Radians(const T& point_1, const U& point_2)
{
	double t_Difference_x = static_cast<double>(point_2.x) - static_cast<double>(point_1.x);
	double t_Difference_y = static_cast<double>(point_2.y) - static_cast<double>(point_1.y);

	return atan2(t_Difference_y, t_Difference_x);
}

/* (�p�x�C�p�x�ŏ��l�C�p�x�ő�l) */
double Angle_Limit(double angle, double min, double max);

/* (�\�����镶���C�����_��, �\�����邘���W�C�\�����邙���W) */
void Print_Screen(const std::string& str, SDL_Renderer* renderer, int x, int y);

/* (�����ɕϊ����鐔�l) */
std::string To_String(double num);
std::string To_String(int num);
std::string To_String(float num);
