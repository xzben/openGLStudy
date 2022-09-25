#include "core/base/Object.h"
#include "json/json.h"
#include "common.h"
#include "core/base/Notify.h"
#include "core/reflex/serializer/Serializer.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <unordered_map>
using namespace OGS;

enum class TestEnum : int
{
	VALUE1 = -1,
	VALUE2
};

class SimpeClass
{
	DECLARE_CLASS_BASE(SimpeClass);
	DECLARE_REFLEX_CLASS_FIELD(SimpeClass)
public:
	SimpeClass() = default;
	SimpeClass(int a, int b, int c, int* ptra) : inta(a), intb(b), intc(c), ptra(ptra){}

	const std::string& GetVar()const { return funcvar; }
	void SetVar(const std::string& val) { funcvar = val; }

	int inta;
	int intb;
	int intc;
	int* ptra{ nullptr };
	TestEnum enume{ TestEnum::VALUE1 };
private:
	std::string funcvar{"teest"};
};

class TempClass : public OGS::Object
{
	DECLARE_CLASS_BASE(TempClass);
	DECLARE_REFLEX_CLASS_FIELD(TempClass)
public:
	int _inta;
};

class Test : public TempClass
{
	DECLARE_CLASS(Test);
	DECLARE_REFLEX_CLASS_FIELD(Test)
public:
	int _inta;
	std::string _strb;
	SimpeClass simpleC;
	SimpeClass* simpleD{ nullptr };
	std::vector<SimpeClass> _vecSimple;
};

IMPLEMENT_CLASS_BASE(SimpeClass);
IMPLEMENT_CLASS_BASE(TempClass);
IMPLEMENT_CLASS(Test);

BEGIN_REFLEX_CLASS_FIELD(SimpeClass)
REFLEX_FIELD(int, inta)
REFLEX_FIELD(int, intb)
REFLEX_FIELD(int, intc)
REFLEX_FIELD(int*, ptra)
REFLEX_FIELD(int, enume)
REFLEX_FIELD_GETSET(std::string, funcvar, &SimpeClass::GetVar, &SimpeClass::SetVar)
END_REFLEX_CLASS_FIELD()

BEGIN_REFLEX_CLASS_FIELD(TempClass)
REFLEX_FIELD(int, _inta)
END_REFLEX_CLASS_FIELD()

BEGIN_REFLEX_CLASS_FIELD(Test)
REFLEX_FIELD(int, _inta)
REFLEX_FIELD(std::string, _strb)
REFLEX_FIELD(SimpeClass, simpleC)
REFLEX_FIELD(SimpeClass*, simpleD)
REFLEX_FIELD(std::vector<SimpeClass>, _vecSimple)
END_REFLEX_CLASS_FIELD()

int main() 
{
	Test obj;
	int* ptra = new int(222);
	obj.TempClass::_inta = 2;
	obj._inta = 1;
	obj._strb = "test string";
	obj.simpleC.inta = 11;
	obj.simpleC.intb = 22;
	obj.simpleC.intc = 33;
	obj.simpleC.ptra = ptra;
	obj.simpleD = new SimpeClass(10, 20, 30, ptra);
	obj.simpleC.SetVar("funcvalue");
	obj._vecSimple.push_back(SimpeClass(1, 2, 3, ptra));
	obj._vecSimple.push_back(SimpeClass(4, 5, 6, ptra));
	obj._vecSimple.push_back(SimpeClass(7, 8, 9, ptra));

	Json::Value root;
	Serializer::Serialize<Test>(&obj, root);

	Json::FastWriter fwriter;
	Json::StyledWriter swriter;
	std::cout << "json origin:" << swriter.write(root).c_str()  << std::endl;

	Test* newobj = Serializer::Deserialize<Test>(root);

	Json::Value newobjJson;
	Serializer::Serialize<Test>(newobj, newobjJson);

	std::cout << "json deserialize obj json:" << swriter.write(newobjJson).c_str() << std::endl;

	return 0;
}