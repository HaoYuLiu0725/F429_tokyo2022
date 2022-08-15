/*
 * 	F429_TOKYO2022
 * 	HaoYuLiu
 * 	kinematic.h
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

#ifndef INC_KINEMATIC_H_
#define INC_KINEMATIC_H_

#include <main.hpp>

class Kinematic
{
public:
  Kinematic();

  void init(double wheel_radius, double l_x, double l_y);
  void readWheelSpeed(double v1, double v2, double v3, double v4);
  void readRobotSpeed(double vx, double vy, double w);
  void forwardKinematic(double v1, double v2, double v3, double v4);
  void inverseKinematic(double vx, double vy, double w);

  struct kinematic
  {
    /* data */
    double vx_;
    double vy_;
    double w_;
  } robot_speed;

  double wheel_speed_[4];

  double wheel_radius_, l_x_, l_y_;
};

#endif /* INC_KINEMATIC_H_ */
