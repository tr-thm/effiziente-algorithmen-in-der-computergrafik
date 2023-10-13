#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 NormVect;
in vec3 VertPos;
in vec3 SunLightObjSpc;
in vec3 CameraPosObjSpc;

uniform sampler2D Diffuse;
uniform sampler2D Roughness;
uniform sampler2D NormalMap;

uniform samplerCube Skybox;

void main()
{
    //vec3 normal = normalize(NormVect);
    vec3 normal = normalize(texture(NormalMap, TexCoord).rgb * 2.0 - 1.0);

    vec3 viewDir = normalize(VertPos - CameraPosObjSpc);
    vec3 reflectDir = reflect(viewDir, normal);

    FragColor = vec4(texture(Skybox, reflectDir).rgb, 1.0);
}
