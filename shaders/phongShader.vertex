#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec3 aColor;

out vec3 VertColor;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 MVP;
uniform mat4 Model;
uniform mat3 NormalModel;

void main()
{
   gl_Position = MVP * vec4(aPos, 1.0);
   VertColor = aColor;
   Normal = NormalModel * aNorm;
   FragPos = vec3(Model * vec4(aPos, 1.0f));
}