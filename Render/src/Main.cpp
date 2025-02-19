
#include "org/template.h"
#include "Render.h"

int main(int argc, const char * argv[])
{
	/*static const Vertex vertices[3] =
	{
		{ { -0.6f, -0.4f }, { 1.f, 0.f, 0.f } },
		{ {  0.6f, -0.4f }, { 0.f, 1.f, 0.f } },
		{ {   0.f,  0.6f }, { 0.f, 0.f, 1.f } }
	};

	templateGL::draw(vertices, sizeof(vertices));*/

	render::Vertex renderVertices[3] = 
	{
		{{ -.6f, -.4f, 0.f, 1.f},{ 1.f, 0.f, 0.f, 1.f },{ 0.f, 0.f, 1.f, 1.f }},
		{{  .6f, -.4f, 0.f, 1.f},{ 0.f, 1.f, 0.f, 1.f },{ 0.f, 0.f, 1.f, 1.f }},
		{{  0.f,  .6f, 0.f, 1.f},{ 0.f, 0.f, 1.f, 1.f },{ 0.f, 0.f, 1.f, 1.f }}
	};

	render::Render(renderVertices, sizeof(renderVertices));
}