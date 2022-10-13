/*
 * 	F429_TOKYO2022
 * 	HaoYuLiu
 * 	pid.cpp
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

#include <pid.h>

PID::PID()
{
}

PID::PID(double dt, double kp, double ki, double kd, double kb)
  : dt_(dt), kp_(kp), ki_(ki), kd_(kd), kb_(kb),setpoint_(0.0), feedback_(0.0), error_(0.0), error_int_(0.0), error_diff_(0.0),	back_cal_(0.0)
{
}

void PID::init()
{
}

void PID::init(double dt, double kp, double ki, double kd, double kb)
{
	dt_ = dt;
	kp_ = kp;
	ki_ = ki;
	kd_ = kd;
	kb_ = kb;

	setpoint_ = 0.0;
	feedback_ = 0.0;
	error_ = 0.0;
	error_int_ = 0.0;
	error_diff_ = 0.0;
	back_cal_ = 0.0;

	init();
}
void PID::setSetpoint(double setpoint)
{
	setpoint_ = setpoint;
}
void PID::setFeedback(double feedback)
{
	feedback_ = feedback;
}
double PID::clacOutput()
{
	error_ = setpoint_ - feedback_;
	for (int i = FILTER_COEFF - 1; i; --i)
	{
		error_hist_[i] = error_hist_[i - 1];
	}
	error_hist_[0] = error_;
	error_int_ += back_cal_; //Back Calculation
	error_int_ += error_ * dt_;
	error_diff_ = error_hist_[0] - error_hist_[1];

	double p = kp_ * error_;
	double i = ki_ * error_int_;
	double d = kd_ * error_diff_;

	i = SATURATION(i, -0.3, 0.3);
	output_ = p + i + d;
	output_SAT_ = SATURATION(output_, -1, 1);
	if(output_ != output_SAT_){
		back_cal_ = (output_SAT_ - output_) * kb_;
	}
	return output_SAT_;
}
