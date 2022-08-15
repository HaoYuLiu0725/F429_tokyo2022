/*
 * 	F429_TOKYO2022
 * 	HaoYuLiu
 * 	vnh5019.cpp
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

#include <vnh5019.h>

VNH5019::VNH5019()
{
}
VNH5019::VNH5019(TIM_HandleTypeDef* htim, uint32_t channel, uint32_t resolution, GPIO_TypeDef* port_a,
                 GPIO_TypeDef* port_b, uint16_t pin_a, uint16_t pin_b)
  : inverted_(false)
  , duty_(0.0)
  , htim_(htim)
  , timer_channel_(channel)
  , timer_resolution_(resolution)
  , port{ port_a, port_b }
  , pin{ pin_a, pin_b }
{
}

void VNH5019::init()
{
	__HAL_TIM_SetCompare(htim_, timer_channel_, 0);
	HAL_TIM_PWM_Start(htim_, timer_channel_);
}

void VNH5019::init(TIM_HandleTypeDef* htim, uint32_t channel, uint32_t resolution, GPIO_TypeDef* port_a,
                   GPIO_TypeDef* port_b, uint16_t pin_a, uint16_t pin_b)
{
	inverted_ = false;
	duty_ = 0.0;
	htim_ = htim;
	timer_channel_ = channel;
	timer_resolution_ = resolution;
	port.a_ = port_a;
	port.b_ = port_b;
	pin.a_ = pin_a;
	pin.b_ = pin_b;
	init();
}

void VNH5019::setInverted(bool inverted)
{
	inverted_ = inverted;
}

void VNH5019::writeDuty(double duty)
{
  if (inverted_)
  {
    duty = -duty;
  }
  duty_ = SATURATION(duty, -1, 1);
  int32_t counterPeriod = ABS(duty_ * timer_resolution_);

  if (duty_ > 0)
  {
    HAL_GPIO_WritePin(port.a_, pin.a_, GPIO_PIN_SET);
    HAL_GPIO_WritePin(port.b_, pin.b_, GPIO_PIN_RESET);
  }
  else if (duty_ < 0)
  {
    HAL_GPIO_WritePin(port.a_, pin.a_, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(port.b_, pin.b_, GPIO_PIN_SET);
  }
  else
  {
    HAL_GPIO_WritePin(port.a_, pin.a_, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(port.b_, pin.b_, GPIO_PIN_RESET);
  }
  __HAL_TIM_SetCompare(htim_, timer_channel_, counterPeriod);
}
