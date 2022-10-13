/*
 * 	F429_TOKYO2022
 * 	HaoYuLiu
 * 	robot.cpp
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

#include <robot.h>

void Robot::init() {
	//Robot hardware parameters
	wheel_radius_ 	= (double)0.075/2;	//meter
	l_x_ 			= (double)0.163/2;	//meter
	l_y_ 			= (double)0.184/2;	//meter
	dt_ = 0.001; //PeriodElapsedCallback rate = 1k Hz (TIM7)
	encoder_resolution_ = 1024;
	reduction_ratio_ = 44; //1:44 reduction_ratio
	one_round_count_ = encoder_resolution_ * reduction_ratio_ * 4; //encoder's count for one round

	motor_[0].init(&htim12, TIM_CHANNEL_2, 4499, GPIOD, GPIOD, GPIO_PIN_8, GPIO_PIN_14); //(*htim, channel, resolution, port_a, port_b, pin_a, pin_b)
	motor_[1].init(&htim12, TIM_CHANNEL_1, 4499, GPIOB, GPIOB, GPIO_PIN_12, GPIO_PIN_13);
	motor_[2].init(&htim9, TIM_CHANNEL_1, 4499, GPIOE, GPIOE, GPIO_PIN_2, GPIO_PIN_3);
	motor_[3].init(&htim9, TIM_CHANNEL_2, 4499, GPIOE, GPIOC, GPIO_PIN_4, GPIO_PIN_13);
	motor_[1].setInverted(true);
	motor_[3].setInverted(true);

	encoder_[0].init(&htim2, 32, TIM_CHANNEL_1, TIM_CHANNEL_2); //(*htim, timer_bits, channel_1, channel_2)
	encoder_[1].init(&htim5, 32, TIM_CHANNEL_1, TIM_CHANNEL_2);
	encoder_[2].init(&htim3, 16, TIM_CHANNEL_1, TIM_CHANNEL_2);
	encoder_[3].init(&htim4, 16, TIM_CHANNEL_1, TIM_CHANNEL_2);

	pid[0].init(dt_, 0.132, 15.47, 0.0, 0); //(dt, kp, ki, kd, kb)
	pid[1].init(dt_, 0.132, 15.47, 0.0, 0);
	pid[2].init(dt_, 0.132, 15.47, 0.0, 0);
	pid[3].init(dt_, 0.132, 15.47, 0.0, 0);

	kn_.init(wheel_radius_, l_x_, l_y_); //(wheel_radius, l_x, l_y)

	LPF_.init(1000, dt_); //(iCutOffFrequency, iDeltaTime)

	HAL_TIM_Base_Start_IT (&htim7);
}

double Robot::diff_to_omega(int32_t diff){
	omega_ = 2 * M_PI * diff / one_round_count_ /dt_;
	return omega_;
}
