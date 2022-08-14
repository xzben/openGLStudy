#include <iostream>
#include "window/Window.h"
#include "AppDeleget.h"
#include "core/base/Ref.h"
#include "core/reflex/ReflexItem.h"
#include "json/json.h"

class Test : public OGS::Object
{
public:
	int a;
	std::string b;
};

int main() {

	OGS::ReflexClass<Test> reflex("Test");

	reflex.RegisterMember<int>("a", &Test::a);
	reflex.RegisterMember<std::string>("b", &Test::b);

	Test obj;
	obj.a = 1;
	obj.b = "test string";

	Json::Value root;

	reflex.Serialize(&obj, root);

	AppDeleget app;
	Window window("OpenGLStudy", 1280, 720);
	app.setGLWin(&window);
	app.run();
	
}