#version 330 core
layout (location = 0) in vec3 VertPosIn;
layout (location = 1) in vec2 TexCoordIn;

out vec2 TexCoord;

uniform mat4 WorldMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

void main()
{
    mat4 WvpMatrix = ProjectionMatrix * ViewMatrix * WorldMatrix;
    gl_Position = WvpMatrix * vec4(VertPosIn, 1.0);
    TexCoord = TexCoordIn;
}
