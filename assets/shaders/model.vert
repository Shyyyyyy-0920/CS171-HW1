#version 330 core
layout(location=0)in vec3 p;
layout(location=1)in vec3 n;
out vec4 worldPosition;
out vec3 worldNormal;
uniform mat4 mvp;
uniform mat4 M;
void main()
{
gl_Position=mvp*vec4(p,1.0);
worldPosition=gl_Position;
mat3 m=mat3(M);
worldNormal=m*n;
}
