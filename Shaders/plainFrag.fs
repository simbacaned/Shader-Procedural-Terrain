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
    if (gFragPos.y < -12)
    {
        float t = (gFragPos.y * -0.25) - 3;
        FragColor = mix(vec4(0.3, 0.3, 0.6, 1), vec4(0, 0, 0.8, 1), t);
    }
    
    else if (gFragPos.y < -8)
    {
        float t = (gFragPos.y * -0.25) - 2;
        FragColor = mix(vec4(0.3, 0.6, 0.3, 1), vec4(0.3, 0.3, 0.6, 1), t);
    }
    
    else if (gFragPos.y < -4)
    {
        float t = (gFragPos.y * -0.25) - 1;
        FragColor = mix(vec4(0.1, 0.6, 0.1, 1), vec4(0.3, 0.6, 0.3, 1), t);
    }

    else if (gFragPos.y < -0)
    {
        float t = (gFragPos.y * -0.25);
        FragColor = mix(vec4(0.3, 0.5, 0.3, 1), vec4(0.1, 0.6, 0.1, 1), t);
    }

    else if (gFragPos.y < 4)
    {
        float t = (gFragPos.y * -0.25) + 1;
        FragColor = mix(vec4(0.5, 0.5, 0.5, 1), vec4(0.3, 0.5, 0.3, 1), t);
    }

    else if (gFragPos.y < 8)
    {
        float t = (gFragPos.y * -0.25) + 2;
        FragColor = mix(vec4(0.6, 0.6, 0.6, 1), vec4(0.5, 0.5, 0.5, 1), t);
    }

    else if (gFragPos.y < 12)
    {
        float t = (gFragPos.y * -0.25) + 3;
        FragColor = mix(vec4(0.7, 0.7, 0.7, 1), vec4(0.6, 0.6, 0.6, 1), t);
    }

    else if (gFragPos.y < 13)
    {
        float t = (-gFragPos.y) + 13;
        FragColor = mix(vec4(0.95, 0.95, 0.95, 1), vec4(0.7, 0.7, 0.7, 1), t);
    }

    else
    {
        FragColor = vec4(0.95);
    }

    FragColor *= (dot(lightDirection, gNormals));
}