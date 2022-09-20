#ifndef __COMMON_2021_09_06_H__
#define __COMMON_2021_09_06_H__
#include <string>
#include <vector>
#include <type_traits>
#include "define.h"
#include "define/shader_define.h"
#include "define/event_define.h"
#include "define/math_define.h"
#include "define/glenum_define.h"
#include "core/ptr/WeakPtr.h"
#include "core/ptr/SharePtr.h"
#include "core/reflex/reflex.h"
#include "core/assets/asset_types.h"
#include "innerJson.h"

#define CCLOG( format, ...) fprintf(stdout, format, ##__VA_ARGS__ )
#define CCLOG_INFO(format, ...) fprintf(stdout, format, ##__VA_ARGS__ )
#define CCLOG_DEBUG(format, ...) fprintf(stdout, format, ##__VA_ARGS__ )
#define CCLOG_WARN(format, ...) fprintf(stderr, format, ##__VA_ARGS__ )
#define CCLOG_ERROR( format, ...) fprintf(stderr, format, ##__VA_ARGS__ )

#endif//__COMMON_2021_09_06_H__