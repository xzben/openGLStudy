#include "Node.h"
#include "base/Component.h"

BEGIN_NAMESPACE

Node::Node()
	: m_parent(nullptr)
	, m_start(false)
	, m_pause(false)
	, m_dirtyMat(true)
	, m_scale(1, 1, 1)
	, m_pos(0,0, 0)
	, m_rotation(0, 0, 0)
	, m_groupmask((uint)GroupMask::DEFAULT)
{

}

Node::~Node() 
{
	this->doPause();
	this->doStop();
	this->doDestroy();
}

bool Node::updateSelfModelMat()
{
	if (!this->m_dirtyMat) return false;
	this->m_dirtyMat = false;

	this->m_localMat = MathUtil::translate(this->m_pos)*MathUtil::rotation(this->m_rotation) * MathUtil::scale(this->m_scale);
	
	return true;
}

void Node::updateWorlModelMat(const fMat4& parentTrans, bool parentDirty)
{
	if(updateSelfModelMat()){
		this->m_matModel = parentTrans * this->m_localMat;
		parentDirty = true;
	}

	for (auto itor = this->m_childrens.begin(); itor != this->m_childrens.end(); itor++)
	{
		(*itor)->updateWorlModelMat(this->m_matModel, parentDirty);
	}
}

const fMat4& Node::getShaderModel()
{
	return m_matModel;
}

Component* Node::addComponent(Component* com)
{
	this->m_components.push_back(com);
	com->setOwner(this);
	return com;
}

void Node::setParent(Node* node) 
{
	this->m_parent = node;
}

void Node::addChild(Node* node)
{
	node->setParent(this);
	node->addRef();
	this->m_childrens.push_back(node);
	if (this->m_start) {
		node->doStart();
	}
}

void Node::removeChild(Node* node)
{
	if (node->m_parent != this) return;

	for (auto itor = this->m_childrens.begin(); itor != this->m_childrens.end(); itor--)
	{
		if (node == *itor) {
			this->m_childrens.erase(itor);
			node->delRef();
			node->m_parent = nullptr;
			break;
		}
	}
}

void Node::removeFromParent()
{
	if (this->m_parent != nullptr) {
		this->m_parent->removeChild(this);
	}
}

void Node::doLoad()
{
	for (auto itor = this->m_childrens.begin(); itor != this->m_childrens.end(); itor++)
	{
		(*itor)->doLoad();
	}

	for (auto itor = this->m_components.begin(); itor != this->m_components.end(); itor++)
	{
		(*itor)->doLoad();
	}
	this->onLoad();
}

void Node::doStart()
{
	m_start = true;
	for (auto itor = this->m_childrens.begin(); itor != this->m_childrens.end(); itor++)
	{
		(*itor)->doStart();
	}

	for (auto itor = this->m_components.begin(); itor != this->m_components.end(); itor++)
	{
		(*itor)->doStart();
	}

	this->start();
}


void Node::doResume()
{
	m_pause = false;
	for (auto itor = this->m_childrens.begin(); itor != this->m_childrens.end(); itor++)
	{
		(*itor)->doResume();
	}

	for (auto itor = this->m_components.begin(); itor != this->m_components.end(); itor++)
	{
		(*itor)->doResume();
	}

	this->onResume();
}

void Node::doPause()
{
	m_pause = true;
	for (auto itor = this->m_childrens.begin(); itor != this->m_childrens.end(); itor++)
	{
		(*itor)->doPause();
	}

	for (auto itor = this->m_components.begin(); itor != this->m_components.end(); itor++)
	{
		(*itor)->doPause();
	}

	this->onPause();
}

void Node::doStop()
{
	for (auto itor = this->m_childrens.begin(); itor != this->m_childrens.end(); itor++)
	{
		(*itor)->doStop();
	}

	for (auto itor = this->m_components.begin(); itor != this->m_components.end(); itor++)
	{
		(*itor)->doStop();
	}
	this->stop();
	m_start = false;
}

void Node::doDestroy()
{
	for (auto itor = this->m_childrens.begin(); itor != this->m_childrens.end(); itor++)
	{
		(*itor)->doDestroy();
	}

	for (auto itor = this->m_components.begin(); itor != this->m_components.end(); itor++)
	{
		(*itor)->doDestroy();
	}

	this->onDestroy();
}

void Node::doUpdate(float dt)
{
	for (auto itor = this->m_childrens.begin(); itor != this->m_childrens.end(); itor++)
	{
		(*itor)->doUpdate(dt);
	}

	for (auto itor = this->m_components.begin(); itor != this->m_components.end(); itor++)
	{
		(*itor)->doUpdate(dt);
	}

	this->update(dt);
}

void Node::setColor(Color&& color)
{
	m_color = color;
	updateDrawColor(m_parentColor);
}

void Node::setColor(Color& color)
{
	m_color = color;
	updateDrawColor(m_parentColor);
}

void Node::updateDrawColor(const Color& parentColor)
{
	this->m_parentColor = parentColor;
	this->m_drawColor = this->m_parentColor * this->m_color;


	for (auto itor = this->m_childrens.begin(); itor != this->m_childrens.end(); itor++)
	{
		(*itor)->updateDrawColor(this->m_drawColor);
	}
}

void Node::setPosition(const POSITION& pos)
{
	setPosition(pos.x, pos.y, pos.z);
}

void Node::setPosition(float x, float y, float z)
{
	this->m_pos.x = x;
	this->m_pos.y = y;
	this->m_pos.z = z;

	m_dirtyMat = true;
}

void Node::setPositionX(float x)
{
	setPosition(x, this->m_pos.y, this->m_pos.z);
}
void Node::setPositionY(float y)
{
	setPosition(this->m_pos.x, y, this->m_pos.z);
}
void Node::setPositionZ(float z)
{
	setPosition(this->m_pos.x,this->m_pos.y, z);
}

void Node::setRotation(const fVec3& rot)
{
	setRotation(rot.x, rot.y, rot.z);
}

void Node::setRotation(float x, float y, float z)
{
	this->m_rotation.x = x;
	this->m_rotation.y = y;
	this->m_rotation.z = z;

	m_dirtyMat = true;
}

void Node::setRotationX(float x)
{
	setRotation(x, this->m_rotation.y, this->m_rotation.z);
}
void Node::setRotationY(float y)
{
	setRotation(this->m_rotation.x, y, this->m_rotation.z);
}

void Node::setRotationZ(float z)
{
	setRotation(this->m_rotation.x, this->m_rotation.y, z);
}

void Node::setScale(const fVec3& scale)
{
	setScale(scale.x, scale.y, scale.z);
}

void Node::setScale(float x, float y, float z)
{
	this->m_scale.x = x;
	this->m_scale.y = y;
	this->m_scale.z = z;

	m_dirtyMat = true;
}

void Node::setScaleX(float x)
{
	setScale(x, this->m_scale.y, this->m_scale.z);
}
void Node::setScaleY(float y)
{
	setScale(this->m_scale.x, y, this->m_scale.z);
}
void Node::setScaleZ(float z)
{
	setScale(this->m_scale.x, this->m_scale.y, z);
}

void Node::setScale(float scale)
{
	setScale(scale, scale, scale);
}

const POSITION& Node::getPosition()
{
	return m_pos;
}

const fVec3& Node::getRotation()
{
	return m_rotation;
}

const fVec3& Node::getScale()
{
	return m_scale;
}

float Node::getPositionX()
{
	return m_pos.x;
}
float Node::getPositionY()
{
	return m_pos.y;
}
float Node::getPositionZ()
{
	return m_pos.z;
}

float Node::getRotationX()
{
	return m_rotation.x;
}
float Node::getRotationY()
{
	return m_rotation.y;
}
float Node::getRotationZ()
{
	return m_rotation.z;
}

float Node::getScaleX()
{
	return m_scale.x;
}
float Node::getScaleY()
{
	return m_scale.y;
}
float Node::getScaleZ()
{
	return m_scale.z;
}

END_NAMESPACE