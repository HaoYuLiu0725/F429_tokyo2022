/*
 * 	F429_TOKYO2022
 * 	HaoYuLiu
 * 	robot.h
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

#ifndef ROBOT_H_
#define ROBOT_H_

#include <main.hpp>
#include <kinematic.h>
#include <pid.h>
#include <vnh5019.h>
#include <encoder.h>
#include <LowPassFilter.h>

class Robot
{
public:
  void init();
  double diff_to_omega(int32_t diff);
  VNH5019 motor_[4];
  Encoder encoder_[4];
  PID pid[4];
  Kinematic kn_;
  LowPassFilter LPF_;

  //Robot hardware parameters
  double wheel_radius_, l_x_, l_y_;
  double dt_;
  int32_t encoder_resolution_;
  int32_t reduction_ratio_;
  int32_t one_round_count_;
  double omega_;
};

#endif /* ROBOT_H_ */
