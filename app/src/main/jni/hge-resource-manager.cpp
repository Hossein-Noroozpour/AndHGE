//#include <stdio.h>
//#include <zlib.h>
//unsigned long file_size(char *filename)
//{
//	FILE *pFile = fopen(filename, "rb");
//	fseek(pFile, 0, SEEK_END);
//	unsigned long size = ftell(pFile);
//	fclose(pFile);
//	return size;
//}
//int decompress_one_file(char *infilename, char *outfilename)
//{
//	gzFile infile = gzopen(infilename, "rb");
//	FILE *outfile = fopen(outfilename, "wb");
//	if (!infile || !outfile) return -1;
//	char buffer[128];
//	int num_read = 0;
//	while ((num_read = gzread(infile, buffer, sizeof(buffer))) > 0)
//	{
//		fwrite(buffer, 1, num_read, outfile);
//	}
//	gzclose(infile);
//	fclose(outfile);
//}
//int compress_one_file(char *infilename, char *outfilename)
//{
//	FILE *infile = fopen(infilename, "rb");
//	gzFile outfile = gzopen(outfilename, "wb");
//	if (!infile || !outfile) return -1;
//	char inbuffer[128];
//	int num_read = 0;
//	unsigned long total_read = 0, total_wrote = 0;
//	while ((num_read = fread(inbuffer, 1, sizeof(inbuffer), infile)) > 0) {
//		total_read += num_read;
//		gzwrite(outfile, inbuffer, num_read);
//	}
//	fclose(infile);
//	gzclose(outfile);
//	printf("Read %ld bytes, Wrote %ld bytes, Compression factor %4.2f%%\n",
//		total_read, file_size(outfilename),
//		(1.0 - file_size(outfilename)*1.0 / total_read)*100.0);
//}
#include "hge-resource-manager.hpp"
#include "hge-terrain-sun-shader.hpp"
#include "hge-system-access.hpp"
#include "hge-configure.hpp"
#include "hge-main-window.hpp"
#include <fstream>
#ifdef ANDROID
#include <android/log.h>
#endif
std::shared_ptr<hge::render::SceneUnit> hge::core::ResourceManager::importScene(std::shared_ptr<utility::Stream> &stream)
{
	bool endianCompatible = endianCompatibilityCheck(stream);
#ifdef HGE_TEST_MODE
	if (endianCompatible)
	{
		HGE_LOG_PRINT("Endian compatible.");
	}
	else
	{
		HGE_LOG_PRINT("Endian incompatible.");
	}
#endif
	std::shared_ptr<render::SceneUnit> result(new render::SceneUnit());
	Protocol::Types::ObjectTypeIdType typeId;
	for(stream->read((char *)(&typeId), sizeof(typeId));
		!stream->isEnd();
		stream->read((char *)(&typeId), sizeof(typeId)))
	{
		switch(typeId)
		{
		case Protocol::ObjectTypes::Geometry:
		{
#ifdef HGE_TEST_MODE
			HGE_LOG_PRINT("Geometry imported.");
#endif
#ifdef HGE_DEBUG_MODE
			if (stream->isEnd())
			{
				HGE_LOG_PRINT("Format error!");
			}
#endif
			std::shared_ptr<render::GeometryUnit> geo(new render::GeometryUnit());
			geo->setData(stream, endianCompatible);
			result->addGeometry(geo);
			break;
		}
		case Protocol::ObjectTypes::Terrain:
		{
#ifdef HGE_TEST_MODE
			HGE_LOG_PRINT("Terrain imported.");
#endif
#ifdef HGE_DEBUG_MODE
			if (stream->isEnd())
			{
				HGE_LOG_PRINT("Format error!");
			}
#endif
			std::shared_ptr<render::TerrainUnit> terrain(new render::TerrainUnit());
			terrain->setData(stream, endianCompatible);
			terrain->setShader(std::shared_ptr<shader::TerrainSunShader>(new shader::TerrainSunShader()));
			const std::string texturesFileAddress("terrain/");
			for (int i = 1; i < 9; i++)
				terrain->addTexture(std::shared_ptr<texture::TextureUnit>(
					new texture::TextureUnit(texturesFileAddress + std::to_string(i) + ".png")));
			result->setTerrain(terrain);
			break;
		}
		case Protocol::ObjectTypes::Mesh:
			break;
		case Protocol::ObjectTypes::SkyBox:
			break;
		default:
			break;
		}
	}
	return result;
}
std::shared_ptr<hge::render::SceneUnit> hge::core::ResourceManager::importScene(const std::string &fileAddress)
{
	auto fileCont = utility::SystemAccess::getFileStream(fileAddress);
	return importScene(fileCont);
}
bool hge::core::ResourceManager::endianCompatibilityCheck(std::shared_ptr<utility::Stream> &stream)
{
	int systemEndian = 1;
	char resourceEndian;
	stream->read(&resourceEndian, 1);
	return resourceEndian == ((char *)(&systemEndian))[0];
}
