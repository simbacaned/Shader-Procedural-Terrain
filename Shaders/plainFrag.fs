#version 330 core
out vec4 FragColor ;


in vec2 gTexCoords ;
in vec3 gFragPos ;
in vec3 gNormals;

void main()
{
    vec3 lightDirection = normalize(vec3(0.4,1.0,0.4));
    vec3 myColour = vec3(0.2,0.8,0.2);
    myColour *= vec3(dot(lightDirection, gNormals));
    FragColor = vec4(myColour,1.0) ;
}