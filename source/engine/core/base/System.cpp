#include "System.h"

BEGIN_OGS_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(System)

System::System(std::string& name)
	: m_name(name)
{
}


END_OGS_NAMESPACE