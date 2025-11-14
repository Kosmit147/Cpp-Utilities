#if defined(_MSC_VER)

#define FORCE_INLINE __forceinline

#elif defined(__GNUC__) || defined(__clang__)

#define FORCE_INLINE __attribute__((always_inline))

#endif

// ---

#if defined(_MSC_VER)

#define NO_INLINE __declspec(noinline)

#elif defined(__GNUC__) || defined(__clang__)

#define NO_INLINE __attribute__((noinline))

#endif
