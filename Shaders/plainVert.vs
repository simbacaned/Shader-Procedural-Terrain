
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;


uniform mat4 model;

out vec3 FragPos ;
out vec2 TexCoords;

void main()
{
    FragPos = (model * vec4(aPos, 1.0)).xyz;
    TexCoords = aTexCoords;  
}