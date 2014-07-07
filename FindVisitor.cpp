#include "StdAfx.h"
#include <iostream>
#include "FindVisitor.h"

template<typename T>
FindVisitor<T>::FindVisitor(std::string &sName) : NodeVisitor(NodeVisitor::TRAVERSE_ALL_CHILDREN)
{
	m_sName = sName;
	m_pNode = 0;
}

template<typename T>
FindVisitor<T>::~FindVisitor(void)
{
}

template<typename T>
void FindVisitor<T>::apply(Node &node)
{
	if (T *pNode = dynamic_cast<T*>(&node)) {
		if (node.getName() == m_sName) 
		{
			m_pNode = pNode;
		}
	}
	traverse(node);
}

template<typename T>
T* FindVisitor<T>::getNode() 
{
	return m_pNode;
}

template<typename T>
void FindVisitor<T>::setName(std::string name) {
	m_sName = name;
}




