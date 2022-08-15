/*
 * 	F429_TOKYO2022
 * 	HaoYuLiu
 * 	LowPassFilter.h
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

#ifndef INC_LOWPASSFILTER_H_
#define INC_LOWPASSFILTER_H_

#include <main.hpp>

class LowPassFilter {
public:
	//constructors
	LowPassFilter();
	LowPassFilter(double iCutOffFrequency, double iDeltaTime);
	void init(double iCutOffFrequency, double iDeltaTime);
	//functions
	double update(double input);
	double update(double input, double deltaTime, double cutoffFrequency);
	//get and configure funtions
	double getOutput() const{return output_;}
	void reconfigureFilter(double deltaTime, double cutoffFrequency);

	double output_;
	double ePow_;
};

#endif /* INC_LOWPASSFILTER_H_ */
