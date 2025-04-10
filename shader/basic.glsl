#Vertex
#version 330 core

uniform mat4 MVP;
in vec4 vColor;
in vec4 vPos;
out vec4 color;

void main()
{
	gl_Position = MVP * vPos;
	color = vColor;
}

#Fragment
#version 330 core

in vec4 color;
out vec4 fragment;
		
void main()
{
	fragment = color;
}