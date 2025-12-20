#pragma once

#include "Log.h"
#include <cstdint>
#include <print>


// I like more concise keywords, especially when it comes to data types.
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float f32;
typedef double f64;



// #############################################################################
//                           Defines
// #############################################################################

// This causes a breakpoint to occur dynamically (ie when an assertion is not met)
#ifdef _WIN32
#define DEBUG_BREAK() __debugbreak()
#define BIGWHOOP_API __declspec(dllexport)
#elif __linux__
#define DEBUG_BREAK() __builtin_debugtrap()
#define BIGWHOOP_API
#elif __APPLE__
#define DEBUG_BREAK() __builtin_trap()
#define BIGWHOOP_API
#endif

// Simple bit shifting function
#define BIT(x) 1 << (x)
#define KB(x) ((unsigned long long)1024 * x)
#define MB(x) ((unsigned long long)1024 * KB(x))
#define GB(x) ((unsigned long long)1024 * MB(x))



#ifdef GFX_DEBUG
	#define GFX_ENABLE_ASSERTS
#endif

#ifdef GFX_ENABLE_ASSERTS
	#define GFX_ASSERT(x, ...) { if(!(x)) { GFX_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define GFX_ASSERT(x, ...)
	#define GFX_CORE_ASSERT(x, ...)
#endif
