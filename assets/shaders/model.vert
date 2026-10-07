#version 330 core
layout(location=0)in vec3 p;
layout(location=1)in vec3 n;
out vec4 worldPosition;
out vec3 worldNormal;
uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
void main()
{
worldPosition=M*vec4(p,1.0);
vec4 clipPosition=P*V*worldPosition;
gl_Position=clipPosition;
mat3 m=mat3(M);
worldNormal=m*n;
}
