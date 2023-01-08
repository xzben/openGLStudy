#ifndef __COMMON_2021_09_06_H__
#define __COMMON_2021_09_06_H__
#include <string>
#include <vector>
#include <type_traits>
#include "define.h"
#include "core/ptr/WeakRef.h"
#include "core/ptr/AutoRef.h"
#include "core/reflex/reflex.h"
#include "core/assets/asset_types.h"
#include "core/base/macro.h"
#include "innerJson.h"
#include "glad/glad.h"

#define CCLOG( format, ...) fprintf(stdout, format, ##__VA_ARGS__ )
#define CCLOG_INFO(format, ...) fprintf(stdout, format, ##__VA_ARGS__ )
#define CCLOG_DEBUG(format, ...) fprintf(stdout, format, ##__VA_ARGS__ )
#define CCLOG_WARN(format, ...) fprintf(stderr, format, ##__VA_ARGS__ )
#define CCLOG_ERROR( format, ...) fprintf(stderr, format, ##__VA_ARGS__ )

#endif//__COMMON_2021_09_06_H__