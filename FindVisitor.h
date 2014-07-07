#pragma once

#include <osg/NodeVisitor>
#include <osg/MatrixTransform>

using namespace osg;

template<typename T>
class FindVisitor: public NodeVisitor
{
public:
	FindVisitor(std::string &sName);
	virtual ~FindVisitor(void);
	virtual void apply(Node &node);
	T* getNode();
	void setName(std::string name);
protected:
	std::string m_sName;
	T *m_pNode;
};

