#if defined(_MSC_VER)

#define ZTH_DEBUG_BREAK __debugbreak()

#elif defined(__GNUC__)

#define ZTH_DEBUG_BREAK __builtin_trap()

#elif defined(__clang__)

#define ZTH_DEBUG_BREAK __builtin_debugtrap()

#else

#define ZTH_DEBUG_BREAK

#endif