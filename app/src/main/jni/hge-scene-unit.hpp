#ifndef HGE_SCENE_UNIT_HPP_
#define HGE_SCENE_UNIT_HPP_
#include "hge-geometry-unit.hpp"
#include "hge-terrain-unit.hpp"
#include "hge-camera-unit.hpp"
#include "hge-perspective-unit.hpp"
#include "hge-skybox-unit.hpp"
#include "hge-sun-shader.hpp"
#include "hge-white-shader.hpp"
#include <memory>
#include <vector>
namespace hge
{
	namespace render
	{
		class SceneUnit
		{
		private:
			std::vector<std::shared_ptr<GeometryUnit>> geometries;
			std::vector<std::shared_ptr<math::CameraUnit>> cameras;
			std::vector<std::shared_ptr<math::PerspectiveUnit>> perspectives;
			std::shared_ptr<TerrainUnit> terrain;
			std::vector<std::shared_ptr<SkyBoxUnit>> skies;
			unsigned int currentCameraIndex;
			unsigned int currentPerspectiveIndex;
			bool hasTerrain;
			bool hasGeometry;
		public:
			SceneUnit();
			void addGeometry(const std::shared_ptr<GeometryUnit> &geometry);
			void addSky(const std::shared_ptr<SkyBoxUnit> &sky);
			void setTerrain(const std::shared_ptr<TerrainUnit> &terrain);
			void draw();
			std::shared_ptr<GeometryUnit> getGeoByID(const core::Protocol::Types::IdType &id);
			std::shared_ptr<math::CameraUnit> getCamera(const unsigned int& cameraIndex = 0);
			std::shared_ptr<SkyBoxUnit> getSky(const unsigned int& skyIndex = 0);
			std::shared_ptr<TerrainUnit> getTerrain();
			static std::shared_ptr<shader::WhiteShader> occlusionQueryShader;
			static std::shared_ptr<shader::SunShader> defaultShader;
			static std::shared_ptr<texture::TextureUnit> defaultTexture;
		};
	}
}
#endif
