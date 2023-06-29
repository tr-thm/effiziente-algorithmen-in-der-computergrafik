#version 330 core
layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec2 TextureCoordinate;
layout (location = 2) in vec3 Normal;
layout (location = 3) in vec3 Tangent;

uniform mat4 WorldMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform vec3 SunLight;
uniform vec3 CameraPos;

out VS_OUT {
    vec3 FragmentPosition;
    vec2 TextureCoordinate;
    vec3 TangentLightDirection;
    vec3 TangentCameraPosition;
    vec3 TangentFragmentPosition;
    mat3 TBN;
} vs_out;

void main()
{
    vs_out.TextureCoordinate = TextureCoordinate;
    vs_out.FragmentPosition  = vec3(WorldMatrix * vec4(VertexPosition, 1.0));

    mat3 normalMatrix = transpose(inverse(mat3(WorldMatrix)));
    vec3 T = normalize(normalMatrix * Tangent);
    vec3 N = normalize(normalMatrix * Normal);
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);
    
    mat3 TBN = transpose(mat3(T, B, N));
    vs_out.TangentLightDirection = TBN * SunLight;
    vs_out.TangentCameraPosition  = TBN * CameraPos;
    vs_out.TangentFragmentPosition  = TBN * vs_out.FragmentPosition;
    vs_out.TBN = mat3(T, B, N);

    gl_Position = ProjectionMatrix * ViewMatrix * WorldMatrix * vec4(VertexPosition, 1.0);
}
