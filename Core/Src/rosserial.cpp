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
#include <rosserial.h>

void vel_callback(const geometry_msgs::Twist &msg)
{
	received_vel.vx = msg.linear.x;
	received_vel.vy = msg.linear.y;
	received_vel.w 	= msg.angular.z;
}

//---------------------------- definition of msg ----------------------------
/* odometry */
//nav_msgs::Odometry odom;
geometry_msgs::Twist base_speed;

//---------------------------- definition of ros ----------------------------
ros::NodeHandle nh;
ros::Subscriber<geometry_msgs::Twist> vel_sub("/cmd_vel", vel_callback);
/* odometry */
//ros::Publisher odom_pub("/base_odom", &odom);
/* base_speed */
ros::Publisher vel_pub("/base_speed", &base_speed);


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
    nh.subscribe(vel_sub);
	/* odometry */
//    nh.advertise(odom_pub);
    /* base_speed */
    nh.advertise(vel_pub);

    HAL_TIM_Base_Start_IT (&htim6);
}

void odom_store(void)
{
	/* odometry */
//	odom.twist.twist.linear.x = odom_vel.vx;
//	odom.twist.twist.linear.y = odom_vel.vy;
//	odom.twist.twist.angular.z = odom_vel.w;
//	odom.pose.pose.position.x = odom_pose.x;
//	odom.pose.pose.position.y = odom_pose.y;
//	odom.pose.pose.orientation = tf::createQuaternionFromYaw(odom_pose.theta);
	/* base_speed */
	base_speed.linear.x = odom_vel.vx;
	base_speed.linear.y = odom_vel.vy;
	base_speed.angular.z = odom_vel.w;
}

void odom_publish(void)
{
	/* odometry */
//	odom_pub.publish(&odom);
	/* base_speed */
	vel_pub.publish(&base_speed);
	nh.spinOnce();
}
