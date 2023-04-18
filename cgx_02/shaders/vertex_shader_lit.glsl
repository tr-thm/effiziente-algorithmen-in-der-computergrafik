#version 330 core
layout (location = 0) in vec3 VertPosIn;
layout (location = 1) in vec2 TexCoordIn;
layout (location = 2) in vec3 NormVectIn;

out vec2 TexCoord;
out vec3 NormVect;
out vec3 SunLightObjSpc;
out vec3 CameraPosObjSpc;
out vec3 VertPos;

uniform mat4 WorldMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform vec3 SunLight;
uniform vec3 CameraPos;

void main()
{
    mat4 WvpMatrix = ProjectionMatrix * ViewMatrix * WorldMatrix;
    gl_Position = WvpMatrix * vec4(VertPosIn, 1.0);
    TexCoord = TexCoordIn;
    NormVect = NormVectIn;
    SunLightObjSpc = normalize(vec3(inverse(WorldMatrix) * vec4(SunLight, 0.0)));
    CameraPosObjSpc = vec3(inverse(WorldMatrix) * vec4(CameraPos, 1.0));
    VertPos = VertPosIn;
}
