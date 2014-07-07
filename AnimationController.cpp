#pragma once

#include "StdAfx.h"
#include "AnimationCallback.h"
#include "AnimationController.h"

#include <map>
#include <iosfwd>
#include <iostream>
#include <ostream>

extern std::map <std::string, AnimationCallback*> g_mCallbackMap;

AnimationController::AnimationController(){
	m_Iterator = m_AnimationQueue.begin();
}

AnimationController::~AnimationController(void) {};

// Animates a single step in the animation process
void AnimationController::animate()
{
	if (!m_AnimationQueue.empty()) {
		m_bReset = false;
		if (m_Iterator != m_AnimationQueue.end())
		{
			if (g_mCallbackMap.find(m_Iterator->m_sName) != g_mCallbackMap.end())
			{
				AnimationCallback *callback = g_mCallbackMap[m_Iterator->m_sName];
				m_Iterator->m_dOriginalRot = callback->getRotation();
				callback->animate(m_Iterator->m_dRotated);
			}
		}
	}
}

// Called by an AnimationCallback when it is done animating
void AnimationController::continueAnimation()
{
	if (!m_bReset)
	{
		m_Iterator++;
		animate();
	}
}

// Only to be called outside of an animation process
void AnimationController::addStep(std::string name, double rotation)
{
	AnimationStep step(name, rotation);
	m_AnimationQueue.push_back(step);

	// Resets the iterator if it is not already placed at the beginning	
	m_Iterator = m_AnimationQueue.begin();
}

void AnimationController::reset()
{
	m_bReset = true;
	for(std::deque<AnimationStep>::iterator it = m_AnimationQueue.begin();
		it != m_AnimationQueue.end();
		it++)
	{
		if (g_mCallbackMap.find(it->m_sName) != g_mCallbackMap.end())
		{
			g_mCallbackMap[it->m_sName]->animate(it->m_dOriginalRot);
		}
	}
	m_AnimationQueue.clear();
}

//void AnimationController::loadFile()
//{
//	std::ifstream in;
//	file.open("savedAnimation.sav");
//	std::string name;
//	string target;
//
//
//	while (!in.eof())
//	{
//		AnimationStep step;
//		if (!i)
//		for (int i = 0; i < 6; i++)
//		{
//			if (!std::getline(file, name) || !getline(file, target))
//			{
//				return;
//			}
//			step->m_mAnimationTargets[name] = stof(target);
//		}
//		addStep(step);
//	}
//	in.close();
//}
//
//void AnimationController::saveFile()
//{
//	if (!m_AnimationQueue.empty())
//	{
//		std::ofstream out;
//		out.open("savedAnimation.sav");
//		out.clear();
//		for (std::deque<AnimationStep>::iterator it = m_AnimationQueue.begin(); it != m_AnimationQueue.end(); ++it)
//		{
//			out << it->m_sName << "_" << it->m_dRotated << std::endl;
//		}
//		out.close();
//	}
//}
//
//void AnimationController::done(string sName)
//{
//	m_mCurrentDone[sName] = true;
//	for (map<string, bool>::iterator it = m_mCurrentDone.begin(); it != m_mCurrentDone.end(); ++it)
//	{
//		if (it->second == false)
//		{
//			return;
//		}
//	}
//
//	animate(false);
//}




