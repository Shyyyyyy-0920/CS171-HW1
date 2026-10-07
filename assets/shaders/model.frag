#version 330 core
in vec3 normal;
out vec4 anormal;
void main()
{
anormal=vec4(normal,1);
}