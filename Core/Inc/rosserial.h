/*
 * 	F429_TOKYO2022
 * 	HaoYuLiu
 * 	rosserial.h
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
#ifndef INC_ROSSERIAL_H_
#define INC_ROSSERIAL_H_

#include <utils.h>
#include <main.hpp>
#include <Rosserial_STM32_Inc/ros.h>
#include <Rosserial_STM32_Inc/geometry_msgs/Twist.h>
#include <Rosserial_STM32_Inc/nav_msgs/Odometry.h>
#include <Rosserial_STM32_Inc/tf/tf.h>

#ifdef __cplusplus
extern "C" {
#endif

extern Speed received_vel;
extern Speed odom_vel;
extern Pose odom_pose;
void rosserial_setup(void);
void odom_publish(void);
void odom_store(void);

#ifdef __cplusplus
}
#endif


#endif /* INC_ROSSERIAL_H_ */
