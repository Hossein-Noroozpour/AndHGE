#ifndef HGE_SYSTEM_ACCESS_HPP
#define HGE_SYSTEM_ACCESS_HPP
#ifdef ANDROID
#include <jni.h>
#endif
#include <memory>
#include "hge-stream.hpp"
#include <string>
namespace hge
{
	namespace utility
	{
		class SystemAccess
		{
		private:
#ifdef ANDROID
			static JavaVM *globalJVM;
#endif
		public:
			static std::shared_ptr<Stream> getFileStream(const std::string &fileName);
#ifdef ANDROID
			static void setGlobalJVM(JavaVM *jvm);
			static JNIEnv *getCurJNIEnv();
#endif
		};
	}
}
#endif
