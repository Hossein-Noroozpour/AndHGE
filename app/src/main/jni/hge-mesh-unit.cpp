#include "hge-mesh-unit.hpp"
#include "hge-main-window.hpp"
#include <iostream>
#include <string>
#ifdef ANDROID
#include <android/log.h>
#endif
hge::render::MeshUnit::MeshUnit() :
vbo(0), ibo(0), vboSize(0), vboElementsNumber(0), iboSize(0), numberOfIndices(0)
{}
hge::render::MeshUnit::MeshUnit(
	const GLfloat* const& vertices,
	const GLuint* const& indices,
	const GLuint& verticesByteSize,
	const GLuint& verticesNumber,
	const GLuint& indicesByteSize) :
	vboSize(verticesByteSize),
	vboElementsNumber(verticesNumber),
	iboSize(indicesByteSize),
	numberOfIndices((iboSize) / (sizeof(GLuint)))
{
	HGE_LOG_PRINT("TILL NOW!");
	HGE_IMMIDIATE_PRINT
#ifdef HGE_INTENSIVE_DEBUG_MODE
	hge::ui::MainWindow::printGraphicAPIErrorAndTerminate();
#endif
	glGenBuffers(1, &vbo);
#ifdef HGE_INTENSIVE_DEBUG_MODE
	hge::ui::MainWindow::printGraphicAPIErrorAndTerminate();
#endif
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
#ifdef HGE_INTENSIVE_DEBUG_MODE
	hge::ui::MainWindow::printGraphicAPIErrorAndTerminate();
#endif
	glBufferData(GL_ARRAY_BUFFER, verticesByteSize, vertices, GL_STATIC_DRAW);
#ifdef HGE_INTENSIVE_DEBUG_MODE
	hge::ui::MainWindow::printGraphicAPIErrorAndTerminate();
#endif
	glGenBuffers(1, &ibo);
#ifdef HGE_INTENSIVE_DEBUG_MODE
	hge::ui::MainWindow::printGraphicAPIErrorAndTerminate();
#endif
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
#ifdef HGE_INTENSIVE_DEBUG_MODE
	hge::ui::MainWindow::printGraphicAPIErrorAndTerminate();
#endif
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesByteSize, indices, GL_STATIC_DRAW);
#ifdef HGE_VERBOSE_TEST_MODE
	HGE_LOG_PRINT("vbo: %d", vbo);
	HGE_LOG_PRINT("ibo: %d", ibo);
	HGE_LOG_PRINT("vboSize: %d", vboSize);
	HGE_LOG_PRINT("vboElementsNumber: %d", vboElementsNumber);
	HGE_LOG_PRINT("iboSize: %d", iboSize);
	HGE_LOG_PRINT("numberOfIndices: %d", numberOfIndices);
#endif
	delete[] vertices;
	delete[] indices;
}
hge::render::MeshUnit::~MeshUnit()
{
//	HGE_LOG_PRINT("VBO is: %d, and IBO is %d", vbo, ibo);
//	HGE_IMMIDIATE_PRINT
	///\todo There is some problem in here, solve it as soon as possible.
#ifdef HGE_INTENSIVE_DEBUG_MODE
	hge::ui::MainWindow::printGraphicAPIErrorAndTerminate();
#endif
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &vbo);
#ifdef HGE_INTENSIVE_DEBUG_MODE
	hge::ui::MainWindow::printGraphicAPIErrorAndTerminate();
#endif
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &ibo);
#ifdef HGE_INTENSIVE_DEBUG_MODE
	hge::ui::MainWindow::printGraphicAPIErrorAndTerminate();
#endif

}
void
hge::render::MeshUnit::bindVBO()
{
#ifdef HGE_INTENSIVE_DEBUG_MODE
	hge::ui::MainWindow::printGraphicAPIErrorAndTerminate();
#endif
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
#ifdef HGE_INTENSIVE_DEBUG_MODE
	hge::ui::MainWindow::printGraphicAPIErrorAndTerminate();
#endif
}
void
hge::render::MeshUnit::bindIBO()
{
#ifdef HGE_INTENSIVE_DEBUG_MODE
	hge::ui::MainWindow::printGraphicAPIErrorAndTerminate();
#endif
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
#ifdef HGE_INTENSIVE_DEBUG_MODE
	hge::ui::MainWindow::printGraphicAPIErrorAndTerminate();
#endif
}
void
hge::render::MeshUnit::bindTotal()
{
#ifdef HGE_INTENSIVE_DEBUG_MODE
	hge::ui::MainWindow::printGraphicAPIErrorAndTerminate();
#endif
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
#ifdef HGE_INTENSIVE_DEBUG_MODE
	hge::ui::MainWindow::printGraphicAPIErrorAndTerminate();
#endif
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
#ifdef HGE_INTENSIVE_DEBUG_MODE
	hge::ui::MainWindow::printGraphicAPIErrorAndTerminate();
#endif
}
void
hge::render::MeshUnit::draw()
{
#ifdef HGE_INTENSIVE_DEBUG_MODE
	hge::ui::MainWindow::printGraphicAPIErrorAndTerminate();
#endif
	glDrawElements(GL_TRIANGLES, numberOfIndices, GL_UNSIGNED_INT, 0);
#ifdef HGE_INTENSIVE_DEBUG_MODE
	hge::ui::MainWindow::printGraphicAPIErrorAndTerminate();
#endif
}
GLuint
hge::render::MeshUnit::getVBO()
{
	return vbo;
}
GLuint
hge::render::MeshUnit::getIBO()
{
	return ibo;
}
void hge::render::MeshUnit::setData(std::shared_ptr<utility::Stream> &stream, const bool &endianCompatible)
{
	core::Protocol::Types::VerticesElementsCountType verticesCount;
	stream->read((char *)(&verticesCount), sizeof verticesCount);
	if (!endianCompatible) swapObject((char *)(&verticesCount), sizeof verticesCount);
#ifdef HGE_TEST_MODE
	HGE_LOG_PRINT("Vertices count: %d", verticesCount);
#endif
	GLfloat *vertices = new GLfloat[verticesCount];
	stream->read((char *)(vertices), sizeof(GLfloat) * verticesCount);
	if (!endianCompatible)
	{
		for (core::Protocol::Types::VerticesElementsCountType i = 0; i < verticesCount; i++)
		{
			swapObject((char *)(&vertices[i]), sizeof(GLfloat));
		}
	}
#ifdef HGE_VERBOSE_TEST_MODE
	std::string str = "Vertices: ";
	for (core::Protocol::Types::VerticesElementsCountType i = 0; i < verticesCount; i++)
	{
		str += "v[" + std::to_string(i) + "]:" + std::to_string(vertices[i]) + "  ";
	}
	HGE_LOG_PRINT("%s", str.c_str());
#endif
	core::Protocol::Types::IndicesCountType indicesCount;
	stream->read((char *)(&indicesCount), sizeof indicesCount);
	if (!endianCompatible) swapObject((char *)(&indicesCount), sizeof indicesCount);
#ifdef HGE_TEST_MODE
	HGE_LOG_PRINT("Indices count: %d", indicesCount);
#endif
	GLuint *indices = new GLuint[indicesCount];
	stream->read((char *)(indices), sizeof(GLuint) * indicesCount);
	if (!endianCompatible)
	{
		for (core::Protocol::Types::IndicesCountType i = 0; i < indicesCount; i++)
		{
			swapObject((char *)(&indices[i]), sizeof(GLuint));
		}
	}
	if (vbo != 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &vbo);
	}
	if (ibo != 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &ibo);
	}
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, verticesCount * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount * sizeof(GLuint), indices, GL_STATIC_DRAW);
	numberOfIndices = indicesCount;
	delete[] vertices;
	delete[] indices;
}
