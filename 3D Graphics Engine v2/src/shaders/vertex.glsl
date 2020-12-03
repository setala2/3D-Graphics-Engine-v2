#version 430 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec3 color;

uniform mat4 projectionMatrix;

out vec3 _color;

void main()
{
	_color = color;
	gl_Position = projectionMatrix * vec4(position, -1.5f, 1.0f);
}