/*
 * 	F429_TOKYO2022
 * 	HaoYuLiu
 * 	encoder.cpp
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

#include <encoder.h>

Encoder::Encoder() {
}
Encoder::Encoder(TIM_HandleTypeDef *htim, uint8_t timer_bits,
		uint32_t channel_1, uint32_t channel_2) :
		inverted_(false), last_(0), current_(0), diff_(0), htim_(htim), timer_bits_(
				timer_bits), timer_channel_ { channel_1, channel_2 } {
}

void Encoder::init() {
	HAL_TIM_Encoder_Start(htim_, timer_channel_[0]);
	HAL_TIM_Encoder_Start(htim_, timer_channel_[1]);
	__HAL_TIM_SET_COUNTER(htim_, 0);
}

void Encoder::init(TIM_HandleTypeDef *htim, uint8_t timer_bits,
		uint32_t channel_1, uint32_t channel_2) {
	inverted_ = false;
	last_ = 0;
	current_ = 0;
	diff_ = 0;
	htim_ = htim;
	timer_bits_ = timer_bits;
	timer_channel_[0] = channel_1;
	timer_channel_[1] = channel_2;
	init();
}

void Encoder::setInverted(bool inverted) {
	inverted_ = inverted;
}

int32_t Encoder::readDelta() {
	/* update encoder data */
	last_ = current_;
	current_ = __HAL_TIM_GET_COUNTER(htim_);

	/* check if inverted */
	if (!inverted_) {
		diff_ = current_ - last_;
	} else {
		diff_ = last_ - current_;
	}

	/* deal with counter overflow */
	/* 16-bit Timer */
	if (timer_bits_ == 16) {
		if (diff_ > UINT16_MAX / 2)
			diff_ -= UINT16_MAX + 1;
		else if (diff_ < -UINT16_MAX / 2)
			diff_ += UINT16_MAX + 1;
	}
	/* 32-bit Timer */
	else if (timer_bits_ == 32) {
		if (diff_ > UINT32_MAX / 2)
			diff_ -= UINT32_MAX + 1;
		else if (diff_ < -UINT32_MAX / 2)
			diff_ += UINT32_MAX + 1;
	}
	else {
		diff_ = -1;
	}
	return diff_;
}
