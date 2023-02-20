#version 330 core
out vec4 FragColor ;


in vec2 gTexCoords ;
in vec3 gFragPos ;
in vec3 normal;

void main()
{
    FragColor = vec4(0.2,0.8,0.2,1.0) ;
}