#include "Component.h"
#include "base/Node.h"
#include "base/Application.h"

Component::Component() 
	:m_node(nullptr)
{
}

Component::~Component()
{

}

void Component::setStatusBit(bool enable, Status status) 
{
	if (enable) {
		this->m_status |= 1 << status;
	}
	else {
		this->m_status &= ~(1 << status);
	}
}

bool Component::getStatusBit(Status status)
{
	return (this->m_status & (1 << status));
}

void Component::setEnable(bool enable) {
	this->setStatusBit(enable, Status::ENABLE);
}

float Component::getLastDt()
{
	return Application::getInstance()->getLastDt();
}

float Component::getLastTime() 
{
	return Application::getInstance()->getLastTime();
}

bool Component::isEnable() {
	return this->getStatusBit(Status::ENABLE);
}

void Component::setOwner(Node* node)
{
	this->m_node = node;
}

void Component::doLoad()
{
	this->onLoad();
}

void Component::doStart()
{
	this->start();
}

void Component::doPause()
{
	this->onPause();
}
void Component::doResume()
{
	this->onResume();
}

void Component::doStop()
{
	this->stop();
}

void Component::doDestroy()
{
	this->onDestroy();
}

void Component::doUpdate(float dt)
{
	this->update(dt);
}