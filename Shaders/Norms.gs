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

// Compute the normal vector of a triangle using the Central Difference Method
vec3 computeTriangleNormal(vec3 v0, vec3 v1, vec3 v2)
{
    // Calculate the two edges of the triangle
    vec3 edge1 = v1 - v0;
    vec3 edge2 = v2 - v0;
    
    // Compute the cross product of the edges to get the unnormalized normal vector
    vec3 normal = cross(edge1, edge2);
    
    return normalize(normal); // Normalize the normal vector to ensure unit length
}

// Get the normal vector for a triangle using the vertex positions
vec3 getTriangleNormal()
{
    // Get the vertex positions of the triangle
    vec3 v0 = vec3(FragPosE[0]);
    vec3 v1 = vec3(FragPosE[1]);
    vec3 v2 = vec3(FragPosE[2]);
    
    // Compute the normal vector 
    return computeTriangleNormal(v0, v1, v2);
}

