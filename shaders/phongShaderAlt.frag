#version 330 core
out vec4 FragColor;
in vec3 fragPos;
in vec3 Normal;

uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	vec3 objectColor = vec3(1.0f, 0.1f, 0.1f);
	vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
	
	vec3 ambientLight = 0.1 * lightColor;
	
	vec3 norm = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - fragPos);
	vec3 diffuseLight = max(dot(norm, lightDirection), 0.0) * lightColor;
	
	vec3 viewDirection = normalize(viewPos - fragPos);
	vec3 reflectDirection = reflect(-lightDirection, norm);
	vec3 specularLight = 7 * pow(max(dot(viewDirection, reflectDirection), 0.0), 64) * lightColor;
	
	vec3 result = (ambientLight + diffuseLight + specularLight) * objectColor;
	FragColor = vec4(result, 1.0f);
}
