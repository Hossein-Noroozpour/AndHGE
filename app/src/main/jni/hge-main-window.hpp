#ifndef HGE_MAIN_WINDOW_HPP
#define	HGE_MAIN_WINDOW_HPP
#include "hge-configure.hpp"
#ifdef HGE_USE_OPENGL
#ifdef ANDROID
#ifdef HGE_USE_OPENGL_ES_2
#include <GLES2/gl2.h>
#elif defined(HGE_USE_OPENGL_ES_3)
#include <GLES2/gl3.h>
#endif
#else
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#endif
#else
#include <windows.h>
#endif
#include "hge-application-unit.hpp"
#include <memory>
#include <chrono>
namespace hge
{
	namespace ui
	{
		class MainWindow
		{
		public:
			static void start(const std::shared_ptr<core::ApplicationUnit>& application);
			static void printGraphicAPIErrorAndTerminate();
#ifdef ANDROID
			static void renderOneFrame();
			static void setFingerMovement(const int &fingerIndex, const float &delatX, const float &delatY);
#endif
		private:
			static std::chrono::high_resolution_clock::time_point lastTime;
#ifdef HGE_USE_OPENGL
#ifndef ANDROID
			static void onErrorEvent(int errorNumber, const char* errorDescription);
			static void onCursorMoveEvent(GLFWwindow* window, double x, double y);
			static void onMouseKeyEvent(GLFWwindow* window, int button, int action, int mods);
			static void onKeyEvent(GLFWwindow* window, int key, int scanCode, int action, int mods);
			static void onChangeSizeEvent(GLFWwindow* window, int width, int height);
#endif
#else
			static HINSTANCE hge_hInst;
			static HWND hge_hWnd;
#endif
			static std::shared_ptr<core::ApplicationUnit> application;
			static double lastCursorXposition;
			static double lastCursorYposition;
		};
	}
}
#endif
