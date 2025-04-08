#include "Renderer/Renderer.h"

MultiExtend::Renderer::Renderer()
{
}

MultiExtend::Renderer::~Renderer()
{
}

MultiExtend::RendererSDL::RendererSDL(SDL_Renderer* renderer):
	m_Renderer(renderer)
	{}

void* MultiExtend::RendererSDL::GetRenderer() const
{
	return m_Renderer;
}

MultiExtend::RendererOpenGL::RendererOpenGL(void* renderer):
	m_Renderer(renderer)
{
}

void* MultiExtend::RendererOpenGL::GetRenderer() const
{
	return m_Renderer;
}
