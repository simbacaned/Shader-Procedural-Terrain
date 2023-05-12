#version 330 core
layout(triangles) in ;
layout(triangle_strip, max_vertices = 3) out ;
vec3 getNormal() ;

in vec3 FragPosE[];
in vec2 TexCoordsE[] ;

out vec3 gFragPos ;
out vec2 gTexCoords;
out vec3 gNormals;
uniform mat4 view;
uniform mat4 projection;
void main()
{
   for(int i = 0 ; i < 3; i++){
      gFragPos = FragPosE[i];
	  gl_Position = gl_in[i].gl_Position;
      gTexCoords = TexCoordsE[i];
      gNormals =  getNormal();
      EmitVertex();
   }
     EndPrimitive() ; 
}

vec3 getNormal()
{
    vec3 a = vec3(FragPosE[1]) - vec3(FragPosE[0]);
    vec3 b = vec3(FragPosE[2]) - vec3(FragPosE[0]);
    return normalize(cross(a, b));
}

