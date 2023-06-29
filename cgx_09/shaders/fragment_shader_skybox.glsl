#version 330 core
out vec4 FragColor;

in vec3 TexCoord;

uniform samplerCube CubeMap;

void main()
{
    FragColor = texture(CubeMap, TexCoord);
    gl_FragDepth = 0.9999998;
}
