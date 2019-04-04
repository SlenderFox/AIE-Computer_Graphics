// Classic Phone fragment shader
#version 410

in vec3 vNormal;

uniform vec3 Ia; // Ambient light colour

uniform vec3 Id; // Diffuse light colour
uniform vec3 Is; // Specular light colour
uniform vec3 LightDirection;

out vec4 FragColour;

void main()
{
	// Ensure normal and light direction are normalised
	vec3 N = normalize(vNormal);
	vec3 L = normalize(LightDirection);

	// Calculate lambert term (negate light direction)
	float lambertTerm = max(0, min(1, dot(N, -L)));

	// Calculate diffuse
	vec3 diffuse = Id * lambertTerm;

	// Output lambert as grayscale
	FragColour = vec4(diffuse, 1);
}