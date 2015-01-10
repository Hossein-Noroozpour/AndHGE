#include "hge-skybox-unit.hpp"
hge::render::SkyBoxUnit::SkyBoxUnit(const std::shared_ptr<MeshUnit> &mesh):
	mesh(mesh),
	modelMatrix(math::Matrix4D<>(100000000000000000000000000000.0f)),
	lastDrawn(std::chrono::system_clock::now())
{
}

void hge::render::SkyBoxUnit::setShader(const std::shared_ptr<shader::SkyBoxShaderUnit> &shader)
{
	this->shader = shader;
}

void hge::render::SkyBoxUnit::setTexture(const std::shared_ptr<texture::TextureUnit> &texture)
{
	this->texture = texture;
}

void hge::render::SkyBoxUnit::draw(const math::Matrix4D<> &vp)
{
	auto mvp = vp * modelMatrix;
	mesh->bindVBO();
	shader->use();
	texture->bind(GL_TEXTURE0);
	shader->setModelViewProjectionMatrix(mvp);
	mesh->bindIBO();
	auto now = std::chrono::system_clock::now();
	std::chrono::duration<float> deltaTime = lastDrawn - now;
	skyTextuePosition += (deltaTime.count() / 100.0f);
	if(skyTextuePosition > 1.0f) skyTextuePosition -= 1.0f;
	shader->setCloudsSpeed(skyTextuePosition);
	lastDrawn = now;
	mesh->draw();
}
