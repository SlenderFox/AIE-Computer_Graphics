// Classic Phone fragment shader
#version 410

in vec4 vPosition;
in vec3 vNormal;

uniform vec3 Ka; // Material ambient
uniform vec3 Kd; // Material diffuse
uniform vec3 Ks; // Material specular
uniform float specularPower;

uniform vec3 Ia; // Ambient light colour
uniform vec3 Id; // Diffuse light colour
uniform vec3 Is; // Specular light colour
uniform vec3 LightDirection;

uniform vec3 CameraPosition;

out vec4 FragColour;

void main()
{
	// Ensure normal and light direction are normalised
	vec3 N = normalize(vNormal);
	vec3 L = normalize(LightDirection);

	// Calculate lambert term (negate light direction)
	float lambertTerm = max(0, min(1, dot(N, -L)));

	// Calculate view vector and reflection vector
	vec3 V = normalize(CameraPosition - vPosition.xyz);
	vec3 R = reflect(L, N);
	R *= lambertTerm + 0.05f;

	// Calculate specular term
	float specularTerm = pow(max(0, dot(R, V)), specularPower);

	// Calculate each colour property
	vec3 ambient = Ia * Ka;
	vec3 diffuse = Id * Kd * lambertTerm;
	vec3 specular = Is * Ks * specularTerm;

	// Output lambert as grayscale
	FragColour = vec4(ambient + diffuse + specular, 1);
}