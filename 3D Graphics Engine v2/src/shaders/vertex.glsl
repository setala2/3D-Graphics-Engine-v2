#version 430 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

out vec3 _color;

void main()
{
	_color = color;
	gl_Position = projectionMatrix * viewMatrix * vec4(position.xy, position.z-1.0f, 1.0f);
}