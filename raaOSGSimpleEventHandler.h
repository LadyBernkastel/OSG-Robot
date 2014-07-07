#pragma once

#include <osg/PolygonMode>
#include <osgGA/GUIEventHandler>

class raaOSGSimpleEventHandler: public osgGA::GUIEventHandler
{
public:
	raaOSGSimpleEventHandler();
	virtual ~raaOSGSimpleEventHandler(void);
	virtual bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa, osg::Object *, osg::NodeVisitor *);

protected:
	osg::PolygonMode::Mode m_mMode;
	void toggleHighlight(osg::Node* node);
	osg::PolygonMode::Mode progressMode();

};

