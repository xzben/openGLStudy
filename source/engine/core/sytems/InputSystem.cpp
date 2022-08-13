#include "InputSystem.h"

BEGIN_OGS_NAMESPACE

InputSystem::InputSystem()
	:System(std::string("InputSystem"))
{

}


bool InputSystem::init()
{
	return true;
}

void InputSystem::update(float dt)
{
	
}

void InputSystem::destroy()
{

}

void InputSystem::processMouseEvent(const InputState& state, const float& x, const float& y)
{
	m_touchNotify.emit(state, x, y);
}

void InputSystem::processKeyboardEvent(const InputState& state, const int& keycode)
{
	m_keyboardNotify.emit(state, keycode);
}

END_OGS_NAMESPACE