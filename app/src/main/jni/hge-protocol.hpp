#ifndef HGEPROTOCOL_HPP
#define HGEPROTOCOL_HPP
#include <cstdint>
namespace hge
{
	namespace core
	{
		class Protocol
		{
		public:
			class Types
			{
			public:
				typedef std::uint8_t HgeBoolean;
				typedef std::uint16_t TerrainAspectType;
				typedef std::uint8_t  TerrainVboComponentsCountType;
				typedef std::uint32_t IdType;
				typedef std::uint16_t ObjectTypeIdType;
				typedef std::uint16_t InstructionsType;
				typedef std::uint32_t ObjectSizeType;
				typedef float VertexElementType;
				typedef std::uint32_t IndexElementType;
				typedef std::uint32_t VerticesElementsCountType;
				typedef std::uint32_t IndicesCountType;
				typedef std::uint16_t StringLengthType;
			};
			class ObjectTypes
			{
			public:
				const static Types::ObjectTypeIdType Terrain = 0;
				const static Types::ObjectTypeIdType Geometry = 1;
				const static Types::ObjectTypeIdType SkyBox = 2;
				const static Types::ObjectTypeIdType Mesh = 3;
			};
			class Values
			{
			public:
				const static Types::HgeBoolean HgeFalse = 0;
				const static Types::HgeBoolean HgeTrue = 1;
			};
		};
	}
}
#endif
