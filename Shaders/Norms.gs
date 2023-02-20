#version 330 core
layout(triangles) in ;
layout(triangle_strip, max_vertices = 3) out ;
vec3 getNormal() ;

in vec3 FragPosE[];
in vec2 TexCoordsE[] ;


out vec3 gFragPos ;
out vec2 gTexCoords;
out vec3 normal;

void main()
{
  
   for(int i = 0 ; i < 3; i++){
      gFragPos = FragPosE[i] ;
	  gl_Position = gl_in[i].gl_Position ;
      gTexCoords = TexCoordsE[i];
      normal = cross(FragPosE[0], FragPosE[1]);
      EmitVertex();
   }
     EndPrimitive() ; 
}
