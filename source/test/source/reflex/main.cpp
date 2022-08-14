#include "core/base/Ref.h"
#include "json/json.h"
#include "core/reflex/reflex.h"
#include <iostream>
using namespace OGS;

class TempClass : public OGS::Object
{
	DECLARE_CLASS(TempClass);
public:
	int a;
};

class SimpeClass
{
	DECLARE_CLASS_BASE(SimpeClass);
public:
	int a;
	int b;
	int c;
};

class Test : public TempClass
{
	DECLARE_CLASS(Test);
public:
	int a;
	std::string b;
	SimpeClass c;
};

IMPLEMENT_CLASS_BASE(SimpeClass);
IMPLEMENT_CLASS(TempClass);
IMPLEMENT_CLASS(Test);

BEGIN_REFLEX_CLASS_FIELD(SimpeClass)
REFLEX_FIELD(SimpeClass, a)
REFLEX_FIELD(SimpeClass, b)
REFLEX_FIELD(SimpeClass, c)
END_REFLEX_CLASS_FIELD()

BEGIN_REFLEX_CLASS_FIELD(TempClass)
REFLEX_FIELD(TempClass, a)
END_REFLEX_CLASS_FIELD()

BEGIN_REFLEX_CLASS_FIELD(Test)
REFLEX_FIELD(Test, a)
REFLEX_FIELD(Test, b)
REFLEX_FIELD(Test, c)
END_REFLEX_CLASS_FIELD()

int main() {


	Test obj;
	obj.TempClass::a = 2;
	obj.a = 1;
	obj.b = "test string";
	obj.c.a = 11;
	obj.c.b = 22;
	obj.c.c = 33;

	Json::Value root;
	ReflexManager::GetInstance()->Serialize<Test>(&obj, root);

	Json::FastWriter fwriter;
	Json::StyledWriter swriter;
	std::cout << "json origin:" << swriter.write(root).c_str()  << std::endl;

	Test* newobj = ReflexManager::GetInstance()->Deserialize<Test>(root);

	Json::Value newobjJson;
	ReflexManager::GetInstance()->Serialize<Test>(newobj, newobjJson);

	std::cout << "json deserialize obj json:" << swriter.write(newobjJson).c_str() << std::endl;

	return 0;
}