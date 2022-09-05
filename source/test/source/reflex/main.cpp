#include "core/base/Object.h"
#include "json/json.h"
#include "common.h"
#include "core/base/Notify.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <unordered_map>
using namespace OGS;

class SimpeClass
{
	DECLARE_CLASS_BASE(SimpeClass);
public:
	SimpeClass() = default;
	SimpeClass(int a, int b, int c) : inta(a), intb(b), intc(c) {}
	int inta;
	int intb;
	int intc;
};

class TempClass : public OGS::Object
{
	DECLARE_CLASS_BASE(TempClass);
public:
	int _inta;
};

class Test : public TempClass
{
	DECLARE_CLASS(Test);
public:
	int _inta;
	std::string _strb;
	SimpeClass simpleC;
	std::vector<SimpeClass> _vecSimple;
};

IMPLEMENT_CLASS_BASE(SimpeClass);
IMPLEMENT_CLASS_BASE(TempClass);
IMPLEMENT_CLASS(Test);

BEGIN_REFLEX_CLASS_FIELD(SimpeClass)
REFLEX_FIELD(int, inta)
REFLEX_FIELD(int, intb)
REFLEX_FIELD(int, intc)
END_REFLEX_CLASS_FIELD()

BEGIN_REFLEX_CLASS_FIELD(TempClass)
REFLEX_FIELD(int, _inta)
END_REFLEX_CLASS_FIELD()

BEGIN_REFLEX_CLASS_FIELD(Test)
REFLEX_FIELD(int, _inta)
REFLEX_FIELD(std::string, _strb)
REFLEX_FIELD(SimpeClass, simpleC)
REFLEX_FIELD(std::vector<SimpeClass>, _vecSimple)
END_REFLEX_CLASS_FIELD()

int main() 
{
	Test obj;
	obj.TempClass::_inta = 2;
	obj._inta = 1;
	obj._strb = "test string";
	obj.simpleC.inta = 11;
	obj.simpleC.intb = 22;
	obj.simpleC.intc = 33;
	obj._vecSimple.push_back(SimpeClass(1, 2, 3));
	obj._vecSimple.push_back(SimpeClass(4, 5, 6));
	obj._vecSimple.push_back(SimpeClass(7, 8, 9));

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