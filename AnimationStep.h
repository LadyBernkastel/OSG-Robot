#pragma once

#include <iostream>

class AnimationStep
{
public:
	AnimationStep(std::string name, double rotated);
	AnimationStep();
	virtual ~AnimationStep(void);
	double m_dRotated;
	std::string m_sName;
	double m_dOriginalRot;
protected:
};
