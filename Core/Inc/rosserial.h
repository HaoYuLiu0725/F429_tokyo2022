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

#ifdef __cplusplus
extern "C" {
#endif

extern Speed received_vel;
extern Speed odom_vel;
void rosserial_setup(void);
void odom_pub(void);
void odom_store(void);

#ifdef __cplusplus
}
#endif


#endif /* INC_ROSSERIAL_H_ */
