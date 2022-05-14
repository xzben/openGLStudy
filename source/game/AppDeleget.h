#ifndef __2021_12_29_APPDELEGATE_H__
#define __2021_12_29_APPDELEGATE_H__

#include "base/Application.h"

USING_NAMESPACE;

class AppDeleget : public Application
{
public:
	virtual void onAppLauchFinish()override;
	virtual void onAppPause()override;
	virtual void onAppResume()override;
	virtual void onAppExit() override;
};


#endif // !__2021_12_29_APPDELEGATE_H__

