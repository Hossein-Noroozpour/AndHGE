/**
 * Author: Hossein Noroozpour Thany Abady
 * Email: Hossein.Noroozpour@gmail.com
 */
#ifndef HGE_MAIN_HPP
#define HGE_MAIN_HPP
#ifdef ANDROID
#include <jni.h>
#ifdef __cplusplus
extern "C"
{
#endif
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *jvm, void *reserved);
JNIEXPORT jboolean JNICALL Java_com_hulixerian_hge_HGELib_init (JNIEnv *, jclass);
JNIEXPORT jboolean JNICALL Java_com_hulixerian_hge_HGELib_resize (JNIEnv *, jclass, jint, jint);
JNIEXPORT jboolean JNICALL Java_com_hulixerian_hge_HGELib_render (JNIEnv *, jclass);
JNIEXPORT jboolean JNICALL Java_com_hulixerian_hge_HGELib_setFingerPosition(JNIEnv *, jclass, jint, jfloat, jfloat);
JNIEXPORT jboolean JNICALL Java_com_hulixerian_hge_HGELib_setFingerMovement(JNIEnv *, jclass, jint, jfloat, jfloat);
#ifdef __cplusplus
}
#endif // __cplusplus
#endif // ANDROID
#endif // HGE_MAIN_HPP
