#include "hge-system-access.hpp"
#include "hge-configure.hpp"
#ifndef ANDROID
#include "hge-file-stream.hpp"
#endif // ANDROID
#ifdef ANDROID
#include <iostream>
#include <streambuf>
#include <sstream>
#include <android/log.h>
#include <android/asset_manager_jni.h>
#include "hge-chunk-stream.hpp"
JavaVM *hge::utility::SystemAccess::globalJVM;
void hge::utility::SystemAccess::setGlobalJVM(JavaVM *jvm)
{
	globalJVM = jvm;
}
JNIEnv *hge::utility::SystemAccess::getCurJNIEnv()
{
	JNIEnv* env;
#ifdef HGE_DEBUG_MODE
	jint result = globalJVM->GetEnv((void**)&env, HGE_JNI_VERSION);
	if (result != JNI_OK || env == NULL)
	{
		if(result == JNI_EDETACHED)
		{
			HGE_LOG_ERROR("Current thread is not attached to the VM.");
			HGE_TERMINATE;
		}
		else if(result == JNI_EVERSION)
		{
			HGE_LOG_ERROR("Specified version is not supported.");
			HGE_TERMINATE;
		}
		else
		{
			HGE_LOG_ERROR("Unknown Error.");
			HGE_TERMINATE;
		}
	}
#else
	globalJVM->GetEnv((void**)&env, HGE_JNI_VERSION);
#endif
	return env;
}
#endif
std::shared_ptr<hge::utility::Stream> hge::utility::SystemAccess::getFileStream(const std::string &fileName)
{
#ifdef ANDROID
	JNIEnv *env = getCurJNIEnv();
	jclass cls = env->FindClass("com/hulixerian/hge/AndroidAccess");
#ifdef HGE_DEBUG_MODE
	if(NULL == cls)
	{
		HGE_LOG_ERROR("Can not find specified class.");
		HGE_TERMINATE;
	}
#endif
//	jmethodID mtd = env->GetStaticMethodID(cls, "getAPKFPath", "()Ljava/lang/String;");
//	jstring pathstr = (jstring) env->CallStaticObjectMethod(cls, mtd);
//	jboolean isCopy;
//	const char *strch = env->GetStringUTFChars(pathstr, &isCopy);
//	zip *apkArchive = zip_open(strch, 0, NULL);
//#ifdef HGE_DEBUG_MODE
//	if(apkArchive == NULL)
//	{
//		HGE_LOG_ERROR("Error in unzipping APK.");
//		HGE_TERMINATE;
//	}
//#endif
//	std::string fileAdd = "assets/" + fileName;
//	struct zip_stat st;
//	zip_stat_init(&st);
//	zip_stat(apkArchive, fileAdd.c_str(), 0, &st);
//	char *contents = new char[st.size];
//	zip_file *file = zip_fopen(apkArchive, fileAdd.c_str(), 0);
//#ifdef HGE_DEBUG_MODE
//	if(!file)
//	{
//		HGE_LOG_ERROR("Error in opening %s in APK.", fileAdd.c_str());
//		HGE_TERMINATE;
//	}
//#endif
//	zip_fread(file, content, st.size);
//	std::istringstream result(std::string(contents, st.size));
//	delete contents;
//	zip_fclose(file);
//	zip_close(apkArchive);
//	env->ReleaseStringUTFChars(pathstr, strch);

	jmethodID mtd = env->GetStaticMethodID(cls, "getAssetManager", "()Landroid/content/res/AssetManager;");
#ifdef HGE_DEBUG_MODE
	if(NULL == mtd)
	{
		HGE_LOG_ERROR("Can not find specified method.");
		HGE_TERMINATE;
	}
#endif
	jobject am = env->CallStaticObjectMethod(cls, mtd);
	AAssetManager *assetManager = AAssetManager_fromJava(env, am);
	AAsset *asset = AAssetManager_open(assetManager, fileName.c_str(), AASSET_MODE_UNKNOWN);
#ifdef HGE_DEBUG_MODE
	if(!asset)
	{
		HGE_LOG_ERROR("Can not open specified asset.");
		HGE_LOG_ERROR("%s", fileName.c_str());
		HGE_TERMINATE;
	}
#endif
	const off_t bufferSize = AAsset_getLength(asset);
	char *buffer = new char[bufferSize];
#ifdef HGE_DEBUG_MODE
	if(bufferSize != AAsset_read(asset, buffer, bufferSize))
	{
		HGE_LOG_ERROR("Can not read specified asset.");
		HGE_TERMINATE;
	}
#else
	AAsset_read(asset, buffer, bufferSize);
#endif
	std::shared_ptr<Stream> result(new ChunkStream(buffer, bufferSize));
	AAsset_close(asset);
	return result;
#else
	std::shared_ptr<Stream> result(new FileStream(fileName));
	return result;
#endif
}
