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

uniform samplerCube CubeMap;

void main()
{
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec3 albedo = pow(texture(Diffuse, TexCoord).rgb, vec3(2.2));
    float roughness = texture(Roughness, TexCoord).r;
    vec3 normal = normalize(texture(NormalMap, TexCoord).rgb * 2.0 - 1.0);

    float lightIntensity = max(dot(normal, -SunLightObjSpc), 0.0);

    vec3 ambient = 0.1 * lightColor * albedo;
    vec3 diffuse = 0.9 * lightIntensity * lightColor * albedo;

    vec3 viewDir = normalize(VertPos - CameraPosObjSpc);
    vec3 reflectDir = reflect(viewDir, normal);
    vec3 reflection = pow(texture(CubeMap, reflectDir).rgb, vec3(2.2)) * (1.0 - roughness);

    FragColor = vec4(ambient + diffuse + reflection, 1.0);

    //gamma correction
    FragColor = vec4(pow(FragColor.rgb, vec3(1.0/2.2)), FragColor.a);
}
