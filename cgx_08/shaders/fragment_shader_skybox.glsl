#version 330 core
out vec4 FragColor;

in vec3 TexCoord;

uniform samplerCube Skybox;

void main()
{
    FragColor = texture(Skybox, TexCoord);
    gl_FragDepth = 0.9999998;
}
