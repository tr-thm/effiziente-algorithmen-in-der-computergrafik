#version 330 core
layout (location = 0) in vec3 VertPosIn;

out vec3 TexCoord;

uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

void main()
{
    TexCoord = VertPosIn;
    gl_Position = ProjectionMatrix * ViewMatrix * vec4(VertPosIn, 1.0);
}
