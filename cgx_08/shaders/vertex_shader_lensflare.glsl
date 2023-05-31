#version 330 core
layout (location = 0) in vec3 VertPosIn;
layout (location = 1) in vec2 TexCoordIn;

out vec2 TexCoord;
out vec3 SunPosition;

uniform mat4 WorldMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform vec3 ViewportSize;
uniform float SunBrightness;

void main()
{
    mat4 WvpMatrix = ProjectionMatrix * ViewMatrix * WorldMatrix;
    vec4 sun = WvpMatrix * vec4(0.0, 0.0, 0.0, 1.0);
    SunPosition = sun.xyz / sun.w;
    SunPosition.z = sun.z;

    gl_Position = vec4(VertPosIn, 1.0);

    TexCoord = TexCoordIn;
}
