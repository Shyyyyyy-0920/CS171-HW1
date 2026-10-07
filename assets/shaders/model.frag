#version 330 core
in vec3 color;
out vec4 aColor;
void main()
{
aColor=vec4(color,1);
}