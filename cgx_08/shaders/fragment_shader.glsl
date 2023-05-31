#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D Diffuse;

void main()
{
    FragColor = texture(Diffuse, TexCoord);
}
