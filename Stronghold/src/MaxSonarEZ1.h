/*
 * MaxSonarEZ1.h
 *
 *  Created on: Feb 11, 2015
 *      Author: nollchr
 */

#ifndef SRC_MAXSONAREZ1_H_
#define SRC_MAXSONAREZ1_H_

#include "WPILib.h"

#define INCHES_PER_VOLT (512.0F / 5.0F)
#define MM_PER_INCH 25.4F

class MaxSonarEZ1 {
private:
	std::shared_ptr<AnalogInput> sensor = nullptr;
public:
	MaxSonarEZ1();
	MaxSonarEZ1(std::shared_ptr<AnalogInput> AI);
	float GetRangeInches();
	float GetRangeMM();
	virtual ~MaxSonarEZ1();
};

#endif /* SRC_MAXSONAREZ1_H_ */
