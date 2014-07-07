#pragma once

#include "AnimationStep.h"
#include <deque>

class AnimationController
{
public:
	AnimationController();
	virtual ~AnimationController(void);

	void animate();
	void continueAnimation();

	void addStep(std::string name, double rotation);
	void reset();

	void loadFile();
	void saveFile();
protected:
	std::deque<AnimationStep> m_AnimationQueue;
	std::deque<AnimationStep>::iterator m_Iterator;
	bool m_bReset;
};