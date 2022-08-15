/*
 * 	F429_TOKYO2022
 * 	HaoYuLiu
 * 	encoder.h
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

#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_

#include <main.hpp>

class Encoder
{
public:
  Encoder();
  Encoder(TIM_HandleTypeDef* htim, uint8_t timer_bits, uint32_t channel_1, uint32_t channel_2);
  void init();
  void init(TIM_HandleTypeDef* htim, uint8_t timer_bits, uint32_t channel_1, uint32_t channel_2);
  void setInverted(bool inverted);
  int32_t readDelta();

  bool inverted_;

  uint32_t last_;
  uint32_t current_;
  int32_t diff_;

  TIM_HandleTypeDef* htim_;
  uint8_t timer_bits_;
  uint32_t timer_channel_[2];
};

#endif /* INC_ENCODER_H_ */
