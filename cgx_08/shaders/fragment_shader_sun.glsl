#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D Diffuse;

void main()
{
    FragColor = vec4(1.0, 1.0, 0.0, 0.0);
    gl_FragDepth = 0.9999999;
}
