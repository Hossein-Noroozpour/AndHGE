#include "hge-configure.hpp"
#include "hge-scene-unit.hpp"
#include "hge-white-shader.hpp"
#include "hge-main-window.hpp"
#include <iostream>
std::shared_ptr<hge::shader::SunShader> hge::render::SceneUnit::defaultShader;
std::shared_ptr<hge::texture::TextureUnit> hge::render::SceneUnit::defaultTexture;
std::shared_ptr<hge::shader::WhiteShader> hge::render::SceneUnit::occlusionQueryShader;
hge::render::SceneUnit::SceneUnit():
	currentCameraIndex(0),
	currentPerspectiveIndex(0),
	hasTerrain(false),
	hasGeometry(false)
{
	cameras.push_back(std::shared_ptr<math::CameraUnit>(new math::CameraUnit()));
	perspectives.push_back(std::shared_ptr<math::PerspectiveUnit>(new math::PerspectiveUnit()));
}
void hge::render::SceneUnit::addGeometry(const std::shared_ptr<GeometryUnit>& geometry)
{
	hasGeometry = true;
#ifdef HGE_BASIC_QUERY_SUPPORT
	geometry->setOcclusionQueryShader(occlusionQueryShader);
#endif
	geometry->setShader(defaultShader);
	geometry->setTexture(defaultTexture);
	//geometry->getModelMatrix()->scale(10.0f);
	//geometry->getModelMatrix()->translate(math::Vector3D<>(0.0f, 0.0f, 0.0f));
	geometries.push_back(geometry);
}
void
hge::render::SceneUnit::draw()
{
	auto vp = cameras[0]->getMatrix() * perspectives[0]->getMatrix();
	auto vp_rot = perspectives[0]->getMatrix() * cameras[0]->getRotateScaleMatrix();
	glDepthMask(GL_FALSE);
	for(unsigned int i = 0; i < skies.size(); i++)
	{
		skies[i]->draw(vp_rot);
	}
	glDepthMask(GL_TRUE);
	if(hasTerrain)
	{
		terrain->draw(vp);
	}
	if(hasGeometry)
	{
#ifdef HGE_BASIC_QUERY_SUPPORT
		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
		glDepthMask(GL_FALSE);
		geometries[0]->occlusionQueryStarter(vp);
		for(unsigned int i = 1; i < geometries.size(); i++)
		{
			geometries[i]->occlusionQuery(vp);
		}
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glDepthMask(GL_TRUE);
#endif
//		for(unsigned int i = 0; i < geometries.size(); i++)
//		{
//#ifdef HGE_BASIC_QUERY_SUPPORT
//			geometries[i]->draw();
//#else
//			ui::MainWindow::printGraphicAPIErrorAndTerminate(); HGE_IMMIDIATE_PRINT;
//			geometries[i]->draw(vp);
//			ui::MainWindow::printGraphicAPIErrorAndTerminate(); HGE_IMMIDIATE_PRINT;
//#endif
//		}
	}
}
std::shared_ptr<hge::render::GeometryUnit> hge::render::SceneUnit::getGeoByID(const core::Protocol::Types::IdType &id)
{
	for(unsigned int i = 0; i < geometries.size(); i++)
	{
		if(geometries[i]->getDataId() == id)
		{
			return geometries[i];
		}
	}
	HGE_LOG_PRINT("Testing");
	return nullptr;
}
void hge::render::SceneUnit::setTerrain(const std::shared_ptr<TerrainUnit>& t)
{
	hasTerrain = true;
	terrain = t;
}
std::shared_ptr<hge::math::CameraUnit> hge::render::SceneUnit::getCamera(const unsigned int& cameraIndex)
{
	return cameras[cameraIndex];
}
void hge::render::SceneUnit::addSky(const std::shared_ptr<SkyBoxUnit> &sky)
{
	skies.push_back(sky);
}

std::shared_ptr<hge::render::SkyBoxUnit> hge::render::SceneUnit::getSky(const unsigned int &skyIndex)
{
	return skies[skyIndex];
}
std::shared_ptr<hge::render::TerrainUnit> hge::render::SceneUnit::getTerrain()
{
	return terrain;
}
