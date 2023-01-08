#include "utils/Utils.h"
#include "gfx/base/Attribute.h"

BEGIN_OGS_NAMESPACE
namespace Utils
{
	void compute_hash(HASH_CODE& seed, const Gfx::Attribute& ab)
	{
		hash_combine(seed, ab.name, ab.format, ab.isNormalized, ab.stream, ab.isInstanced, ab.location);
	}
}


END_OGS_NAMESPACE