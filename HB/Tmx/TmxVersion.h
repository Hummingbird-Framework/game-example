#include <tmxparser/Tmx.h>
#include "../Core/Log.h"

#define TMX_COMPATIBLE_VERSION_MAJOR 1
#define TMX_COMPATIBLE_VERSION_MINOR 0

#ifndef TMX_PARSER_VERSION_MAJOR
	#define TMX_PARSER_VERSION_MAJOR 0
#endif
#ifndef TMX_PARSER_VERSION_MINOR
	#define TMX_PARSER_VERSION_MINOR 0
#endif

#ifndef NDEBUG
	#if !(TMX_COMPATIBLE_VERSION_MAJOR == TMX_PARSER_VERSION_MAJOR && TMX_PARSER_VERSION_MINOR <= TMX_COMPATIBLE_VERSION_MINOR)
		#error tmxparser version not compatible
	#endif
#endif

#ifndef NDEBUG
	#define HB_CHECK_TMXPARSER_VERSION() \
	do { \
		hb_assert(TMX_COMPATIBLE_VERSION_MAJOR == TMX_PARSER_VERSION_MAJOR && TMX_PARSER_VERSION_MINOR <= TMX_COMPATIBLE_VERSION_MINOR, "tmxparser version not compatible"); \
	} while (false)
#else
	#define HB_CHECK_TMXPARSER_VERSION() do { } while (false)
#endif