#version 330 core
out vec4 FragColor;
in vec3 lightingColor;

void main()
{
	vec3 objectColor = vec3(1.0f, 0.1f, 0.1f);
	FragColor = vec4(lightingColor * objectColor, 1.0f);
}
