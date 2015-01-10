#ifndef HGEDIRECTOR_HPP
#define HGEDIRECTOR_HPP
#include "hge-application-unit.hpp"
#include "hge-scene-unit.hpp"
#include "hge-unlit-shader.hpp"
#include <functional>
#include <mutex>
namespace hge
{
	namespace core
	{
		class Director : public ApplicationUnit
		{
		private:
			std::mutex gldo_lock;
			std::vector<std::function<void(void)>> gldo;
			std::shared_ptr<hge::render::SceneUnit> scene;
			bool goForward;
			bool goDownward;
			bool goRightward;
			bool goLeftward;
			bool rotateOn;
			bool wireframeMode;
			float cameraRotationSpeed;
			float cameraMoveSpeed;








			math::CameraUnit c;
			math::PerspectiveUnit p;
			math::ModelUnit mm;
			std::shared_ptr<shader::UnlitShader> us;
			std::shared_ptr<shader::WhiteShader> ws;
			std::shared_ptr<shader::SunShader> ss;
			std::shared_ptr<render::MeshUnit> m;
			std::shared_ptr<texture::TextureUnit> tu;
			std::shared_ptr<render::GeometryUnit> gu;
		public:
			Director();
			~Director();
			void start();
			void initialize();
			void update();
			void buttonPressed(const HGEButton& key);
			void buttonReleased(const HGEButton& key);
			void mouseMoved(const float &dx, const float &dy);
		};
	}
}
#endif
