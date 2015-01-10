#ifndef HGE_CONFIGURE_HPP
#define HGE_CONFIGURE_HPP
#include <cstring>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cstdarg>
#include <iostream>
#include <chrono>
#include <thread>
#define HGE_TERMINATE {std::chrono::milliseconds dura( 5000 );std::this_thread::sleep_for( dura ); std::terminate();}
#define HGE_STRING_BUFFER_SIZE 16192
#ifdef ANDROID
#include <android/log.h>
#define HGE_LOG_TAG "AndHGE-0.1"
#define HGE_JNI_VERSION JNI_VERSION_1_6
#else
#define HGE_LOG_TAG "HGE-0.1"
#endif // ANDROID
#define HGE_USE_OPENGL
/// Check bug conditions that may occur in program, it has perfomance penalty remove it in release
#define HGE_DEBUG_MODE
#ifdef HGE_DEBUG_MODE
/// Intensively check bug conditions that may occur in program, it has high perfomance penalty remore it in release
#define HGE_INTENSIVE_DEBUG_MODE
#endif // HGE_DEBUG_MODE
/// Show information about the excecution of program
#define HGE_TEST_MODE
#ifdef HGE_TEST_MODE
/// Show lots of information about the excecution of program
#define HGE_VERBOSE_TEST_MODE
#endif // HGE_TEST_MODE
#if !defined(HGE_USE_OPENGL) && (defined(_WIN64) || defined(_WIN32))
#define HGE_USE_DIRECTX_11 // do not use it it's not completed yet.
#ifndef HGE_USE_DIRECTX_11
#define HGE_USE_DIRECTX_10 // do not use it it's not completed yet.
#endif // HGE_USE_DIRECTX_11
#elif defined(HGE_USE_OPENGL) && (defined(__unix__) || defined(_WIN64) || defined(_WIN32)) && !defined(ANDROID)
#define HGE_USE_OPENGL_43
#if !defined(HGE_USE_OPENGL_43)
#define HGE_USE_OPENGL_42
#endif
#if !defined(HGE_USE_OPENGL_43) && !defined(HGE_USE_OPENGL_42)
#define HGE_USE_OPENGL_41
#endif
#if !defined(HGE_USE_OPENGL_43) && !defined(HGE_USE_OPENGL_42) && !defined(HGE_USE_OPENGL_41)
#define HGE_USE_OPENGL_40
#endif
#if !defined(HGE_USE_OPENGL_43) && !defined(HGE_USE_OPENGL_42) && !defined(HGE_USE_OPENGL_41) && !defined(HGE_USE_OPENGL_40)
#define HGE_USE_OPENGL_33
#endif
#elif defined(ANDROID)
#define HGE_LOG_ERROR(...)\
{\
	char strBuffer [HGE_STRING_BUFFER_SIZE];\
	snprintf(strBuffer, HGE_STRING_BUFFER_SIZE, __VA_ARGS__);\
	__android_log_print(ANDROID_LOG_ERROR, HGE_LOG_TAG, "%s (%d): %s", __FILE__, __LINE__, strBuffer);\
}
#define HGE_LOG_PRINT(...)\
{\
	char strBuffer [HGE_STRING_BUFFER_SIZE];\
	snprintf(strBuffer, HGE_STRING_BUFFER_SIZE, __VA_ARGS__);\
	__android_log_print(ANDROID_LOG_INFO, HGE_LOG_TAG, "%s (%d): %s", __FILE__, __LINE__, strBuffer);\
}
#define HGE_USE_OPENGL_ES_2
#ifndef HGE_USE_OPENGL_ES_2
#define HGE_USE_OPENGL_ES_3
#endif // HGE_USE_OPENGL_ES_2
#endif
#if defined(HGE_USE_OPENGL_33) || defined(HGE_USE_OPENGL_40) || defined(HGE_USE_OPENGL_41) || defined(HGE_USE_OPENGL_42) || defined(HGE_USE_OPENGL_43) || defined(HGE_USE_OPENGL_ES_3)
#define HGE_BASIC_QUERY_SUPPORT
#endif
#if defined(HGE_USE_OPENGL_33) || defined(HGE_USE_OPENGL_40) || defined(HGE_USE_OPENGL_41) || defined(HGE_USE_OPENGL_42) || defined(HGE_USE_OPENGL_43)
#define HGE_CONDITIONAL_RENDERING_SUPPORT
#define HGE_GEOMETRY_SHADER_SUPPORT
#endif
#ifndef ANDROID
#ifdef _MSC_VER
#define snprintf c99_snprintf
inline int c99_vsnprintf(char* str, size_t size, const char* format, va_list ap)
{
	int count = -1;
	if(size != 0)
		count = _vsnprintf_s(str, size, _TRUNCATE, format, ap);
	if(count == -1)
		count = _vscprintf(format, ap);
	return count;
}
inline int c99_snprintf(char* str, size_t size, const char* format, ...)
{
	int count;
	va_list ap;
	va_start(ap, format);
	count = c99_vsnprintf(str, size, format, ap);
	va_end(ap);
	return count;
}
#endif // _MSC_VER
#if defined(_WIN64) || defined(_WIN32)
#define HGE_LOG_PRINT(format, ...)\
{\
	char strBuffer [HGE_STRING_BUFFER_SIZE];\
	snprintf(strBuffer, HGE_STRING_BUFFER_SIZE, format, __VA_ARGS__ );\
	std::cout << __FILE__ << "(" << __LINE__ << "):\t\t\t" << strBuffer << std::endl;\
}
#define HGE_LOG_ERROR(format, ...)\
{\
	char strBuffer [HGE_STRING_BUFFER_SIZE];\
	snprintf(strBuffer, HGE_STRING_BUFFER_SIZE, format, __VA_ARGS__ );\
	std::cerr << __FILE__ << "(" << __LINE__ << "):\t\t\t" << strBuffer << std::endl;\
}
#elif defined(__unix__)
#define HGE_LOG_ERROR(...)\
{\
	char strBuffer [HGE_STRING_BUFFER_SIZE];\
	snprintf(strBuffer, HGE_STRING_BUFFER_SIZE, __VA_ARGS__);\
	std::cout << __FILE__ << "(" << __LINE__ << "):\t\t\t" << strBuffer << std::endl;\
}
#define HGE_LOG_PRINT(...)\
{\
	char strBuffer [HGE_STRING_BUFFER_SIZE];\
	snprintf(strBuffer, HGE_STRING_BUFFER_SIZE, __VA_ARGS__);\
	std::cerr << __FILE__ << "(" << __LINE__ << "):\t\t\t" << strBuffer << std::endl;\
}
#endif
#endif
// Terrain configurator definitions
#define HGE_TERRAIN_COMPONENT_COUNT 12
#define HGE_TERRAIN_LOD_NUMDER 4
#define HGE_TERRAIN_TEXTURE_COUNT 8
#define HGE_TERRAIN_TEXTURE_COUNT_STRING "8"
#define HGE_TERRAIN_HEIGHT_LIMIT_0 "0.6"
#define HGE_TERRAIN_HEIGHT_LIMIT_1 "3.1"
#define HGE_TERRAIN_HEIGHT_LIMIT_2 "7.0"
#define HGE_TERRAIN_HEIGHT_LIMIT_3 "16.0"
#define HGE_TERRAIN_HEIGHT_LIMIT_4 "30.0"
#define HGE_TERRAIN_HEIGHT_LIMIT_5 "50.0"
#define HGE_TERRAIN_HEIGHT_LIMIT_6 "70.0"
#define HGE_TERRAIN_HEIGHT_LIMIT_7 "100.0"
#define HGE_TERRAIN_HEIGHT_FADE_LIMIT "0.5"
#define HGE_TERRAIN_SLOP_LIMIT_0 "-0.5"
#define HGE_TERRAIN_SLOP_FADE_LIMIT "-0.1"
//
#define HGE_IMMIDIATE_PRINT {HGE_LOG_PRINT("Immidiate debugging"); std::chrono::milliseconds dura( 5000 );std::this_thread::sleep_for( dura );}
#endif // HGE_CONFIGURE_HPP
