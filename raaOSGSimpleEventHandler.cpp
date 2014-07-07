#pragma once

#include "stdafx.h"

#include <osg/Group>
#include <osgFX/Scribe>
#include <osgViewer/Viewer>
#include <osgUtil/IntersectionVisitor>
#include <osgUtil/LineSegmentIntersector>

#include "raaOSGSimpleEventHandler.h"
#include "raaOSGPrintVisitor.h"
#include "AnimationController.h"
#include "AnimationCallback.h"
#include "FindVisitor.h"
#include "FindVisitor.cpp"

#include <iostream>

extern std::map <std::string, AnimationCallback*> g_mCallbackMap;
extern AnimationController* g_pAnimationController;

std::string selected = "";

using namespace osg;
using namespace std;

raaOSGSimpleEventHandler::raaOSGSimpleEventHandler()
{
	m_mMode=PolygonMode::FILL;
}

raaOSGSimpleEventHandler::~raaOSGSimpleEventHandler(void)
{
}

bool raaOSGSimpleEventHandler::handle( const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa, osg::Object *, osg::NodeVisitor * )
{
	osgViewer::Viewer *pViewer=dynamic_cast<osgViewer::Viewer*>(aa.asView());
	if(pViewer && ea.getEventType()==osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
	{
		osgUtil::LineSegmentIntersector* picker;
		picker = new osgUtil::LineSegmentIntersector(osgUtil::Intersector::PROJECTION, ea.getXnormalized(), ea.getYnormalized());
		osgUtil::IntersectionVisitor iv(picker);
		pViewer->getCamera()->accept(iv);
		if(picker->containsIntersections())
		{
			selected = "";
			osgUtil::LineSegmentIntersector::Intersection intersection = picker->getFirstIntersection();
			for(NodePath::const_reverse_iterator rit = intersection.nodePath.rbegin(); rit != intersection.nodePath.rend(); rit++)
			{
				if (selected.empty())
				{
					Node *pNode = *rit;
					if (Group *pMt = dynamic_cast<Group*>(pNode))
					{
						cout << "Picked: " << pMt->getName() << endl;		
						string delimiter = "_";
						string name = pMt->getName().substr(0, pMt->getName().find(delimiter));
						if (g_mCallbackMap.find(name) != g_mCallbackMap.end())
						{
							//toggleHighlight(pMt);
							//Commented out as caused issues with speeding up rotation rate when highlighted
							selected = name;	
							break;
						}

					}
				}
			}
		}			
		
	}
	if(pViewer && ea.getEventType()==osgGA::GUIEventAdapter::KEYDOWN)
	{	
		switch(ea.getKey())
		{
			case 'i':
			case 'I':
			{
				raaOSGPrintVisitor printer;

				printer.traverse(*(pViewer->getScene()->getSceneData()));
			}
			return true;
			case 'p':
			case 'P':
				pViewer->getSceneData()->getOrCreateStateSet()->setAttributeAndModes(new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK, progressMode()), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
				return true;
			case 'x':
			case 'X':
				{
					if (!selected.empty())
					{
						g_mCallbackMap[selected]->rotate();
						return true;
					}
				}
			case 'j':
			case 'J':
				{
					g_pAnimationController->reset();
					return true;
				}
			case 'y':
			case 'Y':
				{
					g_pAnimationController->animate();
					return true;
				}
			case 'k':
			case 'K':
				{
					if (!selected.empty())
					{
						if (g_mCallbackMap.find(selected) != g_mCallbackMap.end())
						{
							std::cout << "adding step" << std::endl;
							g_pAnimationController->addStep(selected, g_mCallbackMap[selected]->getRotation());
						}
					}
					return true;
				}
				return true;
		}
	}
	return false;
}

osg::PolygonMode::Mode raaOSGSimpleEventHandler::progressMode()
{
	switch(m_mMode)
	{
		case osg::PolygonMode::POINT:
			return m_mMode=osg::PolygonMode::LINE;
		case osg::PolygonMode::LINE:
			return m_mMode=osg::PolygonMode::FILL;
		default:
			return m_mMode=osg::PolygonMode::POINT;
	}
}

void raaOSGSimpleEventHandler::toggleHighlight(osg::Node* node)
{
	Group* parent = node->getParent(0);
	osgFX::Scribe* parentAsScribe = dynamic_cast<osgFX::Scribe*>(parent);
	if (!parentAsScribe)
	{
		osgFX::Scribe* scribe = new osgFX::Scribe();
		scribe->addChild(node);
		parent->replaceChild(node, scribe);
	}
	else {
		osg::Node::ParentList parentList = parentAsScribe->getParents();
		for (osg::Node::ParentList::iterator itr=parentList.begin();
			itr!=parentList.end();
			++itr ) {
				(*itr)->replaceChild(parentAsScribe, node);
		}
	}
}