#pragma once

#include "StdAfx.h"
#include "AnimationController.h"
#include "AnimationCallback.h"

extern AnimationController* g_pAnimationController;

AnimationCallback::AnimationCallback(MatrixTransform* mt, int rotHigh, int rotLow, double rotRate, char axis)
{
	m_dRotHigh = rotHigh;
	m_dRotLow = rotLow;
	m_dRotRate = rotRate;
	m_dRotated = 0;
	m_cAxis = axis;
	m_bRotate = false;
	m_bReverse = false;
	m_bAnimating = false;
	m_dAnimationRot = 0;
}

 AnimationCallback::~AnimationCallback(void) {};

 void AnimationCallback::operator()(Node* node, NodeVisitor* nv)
 {
	 if (m_bRotate || m_bAnimating)
	 {
		 if (MatrixTransform *pMT = dynamic_cast<MatrixTransform*>(node))
		 {
			 if (!m_bAnimating)
			 {
				 if (m_dRotated >= m_dRotHigh || m_dRotated <= m_dRotLow)
					 m_bReverse = !m_bReverse;
				 rotate(pMT);
			 } else {
				 if (((m_dAnimationRot > m_dRotated) && !m_bReverse) || ((m_dAnimationRot < m_dRotated) && m_bReverse)) {
					 rotate(pMT);
				 }
				 else {
					 m_bAnimating = false;
					 g_pAnimationController->continueAnimation();
				 }					
			 }
		 }
	 }
	 traverse(node, nv);
 }

 void AnimationCallback::rotate() {
	 m_bRotate = !m_bRotate;
 }
 
 void AnimationCallback::rotate(MatrixTransform *pMT) 
 {
	 Matrix matrix = pMT->getMatrix();
	 Matrix rotMatrix;
	 double rotationRate = m_dRotRate;

	 if (m_bReverse)
		 rotationRate = -rotationRate;

	 switch(m_cAxis)
	 {
	 case 'x':
		 rotMatrix = matrix.rotate(0.1, rotationRate, 0, 0);
		 break;
	 case 'y':
		 rotMatrix = matrix.rotate(0.1, 0, rotationRate, 0);
		 break;
	 case'z':
		 rotMatrix = matrix.rotate(0.1, 0, 0, rotationRate);
		 break;
	 }

	 m_dRotated += rotationRate;
	 pMT->setMatrix(matrix * rotMatrix);
 }

 void AnimationCallback::animate(double rotation)
 {
	m_bAnimating = true;
	m_dAnimationRot = rotation;
	if (m_dAnimationRot > m_dRotated)
		m_bReverse = false;
	else
		m_bReverse = true;
 }

 double AnimationCallback::getRotation()
 {
	 return m_dRotated;
 }