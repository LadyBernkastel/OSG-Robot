#pragma once

#include "StdAfx.h"
#include "AnimationStep.h"

AnimationStep::AnimationStep(std::string name, double rotated)
{
	m_dRotated = rotated;
	m_sName = name;
}

AnimationStep::AnimationStep() {
	m_dRotated = 0;
}

AnimationStep::~AnimationStep(void) {};