// Classic Phong vertex shader
#version 410

layout(location = 0) in vec4 Position;
layout(location = 1) in vec4 Normal;

out vec4 vPosition;
out vec3 vNormal;

uniform mat4 ProjectionViewModel;

// We need this matrix to transform the position
uniform mat4 ModelMatrix;

// We need this matrix to transform the model
uniform mat3 NormalMatrix;

void main()
{
	vPosition = ModelMatrix * Position;
	vNormal = NormalMatrix * Normal.xyz;
	gl_Position = ProjectionViewModel * Position;
}