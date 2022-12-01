/*
 * 	F429_TOKYO2022
 * 	HaoYuLiu
 * 	util.h
 *      _____
 *     /  /::\       ___           ___
 *    /  /:/\:\     /  /\         /  /\
 *   /  /:/  \:\   /  /:/        /  /:/
 *  /__/:/ \__\:| /__/::\       /  /:/
 *  \  \:\ /  /:/ \__\/\:\__   /  /::\
 *   \  \:\  /:/     \  \:\/\ /__/:/\:\
 *    \  \:\/:/       \__\::/ \__\/  \:\
 *     \  \::/        /__/:/       \  \:\
 *      \__\/         \__\/         \__\/
 *
 */

#ifndef INC_UTILS_H_
#define INC_UTILS_H_

#include "stm32f4xx_hal.h"
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define ABS(x) ((x) > 0 ? (x) : -(x))
#define SATURATION(amt, low, high) ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))
#define ROUND(x) ((x) >= 0 ? (long)((x) + 0.5) : (long)((x)-0.5))
#define DEG_TO_RAD(deg) ((deg)*_DEG_TO_RAD_COEFF)
#define RAD_TO_DEG(rad) ((rad)*_RAD_TO_DEG_COEFF)

typedef struct
{ /* data */
	double vx;
	double vy;
	double w;
}Speed;

typedef struct
{ /* data */
	double x;
	double y;
	double theta;
}Pose;

#endif /* INC_UTILS_H_ */
