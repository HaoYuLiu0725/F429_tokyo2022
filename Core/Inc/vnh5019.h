/*
 * 	F429_TOKYO2022
 * 	HaoYuLiu
 * 	vnh5019.h
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

#ifndef INC_VNH5019_H_
#define INC_VNH5019_H_

#include <main.hpp>

class VNH5019
{
public:
  VNH5019();
  VNH5019(TIM_HandleTypeDef* htim, uint32_t channel, uint32_t resolution, GPIO_TypeDef* port_a, GPIO_TypeDef* port_b,
          uint16_t pin_a, uint16_t pin_b);

  void init();
  void init(TIM_HandleTypeDef* htim, uint32_t channel, uint32_t resolution, GPIO_TypeDef* port_a, GPIO_TypeDef* port_b,
            uint16_t pin_a, uint16_t pin_b);
  void setInverted(bool inverted);
  void writeDuty(double duty);

  bool inverted_;

  double duty_;

  TIM_HandleTypeDef* htim_;
  uint8_t timer_channel_;
  uint32_t timer_resolution_;

  struct
  {
    /* data */
    GPIO_TypeDef* a_;
    GPIO_TypeDef* b_;
  } port;
  struct
  {
    /* data */
    uint16_t a_;
    uint16_t b_;
  } pin;
};

#endif /* INC_VNH5019_H_ */
