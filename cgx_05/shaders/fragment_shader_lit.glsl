#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 NormVect;
in vec3 VertPos;
in vec3 SunLightObjSpc;
in vec3 CameraPosObjSpc;

uniform sampler2D Diffuse;

void main()
{
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec3 albedo = vec3(texture(Diffuse, TexCoord));

    float lightIntensity = max(dot(NormVect, -SunLightObjSpc), 0.0);

    vec3 ambient = 0.1 * lightColor * albedo;
    vec3 diffuse = 0.9 * lightIntensity * lightColor * albedo;

    vec3 viewDir = normalize(VertPos - CameraPosObjSpc);
    vec3 reflectDir = reflect(-SunLightObjSpc, NormVect);
    vec3 specular = 0.5 * pow(max(dot(viewDir, reflectDir), 0.0), 16) * lightColor;

    FragColor = vec4(ambient + diffuse + specular, 1.0);
}
