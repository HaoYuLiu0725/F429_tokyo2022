/*
 * 	F429_TOKYO2022
 * 	HaoYuLiu
 * 	rosserial.cpp
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

#include <main.hpp>
#include <rosserial.h>
#include <Rosserial_STM32_Inc/geometry_msgs/Twist.h>
#include <Rosserial_STM32_Inc/ros.h>

void vel_callback(const geometry_msgs::Twist &msg)
{
	received_vel.vx = msg.linear.x;
	received_vel.vy = msg.linear.y;
	received_vel.w 	= msg.angular.z;
}

//---------------------------- definition of msg ----------------------------
geometry_msgs::Twist real_speed;

//---------------------------- definition of ros ----------------------------
ros::NodeHandle nh;
ros::Publisher pub("base_speed", &real_speed);
ros::Subscriber<geometry_msgs::Twist> vel_sub("/cmd_vel", vel_callback);

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    nh.getHardware()->flush();
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    nh.getHardware()->reset_rbuf();
}

void rosserial_setup(void)
{
    nh.initNode();
    nh.advertise(pub);
    nh.subscribe(vel_sub);
    HAL_TIM_Base_Start_IT (&htim6);
}

void odom_store(void)
{
	real_speed.linear.x  = odom_vel.vx;
	real_speed.linear.y  = odom_vel.vy;
	real_speed.angular.z = odom_vel.w;
}

void odom_pub(void)
{
	pub.publish(&real_speed);
	nh.spinOnce();
}
