#include "Screen.h"

BEGIN_OGS_NAMESPACE
Rect Screen::m_viewport{0.f,0.f,0.f,0.f};

const Rect& Screen::getViewport() 
{ 
	return m_viewport; 
}

void Screen::setViewport(const Rect& viewport) 
{ 
	m_viewport = viewport;
}

Size Screen::getSize()
{
	return Size(m_viewport.width, m_viewport.height);
}

END_OGS_NAMESPACE