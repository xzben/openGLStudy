#pragma once

#include "common.h"
#include <vector>

BEGIN_OGS_NAMESPACE

class Node;

class NodeContainor
{
public:
	NodeContainor();

	void addChild(Node* node);
	void removeChild(Node* node);
	Node* getChildByName(const std::string& name);
	const std::vector<Node*>& getChildrens() { return m_childrens; }
	void foreach(std::function<bool(Node*)> func);
protected:
	std::vector<Node*> m_childrens;
};
END_OGS_NAMESPACE