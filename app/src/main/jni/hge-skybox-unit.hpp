#ifndef HGESKYBOXUNIT_HPP
#define HGESKYBOXUNIT_HPP
#include "hge-mesh-unit.hpp"
#include "hge-shader-unit.hpp"
#include "hge-texture-unit.hpp"
#include "hge-skybox-shader-unit.hpp"
#include <vector>
#include <chrono>
#include <memory>
namespace hge
{
	namespace render
	{
		class SkyBoxUnit
		{
		private:
			std::shared_ptr<MeshUnit> mesh;
			math::Matrix4D<> modelMatrix;
			std::shared_ptr<shader::SkyBoxShaderUnit> shader;
			std::shared_ptr<texture::TextureUnit> texture;
			std::chrono::time_point<std::chrono::system_clock> lastDrawn;
			float skyTextuePosition;
		public:
			SkyBoxUnit(const std::shared_ptr<MeshUnit> &mesh);
			void setShader(const std::shared_ptr<shader::SkyBoxShaderUnit> &shader);
			void setTexture(const std::shared_ptr<texture::TextureUnit> &texture);
			void draw(const math::Matrix4D<> &vp);
		};
	}
}
#endif
