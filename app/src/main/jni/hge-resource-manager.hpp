#include "hge-configure.hpp"
#include "hge-scene-unit.hpp"
#include "hge-stream.hpp"
namespace hge
{
	namespace core
	{
		class ResourceManager
		{
		public:
			enum exceptions
			{
				CanNotOpenFile,
				ErrorInStream
			};
			static std::shared_ptr<render::SceneUnit> importScene(std::shared_ptr<utility::Stream> &stream);
			static std::shared_ptr<render::SceneUnit> importScene(const std::string &fileAddress);
		private:
			static bool endianCompatibilityCheck(std::shared_ptr<utility::Stream> &stream);
		};
	}
}
