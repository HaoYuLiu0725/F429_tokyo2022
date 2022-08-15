/*
 * 	F429_TOKYO2022
 * 	HaoYuLiu
 * 	pid.h
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

#ifndef INC_PID_H_
#define INC_PID_H_

#include <main.hpp>

#define FILTER_COEFF (100)
class PID
{
public:
  PID();
  PID(double dt, double kp, double ki, double kd, double kb);
  void init();
  void init(double dt, double kp, double ki, double kd, double kb);
  void setSetpoint(double setpoint);
  void setFeedback(double feedback);
  double clacOutput();

  double dt_;
  double kp_;
  double ki_;
  double kd_;
  double kb_; //Back Calculation

  double setpoint_;
  double feedback_;
  double error_;
  double error_int_;
  double error_diff_;
  double error_hist_[FILTER_COEFF];
  double back_cal_;

  double output_;
  double output_SAT_;
};

#endif /* INC_PID_H_ */
