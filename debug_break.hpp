#if defined(_MSC_VER)

#define DEBUG_BREAK __debugbreak()

#elif defined(__GNUC__)

#define DEBUG_BREAK __builtin_trap()

#elif defined(__clang__)

#define DEBUG_BREAK __builtin_debugtrap()

#endif