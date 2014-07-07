#pragma once
#include <osg/NodeCallback>
#include <osg/MatrixTransform>

using namespace osg;

class AnimationCallback: public NodeCallback
{
	public:
		AnimationCallback(MatrixTransform* mt, int rotHigh, int rotLow, double rotRate, char axis);
		virtual ~AnimationCallback(void);
		virtual void operator()(Node* node, NodeVisitor* nv);
		void rotate();
		void animate(double rotation);		
		double getRotation();
	protected:
		void rotate(MatrixTransform *pMT);
		double m_dRotated;
		double m_dRotHigh;
		double m_dRotLow;
		double m_dRotRate;
		char m_cAxis;
		bool m_bRotate;
		bool m_bReverse;
		bool m_bAnimating;
		double m_dAnimationRot;
};
