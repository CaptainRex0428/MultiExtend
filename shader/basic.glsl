#Vertex
#version 330 core

uniform mat4 uMVP;
in vec4 vColor;
in vec4 vPos;
out vec4 color;

void main()
{
	gl_Position = uMVP * vPos;
	color = vColor;
}

#Fragment
#version 330 core

uniform float uTime;
in vec4 color;
out vec4 fragment;
		
void main()
{
	float pulse = abs(sin(uTime));
	fragment = color * vec4(pulse, pulse, pulse, 1.0);
}