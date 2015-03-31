#ifndef HB_LOG
#define HB_LOG
#include <iostream>

#ifndef NDEBUG
	#define hb_assert(condition, message) \
	do { \
		if (! (condition)) { \
			std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
						<< " line " << __LINE__ << ": " << message << std::endl; \
			std::exit(EXIT_FAILURE); \
		} \
	} while (false)
#else
	#define hb_assert(condition, message) do { } while (false)
#endif


#ifndef NDEBUG
	#define hb_log_d(message) \
	do { \
		std::cout << message << std::endl; \
	} while (false)
#else
	#define hb_log_d(message) do { } while (false)
#endif


#define hb_log(message) \
do { \
	std::cout << message << std::endl; \
} while (false)


#define hb_log_e(message) \
do { \
	std::cerr << message << std::endl; \
} while (false)

#endif