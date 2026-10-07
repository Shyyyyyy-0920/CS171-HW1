#version 330 core
in vec4 worldPosition;
in vec3 worldNormal;
out vec4 aColor;
void main()
{
aColor=vec4(worldPosition,1.0);
}