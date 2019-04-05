// A normal map fragment shader
#version 410

in vec2 vTexCoord;
in vec3 vNormal;
in vec3 vTangent;
in vec3 vBiTangent;
in vec4 vPosition;

out vec4 FragColour;

uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;
uniform sampler2D normalTexture;

uniform vec3 Ka; // Material ambient
uniform vec3 Kd; // Material diffuse
uniform vec3 Ks; // Material specular
uniform float specularPower;

uniform vec3 Ia; // Light ambient
uniform vec3 Id; // Light diffuse
uniform vec3 Is; // Light specular
uniform vec3 LightDirection;

uniform vec3 CameraPosition;

void main()
{
	vec3 N = normalize(vNormal);
	vec3 T = normalize(vTangent);
	vec3 B = normalize(vBiTangent);
	vec3 L = normalize(LightDirection);
	
	mat3 TBN = mat3(T,B,N);
	
	vec3 texDiffuse = texture(diffuseTexture, vTexCoord).rgb;
	vec3 texSpecular = texture(specularTexture, vTexCoord).rgb;
	vec3 texNormal = texture(normalTexture, vTexCoord).rgb;
	
	N = TBN * (texNormal * 2 - 1);
	
	// Calculate lambert term
	float lambertTerm = max(0, dot(N, -L));
	
	// Calculate view vector and reflection vector
	vec3 V = normalize(CameraPosition + vPosition.xyz);
	vec3 R = reflect(L, N);
	R *= lambertTerm + 0.1f;
	
	// Calculate specular term
	float specularTerm = pow(max(0, dot(R, V)), specularPower);
	
	// Calculate each light properly
	vec3 ambient = Ia * Ka;
	vec3 diffuse = Id * Kd * texDiffuse * lambertTerm;
	vec3 specular = Is * Ks * texSpecular * specularTerm;
	
	//FragColour = vec4(N, 1);
	FragColour = vec4(ambient + diffuse + specular, 1);
}