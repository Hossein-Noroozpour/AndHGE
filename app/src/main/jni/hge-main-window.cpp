#include "hge-main-window.hpp"
#include "hge-configure.hpp"
#include "hge-system-access.hpp"
#include <iostream>
std::shared_ptr<hge::core::ApplicationUnit> hge::ui::MainWindow::application;
double hge::ui::MainWindow::lastCursorXposition = 0.0;
double hge::ui::MainWindow::lastCursorYposition = 0.0;
std::chrono::high_resolution_clock::time_point hge::ui::MainWindow::lastTime;
#ifdef ANDROID
#include <android/log.h>
#else
void hge::ui::MainWindow::onErrorEvent(int errorNumber, const char* errorDescription)
{
	HGE_LOG_ERROR("Error number is: %d  %s %d", errorNumber, "Error description: ", errorDescription);
	HGE_TERMINATE
}
void hge::ui::MainWindow::onKeyEvent(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
	switch(action)
	{
		case(GLFW_PRESS):
			switch(key)
			{
				case(GLFW_KEY_ESCAPE):
					glfwSetWindowShouldClose(window, GL_TRUE);
					break;
				case(GLFW_KEY_F1):
					application->buttonPressed(core::ApplicationUnit::F1KeyButton);
					break;
				case(GLFW_KEY_W):
					application->buttonPressed(core::ApplicationUnit::wKeyButton);
					break;
				case(GLFW_KEY_A):
					application->buttonPressed(core::ApplicationUnit::aKeyButton);
					break;
				case(GLFW_KEY_S):
					application->buttonPressed(core::ApplicationUnit::sKeyButton);
					break;
				case(GLFW_KEY_D):
					application->buttonPressed(core::ApplicationUnit::dKeyButton);
					break;
				case(GLFW_KEY_UP):
					application->buttonPressed(core::ApplicationUnit::upArrowKeyButton);
					break;
				case(GLFW_KEY_DOWN):
					application->buttonPressed(core::ApplicationUnit::downArrowKeyButton);
					break;
				case(GLFW_KEY_LEFT):
					application->buttonPressed(core::ApplicationUnit::leftArrowKeyButton);
					break;
				case(GLFW_KEY_RIGHT):
					application->buttonPressed(core::ApplicationUnit::rightArrowKeyButton);
					break;
				case(GLFW_KEY_PAGE_UP):
					application->buttonPressed(core::ApplicationUnit::PageUpButton);
					break;
				case(GLFW_KEY_PAGE_DOWN):
					application->buttonPressed(core::ApplicationUnit::PageDownButton);
					break;
				default:
					break;
			}
			break;
		case(GLFW_RELEASE):
			switch(key)
			{
				case(GLFW_KEY_ESCAPE):
					break;
				case(GLFW_KEY_W):
					application->buttonReleased(core::ApplicationUnit::wKeyButton);
					break;
				case(GLFW_KEY_A):
					application->buttonReleased(core::ApplicationUnit::aKeyButton);
					break;
				case(GLFW_KEY_S):
					application->buttonReleased(core::ApplicationUnit::sKeyButton);
					break;
				case(GLFW_KEY_D):
					application->buttonReleased(core::ApplicationUnit::dKeyButton);
					break;
				case(GLFW_KEY_UP):
					application->buttonReleased(core::ApplicationUnit::upArrowKeyButton);
					break;
				case(GLFW_KEY_DOWN):
					application->buttonReleased(core::ApplicationUnit::downArrowKeyButton);
					break;
				case(GLFW_KEY_LEFT):
					application->buttonReleased(core::ApplicationUnit::leftArrowKeyButton);
					break;
				case(GLFW_KEY_RIGHT):
					application->buttonReleased(core::ApplicationUnit::rightArrowKeyButton);
					break;
				default:
					break;
			}
			break;
		case(GLFW_REPEAT):
			break;
		default:
			break;
	}
}
void hge::ui::MainWindow::onMouseKeyEvent(GLFWwindow* window, int button, int action, int mods)
{
	switch(action)
	{
		case GLFW_PRESS:
			switch(button)
			{
				case GLFW_MOUSE_BUTTON_LEFT:
					application->buttonPressed(core::ApplicationUnit::leftMouseButton);
					break;
				case GLFW_MOUSE_BUTTON_RIGHT:
					application->buttonPressed(core::ApplicationUnit::rightMouseButton);
					break;
				case GLFW_MOUSE_BUTTON_MIDDLE:
					application->buttonPressed(core::ApplicationUnit::middleMouseButton);
					break;
				default:
					break;
			}
			break;
		case GLFW_RELEASE:
			switch(button)
			{
				case GLFW_MOUSE_BUTTON_LEFT:
					application->buttonReleased(core::ApplicationUnit::leftMouseButton);
					break;
				case GLFW_MOUSE_BUTTON_RIGHT:
					application->buttonReleased(core::ApplicationUnit::rightMouseButton);
					break;
				case GLFW_MOUSE_BUTTON_MIDDLE:
					application->buttonReleased(core::ApplicationUnit::middleMouseButton);
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
}
void hge::ui::MainWindow::onCursorMoveEvent(GLFWwindow* window, double x, double y)
{
	application->mouseMoved((float)(x - lastCursorXposition),(float)(y - lastCursorYposition));
	lastCursorXposition = x;
	lastCursorYposition = y;
}
void hge::ui::MainWindow::onChangeSizeEvent(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	glScissor(0, 0, width, height);
}
#endif
void hge::ui::MainWindow::start(const std::shared_ptr<hge::core::ApplicationUnit>& app)
{
	lastTime = std::chrono::high_resolution_clock::now();
	application = app;
	application->start();
#ifndef ANDROID
	GLFWwindow* window;
	glfwSetErrorCallback(onErrorEvent);
	if(!glfwInit())
	{
		HGE_TERMINATE
	}
	auto priMon = glfwGetPrimaryMonitor();
	auto vidMod = glfwGetVideoMode(priMon);
#ifdef HGE_TEST_MODE
	window = glfwCreateWindow(750, 500, "Hulixerian Game Engine", 0, NULL);
#else
	window = glfwCreateWindow(vidMod->width, vidMod->height, "Hulixerian Game Engine", priMon, NULL);
#endif
	if (!window)
	{
		glfwTerminate();
		HGE_TERMINATE
	}
	glfwMakeContextCurrent(window);
	if(glewInit() != GLEW_OK)
	{
		HGE_TERMINATE
	}
#endif
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_SCISSOR_TEST);
	glEnable(GL_STENCIL_TEST);
#if !defined(HGE_USE_OPENGL_ES_2) && !defined(HGE_USE_OPENGL_ES_3)
	glEnable(GL_ALPHA_TEST);
#endif
#ifndef ANDROID
	glfwSetKeyCallback(window, onKeyEvent);
	glfwSetMouseButtonCallback(window, onMouseKeyEvent);
	glfwSetCursorPosCallback(window, onCursorMoveEvent);
#endif
#ifndef ANDROID
#ifdef HGE_TEST_MODE
	glViewport(0, 0, 740, 490);
	glScissor(0, 0, 740, 490);
#else // not HGE_TEST_MODE
	glViewport(0, 0, vidMod->width, vidMod->height);
#endif // end of if HGE_TEST_MODE
#else // if ANDROID is defined.
	JNIEnv *env = utility::SystemAccess::getCurJNIEnv();
	jclass cls = env->FindClass("com/hulixerian/hge/AndroidAccess");
#ifdef HGE_DEBUG_MODE
	if(NULL == cls)
	{
		HGE_LOG_ERROR("Can not find specified class.");
		HGE_TERMINATE;
	}
#endif // end of HGE_DEBUG_MODE
	jmethodID mtd = env->GetStaticMethodID(cls, "getScreenWidth", "()I");
#ifdef HGE_DEBUG_MODE
	if(NULL == mtd)
	{
		HGE_LOG_ERROR("Can not find specified method.");
		HGE_TERMINATE;
	}
#endif // end of HGE_DEBUG_MODE
	GLuint width = (GLuint)env->CallStaticIntMethod(cls, mtd);
	mtd = env->GetStaticMethodID(cls, "getScreenHeight", "()I");
#ifdef HGE_DEBUG_MODE
	if(NULL == mtd)
	{
		HGE_LOG_ERROR("Can not find specified method.");
		HGE_TERMINATE;
	}
#endif // end of HGE_DEBUG_MODE
	GLuint height = (GLuint)env->CallStaticIntMethod(cls, mtd);
#ifdef HGE_VERBOSE_TEST_MODE
	HGE_LOG_PRINT("Height: %d    Width: %d", height, width);
#endif // HGE_VERBOSE_TEST_MODE
	glViewport(0, 0, width, height);
	glScissor(0, 0, width, height);
#endif // end of ifndef ANDROID
	application->initialize();
#ifndef ANDROID
	glfwSetFramebufferSizeCallback(window, onChangeSizeEvent);
#ifndef HGE_TEST_MODE
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
#endif
	while(!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		application->update();
//		glBegin(GL_TRIANGLES);
//		glVertex3f(0.f, 0.f, 0.f);
//		glVertex3f(10.f, 0.f, 0.f);
//		glVertex3f(10.f, 10.f, 0.f);
//		glEnd();
		glFinish();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
#endif
}
void hge::ui::MainWindow::printGraphicAPIErrorAndTerminate()
{
	switch(glGetError())
	{
		case GL_NO_ERROR :
			break;
		case GL_INVALID_ENUM :
			HGE_LOG_ERROR("Invalid enum error.");
			HGE_TERMINATE;
			break;
		case GL_INVALID_VALUE :
			HGE_LOG_ERROR("Invalid value error.");
			HGE_TERMINATE;
			break;
#if !defined(HGE_USE_OPENGL_ES_2) && !defined(HGE_USE_OPENGL_ES_3)
		case GL_INVALID_INDEX :
			HGE_LOG_ERROR("Invalid index error.");
			HGE_TERMINATE;
			break;
#endif
		case GL_INVALID_OPERATION :
			HGE_LOG_ERROR("Invalid operation error.");
			HGE_TERMINATE;
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION :
			HGE_LOG_ERROR("Invalid framebuffer operation error.");
			HGE_TERMINATE;
			break;
		case GL_OUT_OF_MEMORY :
			HGE_LOG_ERROR("Out of memory error.");
			HGE_TERMINATE;
			break;
#if !defined(HGE_USE_OPENGL_ES_2) && !defined(HGE_USE_OPENGL_ES_3)
		case GL_STACK_OVERFLOW :
			HGE_LOG_ERROR("Stack overflow error.");
			HGE_TERMINATE;
			break;
		case GL_STACK_UNDERFLOW :
			HGE_LOG_ERROR("Stack underflow error.");
			HGE_TERMINATE;
			break;
#endif
		default :
			HGE_LOG_ERROR("Unknown error.");
			HGE_TERMINATE;
			break;
	}
}
#ifdef HGE_USE_OPENGL
#ifdef ANDROID
void hge::ui::MainWindow::renderOneFrame()
{
	auto now = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(now - lastTime);
	lastTime = std::chrono::high_resolution_clock::now();
	//HGE_LOG_PRINT("FRPS: %f", 1.0f/float(time_span.count()));
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	application->update();
	glFinish();
}
void hge::ui::MainWindow::setFingerMovement(const int &fingerIndex, const float &delatX, const float &delatY)
{
	application->buttonPressed(hge::core::ApplicationUnit::middleMouseButton);
	application->mouseMoved(delatX, delatY);
	application->buttonReleased(hge::core::ApplicationUnit::middleMouseButton);
}
#endif // ANDROID
#endif // HGE_USE_OPENGL
