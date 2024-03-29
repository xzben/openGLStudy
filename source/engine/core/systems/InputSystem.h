#pragma once

#include "common.h"
#include "core/base/System.h"
#include "core/tool/Singleton.h"
#include "core/base/Notify.h"
#include <functional>

BEGIN_OGS_NAMESPACE

enum class InputType
{
	TOUCH,
	KEYBOARD,


	COUNT, // must been end
};

enum class InputState
{
	BEGIN,
	CHANGE,
	ENDLE,
	CANCEL,
};

enum KEYVALUE
{

};

class InputSystem : public System, public Singleton<InputSystem>
{
	DECLARE_RUNTIME_CLASS(InputSystem)
protected:
	friend class Singleton<InputSystem>;
	InputSystem();
	virtual ~InputSystem();
public:
	typedef Notify<InputState, float, float> NotifyTouch;
	typedef Notify<InputState, int> NotifyKeyboard;


	virtual bool init();

	virtual void update(float dt) override;
	virtual void destroy()override;
	
	NotifyKeyboard& getKeyboardNotify() { return m_keyboardNotify; }
	NotifyTouch& getTouchNotify() { return m_touchNotify; }
private:
	void processMouseEvent(const InputState& state, const float& x, const float& y);
	void processKeyboardEvent(const InputState& state, const int& keycode);
private:
	NotifyTouch m_touchNotify;
	NotifyKeyboard m_keyboardNotify;
};

END_OGS_NAMESPACE