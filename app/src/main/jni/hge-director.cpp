#include "hge-director.hpp"
#include "hge-texture-unit.hpp"
#include "hge-terrain-unit.hpp"
#include "hge-terrain-sun-shader.hpp"
#include "hge-protocol.hpp"
#include "hge-skybox-shader-unit.hpp"
#include "hge-resource-manager.hpp"
#include "hge-main-window.hpp"
#include <thread>
#include <iostream>
#include <fstream>
hge::core::Director::Director() :
goForward(false),
goDownward(false),
goRightward(false),
goLeftward(false),
rotateOn(false),
wireframeMode(false),
cameraRotationSpeed(0.001f),
cameraMoveSpeed(5.0f)
{
}
hge::core::Director::~Director()
{
}
void hge::core::Director::start()
{
}
void hge::core::Director::initialize()
{
	render::SceneUnit::defaultShader = std::shared_ptr<hge::shader::SunShader>(new hge::shader::SunShader());
	render::SceneUnit::defaultTexture = std::shared_ptr<hge::texture::TextureUnit>(new hge::texture::TextureUnit(std::string("hge-logo.png")));
	render::SceneUnit::occlusionQueryShader = std::shared_ptr<hge::shader::WhiteShader>(new hge::shader::WhiteShader());
	scene = ResourceManager::importScene("hge-sample.hge");
}
void hge::core::Director::update()
{
	gldo_lock.lock();
	for (auto f : gldo)
	{
		f();
	}
	gldo.clear();
	gldo_lock.unlock();
	if (goForward)
	{
		scene->getCamera()->moveForward(-cameraMoveSpeed);
	}
	if (goDownward)
	{
		scene->getCamera()->moveForward(cameraMoveSpeed);
	}
	if (goRightward)
	{
		scene->getCamera()->moveSideward(cameraMoveSpeed);
	}
	if (goLeftward)
	{
		scene->getCamera()->moveSideward(-cameraMoveSpeed);
	}
	scene->draw();
}
void hge::core::Director::buttonPressed(const HGEButton& key)
{
	switch (key)
	{
	case(F1KeyButton) :
		if (wireframeMode)
		{
			wireframeMode = false;
#if !defined(HGE_USE_OPENGL_ES_3) && !defined(HGE_USE_OPENGL_ES_2)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif
		}
		else
		{
			wireframeMode = true;
#if !defined(HGE_USE_OPENGL_ES_3) && !defined(HGE_USE_OPENGL_ES_2)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#endif
		}
		break;
	case(PageUpButton) :
		cameraMoveSpeed *= 2;
		break;
	case(PageDownButton) :
		cameraMoveSpeed /= 2;
		break;
	case(wKeyButton) :
		goForward = true;
		break;
	case(sKeyButton) :
		goDownward = true;
		break;
	case(aKeyButton) :
		goLeftward = true;
		break;
	case(dKeyButton) :
		goRightward = true;
		break;
	case(middleMouseButton) :
		rotateOn = true;
		break;
	default:
		break;
	}
}
void hge::core::Director::buttonReleased(const HGEButton& key)
{
	switch (key)
	{
	case(wKeyButton) :
		goForward = false;
		break;
	case(sKeyButton) :
		goDownward = false;
		break;
	case(aKeyButton) :
		goLeftward = false;
		break;
	case(dKeyButton) :
		goRightward = false;
		break;
	case(middleMouseButton) :
		rotateOn = false;
		break;
	default:
		break;
	}
}
void hge::core::Director::mouseMoved(const float &dx, const float &dy)
{
	HGE_LOG_PRINT("Movement is: (%f, %f)", dx, dy);
	if (rotateOn)
	{
		scene->getCamera()->rotateGlobalZ(-dx * cameraRotationSpeed);
		scene->getCamera()->rotateLocalX(-dy * cameraRotationSpeed);
		HGE_LOG_PRINT("Movement is: (%f, %f)", dx, dy);
	}
}
