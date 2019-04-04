// A simple textured shader
#version 410

in vec2 vTexCoord;

uniform sampler2D DiffuseTexture;

out vec4 FragColour;

void main()
{
	FragColour = texture(diffuseTexture, vTexCoord);
}