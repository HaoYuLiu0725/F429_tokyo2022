/*
 * 	F429_TOKYO2022
 * 	HaoYuLiu
 * 	LowPassFilter.cpp
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
 *	https://github.com/jimmyberg/LowPassFilter
 */

#include <LowPassFilter.h>

LowPassFilter::LowPassFilter():
	output_(0),ePow_(0)
{
}

LowPassFilter::LowPassFilter(double iCutOffFrequency, double iDeltaTime):
	output_(0),
	ePow_(1 - exp(-iDeltaTime * 2 * M_PI * iCutOffFrequency))
{
}

void LowPassFilter::init(double iCutOffFrequency, double iDeltaTime)
{
	output_ = 0;
	ePow_ = 1 - exp(-iDeltaTime * 2 * M_PI * iCutOffFrequency);
}

double LowPassFilter::update(double input)
{
	return output_ += (input - output_) * ePow_;
}

double LowPassFilter::update(double input, double deltaTime, double cutoffFrequency)
{
	reconfigureFilter(deltaTime, cutoffFrequency); //Changes ePow accordingly.
	return output_ += (input - output_) * ePow_;
}

void LowPassFilter::reconfigureFilter(double deltaTime, double cutoffFrequency)
{
	ePow_ = 1 - exp(-deltaTime * 2 * M_PI * cutoffFrequency);
}

