/*
 * 	F429_TOKYO2022
 * 	HaoYuLiu
 * 	kinematic.cpp
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
#include <kinematic.h>

Kinematic::Kinematic()
{
}

void Kinematic::init(double wheel_radius, double l_x, double l_y)
{
	wheel_radius_ = wheel_radius;  //meter
	l_x_ = l_x; //meter
	l_y_ = l_y; //meter
}

void Kinematic::readWheelSpeed(double v1, double v2, double v3, double v4)
{
	wheel_speed_[0] = v1;
	wheel_speed_[1] = v2;
	wheel_speed_[2] = v3;
	wheel_speed_[3] = v4;
}

void Kinematic::readRobotSpeed(double vx, double vy, double w)
{
	robot_speed.vx_ = vx;
	robot_speed.vy_ = vy;
	robot_speed.w_  = w;
}

void Kinematic::forwardKinematic(double v1, double v2, double v3, double v4)
{
	readWheelSpeed(v1, v2, v3, v4);
	robot_speed.vx_ = ( wheel_speed_[0] + wheel_speed_[1] + wheel_speed_[2] + wheel_speed_[3]) * wheel_radius_ / 4;
	robot_speed.vy_ = (-wheel_speed_[0] + wheel_speed_[1] + wheel_speed_[2] - wheel_speed_[3]) * wheel_radius_ / 4;
	robot_speed.w_  = (-wheel_speed_[0] + wheel_speed_[1] - wheel_speed_[2] + wheel_speed_[3]) * wheel_radius_ /(4 *(l_x_ + l_y_));
}

void Kinematic::inverseKinematic(double vx, double vy, double w)
{
	readRobotSpeed(vx, vy, w);
	wheel_speed_[0] = (robot_speed.vx_ - robot_speed.vy_ - (l_x_ + l_y_)*robot_speed.w_) / wheel_radius_;
	wheel_speed_[1] = (robot_speed.vx_ + robot_speed.vy_ + (l_x_ + l_y_)*robot_speed.w_) / wheel_radius_;
	wheel_speed_[2] = (robot_speed.vx_ + robot_speed.vy_ - (l_x_ + l_y_)*robot_speed.w_) / wheel_radius_;
	wheel_speed_[3] = (robot_speed.vx_ - robot_speed.vy_ + (l_x_ + l_y_)*robot_speed.w_) / wheel_radius_;
}
