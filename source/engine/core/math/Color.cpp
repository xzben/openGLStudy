#include "Color.h"

BEGIN_OGS_NAMESPACE
IMPLEMENT_CLASS_BASE(Color)

BEGIN_REFLEX_CLASS_FIELD(Color)
REFLEX_FIELD(float, r)
REFLEX_FIELD(float, g)
REFLEX_FIELD(float, b)
REFLEX_FIELD(float, a)
END_REFLEX_CLASS_FIELD()


const Color Color::WHITE(1.0, 1.f, 1.f, 1.f);
const Color Color::BLACK(0.0f,0.f,0.0f,1.0f);
const Color Color::RED(1.0f, 0.f, 0.f, 1.f);
const Color Color::GREEN(0.f, 1.f, 0.f, 1.f);
const Color Color::BLUE(0.f, 0.f, 1.f, 1.f);
const Color Color::GRAY(0.7f, 0.7f, 0.7f, 1.0f);

END_OGS_NAMESPACE