#include <iostream>
#include "window/Window.h"
#include "AppDeleget.h"
#include "core/base/Ref.h"
#include "core/reflex/ReflexItem.h"


class Test : public OGS::Object
{
public:
	int a;
	std::string b;
};

template<>
void OGS::FieldSerialize<int>::Serialize(OGS::JSON& json, int* field, const std::string& name)
{
	json += "|field:" + name + "|=|" + std::to_string(*field) + "|";
}

template<>
void OGS::FieldSerialize<std::string>::Serialize(OGS::JSON& json, std::string* field, const std::string& name)
{
	json += "|field:" + name + "|=|" +(*field) + "|";
}

template<>
void OGS::FieldSerialize<int>::Deserialize(const OGS::JSON& json, int* field, const std::string& name)
{

}

template<>
void OGS::FieldSerialize<std::string>::Deserialize(const OGS::JSON& json, std::string* field, const std::string& name)
{

}

int main() {

	OGS::ReflexClass<Test> reflex("Test");

	reflex.RegisterMember<int>("a", &Test::a);
	reflex.RegisterMember<std::string>("b", &Test::b);

	Test obj;
	obj.a = 1;
	obj.b = "test string";

	std::string json;
	reflex.Serialize(&obj, json);

	AppDeleget app;
	Window window("OpenGLStudy", 1280, 720);
	app.setGLWin(&window);
	app.run();
	
}