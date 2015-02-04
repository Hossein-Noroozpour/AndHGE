/**
 * Author: Hossein Noroozpour Thany Abady
 * Email: Hossein.Noroozpour@gmail.com
 */
#include "hge-main.hpp"
#include "hge-director.hpp"
#include "hge-system-access.hpp"
#include "hge-main-window.hpp"
#include "hge-test-scenarios.hpp"
#include <memory>
#include <fstream>
#include <iostream>
#ifdef ANDROID
#include <android/log.h>
//#ifdef __cplusplus
//extern "C"
//{
//#endif // End of __cplusplus
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *jvm, void *reserved)
{
	(void) reserved;
	hge::utility::SystemAccess::setGlobalJVM(jvm);
	JNIEnv *lEnv;
	if (jvm->GetEnv((void**)&lEnv, HGE_JNI_VERSION) != JNI_OK)
	{
		HGE_LOG_ERROR("Error in initializing.");
		return JNI_ERR;
	}
	HGE_LOG_PRINT("Initialized successfully.");
	return HGE_JNI_VERSION;
}
JNIEXPORT jboolean JNICALL Java_com_hulixerian_hge_HGELib_init (JNIEnv *pEnv, jclass clazz)
{
	hge::ui::MainWindow::start(std::shared_ptr<hge::core::ApplicationUnit>(new hge::core::Director()));
	return JNI_TRUE;
}
JNIEXPORT jboolean JNICALL Java_com_hulixerian_hge_HGELib_resize (JNIEnv *pEnv, jclass clazz, jint width, jint height)
{
	return JNI_TRUE;
}
JNIEXPORT jboolean JNICALL Java_com_hulixerian_hge_HGELib_render (JNIEnv *pEnv, jclass clazz)
{
	hge::ui::MainWindow::renderOneFrame();
	return JNI_TRUE;
}
JNIEXPORT jboolean JNICALL Java_com_hulixerian_hge_HGELib_setFingerPosition(JNIEnv *pEnv, jclass clazz, jint fingerIndex, jfloat x, jfloat y)
{
	return JNI_TRUE;
}
JNIEXPORT jboolean JNICALL Java_com_hulixerian_hge_HGELib_setFingerMovement(JNIEnv *pEnv, jclass clazz, jint fingerIndex, jfloat deltaX, jfloat deltaY)
{
	hge::ui::MainWindow::setFingerMovement(fingerIndex, deltaX, deltaY);
	return JNI_TRUE;
}
//#ifdef __cplusplus
//}
//#endif // End of __cplusplus
#else // End of ANDROID
int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
#ifdef HGE_TEST_SCENARIO_MATH



#else
	std::shared_ptr<hge::core::ApplicationUnit> app(new hge::core::Director());
	hge::ui::MainWindow::start(app);
#endif
	return 0;
}
#endif



/*std::string logoFileAddress("C:\\Users\\Thany Hulixer\\Documents\\Visual Studio 2013\\Projects\\HGE-Previewer\\x64\\Debug\\HGE-Logo1024x1024.png");
std::ifstream logoFileStream;
logoFileStream.open(logoFileAddress, std::ios_base::binary);
if (logoFileStream.is_open())
{
	std::shared_ptr<hge::texture::TextureUnit> logoTexture(new hge::texture::TextureUnit(GL_TEXTURE_2D, logoFileStream));
}
else
{
	HGE_LOG_ERROR("Error in logo file opening process.");
	HGE_TERMINATE;
}*/
