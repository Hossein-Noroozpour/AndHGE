#ifndef HGE_APPLICATION_UNIT_HPP_
#define HGE_APPLICATION_UNIT_HPP_
#include <string>
#include <memory>
namespace hge
{
	namespace render
	{
		class TerrainUnit;
	}
	namespace core
	{
		class ApplicationUnit
		{
		public:
			enum HGEButton
			{
				/// Function keys
				F1KeyButton,
				/// Control keys
				PageUpButton,
				PageDownButton,
				/// Mouse Buttons
				rightMouseButton,
				middleMouseButton,
				leftMouseButton,
				/// Arrow Key Buttons
				upArrowKeyButton,
				downArrowKeyButton,
				leftArrowKeyButton,
				rightArrowKeyButton,
				/// Normal key Buttons
				wKeyButton,
				sKeyButton,
				aKeyButton,
				dKeyButton
			};
			/// \warning this function will be called in starting process of
			/// do not call any OpenGL function in it.
			virtual void start() = 0;
			/// \note this function will be called in OpenGL initializing
			/// procedure.
			virtual void initialize() = 0;
			/// this function will be called in every frame update
			virtual void update() = 0;
			/// \return true if every things went correct
			/// else false if any thing went wrong.
			virtual void buttonPressed(const HGEButton& key) = 0;
			virtual void buttonReleased(const HGEButton& key) = 0;
			virtual void mouseMoved(const float& dx, const float& dy) = 0;
		};
	}
}
#endif
